# Metaprogrammierung und Listenverarbeitung

[Zur�ck](../../Readme.md)

---

[Teil I: Einf�hrung in die Metaprogrammierung](Metaprogramming01.md)

---

## Listenverarbeitung

Dieser Beitrag zeigt, wie sich eine einfach verkettete Datenstruktur (*Linked List*) zur �bersetzungsszeit in C ++ realisieren l�sst.
H�ufige Operationen wie das Erstellen einer Liste, zus�tzliche Elemente einf�gen, L�nge einer Liste berechnen etc. werden betrachtet.

## Einstieg

Zun�chst m�ssen wir uns �berlegen, wie wir eine Liste erstellen wollen, wenn wir - in der Metaprogrammierung - nur Typen und keine Werte haben.
Dies bedeutet, dass eine Liste wie `"int, char, double, Foo"` und nicht wie `"1, 2, 3"` aussieht.
Es gibt eine M�glichkeit, den Compiler dazu zu bringen, einen Typ aus einem ganzzahligen Wert zu erstellen:

```cpp
template <int N>
struct Int {
    static constexpr int value = N;
};
```

Voil�! Damit k�nnen wir eine Liste mit ganzen Zahlen erstellen. Bevor wir nun auf die Darstellung einer verketteten Liste
durch Templates eingehen, betrachten wir eine programmiersprachenunabh�ngige Definition einer solchen Liste:

// Eine Liste ist ein Tupel `T` mit zwei Werten<br/>
`List: [ ..., ... ]`
 
// wobei das erste Element, `Head` genannt, das erste Element der Liste ist ...<br/>
`List: [ Head, ... ]`
 
// ... und das zweite Element, `Tail` genannt, ...<br/>
`List: [ Head, Tail]`
 
// ... entweder eine Liste oder das `NULL`-Element (auch als `Nil` bezeichnet) ist:<br/>
`List: [ Head, Tail]`
`Tail: List | Nil`

*Beispiel*:

```cpp
List(1, List(2, List(3, NIL )))
```

Mit diesen Vor�berlegungen k�nnen wir die Definition einer Liste in C++ angehen:

```cpp
struct Nil {
    using Head = Nil;
    using Tail = Nil;
};

template <typename H, typename T = Nil>
struct List {
    using Head = H;
    using Tail = T;
};
```

*Test*:

```cpp
// List(1, List(2, List(3, Nil)))
using OneTwoThree = List<Int<1>, List<Int<2>, List<Int<3>>>>;
```

Noch k�nnen wir mit dieser Liste nicht viel anfangen, wir gehen nun auf einzelne Listenoperationen n�her ein:

## L�nge einer Liste

Bei der Bestimmung der L�nge einer Liste denkt man unwillk�rlich an den Gebrauch der `for`-Wiederholungsanweisung.
Nicht vergessen: In der Metaprogrammierung haben wir keine `for`-Schleife, die Verwendung von Rekursion ist
der einzig gangbare Weg. Es wird einfacher, wenn wir noch einmal �ber unsere Definition der Liste nachdenken:
�Eine Liste ist ein Tupel mit zwei Elementen, das erste (`Head` genannt) ist das erste Element der Liste
und das zweite Element (`Tail` genannt) ist eine weitere Liste oder das `Nil`-Objekt�. 
Mit dieser Definition ist ihre L�nge 1 (`Head`) + L�nge der verbleibenden Liste (`Tail`),
mit dem Sonderfall der L�nge des `Nil`-Objekts, die immer 0 sein sollte. Damit in "Template"-Sprechweise:

```cpp
template <typename LIST>
struct LengthVerbose {
    using Tail = typename LIST::Tail;
    static constexpr unsigned int tailLength = LengthVerbose<Tail>::result;
    static constexpr unsigned int result = 1 + tailLength;
};

template <>
struct LengthVerbose<Nil> {
    static constexpr unsigned int result = 0;
};

// oder 

template <typename LIST>
struct Length {
    static constexpr unsigned int result = 1 + Length<typename LIST::Tail>::result;
};

template <>
struct Length<Nil> {
    static constexpr unsigned int result = 0;
};
```

Wie immer kommen dieselben Features der Metaprogrammierung zum Tragen:

  * `typename` wird ben�tigt, um dem Compiler mitzuteilen, dass `LIST::Tail` ein Typ und keine statische Variable ist.
  * Die Templates sind wieder rekursiv definiert.
  * Das Ende der Rekursion ist durch eine partielle Template Spezialisierung gegeben.

## Zugriff auf das *n*.-te Listenelement

Wir betrachten den Zugriff auf das *n*.-te Listenelement zun�chst in Pseudocode-Notation:

```cpp
Nth(0, lst) <- lst.Head
Nth(n, lst) <- Nth(n-1, lst.Tail)
```

Diese Notation setzen wir unmittelbar in C++ um:

```cpp
template <typename LIST, int N>
struct Nth {
    using Tail = typename LIST::Tail;
    using result = typename Nth<Tail, N - 1>::result;
};

template <typename LIST>
struct Nth<LIST, 0> {
    using result = typename LIST::Head;
};
```

*Test*:

```cpp
using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
std::cout << Nth<List12345, 3>::result::result << std::endl;
```

*Hinweis*:
Man beachte das zweifache Anwenden von result auf die Schabloneninstanz! 
Bei Verwendung der zuvor definierten `Int`-Klasse ergibt "`Nth::result`" den Datentyp "`Int`",
darauf l�sst sich "`cout << Int << endl;`" nicht anwenden!
Man ben�tigt deshalb ein zweites "`::result`".

*Ausgabe*:

```cpp
4
```

*Hinweis*:

Da alle Anweisungen zur �bersetzungszeit �bersetzt - und damit auch auf Sinnhaftigkeit �berpr�ft werden -,
lassen sich Instanziierungen der `Nth`-Schablone mit falschen Argumenten nicht �bersetzen:

```cpp
using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
std::cout << Nth<List12345, 99>::result::result << std::endl;
```

wird von meinem �bersetzer (Visual C++) mit der Fehlermeldung *"'result': is not a member of 'Metaprogramming::Nil'"* abgewiesen!

## Funktionalit�t `Contains`

Wir beginnen wieder mit den �berlegungen zum Pseudo-Code:

```cpp
Contains(lst.head, lst) <- true
Contains(e, NIL) <- false
Contains(e, lst) <- Includes(e, lst.tail)
```

Ein erster - unvollst�ndiger - Ansatz in C++ k�nnte so aussehen:

```cpp
template <class Elm, class LST>
    struct Contains {
    using Head = typename LIST::Head;
    using Tail = typename LIST::Tail;
 
    static constexpr bool found = (Elm == Head);
    ...
};
 
template <class Elm>
    struct Contains <Elm, NIL> {
    static constexpr bool result = false;
};
```

Finden Sie die Schwachstelle? Richtig erkannt, Sie k�nnen zwei Typen nicht *vergleichen*.
Was w�rde `int == char` in C ++ bedeuten?
Wir m�ssen den Vergleich zweier Typen anders angehen.
Die partielle Spezialisierung von Templates kommt uns - wieder Mal - zur Hilfe:

```cpp
template <class X, class Y>
struct Equals { static constexpr bool result = false; };

template <class X>
struct Equals<X, X> { static constexpr bool result = true; };
```

Damit k�nnen wir eine Klasse `Contains` wie folgt definieren:

```cpp
template <class Elm, class LIST>
struct Contains {
    using Head = typename LIST::Head;
    using Tail = typename LIST::Tail ;

    static constexpr bool result = Equals<Elm, Head>::result || Contains<Elm, Tail>::result;

    // shorter
    // static constexpr bool result = Equals<Elm, typename LIST::Head>::result ||
    //    Contains<Elm, typename LIST::Tail>::result;
};

template <class Elm>
struct Contains<Elm, Nil> {
    static constexpr bool result = false;
};
```

*Test*:

```cpp
using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;
std::cout << Contains<Int<5>, List12345>::result << std::endl;
std::cout << Contains<Int<10>, List12345>::result << std::endl;
```

*Ausgabe*:

```cpp
1
0
```

## Funktionalit�t `Prepend` und `Append`

Die ultimativen Funktionen f�r verkettete Listen sind das Einf�gen eines Elements am Listenanfang und -ende.
Wie immer zun�chst die Betrachtung in Pseude-Code:

```cpp
Prepend(e, lst) <- LST(e, lst)
Append(e, NIL)  <- LST(e)
Append(e, lst)  <- LST(lst.head, Append(e, lst.tail))
```

Umsetzung in C++:

```cpp
template <typename Elm, typename LIST = Nil>
struct Prepend {
    using result = List<Elm, LIST>;
};

template <class Elm, class LIST>
struct Append {
    using Head = typename LIST::Head;
    using Tail = typename LIST::Tail;

    using Next = typename Append<Elm, Tail>::result;
    using result = List<Head, Next>;
};

template <class Elm>
struct Append<Elm, Nil> {
    using result = List<Elm>;
};
```

Zum Testen der beiden Klassen tun wir uns noch etwas schwer, da wir die Listen - es sind Datentypen (!) - nicht
so einfach in der Konsole ausgeben k�nnen. F�r das Erste behelfen wir uns damit, die L�ngen der Listen auszugeben.
Das ist weit entfernt von "optimal", aber zun�chst einmal "besser wie nichts":


*Test*:

```cpp
using List12345 = List<Int<1>, List<Int<2>, List<Int<3>, List<Int<4>, List<Int<5>>>>>>;

using newList = Prepend<Int<0>, List12345>::result;
std::cout << Length<newList>::result << std::endl;
std::cout << Length<Prepend <Int<0>, List12345>::result>::result << std::endl;
std::cout << Length<Prepend <Int<1>, newList>::result>::result << std::endl;

std::cout << Length<Append <Int<6>, List12345>::result>::result << std::endl;
std::cout << Length<Append <Int<7>, newList>::result>::result << std::endl;
```

*Ausgabe*:

```cpp
6
6
7
6
7
```

---

## Literaturhinweise

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[Nico Brailovsky's blog](https://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming//)<br>(abgerufen am 20.05.2020).

---

[Zur�ck](../../Readme.md)

---
