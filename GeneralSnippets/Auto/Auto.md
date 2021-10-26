# `auto`

[Zurück](../../Readme.md)

---

[Quellcode](Auto.cpp)

---

WEITER: Den Quellcode und den Text Korrekturlesen

WEITER: 3 Bilder im Markdwon integrieren

WEITER: auto als Snipper ergänzen

WEITER: auto im Inhaltsverzeichnis ergänzen

---


Das Schlüsselwort `auto` besitzt mehrere, völlig unterschiedliche Einsatzmöglichkeiten.

*Hinweis*: Das Schlüsselwort `auto` fällt in der C++&ndash;Sprachbeschreibung in die Kategorie der 
so genannten *Type Inference*. Hierzu zählen die beiden Schlüsselwörter `auto` und `decltype`.


TODO: Derselbe Satz auch bei `decltype` hinzu.


---

## Vereinbarung von Variablen / Automatic Type Deduction

Mit `auto` lassen sich Variablen definieren. Der Typ der Variablen leitet sich in diesem Fall
aus dem Vorbelegungswert der Variablen ab:

```cpp
auto n = 123;    // n is type of int
```

*Bemerkung*: Im letzten Beispiel hat man durch die Verwendung von `auto` nicht viel gewonnen.
Etwas anders ist die Situation im nächsten Beispiel:

```cpp
auto result = getFunction(); 
```

Hier gewinnt man zwei Vorteile:

  * Ist der Rückgabetyp von `getFunction` längerer Natur, dann spart man mit `auto` Tipparbeit
    (z.B. an Stelle von `std::map<int, std::string>`).
  * Ändert sich der Rückgabetyp von `getFunction`, so muss man den Quellcode an all den Stellen,
    an denen ein Aufruf von `getFunction` steht, nicht nachgezogen werden.

## Neuartige Möglichkeit in der Definition von Funktionen / Function Return Type Deduction

Ab C++ 14 ist es möglich, dass der Rückgabetyp einer Funktion vom Compiler automatisch bestimmt wird.
Zu diesem Zweck

  * verwendet man das Schlüsselwort `auto` als Rückgabetyp in der Funktionsdefinition
  * muss der Compiler auf Grund einer oder auch mehrerer `return`-Anweisungen eindeutig in der Lage sein,
    den Rückgabetyp zu ermitteln.

Man sagt auch, dass es sich hierbei um einen &ldquo;optionalen Rückgabetyp&rdquo; handelt.

*Beispiel*:

```cpp
auto sum(float f1, float f2)
{
    return f1 + f2;
}
```

*Anwendung*:

```cpp
auto result = sum(1.0, 2.0);  // float
```

Häufig kann man die Beobachtung machen, dass der Umstieg auf &ldquo;Function Return Type Deduction&rdquo;
(auch: &ldquo;Automatic Return Type Deduction&rdquo;) zu leichter lesbarem Quellcode führt:

*Beispiel*:

<pre>
class Contact
{
    std::string m_name;
    size_t m_number;

public:
    <b>auto</b> getName() const { return m_name; }
    <b>auto</b> getMobileNumber () const { return m_number; }
};
</pre>

Oder etwa an folgendem realen Beispiel:

```cpp
template <typename Type, typename ...Args>
auto make_unique(Args&&... args) // no return type
{
    return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}
```

**Beachte**:

Das &ldquo;Automatic Return Type Deduction&rdquo; zieht einen interessanten Anwendungsfall nach sich:
Es ist möglich, den Rückgabetyp einer Funktion lokal in dieser zu definieren und
den Aufruf dieser Funktion mit &ldquo;Automatic Return Type Deduction&rdquo; durchzuführen.
Hierzu das folgende Beispiel:

```cpp
auto make_planet()
{
    struct Planet { std::string name; int moons; bool rings; };

    return Planet{ "Saturn", 82, true };
}
```

Damit kann die Funktion `make_planet` wie folgt aufgerufen werden:

```cpp
// using automatic return type deduction
auto planet = make_planet();

std::cout 
    << planet.name << ' '
    << planet.moons << ' '
    << planet.rings << std::endl;

// using automatic return type deduction & structured binding
auto [name, num_moons, has_rings] = make_planet();

std::cout
    << name << ' '
    << num_moons << ' '
    << has_rings << std::endl;
```

Im letzten Code-Fragment finden Sie noch eine Kombination der &ldquo;Automatic Return Type Deduction&rdquo; und dem
&ldquo;Structured Binding&rdquo; vor!


## Funktionsdefinition mit *Trailing Return Type*

Unter dem Begriff &ldquo;*Trailing Return Type*&rdquo; versteht man die Möglichkeit,
den Rückgabetyp hinter der Parameterliste statt wie ursprünglich vor dem Funktionsnamen zu platzieren.
Die neue und alte Syntax sind zueinander kompatibel und können im Code durchaus gemeinsam verwendet werden.

*Beispiel*:

```cpp
// old, "classical" syntax
std::string toString(int value);

// new syntax with trailing return type
auto toString(int value) -> std::string;
```

Eine Funktionsdefinition mit *Trailing Return Type* bietet sich dann an,
wenn es Funktionen in der Schreibweise &ldquo;Function Return Type Deduction&rdquo; bei mehreren `return`-Anweisungen
zu Mehrdeutigkeiten kommt:

*Beispiel*:

```cpp
// error: "'double': all return expressions must deduce to the same type:
// previously it was 'char'"
auto foo(bool flag, char ch, double d)
{
    if (flag) {
        return ch;
    }
    else {
        return d;
    }
}
```

Eine übersetzungsfähige Version sieht so aus:

```cpp
auto foo(bool flag, char ch, double d) -> double
{
    if (flag) {
        return ch;
    }
    else {
        return d;
    }
}
```

## Verlust von `const` und `&` (Referenz) bei `auto`

Die automatische Typableitung mit `auto` hat einen Nebeneffekt:
Die zwei möglichen Qualifizierer `const` und `&` (Referenz)
gehen bei der Typableitung verloren.
Wir demonstrieren dies an einem Beispiel:

```cpp
const std::string message{ "This is an important message :)" };

const std::string& getMessage()
{
    return message;
}
```

Wenn wir die Funktion `getMessage` aufrufen und ihr Resultat in einer mit `auto`  deklarierten Variablen abspeichern,
verlieren wir sowohl `const` als auch die Referenz:

```cpp
auto msg = getMessage();   // msg has type 'std::string'
```

Die Variable `msg` hat den Typ `std::string` &ndash; und damit nicht den Typ `const std::string&`!

*Hinweis*:
Der Visual C++ Compiler weißt in einem Tooltip darauf hin:

BILD: >!!!!!

Man kann dies natürlich dadurch verhindern, dass man die Variable vom Typ `auto&` oder `const auto&` deklariert!

*Hinweis*:
Es würde eine *zweite* Möglichkeit geben, den Verlust von `const` bzw. von `&` auszugleichen.
Hierzu darf man nicht `auto` einsetzen, sondern muss mit `decltype` arbeiten:

```cpp
decltype(getMessage()) msg3 = getMessage();  // msg3 has type `const std::string&`
std::cout << "Message: " << msg3 << std::endl;
```

Ein letzter Schönheitsfehler verbleibt: Es kommt quasi zu einer Dopplung des Ausdrucks, in unserem Beispiel `getMessage()`.
Auch das beheben wir noch, siehe weiter unten den Abschnitt [XXX](decltype(auto)).

// TODO: Wie definiere ich einen lokalen Markdown Link !!!!

## Generische Lambda Ausdrücke

Das Feature der &ldquo;Automatic Type Deduction&rdquo; lässt sich auch bei Lambda-Funktionen anwenden,
und zwar sowohl beim Rückgabetyp als auch bei den Parametern der Lambda-Funktion.
Um &ldquo;Automatic Type Deduction&rdquo; für Parameter anwenden zu können, müssen diese als `auto` deklariert werden.
Auch hierzu ein Beispiel:

```cpp
std::vector<int> intValues { 44, 65, 22, 77, 2 };

// use generic lambda with a vector of integers
auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFifty);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

// use exactly the *same* generic lambda with a vector of doubles
auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFifty);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

*Ausgabe*:

```
Found a value: 65
Found a value: 75
```

**Bemerkung**:
Zwischen Funktionstemplates und generischen Lambda Ausdrücken kann man Gemeinsamkeiten erkennen.
Das letzte Beispiel hätte man auch mit einem Funktionstemplate realisieren können:

```cpp
template <typename T>
bool isGreaterThanFiftyEx (const T& n) 
{
    return n > 50;
};
```

Damit sehen die Aufrufe von `std::find_if` so aus:

```cpp
std::vector<int> intValues{ 44, 65, 22, 77, 2 };

// use template function with a vector of integers
auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFiftyEx<int>);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

// use exactly the *same* template function with another specialization with a vector of doubles
auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFiftyEx<double>);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

## Typableitung bei Template Parametern (Template Parameter Type Deduction)

Der Typ von Template Parametern wird vom Übersetzer an Hand der Argumente aufgelöst,
mit denen ein Funktionstemplate aufgerufen wird. Template Parameter, die sich aus den Argumenten nicht erschließen lassen,
müssen folglich explizit angegeben werden.

Wir betrachten ein Funktionstemplate mit drei Template Parametern:

TEMPALTE

Ein Aufruf mit allen drei Template Parametern sieht so aus:

```cpp
auto result = add<long, int , int>(10, 20);
```

Da sich, um bei diesem Beispiel zu bleiben, die Template Parameter für `T1` und `T2` aus den
Werten 10 und 20 ableiten lassen können,
kann man auch verkürzt schreiben:

```cpp
auto result = add<long>(10, 20);
```

Es ist logischerweise nur noch der Typ für den Rückgabetyp aufzuführen, da dieser von `T1` und `T2` abweichen kann.
Dies wiederum kann nur funktionieren, wenn diejenigen Template Parameter, die der Compiler automatisch ermitteln soll,
sich am Ende der Template Parameter Liste befinden.
Also eine Funktionstemplate Definition in der Gestalt

```cpp
template <typename T1, typename T2, typename RetType>
RetType add2(const T1& t1, const T2& t2)
{
    return t1 + t2;
}
```

besitzt diese Eigenschaft nicht.

*Hinweis*: Ist man auf der Suche nach einer Funktionstemplate Definition, die bei Bedarf ohne jegliche
Spezifikationen von Datentypen beim Aufruf auskommt, so kann man mit Default Werten für die Template Parameter arbeiten:

```cpp
template <typename RetType = long, typename T1, typename T2>
RetType add(const T1& t1, const T2& t2)
{
    return t1 + t2;
}
```

Jetzt ist ein Aufruf der Gestalt

```cpp
auto result = add(10, 20);
```

übersetzungsfähig.

## `decltype(auto)`

`decltype(auto)` wird genau benutzt wie `auto`, nur sind die Regeln zum Ableiten des Typ (*type deduction*)
unterschiedlich.

  * Bei `auto` gehen mögliche Qualifizierer wie `const` und `&` (Referenz) verloren.
  * Bei `decltype(auto)` gehen diese Qualifizierer **nicht** verloren.

Wir betrachten dazu ein Beispiel:

```cpp
decltype(auto) getFirstCharacter1(const std::string& s)
{
    return s[0];
}

decltype(auto) getFirstCharacter2(const std::string& s)
{
    return s[0];
}
```

Wenn wir diese beiden Funktionen aufrufen, erkennen wir den Unterschied:

```cpp
auto ch1 = getFirstCharacter1(std::string{ "ABC" });
decltype(auto) ch2 = getFirstCharacter2(std::string{ "ABC" });
```

Variable `ch1` ist vom Typ `char`, `ch2` hingegen vom Typ `const char&`,
siehe hierzu auch XX und XXXX:

BILD 

BILD

## Perfect Forwarding mit generischen Lambdas

Das Prinzip des &ldquo;prefekten Weiterleitens&rdquo; gibt es auch für generische Lambdas
Definiert man einen Parameter eines generischen Lambdas vom Typ `auto&&`, also als so genannte *Universal Reference*,
so lassen sich die Argumente beim Aufruf &ldquo;prefekt&rdquo; Weiterleiten:

```cpp
void foo(const std::string& s) {
    std::cout << "Signature: const&" << std::endl;
}

void foo(std::string&& s) {
    std::cout << "Signature: &&" << std::endl;
}

auto callingFoo = [](auto&& s) {
    std::cout << "Calling foo(): " << s;
    foo(std::forward<decltype(s)>(s));
};
```

Wir rufen die Lambda-Funktion mit zwei unterschiedlichen Argumenten auf. Studieren Sie die Ausgabe sorgfältig:

```cpp
const std::string str{ "Hello World with LValue" };
callingFoo(str);
callingFoo("Hello World with RValue");
```

*Ausgabe*:

```
Calling foo(): Hello World with LValueSignature: const&
Calling foo(): Hello World with RValueSignature: &&
```


## Automatic Type Deduction im Vergleich: `auto`, `auto&`, `const auto&`, `auto&&` und `decltype(auto)`

### `auto`

Steht für eine Kopie eines Elements.

### `auto&`

Steht für eine Referenz eines Elements mit der Intention, dieses zu ändern.

### `const auto&`

Steht für eine Referenz eines Elements mit der Intention, dieses **nicht** zu ändern.

### `auto&&`

Steht für eine *Universal Referenz* eines Elements im Kontext von generischen Code (Template, generisches Lambda).
`auto&&` bezeichnet man auch als *Vorwärtsreferenz*, dies bedeutet:

  * Wenn `auto&&` mit einem *LValue* initialisiert wird, verhält sich die Referenz wie eine *LValue* Referenz.
  * Wenn `auto&&` mit einem *RValue* initialisiert wird, verhält sich die Referenz wie eine *RValue* Referenz.

### `decltype(auto)`

`decltype(auto)` verhält sich im Prinzip wie `auto`, nur werden `const`, `volatile` und `&` beibehalten.

---

Zusammenfassend kann man sagen:

  * Verwende `auto`, wenn man zum Beispiel in einer *range-based loop* mit einer Kopie arbeiten möchte.
  * Verwende `auto&`, wenn man zum Beispiel in einer *range-based loop* die Elemente verändern möchte.
  * Verwende `auto&&`, wenn man zum Beispiel in einer *range-based loop* im Kontext von generischen Code die Elemente verändern möchte.
  * Verwende `const auto&`, wenn man zum Beispiel in einer *range-based loop* auf die Elemente nur mit lesendem Zugriff zugreifen möchte (auch im Kontext von generischen Code).

---

## Literaturhinweise:

Die Anregungen zu diesem Code-Snippet finden sich unter anderem unter

[Modern C++ Features](https://arne-mertz.de/2017/01/decltype-declval/)<br>(abgerufen am 23.05.2020).

https://blog.petrzemek.net/2016/08/17/auto-type-deduction-in-range-based-for-loops/


---

[Zurück](../../Readme.md)

---
