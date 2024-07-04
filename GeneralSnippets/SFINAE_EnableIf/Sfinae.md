# SFINAE and `std::enable_if`

[Zurück](../../Readme.md)

---

[Quellcode 1](Sfinae01.cpp) und [Quellcode 2](Sfinae02.cpp)

---

## Einleitung

Wir betrachten ein Problem, das bei der gleichzeitigen Verwendung von Funktionsüberladungen
mit Templates auftritt. Es besteht darin, dass Templates in ihrem Gebrauch (bei der Instanziierung)
normalerweise zu allgemein gehalten sind.
Wenn Templates mit Überladungen gemischt werden, kann das Ergebnis überraschend sein:

```cpp
void foo(unsigned i) {
    std::cout << "unsigned " << i << "\n";
}

template <typename T>
void foo(const T& t) {
    std::cout << "template " << t << "\n";
}
```

Welche der beiden Funktionen `foo` wird Ihrer Meinung nach beim Aufruf von `foo(123);` verwendet?

```cpp
foo(123);
```

Die Antwort lautet: Es ist die Funktionstemplate Variante, die Ausgabe lautet folglich "`template 123`".
Der Grund dafür ist, dass ganzzahlige Literale (wie zum Beispiel `123`) standardmäßig `signed` sind
(sie werden nur mit dem Suffix `U` vorzeichenlos). Wenn der Compiler die Überladungs-Kandidaten untersucht,
aus denen er für diesen Aufruf auswählen kann, stellt er fest, dass die erste Funktion eine Konvertierung benötigt,
während die zweite perfekt übereinstimmt, so dass diese ausgewählt wird.

## Prinzip der Substitution

Wenn der Compiler Überladungs-Kandidaten betrachtet, bei denen es sich um Templates handelt,
muss er tatsächlich die explizit angegebenen oder abgeleiteten Typen in die Template Argumente einsetzen.
Dies führt nicht immer zu sinnvollem Code, wie das folgende Beispiel zeigt.
Es ist zwar einerseits ein nicht so sehr praxisrelevantes Beispiel, dafür aber repräsentativ für viele generische Quellcodes,
die in Modern C ++ geschrieben werden:

```cpp
int negate(int i) {
    return -i;
}

template <typename T>
typename T::value_type negate(const T& t) {
    return -T(t);
}
```

Wir betrachten einen Aufruf `negate(123)`. Es kommt die erste Überladung zum Tragen, es
wird der Wert -123 zurückgegeben. Bei der Suche nach der besten Überladung müssen jedoch alle Kandidaten berücksichtigt werden.
Wenn der Compiler die Schablone `negate` analysiert, substituiert er den abgeleiteten Argumenttyp 
(*deduced argument type*) des Aufrufs (in diesem Fall `int`) in der Vorlage und erhält damit die folgende Deklaration:

```cpp
int::value_type negate(const int& t);
```

Dieser Code ist natürlich ungültig, da `int` keinen Member des Namens `value_type` hat.
Man könnte also die Frage stellen, ob der Compiler in diesem Fall eine Fehlermeldung ausgeben sollte?
Er tut es nicht, denn in diesem Fall wäre das Schreiben von generischem Code in C ++ noch schwieriger.
Tatsächlich enthält der C ++ - Standard für solche Fälle eine spezielle Klausel,
die genau erklärt, wie sich ein Compiler verhalten soll:

## SFINAE

Um es nicht zu formal werden zu lassen: Wenn ein Substitutionsfehler wie der oben gezeigte auftritt, schlägt die "*type deduction*" für diesen Typ fehl -
was aber **nicht** einen Übersetzungsfehler nach sich zieht:
Der Compiler ignoriert diesen Kandidaten einfach und sieht sich die anderen Möglichkeiten an.

Im C ++ Sprachjargon bezeichnet man diese Regel als **SFINAE**: "**Substitution Failure Is Not An Error**".

Hierbei gilt es für den Programmierer aber Folgendes zu beachten - siehe dazu das nächste Beispiel:

```cpp
// not interested in returning a value, just want to negate a number
template <typename T>
void negate(const T& t) {
  typename T::value_type n = -t();
}
```

Wenn die "*Type Deduction*" für eine bestimmte Überladung einen "Treffer" vermeldet,
wird aufgrund des vorliegenden Ausdrucks `T::value_type` im Rumpf der Funktion tatsächlich ein Kompilierungsfehler angezeigt!
Die Moral von der Geschichte ist: Wenn wir ein Template schreiben wollen, das nur für einige Typen sinnvoll ist,
dann müssen wir dafür Sorge tragen, dass der Mechanismus der "*Type Deduction*" bereits in der *Deklaration*
für ungültige Typen fehlschlägt, um auf diese Weise einen Substitutionsfehler zu verursachen.
Wenn sich der ungültige Typ in die Übersetzungsphase *nach* der Auswahl der Überladungskandidaten einschleicht,
also in den eigentlichen Rumpf der Übersetzungseinheit, wird die Übersetzung des Programms auf Grund eines 
Syntaxfehlers abgebrochen:

```cpp
negate(123);
```

resultiert in einem Übersetzungsfehler der Art *"'T': must be a class or namespace when followed by '::'"** bzw. *"'T': left of '::' must be a class/struct/union"*.
Wie lassen sich derartige Übersetzungsfehler vermeiden?

## `enable_if` - Ein Schalter für Templates zur Übersetzungszeit

Der Trick in der Vermeidung derartiger Übersetzungsfehler liegt in der Definition von Templates 
des folgenden Aussehens:

```cpp
template <bool, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};
```

Damit lassen sich nun Funktionen (genauer gesagt: Funktionsschablonen) in der folgenden Art und Weise definieren:

```cpp
template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* U = nullptr>
void doSomething(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, typename enable_if<std::is_class<T>::value, T>::type* U = nullptr>
void doSomething(const T& t) {
    // an implementation for class types
    std::cout << "doSomething class type: " << t() << std::endl;
}
```

Lassen Sie uns SFINAE bei der Arbeit betrachten:
Wenn wir den Aufruf `doSomething (<int var>)` absetzen wollen,
wählt der Compiler die erste Überladung aus: Da die Bedingung `std::is_integral<int>` mit `true` evaluiert,
wird die Spezialisierung von `struct enable_if` für `true` verwendet,
der Strukturmember `type` ist in Folge dessen definiert und der interne Typ (*type deduction*) wird auf `int` gesetzt.
Die zweite Überladung wird weggelassen, da ohne die `true`-Spezialisierung (`std::is_class<int>` ist `false`) 
die allgemeine Form von `struct enable_if` ausgewählt wird, diese keinen Member `type` hat, 
sodass der Typ des Arguments zu einem Substitutionsfehler führt:

*Beispiel*:

```cpp
class SomeClass {
public:
    std::string operator()() const {
        return "SomeClass object";
    }
};

void test_04() {
    doSomething(123);
    doSomething(SomeClass{});
}
```

*Ausgabe*:

```cpp
doSomething integral type: 123
doSomething class type: SomeClass object
```

*Hinweis*:
In den Funktionsschablonen von `doSomething` werden zwei Template Parameter `T` und `U` definiert, zum Beispiel:

```cpp
template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* U = nullptr>
```

Da der zweite Template Parameter `U` nirgends explizit verwendet wird, kann man den Bezeichner `U` auch einfach weglassen.
Die folgende Zeile ist damit ebenso korrekt übersetzungsfähig:
 
```cpp
template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* = nullptr>
```

**Beachte**: Die Strukturen `enable_if` sind auch in der C++-Klassenbibliothek definiert (`#include`-Datei `<type_traits>`),
Sie müssen diese also nicht selbst definieren.

Die beiden Templates `doSomething` sind in ihrer Definition etwas schwerfällig geraten. Mit der zusätzlichen
Schablone `enable_if_t` kann man diese etwas vereinfachen:

```cpp
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T, enable_if_t<std::is_integral<T>::value, T>* U = nullptr>
void doSomething2(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, enable_if_t<std::is_class<T>::value, T>* U = nullptr>
void doSomething2(const T& t) {
    // an implementation for class types
    std::cout << "doSomething class type: " << t() << std::endl;
}
```

## Platzierungsmöglichkeiten von `std::enable_if`

Syntaktisch gesehen gibt es für die Anwendung des **SFINAE** Patterns &ndash; und damit für die Platzierung von `std::enable_if` &ndash; drei Möglichkeiten:

  * Im Kopf des Templates in der Definition eines zusätzlichen Template Parameters mit Default-Wert,
  * in der Liste der Funktionsparameter mit einem zusätzlichen Parameter mit Default-Wert oder
  * in der Definition des Rückgabetyps der Funktion

Wir betrachten die drei Möglichkeiten jeweils an einem Beispiel:

```cpp
template<typename T, typename U = std::enable_if_t<std::is_integral_v<T>>>
void negate1(T& value)
{
    value = -value;
}

template<typename T>
void negate2(T& value, std::enable_if_t<std::is_integral_v<T>>* dummy = nullptr)
{
    value = -value;
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>>
negate3(T& value)
{
    value = -value;
}

template<typename T>
auto negate4(T& value) -> std::enable_if_t<std::is_integral_v<T>>
{
    value = -value;
}
```

*Hinweis*: Für die Variante &bdquo;*In der Definition des Rückgabetyps*&rdquo; habe ich das Beispiel zweimal formuliert:
Zum einen mit einem regulären Rückgabetyp und zum zweiten mit `auto` und einem nachgestellten Rückgabetyp.

Um es ausdrücklich zu betonen: Für die reine Arbeitsweise der Funktion `negate` bräuchte man in den ersten beiden Varianten
den zusätzlichen Parameter (Template bzw. Funktionsparameter) *nicht*. Man könnte deshalb die in den Beispielen
benutzten Parameterbezeichner (hier: `U` bzw. `dummy`) auch einfach weglassen. Der Compiler akzeptiert dies:

```cpp
template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
...

template<typename T>
void negate2(T& value, std::enable_if_t<std::is_integral_v<T>>* = nullptr)
...
```

*Hinweis*: In den Beispielen zur `negate`-Funktion wurden die Schablonen `std::enable_if_t` und `std::is_integral_v` eingesetzt.
Beide Schablonen ermöglichen es dem Programmierer mit weniger Schreibarbeit auszukommen,
dafür erschweren sie &ndash; zumindest auf den ersten Blick &ndash; das Verständnis,
da sie den Blick auf die &bdquo;*versteckten*&rdquo; Alias-Definitionen verbergen:
Die &bdquo;*Langschreibweise*&rdquo; dieser Beispiele (mit den Schablonen `std::enable_if` und `std::is_integral`)
würde so aussehen:

```cpp
template<typename T, typename U = typename std::enable_if<std::is_integral<T>::value>::type>
void negate10(T& value)
{
    value = -value;
}

template<typename T>
void negate11(T& value, typename std::enable_if<std::is_integral<T>::value>::type* dummy = nullptr)
{
    value = -value;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
negate12(T& value)
{
    value = -value;
}

template<typename T>
auto negate13(T& value) -> typename std::enable_if<std::is_integral<T>::value>::type
{
    value = -value;
}
```

## Literaturhinweise

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[Eli Bendersky's website](https://eli.thegreenplace.net/2014/sfinae-and-enable_if/)<br>(abgerufen am 22.05.2020).

und

[Fernando García](https://medium.com/@mortificador/choose-between-different-implementations-depending-on-type-properties-at-compile-time-in-c-68e3fd5cd2f8)<br>(abgerufen am 22.05.2020).

Eine weitere Empfehlung:

[Jean Guegant](http://jguegant.github.io/blogs/tech/sfinae-introduction.html)<br>(abgerufen am 29.05.2020).

---

[Zurück](../../Readme.md)

---

