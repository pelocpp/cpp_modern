# Expression Templates 

[Quellcode](ExpressionTemplates.cpp)

---

## Einführung in Expression Templates 

Ein *Expression Template* ist eine Optimierungstechnik zur Übersetzungszeit,
die hauptsächlich im "Scientific Computing" Anwendung findet.
Der Hauptzweck besteht darin, unnötige Temporärvariablen bzw. -objekte zu vermeiden und Schleifenberechnungen
mit einem einzigen Durchgang zu optimieren (bei Operationen mit wiederholten numerischen Operationen).
*Expression Templates* wurden ursprünglich entwickelt, um die Ineffizienzen einer naiven Operatoren-Überladung bei der Implementierung
numerischer `Vector`- oder `Matrix`-Klassen zu umgehen.

#### Klassische Vorgehensweise 

Um ein besseres Verständnis für *Expression Templates* zu erlangen, versuchen wir zu verstehen,
warum wir sie überhaupt benötigen. Dazu betrachten wir zur Veranschaulichung eine einfache `Matrix`-Klasse:

```cpp
template <typename T, size_t COL, size_t ROW>
class Matrix {
public:
    using value_type = T;

    Matrix() : m_values(COL * ROW) {}

    static size_t cols() { return COL; }
    static size_t rows() { return ROW; }

    const T& operator()(size_t x, size_t y) const { return m_values[y * COL + x]; }
    T& operator()(size_t x, size_t y) { return m_values[y * COL + x]; }

private:
    std::vector<T> m_values;
};

template <typename T, size_t COL, size_t ROW>
Matrix<T, COL, ROW>
operator+(const Matrix<T, COL, ROW>& lhs, const Matrix<T, COL, ROW>& rhs)
{
    Matrix<T, COL, ROW> result;

    for (size_t y = 0; y != lhs.rows(); ++y) {
        for (size_t x = 0; x != lhs.cols(); ++x) {
            result(x, y) = lhs(x, y) + rhs(x, y);
        }
    }
    return result;
}
```

Mit dieser Definition einer Klasse `Matrix` können wir nun eine Addition von Matrizen wie folgt formulieren:

```cpp
const std::size_t cols = 1000;
const std::size_t rows = 1000;

Matrix<double, cols, rows> a, b, c;

// initialize a, b & c
for (std::size_t y = 0; y != rows; ++y) {
    for (std::size_t x = 0; x != cols; ++x) {
        a(x, y) = 1.0;
        b(x, y) = 2.0;
        c(x, y) = 3.0;
    }
}  

Matrix<double, cols, rows> result = a + b + c;  // result(x, y) = 6 
```

Durch das Überladen des `+` -Operators erlangen wir eine Schreibweise in C ++, 
die die natürliche mathematische Notation für Matrizen nachahmt, um nicht zu sagen: kopiert.
Damit ist vor allem die letzte Anweisung `result = a + b + c;` gemeint.

Leider ist genau diese Anweisung im Vergleich zu einer äquivalenten, optimierten Version sehr ineffizient.
Um zu verstehen, warum, müssen wir uns überlegen, was passiert, wenn wir einen Ausdruck wie `Matrix result = a + b + c;` schreiben.
Dieser lautet im Opcode tatsächlich `((a + b) + c)` oder `operator+ (operator+ (a, b), c)`.
Mit anderen Worten, die Wiederholungsschleife innerhalb des `+`-Operators wird zweimal ausgeführt,
während sie genauso leicht auch in einem einzigen Durchgang ausführbar wäre.
Dies führt auch dazu, dass zwei temporäre `Matrix`-Objekte erstellt werden, was sich zwar zunächst nur auf den benötigten Speicherplatz auswirkt,
die Rechenleistung des Programms trotzdem zusätzlich beeinträchtigt.

Im Prinzip haben wir die Klasse `Matrix` mit einer Notation in der Nähe ihres mathematischen Gegenstücks
sehr ineffizient gemacht! Ohne Überladung des `+`-Operators könnten wir beispielsweise eine weitaus effizientere Summenbildung von Matrizen
mit einem einzigen Durchlauf wie folgt implementieren:

```cpp
template<typename T, std::size_t COL, std::size_t ROW>
Matrix<T, COL, ROW> add3(const Matrix<T, COL, ROW>& a,
                         const Matrix<T, COL, ROW>& b,
                         const Matrix<T, COL, ROW>& c)
{
    Matrix<T, COL, ROW> result;
    for (size_t y = 0; y != ROW; ++y) {
        for (size_t x = 0; x != COL; ++x) {
            result(x, y) = a(x, y) + b(x, y) + c(x, y);
        }
    }
    return result;
}
```

#### Vorgehensweise mit Expression Templates

Das vorherige Beispiel hat jedoch wiederum andere Nachteile, da es eine weitaus kompliziertere Schnittstelle
für die `Matrix`-Klasse zur Folge hat: Sie müssten Methoden wie `add2`, `add3`, `add4`, `add5`, usw. implementieren.
Wir gehen einen Schritt zurück und überlegen uns, wie wir die Überladung des `+`-Operators anpassen können,
um eine bessere Laufzeit zu erzielen.

Das Problem ergibt sich aus der Tatsache, dass der Ausdruck `Matrix result = a + b + c;` zu
"eifrig" (engl.  "eagerly") ausgewertet wird, bevor der Compiler die Möglichkeit hatte,
den gesamten Baum des arithmetischen Ausdrucks zu erstellen.
Mit anderen Worten, was wir wirklich erreichen möchten, ist, dass `a + b + c` in einem Durchlauf berechnet wird
und der resultierende Ausdruck an `result` nur einmal zugewiesen wird.

Das ist die Kernidee von "*Expression Templates*": Anstatt dass der `+`-Operator
das Ergebnis des Addierens von zwei Matrix-Instanzen sofort bildet,
wird statt dessen eine "Vorlage" für die zukünftige Auswertung des Teilausdrucks zurückgegeben,
sobald der gesamte Ausdrucksbaum erstellt wurde.

Eine derartige Vorlage, die der Summierung von zwei `Matrix`-Objekten entspricht, könnte
so aussehen:

```cpp
template <typename LHS, typename RHS>
class MatrixSum
{
public:
    using value_type = typename LHS::value_type;

    MatrixSum(const LHS& lhs, const RHS& rhs) : rhs(rhs), lhs(lhs) {}
    
    value_type operator() (int x, int y) const  {
        return lhs(x, y) + rhs(x, y);
    }
private:
    const LHS& lhs;
    const RHS& rhs;
};
```

Eine aktualisierte Version des `+`-Operators sieht nun so aus:

```cpp
template <typename LHS, typename RHS>
MatrixSum<LHS, RHS> operator+(const LHS& lhs, const LHS& rhs) {
    return MatrixSum<LHS, RHS>(lhs, rhs);
}
```

Es ist unmittelbar zu erkennen, dass der `+`-Operator nicht mehr eine "eifrige" Berechnung des Ergebnisses
(Summe von 2 Matrixinstanzen, die eine weitere Matrixinstanz wäre) zurückliefert,
sondern eine Ausdrucksvorlage, die die Additionsoperation "repräsentiert".
Der wichtigste zu beachtende Punkt ist, dass der Ausdruck noch nicht berechnet wurde.
Er enthält lediglich Verweise (folglich auch keine Kopien) auf seine beiden Operanden.

Tatsächlich hindert uns nichts daran, ein `MatrixSum`-Objekt und damit eine Ausdrucksvorlage wie folgt zu instanziieren:

```cpp
MatrixSum<Matrix<double>, Matrix<double> > sumAB(a, b);
```

Zu einem späteren Zeitpunkt, wenn man das Ergebnis der Summe tatsächlich benötigt,
kann man den Ausdruck `result = a + b` wie folgt auswerten:

```cpp
for (size_t y = 0; y != a.rows(); ++y) {
    for (size_t x = 0; x != a.cols(); ++x) {
        result(x, y) = sumAB(x, y);
    }
}
```

Man erkennt ferner, dass ein weiterer Vorteil der Verwendung einer Ausdrucksvorlage darin besteht, 
dass die Summe von `a` und `b` in einem einzigen Durchlauf ausgewertet und dem Ergebnisobjekt `result` zugewiesen wird.

Wie sieht es bei einer Summe der Gestalt  `a + b + c` aus? Dazu benötigen wir eine Ausdrucksvorlage der Gestalt 

```cpp
MatrixSum<Matrix<double>, Matrix<double> > sumAB(a, b);   // von oben
MatrixSum<MatrixSum<Matrix<double>, Matrix<double> >, Matrix<double> > sumABC(sumAB, c);
```

Wiederum können wir in einem einzigen Durchlauf das gewünschte Resultat berechnen:

```cpp
for (std::size_t y = 0; y != a.rows(); ++y) {
    for (std::size_t x = 0; x != a.cols(); ++x) {
        result(x, y) = sumABC(x, y);
    }
}
```

Das letzte Puzzleteil besteht nun darin, die betrachtete Ausdrucksvorlage tatsächlich in die `Matrix`-Klasse einzufügen.
Dies wird im Wesentlichen durch die Bereitstellung einer Implementierung des Wertzuweisungsoperators+
`operator=()` erreicht, der die Ausdrucksvorlage als Argument nimmt und in einem Durchgang auswertet,
wie Sie es zuvor schon "manuell" betrachtet haben:

```cpp
template <typename E>
Matrix<T, COL, ROW>& operator=(const E& expression) {
    for (std::size_t y = 0; y != rows(); ++y) {
        for (std::size_t x = 0; x != cols(); ++x) {
            m_values[y * COL + x] = expression(x, y);
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
for (int i = 0; i < iterations; ++i) {
    result = a1 + a2 + a3 + a4 + a5;
}
```

Um es noch einmal zu verdeutlichen: Genau diese "unschuldige" Formulierung wird hinter den Kulissen so abgearbeitet:

```cpp
for (int i = 0; i < iterations; ++i) {
    result = ((((a1 + a2) + a3) + a4) + a5);
}
```

Die runden Klammern verdeutlichen den jeweiligen `+`-Operator-Aufruf mit seinen beiden Operanden, die
Anzahl der temporären `Matrix`-Objekte lässt sich erahnen!

Im Vergleich dazu die Quellcode-Gestaltung mit "*Expression Templates*":

```cpp
MatrixSum<Matrix<double>, Matrix<double>> sumAB(a1, a2);
MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>> sumABC(sumAB, a3);
MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCD(sumABC, a4);
MatrixSum<MatrixSum<MatrixSum<MatrixSum<Matrix<double>, Matrix<double>>, Matrix<double>>, Matrix<double>>, Matrix<double>> sumABCDE(sumABCD, a5);

for (int i = 0; i < iterations; ++i) {
    result = sumABC;
}
```

Das sieht zunächst einmal etwas aufwendiger aus - die  "*Expression Templates*" sind für alle 5 `Matrix`-Objekte zu erstellen.
Das Resultat überzeugt uns, dass der Aufwand die Mühe wert war:

```
Start:
4897 milliseconds.
1674 milliseconds.
Done.
```

---

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet finden sich unter

[RIP Tutorial](https://riptutorial.com/cplusplus/example/19992/a-basic-example-illustrating-expression-templates/)<br>(abgerufen am 25.05.2020).

Zwei sehr interessante Artikel zu diesem Thema stammen von

[Angelika Langer](http://www.angelikalanger.com/Articles/Cuj/ExpressionTemplates/ExpressionTemplates.htm/)<br>(abgerufen am 25.05.2020).

und

[Arindam Mukherjee](http://shoddykid.blogspot.com/2008/07/expression-templates-demystified.html/)<br>(abgerufen am 25.05.2020).

Eine kürzere Fassung des Artikels von Angelika Langer ist im *Dr. Dobbs Journal* zu finden:

[C++ Expression Templates](https://www.drdobbs.com/c-expression-templates/184401627/)<br>(abgerufen am 25.05.2020).

---

[Zurück](../../Readme.md)

---
