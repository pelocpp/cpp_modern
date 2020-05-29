# SFINAE and enable_if

[Quellcode 1](Sfinae01.cpp) und [Quellcode 2](Sfinae02.cpp)

---

## Einleitung

Es gibt ein interessantes Problem, das es bei der gleichzeitigen Verwendung von Funktionsüberladungen
mit Templates zu berücksichtigen gilt. Das Problem besteht darin, dass Templates in ihrem Gebrauch (Instanziierung)
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
Die Antwort lautet: Es ist die Funktions-Template Variante, die Ausgabe lautet folglich "`template 123`".
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

Um es nicht zu formal werden zu lassen: Wenn ein Substitutionsfehler wie der oben gezeigte auftritt, schlägt die "type deduction" für diesen Typ fehl -
was aber nicht einen Übersetzungsfehler nach sich zieht:
Der Compiler ignoriert diesen Kandidaten einfach und sieht sich die anderen Möglichkeiten an.

Im C ++ Sprachjargon bezeichnet man diese Regel als **SFINAE**: "**Substitution Failure Is Not An Error**".

Hierbei gilt es für den Programmierer aber Folgendes zu beachten - siehe dazu das nächste Beispiel:

```cpp
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
Wenn sich der ungültige Typ in die Übersetzungsphase *nach* der Auswahl der Überladungskandidaten schleicht,
also in den eigentlichen Rumpf der Übersetzungseinheit, wird das Programm nicht kompiliert:

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
template <typename T, typename enable_if<std::is_integral<T>::value, T>::type* = nullptr>
void doSomething(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, typename enable_if<std::is_class<T>::value, T>::type* = nullptr>
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

**Beachte**: Die Strukturen `enable_if` sind auch in der C++-Klassenbibliothek definiert (`inlude`-Datei `<type_traits>`),
Sie müssen diese also nicht selbst definieren.

Die beiden Templates `doSomething` sind in ihrer Definition etwas schwerfällig geraten. Mit der zusätzlichen
Schablone `enable_if_t` kann man diese etwas vereinfachen:

```cpp
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T, typename enable_if_t<std::is_integral<T>::value, T>* = nullptr>
void doSomething2(const T& t) {
    // an implementation for integral types (int, char, unsigned, etc.)
    std::cout << "doSomething integral type: " << t << std::endl;
}

template <typename T, typename enable_if_t<std::is_class<T>::value, T>* = nullptr>
void doSomething2(const T& t) {
    // an implementation for class types
    std::cout << "doSomething class type: " << t() << std::endl;
}
```

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[Eli Bendersky's website](https://eli.thegreenplace.net/2014/sfinae-and-enable_if/)<br>(abgerufen am 22.05.2020).

und

[Fernando García](https://medium.com/@mortificador/choose-between-different-implementations-depending-on-type-properties-at-compile-time-in-c-68e3fd5cd2f8)<br>(abgerufen am 22.05.2020).

Eine weitere Empfehlung:

[Jean Guegant](http://jguegant.github.io/blogs/tech/sfinae-introduction.html)<br>(abgerufen am 29.05.2020).

---

[Zurück](../../Readme.md)

---

