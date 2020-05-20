# Metaprogramming

## Überblick

C++ -Metaprogrammierung bezeichnet die Technik der Metaprogrammierung innerhalb der Programmiersprache C++,
also eine Technik, um in C++ Programmcode zur Übersetzungszeit generieren zu lassen

Bei der Templatemetaprogrammierung macht man sich zunutze, dass Templates während des Kompilierens ausgewertet werden.
So kann man Code schreiben, der zur Übersetzungszeit ausgeführt wird. Obwohl sich so die Dauer des Kompilierens verlängert, hat das Verfahren den Vorteil, dass es zu einer Verkürzung der Laufzeit kommen kann.

## Das klassische Beispiel

[Quellcode](MetaProgramming01.cpp)

```cpp
template <int N>
struct Factorial {

    static const int result = N * Factorial<N - 1>::result;

};

template <>
struct Factorial<1> {
    static const int result = 1;
};
```

In den Code-Snippets wird zum Thema "*Metaprogrammierung*" das wohl bekannteste Beispiel demontriert, die Berechnung
der Fakultät-Funktion zur Übersetzungszeit. Dabei ist zu beachten, dass es auch sehr wohl zur Übersetzungszeit zu Fehler kommen kann.

Diese werden vom Compiler - in meinem Fall als "*warning*" - gemeldet:

warning C4307: '*': signed integral constant overflow
message : see reference to class template instantiation 'Metaprogramming::Factorial<13>' being compiled

Es tritt also der (hinlänglich bekannte) Überlauf in der Fakultätfunktion bei Verwendung des Datentyps `int` auf.

Die Ausgabe des Programms - mit Fehlern - sieht auf meinem Rechner wie folgt aus:

```cpp
1
2
6
24
120
720
5040
40320
362880
3628800
39916800
479001600
1932053504
1278945280
2004310016
2004189184
-288522240
```

## Parcours durch gängige Metaprogramming Techniken

#### `static const`

Templates werden beim Übersetzen ausgewertet.
Das bedeutet, dass der gesamte Quellcode beim Übersetzen der Quelle tatsächlich ausgeführt wird,
also nicht zur Laufzeit. Da der Übersetzer Klassen - keine Objekte - übersetzt, können Templates
nur auf Klassen angewendet werden, es machen also nur Klassenvariablen (`const int`) Sinn.

#### Definition neuer Datentypen mit `using`

Wir betrachten ein weiteres Beispiel: Die klassische *"Bruchrechnung"* aus der Schulmathematik.
Beachten Sie am folgenden Beispiel: In der Metaprogrammierung gibt es *keine* Variablen,
es lassen sich aber sehr wohl *neue* Datentypen aus bestehenden Datentypen bilden.
`Frak` ist ebenfalls ein Typ, wenn er an zwei konkrete Werte gebunden wird.
Binden wir diesen Typ mit `using` an einen Namen, können wir diesen neuen Typen ansprechen,
siehe dazu die Schablone `ScalarMultiplication`:

```cpp
template <int N, int D>
struct Frak {
    static const long Num = N;
    static const long Den = D;
};

template <int N, typename F>
struct ScalarMultiplication {
    using result = Frak<N * F::Num, N * F::Den>;
};
```

*Test*:

```cpp
using TwoThirds = Frak< 2, 3 >;
using Four_Sixths = ScalarMultiplication< 2, TwoThirds >::result;
std::cout << Four_Sixths::Num << "/" << Four_Sixths::Den << std::endl;
```

*Ausgabe*:

```cpp
4/6
```

Es werden also in Schablonen neue Typen gebildet, auf die über einen Namen von außen zugegriffen werden kann!


#### Partielle Spezialisierung von Templates

Die partielle Spezialisierung von Templates ist zentrales Hilfsmittel in der Metaprogrammierung.
Wenn wir dieses Feature noch mit der rekursiven Definition von Templates zusammenführen,
lassen sich mächtige Funktionen definieren! Wir demonstrieren dies am Beispiel der Berechnung
des größten gemeinsamen Teilers zweier natürlicher Zahlen (ggt):

```cpp
template <int X, int Y>
struct GGT {
    static const long result = GGT<Y, X % Y>::result;
};

template <int X>
struct GGT<X, 0> {
    static const long result = X;
};

template <class F>
struct FrakNormalizedVerbose {
    static const long ggt = GGT<F::Num, F::Den>::result;
    static const long newNum = F::Num / ggt;
    static const long newDen = F::Den / ggt;
    using result = Frak<newNum, newDen>;
};

template <class F>
struct FrakNormalized {
    static const long ggt = GGT<F::Num, F::Den>::result;
    using result = Frak<F::Num / ggt, F::Den / ggt>;
};
```

Betrachten Sie die Definition von GGT<X, 0> an: Dies ist eine partielle Template Spezialisierung!

*Test*:

```cpp
typedef Frak<16, 4> Four;
typedef FrakNormalizedVerbose<Four>::result FourNormalized;
std::cout << FourNormalized::Num << "/" << FourNormalized::Den << "\n";
typedef Frak<32, 4> Eight;
typedef FrakNormalized<Eight>::result EightNormalized;
std::cout << EightNormalized::Num << "/" << EightNormalized::Den << "\n";
```

*Ausgabe*:

```cpp
4/1
8/1
```

#### Erste Zusammenfassung: Wiederholungsanweisung, bedingte Anweisungen und Rückgabewerte

In der Metaprogrammierung gelten andere Regeln als in der gewöhnlichen Programmierung. Für die klassischen
programmiersprachlichen Konstrukte Wiederholungsanweisung, bedingte Anweisung und Rückgabewert von Funktionen
lauten die Äquivalente in der Metaprogrammierung:
 
  * **Wiederholungsanweisung**: Rekursive Template-Definition 
  * **bedingte Anweisung**: Partielle Template Spezialisierung
  * **Rückgabewert von Funktionen**: `using`-Anweisung (oder `typdef` Anweisung)

Wir betrachten hierzu ein "komplexeres" Beispiel, in dem alle drei Mechanismen angewendet werden:

```cpp
template <typename X1, typename Y1>
struct SameBase {
    using X = typename ScalarMultiplication<Y1::Den, X1>::result;
    using Y = typename ScalarMultiplication<X1::Den, Y1>::result;
};

template <typename X, typename Y>
struct Sum {
    using BASE = SameBase<X, Y>;
    static const long Num = BASE::X::Num + BASE::Y::Num;
    static const long Den = BASE::Y::Den; // same as BASE::X::Den
    using result = typename FrakNormalized<Frak<Num, Den>>::result;
};
```

*Hinweis*: Man beachte die Verwendung des Schlüsselworts `typename` in den Schablonen `SameBase` und `Sum`: 
 `typename` wird hier benötigt, um den Compiler wissen zu lassen, dass der nachfolgenden Bezeichner ein Typ und kein statischer Member der Klasse (Struktur) ist.

*Test*:

```cpp
typedef Frak<3, 7> Frak1;
typedef Frak<1, 7> Frak2;
typedef Sum<Frak1, Frak2>::result Result;
std::cout << Result::Num << "/" << Result::Den << "\n";
```

*Ausgabe*:

```cpp
4/7
```

#### Ein Beispiel: Die Eulersche Zahl *e*

Die Eulersche Zahl *e* lässt sich mit folgender Formel berechnen:

<img src="euler_number.png" width="300"> 

Abbildung: Reihenentwicklung der Eulerschen Zahl *e*.

Da wir bereits wissen, wie Wiederholungsanweisungen, bedingte Anweisungen und Rückgabewerte in der Metaprogrammierung
formuliert werden, fällt uns eine Implementierung nicht schwer:

```cpp
template <int N>
struct E {
    // e = 1/0! + 1/1! + 1/2! + ...
    static const long Den = Factorial<N>::result;
    using Term = Frak<1, Den>;
    using NextTerm = typename E<N - 1>::result;
    using result = typename Sum<Term, NextTerm>::result;
};

template <>
struct E<0> {
    using result = Frak<1, 1>;
};
```

*Test*:

```cpp
typedef E<8>::result X;
std::cout << "e = " << (1.0 * X::Num / X::Den) << "\n";
std::cout << "e = " << X::Num << "/" << X::Den << "\n";
```

*Ausgabe*:

```cpp
e = 2.71828
e = 109601/40320
```


---

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[Nico Brailovsky's blog](https://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming//)<br>(abgerufen am 20.05.2020).


---

[Zurück](../../Readme.md)

---


*Test*:

```cpp
```

*Ausgabe*:

```cpp
```
