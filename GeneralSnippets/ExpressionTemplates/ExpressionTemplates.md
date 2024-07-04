# Expression Templates 

[Zurück](../../Readme.md)

---

[Quellcode](ExpressionTemplates.cpp)

---

## Einführung in Expression Templates 

Ein *Expression Template* ist eine Optimierungstechnik zur Übersetzungszeit,
die hauptsächlich im "*Numerical Computing*" Anwendung findet.
Der Hauptzweck besteht darin, unnötige Temporärvariablen bzw. -objekte zu vermeiden und Schleifenberechnungen
mit einem einzigen Durchgang zu optimieren (bei Operationen mit wiederholten numerischen Operationen).
*Expression Templates* wurden ursprünglich entwickelt, um die Ineffizienzen einer naiven Operatoren-Überladung bei der Implementierung
numerischer `Vector`- oder `Matrix`-Klassen zu umgehen.

#### Klassische Vorgehensweise 

Um ein besseres Verständnis für *Expression Templates* zu bekommen, versuchen wir zu verstehen,
warum wir sie überhaupt benötigen. Dazu betrachten wir zur Veranschaulichung eine einfache `Matrix`-Klasse:

```cpp
01: template<size_t N, typename T = ElemType>
02: class Matrix {
03: private:
04:     size_t m_size;
05:     std::array<std::array<T, N>, N> m_values;
06: 
07: public:
08:     // c'tor(s)
09:     Matrix() : Matrix{ T{} } {}
10:     Matrix(T preset) : m_size{ N } {
11:         std::for_each(
12:             std::begin(m_values),
13:             std::end(m_values),
14:             [=](auto& row) {
15:                 row.fill(preset);
16:             }
17:         );
18:     }
19: 
20:     size_t inline getSize() const { return N; };
21: 
22:     const T& operator()(size_t x, size_t y) const {
23:         return m_values[x][y];
24:     };
25: 
26:     T& operator()(size_t x, size_t y) {
27:         return m_values[x][y];
28:     }
29: 
30:     Matrix<N> operator+(const Matrix<N>& other) const
31:     {
32:         Matrix<N> result;
33:         for (size_t y{}; y != N; ++y) {
34:             for (size_t x{}; x != N; ++x) {
35:                 result.m_values[x][y] = m_values[x][y] + other.m_values[x][y];
36:             }
37:         }
38:         return result;
39:     }
40: };
```

Mit dieser Definition einer Klasse `Matrix` könnten wir nun eine Addition von Matrizen
so formulieren:

```cpp
Matrix<5> result{};
Matrix<5> a{ 1.0 }, b{ 2.0 }, c{ 3.0 };
result = a + b + c;   // result(x, y) = 6.0
```

Durch das Überladen des `+` -Operators haben wir eine Schreibweise in C ++, 
die die natürliche mathematische Notation für Matrizen nachahmt, um nicht zu sagen: kopiert.
Damit ist vor allem die letzte Anweisung `result = a + b + c;` gemeint.

Leider ist genau diese Anweisung im Vergleich zu einer äquivalenten, optimierten Version sehr ineffizient.
Um zu verstehen, warum, müssen wir uns überlegen, was passiert, wenn wir einen Ausdruck wie `Matrix result = a + b + c;` schreiben.
Dieser lautet im Opcode tatsächlich `((a + b) + c)` oder `operator+ (operator+ (a, b), c)`.
Mit anderen Worten, die Wiederholungsschleife innerhalb des `+`-Operators wird zweimal ausgeführt,
während sie genauso leicht in einem einzigen Durchgang ausführbar wäre.
Dies führt auch dazu, dass zwei temporäre `Matrix`-Objekte erstellt werden, was sich zwar zunächst nur auf den benötigten Speicherplatz auswirkt,
die Rechenleistung des Programms trotzdem zusätzlich beeinträchtigt.

Im Prinzip haben wir die Klasse `Matrix` mit Notationen in der Nähe
der mathematischen Realität sehr ineffizient gemacht!
Ohne Überladung des `+`-Operators könnten wir beispielsweise eine weitaus effizientere Summenbildung von Matrizen
mit einem einzigen Durchlauf auf diese Weise implementieren:

```cpp
01: template<size_t N>
02: Matrix<N> add3(const Matrix<N>& a, const Matrix<N>& b, const Matrix<N>& c)
03: {
04:     Matrix<N> result;
05: 
06:     for (size_t y = 0; y != a.getSize(); ++y) {
07:         for (size_t x = 0; x != a.getSize(); ++x) {
08:             result.m_values[x][y] = a.m_values[x][y] + b.m_values[x][y] + c.m_values[x][y];
09:         }
10:     }
11:     return result;
12: }
```

#### Vorgehensweise mit Expression Templates

Das vorherige Beispiel hat jedoch wiederum andere Nachteile, da es eine weitaus kompliziertere Schnittstelle
für die `Matrix`-Klasse zur Folge hat: Sie müssten Methoden wie `add2`, `add3`, `add4`, `add5`, usw. implementieren.
Wir gehen einen Schritt zurück und überlegen uns, wie wir die Überladung des `+`-Operators anpassen können,
um eine bessere Laufzeit zu erzielen.

Das Problem ergibt sich aus der Tatsache, dass der Ausdruck `Matrix result = a + b + c;` zu
"eifrig" (engl. "*eager*") ausgewertet wird, bevor der Compiler die Möglichkeit hat,
den gesamten Baum des arithmetischen Ausdrucks zu erstellen.
Mit anderen Worten: Was wir wirklich erreichen möchten, ist, dass `a + b + c` in einem Durchlauf berechnet wird
und der resultierende Ausdruck an `result` nur einmal zugewiesen wird.

Das ist die Kernidee von "*Expression Templates*": Anstatt dass der `+`-Operator
das Ergebnis des Addierens von zwei Matrix-Instanzen sofort bildet,
wird stattdessen eine "Vorlage" für die zukünftige Auswertung des Teilausdrucks zurückgegeben,
sobald der gesamte Ausdrucksbaum erstellt wurde.

Eine derartige Vorlage, die der Summierung von zwei `Matrix`-Objekten entspricht, könnte
so aussehen:

```cpp
01: template <typename TLhs, typename TRhs, typename T = ElemType>
02: class MatrixExpr
03: {
04: private:
05:     const TLhs& m_lhs;
06:     const TRhs& m_rhs;
07: 
08: public:
09:     MatrixExpr(const TLhs& lhs, const TRhs& rhs) : m_rhs{ rhs }, m_lhs{ lhs } {}
10: 
11:     T operator() (size_t x, size_t y) const {
12:         return m_lhs(x, y) + m_rhs(x, y);
13:     }
14: };
```

Eine aktualisierte Version des `+`-Operators sieht nun so aus:

```cpp
01: template <typename TLhs, typename TRhs>
02: MatrixExpr<TLhs, TRhs> operator+(const TLhs& lhs, const TRhs& rhs) {
03:     return MatrixExpr<TLhs, TRhs>(lhs, rhs);
04: }
```

Es ist unmittelbar zu erkennen, dass der `+`-Operator
nicht mehr eine "eifrige" Berechnung des Ergebnisses zurückliefert
(Summe von 2 Matrixinstanzen, Erzeugung eines weiteren `Matrix`-Objekts),
sondern nur eine "Ausdrucksvorlage", die die Additionsoperation "repräsentiert".
Der wichtigste zu beachtende Punkt ist, dass der Ausdruck noch nicht berechnet wurde.
Er enthält lediglich Verweise (folglich auch keine Kopien) auf seine beiden Operanden.

Tatsächlich hindert uns nichts daran, ein `MatrixExpr`-Objekt und damit eine Ausdrucksvorlage wie folgt zu instanziieren:

```cpp
MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB(a, b);
```

Zu einem späteren Zeitpunkt kann man, wenn man das Ergebnis der Summe tatsächlich benötigt,
den Ausdruck `result = a + b` wie folgt auswerten:

```cpp
for (size_t y{}; y != a.getSize(); ++y) {
    for (size_t x{}; x != a.getSize(); ++x) {
        result(x, y) = sumAB(x, y);
    }
}
```

Man erkennt ferner, dass ein weiterer Vorteil der Verwendung einer Ausdrucksvorlage darin besteht, 
dass die Summe von `a` und `b` in einem einzigen Durchlauf ausgewertet und dem Ergebnisobjekt `result` zugewiesen wird.

Wie sieht es bei einer Summe der Gestalt  `a + b + c` aus? Dazu benötigen wir eine Ausdrucksvorlage der Gestalt 

```cpp
MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB(a, b);
MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>> sumABC(sumAB, c);
```

Wiederum können wir in einem einzigen Durchlauf das gewünschte Resultat berechnen:

```cpp
for (size_t y{}; y != a.getSize(); ++y) {
    for (size_t x{}; x != a.getSize(); ++x) {
        result(x, y) = sumABC(x, y);
    }
}
```

*Hinweis*:
Betrachten Sie in dem letzten Ausschnitt den Ausdruck `sumABC(x, y)`: Wir können diesen
gedanklich so umformulieren:

```
sumABC(x, y) = sumAB(a, b) + c(x, y) = a(x, y) + b(x, y) + c(x, y);
```

Das letzte Puzzleteil besteht nun darin, die betrachtete Ausdrucksvorlage
in die `Matrix`-Klasse einzufügen.
Dies wird im Wesentlichen durch die Bereitstellung einer Implementierung des Wertzuweisungsoperators
`operator=()` erreicht, der eine Ausdrucksvorlage als Argument entgegen nimmt
und in einem Durchgang auswertet, wie wir es zuvor schon "manuell" betrachtet haben:

```cpp
// operator= --> expression template approach
template <typename TExpr>
Matrix<N>& operator=(const TExpr& expr)
{
    for (size_t y{}; y != N; ++y) {
        for (size_t x{}; x != N; ++x) {
            m_values[x][y] = expr(x, y);
        }
    }
    return *this;
}
```

Die komplette Realisierung des Beispiels finden Sie [hier](ExpressionTemplates.cpp) vor.

---

## Ein Benchmark-Test

Natürlich wäre es wünschenswert, dass sich die theoretischen Überlegungen in der realen Welt verifizieren lassen.
Zu diesem Zweck finden Sie im Code-Teil des Snippets einen Laufzeitvergleich vor:
Die Addition von 5 Matrizen wird im klassischen Ansatz und mit "*Expression Templates*" verglichen.
Das Kernstück der klassischen Realisierung sieht kurz und bündig so aus:

```cpp
for (size_t i{}; i != iterations; ++i) {
    result = a1 + a2 + a3 + a4 + a5;
}
```

Um es noch einmal zu verdeutlichen: Genau diese "unschuldige" Formulierung wird hinter den Kulissen so abgearbeitet:

```cpp
for (size_t i{}; i != iterations; ++i) {
    result = ((((a1 + a2) + a3) + a4) + a5);
}
```

Die runden Klammern verdeutlichen den jeweiligen `+`-Operator-Aufruf mit seinen beiden Operanden, die
Anzahl der temporären `Matrix`-Objekte lässt sich erahnen!

Im Vergleich dazu die Quellcode-Gestaltung mit "*Expression Templates*":

```cpp
// adding 4 matrices using modified operator=
MatrixExpr<Matrix<Size>, Matrix<Size>> sumAB{ a1, a2 };
MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>> sumABC{ sumAB, a3 };
MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCD{ sumABC, a4 };
MatrixExpr<MatrixExpr<MatrixExpr<MatrixExpr<Matrix<Size>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>>, Matrix<Size>> sumABCDE{ sumABCD, a5 };

result = sumABCD;
```

oder - mit dem Feature der *Template Argument Type Deduction* geschrieben:

```cpp
MatrixExpr sumAB{ a1, a2 };
MatrixExpr sumABC{ sumAB, a3 };
MatrixExpr sumABCD{ sumABC, a4 };
MatrixExpr sumABCDE{ sumABCD, a5 };

result = sumABCD;
```

Das sieht zunächst einmal etwas aufwendiger aus - die  "*Expression Templates*" sind für alle 5 `Matrix`-Objekte zu erstellen.
Das Resultat überzeugt uns, dass der Aufwand die Mühe wert war:


```
Start:
5153 milliseconds.
1241 milliseconds.
Done.
```

Dabei wurden im Quellcode folgende Werte verwendet:

```cpp
using ElemType = double;

// benchmark sizes
constexpr int Iterations{ 500000 };
constexpr size_t BenchmarkSize{ 50 };
```

---

## Literaturhinweise

Die Anregungen zu den Beispielen dieses Code-Snippets finden sich unter

[RIP Tutorial](https://riptutorial.com/cplusplus/example/19992/a-basic-example-illustrating-expression-templates/)<br>(abgerufen am 25.05.2020).

Zwei sehr interessante Artikel zu diesem Thema stammen von

[Angelika Langer](http://www.angelikalanger.com/Articles/Cuj/ExpressionTemplates/ExpressionTemplates.htm)<br>(abgerufen am 25.05.2020).

und

[Arindam Mukherjee](http://shoddykid.blogspot.com/2008/07/expression-templates-demystified.html)<br>(abgerufen am 25.05.2020).

Eine kürzere Fassung des Artikels von Angelika Langer ist im *Dr. Dobbs Journal* zu finden:

[C++ Expression Templates](https://www.drdobbs.com/c-expression-templates/184401627/)<br>(abgerufen am 25.05.2020).

---

[Zurück](../../Readme.md)

---
