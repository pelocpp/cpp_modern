# `decltype` und `std::declval`

[Zurück](../../Readme.md)

---

[Quellcode](decltype.cpp)

---

## `decltype`

*Hinweis*: Das Schlüsselwort `decltype` fällt in der C++&ndash;Sprachbeschreibung in die Kategorie der 
so genannten *Type Inference*. Hierzu zählen die beiden Schlüsselwörter `auto` und `decltype`.

Der in C ++ 11 eingeführte `decltype`-Operator gibt, grob gesagt, den Typ eines Ausdrucks oder einer Entität wieder.
Es ist nicht von der Hand zu weisen, dass der `decltype`-Operator Gemeinsamkeiten mit dem
`typeof`-Operator hat. Vermutlich auf Grund vorhandener, inkompatibler Erweiterungen
dieses Namens in vielen Compilern wurde stattdessen `decltype` gewählt.

`decltype` gibt einen Typ zurück. Der Operator kann grundsätzlich überall dort eingesetzt werden, wo ein Typ benötigt wird:

```cpp
// decltype may modify type deduction, e.g. in generic lambdas
// (decltype (t + u), decltype (t) or decltype (u) are valid)
template <typename T, typename U>
auto add(const T& t, const U& u) -> decltype (t + u) 
{ 
    return t + u;
}
```

In diesem Beispiel wird `decltype` zusammen mit dem so genannten *trailing return type*, zu deutsch etwa
*nachgereichter Rückgabetyp* demonstriert.

Weitere Beispiele:

```cpp
// demonstrating decltype with entities / instances of types:
std::vector<int> vec;

// decltype(vec) yields std::vector<int>,
// so the next line is equivalent to 'std::vector<int> v2;':
decltype(vec) vec2;

// foo returns the type of f, in this case float,
// so this is equivalent to 'float foo(int b);':
float f;
auto foo(int b) -> decltype(f);
```

und `decltype` mit Ausdrücken:

```cpp
// decltype(foo()) yields the type of whatever foo() returns,
// in this case, float:
float foo();
decltype(foo()) b;

//decltype yields void, so this is the same as void bar();
std::vector<int> vec;
auto bar() -> decltype(vec.push_back(int{})); 
```

## `std::declval`

In manchen Situationen stehen Objekte nicht zur Verfügung,
die wir an einen Ausdruck übergeben wollen, um diesen mit `decltype` auszuwerten.
Möglicherweise lassen sich derartige Objekte überhaupt nicht erstellen,
z.B. weil ihre Klassen nur private oder geschützte Konstruktoren haben.

Betrachten wir das Beispiel einer Funktion `f`. `decltype(f(11))` besagt 
"Welchen Typ bekomme ich, wenn ich `f` mit `11` aufrufe?".
Was wir eigentlich meinen, ist "Welchen Typ bekomme ich, wenn ich `f` mit einem `int` aufrufe?".
Im Fall von `int` könnten wir ein standardmäßig initialisiertes `int` verwenden.
Der Standardkonstruktor ist jedoch nicht immer verfügbar.

Für solche Fälle ist `std::declval` konzipiert.
Es handelt sich um eine Funktionsschabone, die eine *r*-Value-Referenz auf alles zurückgibt,
was an sie übergeben wird. 
Auf diese Weise müssen wir nicht eine Funktion künstlich deklarieren,
um etwas zu haben, das wir im `decltype`-Argument verwenden können:

```cpp
double f(int);
float f(int, int);
using some_type1 = decltype(f(std::declval<int>()));
using some_type2 = decltype(f(std::declval<int>(), std::declval<int>()));
```

In diesem Fall entspricht `some_type1` dem Datentyp `double` und `some_type2` `float`.
Dies ist besonders praktisch,
wenn man sich in einem Template-Kontext befindet und der Wert, den man erhalten möchte,
von einem Template-Parameter abhängt. Siehe zum Beispiel:

```cpp
template<typename T, typename U>
using sum_t = decltype(std::declval<T>() + std::declval<U>());
```

Dies ist zu lesen in der Form: "`sum_t` ist der Typ, den ich bekomme, wenn ich zu *einem U* *ein T* hinzufüge."

*Beachte*:

Eine kürzere `using`-Anweisung der Gestalt

```cpp
template<typename T, typename U>
using sum_t = decltype(T + U);
```

ist nicht übersetzungsfähig! Zwei Typen lassen sich nicht "addieren"!

## Literaturhinweise:

Die Anregungen zu diesem Code-Snippet finden sich unter anderem unter

[Modern C++ Features](https://arne-mertz.de/2017/01/decltype-declval/)<br>(abgerufen am 23.05.2020).

---

[Zurück](../../Readme.md)

---
