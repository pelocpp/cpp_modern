# Konzepte (*Concepts*) und Einschränkungen (*Requirements*) für Funktionen

[Zurück](../../Readme.md)

---

[Quellcode](ConceptsRequiresFunctions.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Variante 1: `requires`-Klausel zwischen der Template-Parameterliste und dem Rückgabetyp der Funktion](#link2)
  * [Variante 2: Nachgestellte `requires`-Klausel](#link3)
  * [Variante 3: Template-Parameter mit Einschränkungen (&bdquo;Constraints&rdquo;)](#link4)
  * [Variante 4: Abgekürzte Funktionstemplates (&bdquo;Abbreviated Function Templates&rdquo;)](#link5)
  * [`requires`-Klauseln mit benutzerdefinierten Einschränkungen](#link6)
  * [Literaturhinweise](#link7)

---

## Allgemeines <a name="link1"></a>

Templates eignen sich sehr gut zum Schreiben von Code,
der mit unterschiedlichen Datentypen funktioniert.

Mit dem Konzept von &bdquo;C++ Concepts&rdquo; wiederum
können die Parameter für Templates durch boolesche Prädikate validiert werden.

Auf diese Weise kann man erreichen, dass Funktionstemplates nur für
sinnvolle Template Parameter instanziiert werden.

---

## Variante 1: `requires`-Klausel zwischen der Template-Parameterliste und dem Rückgabetyp der Funktion <a name="link2"></a>

Bei der ersten der vier vorgestellten Möglichkeiten verwenden wir die
`requires`-Klausel zwischen der Template-Parameterliste und dem Rückgabetyp der Funktion.

Der Rückgabetyp der Funktion kann dann `auto` oder einer der Template Parameter sein.

*Beispiel*:

```cpp
01: template <typename T>
02: concept Numerical = std::integral<T> || std::floating_point<T>;
03: 
04: template <typename T>
05:     requires Numerical<T>
06: auto add(T a, T b)
07: {
08:     return a + b;
09: }
```

Natürlich kann ein Funktionstemplate mehrere Template Parameter haben.
Im nachfolgenden Beispiel lassen sich Werte unterschiedlichen Typs addieren:

```cpp
template <typename T, typename U>
    requires Numerical<T> && Numerical<U>
auto add(T a, U b)
{
    return a + b;
}
```

Das Schlüsselwort `requires` ist neu ab C++ 20.
Es wendet Einschränkungen (*Constraints*) auf ein Template
bzw. auf die Parameter eines Templates an.
`Numerical` ist der Name eines Konzepts, das nur Integer- und Gleitkommatypen akzeptiert.

Versucht man, derartige Templates mit unzulässigen Datentyp Parametern zu übersetzen,
erhält man verständliche Übersetzungsfehler:

```
The concept 'Numerical<std::string>' evaluated to false	
The associated constraints are not satisfied
```

Man kann die Requirements der Template Parameter auch in einer Art 
&bdquo;inline&rdquo;&ndash;Notation formulieren. In diesem Fall entfällt die separate
`concept`-Definition:

```cpp
01: template <typename T>
02:     requires std::integral<T> || std::floating_point<T>
03: auto add(T a, T b)
04: {
05:     return a + b;
06: }
```

*Zur Nomenklatur*:

Der C++&ndash;Standard verwendet die Begriffe *Konjunktion*, *Disjunktion* und *atomar*,
um Arten von Ausdrücken zu beschreiben, die zum Erstellen einer `requires`-Klausel / eines Konzepts
verwendet werden können:

  * Eine Einschränkungs-Konjunktion (*constraint conjunction*) wird gebildet,
  indem der `&&`-Operator auf zwei Einschränkungen angewendet wird.

  * Eine Einschränkungs-Disjunktion (*constraint disjunction*) wird gebildet,
  indem der `||`-Operator auf zwei Einschränkungen angewendet wird.

  * Eine atomare Einschränkung bezeichnet einen Ausdruck, der einen boolschen Typ zurückgibt und
  nicht weiter zerlegt werden kann.

  * Der logische *Not*-Operator (`!`) wird verwendet, um den negierten Wert einer Einschränkung zu erhalten.


---

## Variante 2: Nachgestellte `requires`-Klausel <a name="link3"></a>

Das Schlüsselwort `requires` tritt in dieser Variante in der Funktionssignatur
in Erscheinung:

*Beispiel*:

```cpp
01: template <typename T>
02: auto add(T a, T b) requires Numerical<T>
03: {
04:     return a + b;  
05: }
```

Wir erhalten das gleiche Ergebnis wie bei der `requires`-Klausel zuvor,
wir haben die Klausel nur mit einer anderen Syntax geschrieben.

In dieser Definition können wir wieder nicht zwei Zahlen unterschiedlichen Typs addieren.
Wir müssten die Template Definition ähnlich wie zuvor ändern:

```cpp
01: template <typename T, typename U>
02: auto add(T a, U b) requires Numerical<T> && Numerical<U>
03: {
04:     return a + b;
05: }
```

---

## Variante 3: Template-Parameter mit Einschränkungen (&bdquo;Constraints&rdquo;) <a name="link4"></a>

Die dritte Art, ein Konzept zu verwenden,
ist in der Schreibweise etwas knapper als die vorherigen.
Der Bezeichner des Konzepts wird in der Template Deklaration verwendet:

*Beispiel*:

```cpp
01: template <Numerical T>
02: auto add(T a, T b)
03: {
04:     return a + b;
05: }
```

In dieser Schreibweise kann man erkennen, das es keine `requires`-Klausel mehr gibt.
Der Template Parameter &ndash; in der Regel `T` &ndash; wird anstelle mit 
dem Schlüsselwort `typename` jetzt mit einem Bezeichner für ein Konzept (hier: `Numerical`) definiert.
Wir erzielen das gleiche Ergebnis wie mit den beiden vorherigen Varianten.

Die dritte Variante besitzt einige Einschränkungen.

Wenn man die `requires`-Klausel wie in der Art von Variante 1 oder 2 verwenden wollte,
könnte man einen Ausdruck wie z.B.

```cpp
requires std::integral<T> || std::floating_point<T>
```

schreiben. In der dritten Variante geht das nicht.

---

## Variante 4: Abgekürzte Funktionstemplates (&bdquo;Abbreviated Function Templates&rdquo;) <a name="link5"></a>

Für all diejenigen, die es kurz lieben, gibt es die so genannte &bdquo;*Abbreviated Function Templates*&rdquo;
Schreibweise:

```cpp
01: auto add(Numerical auto a, Numerical auto b)
02: {
03:     return a + b;
04: }
```

Wenn Sie sich für die &bdquo;Abbreviated Function Templates&rdquo; Schreibweise entscheiden,
können Sie sowohl auf Template Parameter als auch auf `requires`-Klauseln verzichten.

Sie können `concept`-Bezeichner direkt dort verwenden,
wo die Funktionsargumente aufgelistet sind.

*Beachte*:

Der `concept`-Bezeichner wird in dieser Variante ohne Template Parameter verwendet! 

---

## `requires`-Klauseln mit benutzerdefinierten Einschränkungen <a name="link6"></a>

Zum Schreiben einer `requires`-Klausel lassen sich die vordefinierten
Merkmale (&bdquo;*Traits*&rdquo;) aus dem Header `<type_traits>` verwenden.

Man kann aber auch seine eigenen Merkmale definieren.
Diese müssen dann den Typ `constexpr bool` zurückgeben.

*Beispiel*:

```cpp
template<typename T>
constexpr bool isGreaterThanWord{ sizeof(T) > 2 };
```

Damit ließe sich dann ein Konzept so definieren:

```cpp
// using <type_traits>
template <typename T>
concept GreatIntegral = std::is_integral<T>::value && isGreaterThanWord<T>;
```

Eine mögliche Anwendung könnte dann so aussehen:

```cpp
template<GreatIntegral T>
T incrementByOne(const T& arg) {
    return arg + 1;
}
```

---

## Literaturhinweise <a name="link7"></a>

Ideen und Anregungen zu den Beispielen aus diesem Abschnitt stammen aus

[4 ways to use C++ Concepts in Functions](https://www.sandordargo.com/blog/2021/02/17/cpp-concepts-4-ways-to-use-them) (abgerufen am 09.04.2023).

von Sandor Dargo.

---

[Zurück](../../Readme.md)

---

