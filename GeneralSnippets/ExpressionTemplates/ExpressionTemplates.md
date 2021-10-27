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
class Matrix {
private:
    size_t m_cols;
    size_t m_rows;
    std::vector<double> m_values;

public:
    // c'tor(s)
    Matrix() : Matrix(Cols, Rows) {}

    Matrix(size_t cols, size_t rows) : m_cols{ cols }, m_rows{ rows }
    {
        m_values.resize(cols*rows);
    }

    // getter
    size_t inline getCols() const { return m_cols; };
    size_t inline getRows() const { return m_rows; };

    // functor - representing index operator
    const double& operator()(size_t x, size_t y) const;
    double& operator()(size_t x, size_t y);

    // operator= --> classical definition
    Matrix& operator=(const Matrix& rhs);

    // operator= --> expression template approach (template member method)
    template <typename TEXPR>
    Matrix& operator=(const TEXPR& expression);
};

// classical operator+ definition
Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    Matrix result{ lhs.getCols(), lhs.getRows() };

    for (size_t y{}; y != lhs.getRows(); ++y) {
        for (size_t x{}; x != lhs.getCols(); ++x) {
            result(x, y) = lhs(x, y) + rhs(x, y);
        }
    }
    return result;
}
```

Mit dieser Definition einer Klasse `Matrix` könnten wir nun eine Addition von Matrizen
so formulieren:

```cpp
Matrix a, b, c;

// initialize a, b & c
for (size_t y = 0; y != a.getRows(); ++y) {
    for (size_t x = 0; x != a.getCols(); ++x) {
        a(x, y) = 1.0;
        b(x, y) = 2.0;
        c(x, y) = 3.0;
    }
}  

Matrix result = a + b + c;  // result(x, y) = 6 
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
der mathematischen Realität sehr ineffizient gemacht! Ohne Überladung des `+`-Operators könnten wir beispielsweise eine weitaus effizientere Summenbildung von Matrizen
mit einem einzigen Durchlauf auf diese Weise implementieren:

```cpp
Matrix add3(const Matrix& a, const Matrix& b, const Matrix& c)
{
    Matrix result{ a.getCols(), a.getRows() };
    for (size_t y = 0; y != a.getRows(); ++y) {
        for (size_t x = 0; x != a.getCols(); ++x) {
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
template <typename LHS, typename RHS>
class MatrixExpr
{
private:
    const LHS& m_lhs;
    const RHS& m_rhs;

public:
    MatrixExpr(const LHS& lhs, const RHS& rhs) : m_rhs{ rhs }, m_lhs{ lhs } {}

    double operator() (size_t x, size_t y) const {
        return m_lhs(x, y) + m_rhs(x, y);
    }
};
```

Eine aktualisierte Version des `+`-Operators sieht nun so aus:

```cpp
template <typename LHS, typename RHS>
MatrixExpr<LHS, RHS> operator+(const LHS& lhs, const LHS& rhs) {
    return MatrixExpr<LHS, RHS>(lhs, rhs);
}
```

Es ist unmittelbar zu erkennen, dass der `+`-Operator
nicht mehr eine "eifrige" Berechnung des Ergebnisses zurückliefert
(Summe von 2 Matrixinstanzen, Erzeugung eines weiteren `Matrix`-Objekts),
sondern nur eine "Ausdrucksvorlage", die die Additionsoperation "repräsentiert".
Der wichtigste zu beachtende Punkt ist, dass der Ausdruck noch nicht berechnet wurde.
Er enthält lediglich Verweise (folglich auch keine Kopien) auf seine beiden Operanden.

Tatsächlich hindert uns nichts daran, ein `MatrixExpr`-Objekt und damit eine Ausdrucksvorlage wie folgt zu instanziieren:

```cpp
MatrixExpr<Matrix, Matrix> sumAB(a, b);
```

Zu einem späteren Zeitpunkt kann man, wenn man das Ergebnis der Summe tatsächlich benötigt,
den Ausdruck `result = a + b` wie folgt auswerten:

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
MatrixExpr<Matrix, Matrix> sumAB(a, b);
MatrixExpr<MatrixExpr<Matrix, Matrix>, Matrix> sumABC(sumAB, c);
```

Wiederum können wir in einem einzigen Durchlauf das gewünschte Resultat berechnen:

```cpp
for (size_t y = 0; y != a.rows(); ++y) {
    for (size_t x = 0; x != a.cols(); ++x) {
        result(x, y) = sumABC(x, y);
    }
}
```

Das letzte Puzzleteil besteht nun darin, die betrachtete Ausdrucksvorlage
in die `Matrix`-Klasse einzufügen.
Dies wird im Wesentlichen durch die Bereitstellung einer Implementierung des Wertzuweisungsoperators
`operator=()` erreicht, der eine Ausdrucksvorlage als Argument entgegen nimmt
und in einem Durchgang auswertet, wie wir es zuvor schon "manuell" betrachtet haben:

```cpp
// expression template approach: operator=
template <typename TEXPR>
Matrix& Matrix::operator=(const TEXPR& expr) {
    for (size_t y{}; y != getRows(); ++y) {
        for (size_t x{}; x != getCols(); ++x) {
            m_values[y * getCols() + x] = expr(x, y);
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
// adding 4 matrices using modified operator=
MatrixExpr<Matrix, Matrix> sumAB{ a, b };
MatrixExpr<MatrixExpr<Matrix, Matrix>, Matrix> sumABC{ sumAB, c };
MatrixExpr<MatrixExpr<MatrixExpr<Matrix, Matrix>, Matrix>, Matrix> sumABCD{ sumABC, d };

result = sumABCD;
```

oder - mit dem Feature der *Template Argument Type Deduction* geschrieben:

```cpp
MatrixExpr sumAB{ a, b };
MatrixExpr sumABC{ sumAB, c };
MatrixExpr sumABCD{ sumABC, d };

result = sumABCD;
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
