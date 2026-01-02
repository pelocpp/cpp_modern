# Programmierung zur Übersetzungszeit mit `constexpr`

[Zurück](../../Readme.md)

---

[Quellcode](ConstExpr.cpp)<br />
[Quellcode CRC](ConstExpr_CRC.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Variablen](#link2)
  * [Funktionen](#link3)
  * [Klassen und Objekte](#link4)
  * [`constexpr` und dynamische Speicherverwaltung](#link5)
  * [`constexpr`-Funktionen und `constexpr`-Lambda-Funktionen](#link6)
  * [Literaturhinweise](#link7)

---

## Allgemeines <a name="link1"></a>

Die Berechnung von Ausdrücken zur Übersetzungszeit wurde mit C++&ndash;17 auf ein neues Niveau angehoben.
Längst haben wir es nicht mehr mit nur konstanten Literalen oder einfachen Ausdrücken,
bestehend aus einer Summation oder Multiplikation, zu tun.
In C++&ndash;17 können zur Übersetzungszeit Variablen, Funktionen und auch ganze Klassen bzw. deren Objekte mit entsprechenden Konstruktoren
zur Übersetzungszeit ausgeführt bzw. erzeugt werden.

Von Interesse ist dieser Aspekt in der Anwendung zum Beispiel für die *Embedded Programmierung*, wenn es darum geht, 
möglichst viele Daten vom Übersetzer berechnen zu lassen, um diese mit Hilfe des Kompilats in das *ROM* (*Read-Only-Memory*)
einer speziellen Hardware zu packen.

Die syntaktischen Einsatzmöglichkeiten konstanter Ausdrücke mit `constexpr` sind sehr vielfältiger Natur.
Wir stellen einige signifikante Beispiele vor:

  * Variablen,
  * Klassen / benutzerdefinierte Datentypen mit `constexpr` Konstruktoren,
  * Klassentemplates mit `constexpr` Konstruktoren,
  * `constexpr`-Funktionen und `constexpr`-Lambda-Objekte und
  * Konstante `std::array<>`-Objekte, initialisiert mit variadischen Templates 

## Variablen <a name="link2"></a>

Bei Deklaration einer Variablen mit dem Schlüsselwort `constexpr` wird diese zu einem konstanten Ausdruck:

```cpp
constexpr double Pi = 3.14159265359;
```

Für Variablen, die mit `constexpr` definiert sind, gelten folgende Regeln, die mehr oder minder naheliegend oder einleuchtend sind:

  * Die Variable ist implizit `const`.
  * Die Variable hat einen expliziten Typ &ndash; in diesem Beispiel `double`.
  * Die Variable muss vorbelegt werden.
  * Der Vorbelegungswert muss ein konstanter Ausdruck sein.
  * Der Compiler kann Missbrauch erkennen.

*Bemerkung*:<br />
Was sind die Vorteile einer `constexpr`-Variablendefinition gegenüber dem Gebrauch der `#define`-Präprozessoranweisung?

```cpp
#define   Pi    3.14159
```

  * Pi besitzt keinen Typ.
  * Der Bezeichner `Pi` kann stillschweigend in einen beliebigen Wert konvertiert werden.


## Funktionen <a name="link3"></a>

Einfache Funktionen, z. B. kleine Hilfsfunktionen wie ein Vergleich zweier Werte,
lassen sich in klassischem C als Makro und in modernem C++ als `constexpr`-Funktion oder -Lambda schreiben.

Man sollte auf Grund der Nachteile von C-Makros immer der `constexpr`-Variante den Vorzug geben.

*Beispiel*:<br />

C-Makro mit Nachteilen:

```cpp
#define   SQUARE(x)    x * x
```

Eine Anwendung von `SQUARE` wie etwa

```cpp
std::size_t a{ 1 };
std::size_t b{ 2 };
std::size_t value{ SQUARE(a + b) };  
```

liefert einen falschen Wert zurück! Erkennen Sie das Problem?
Eine Textersetzung von `SQUARE(a + b)` resultiert in dem Ausdruck `a + b * a + b`
und dieser Ausdruck evaluiert zu *1 + 2 * 1 + 2* ist gleich 5. 
Man würde aber 3 * 3 = 9 als Ergebnis erwarten.

Okay, man hätte das in dem Makro `SQUARE` besser machen können, zum Beispiel so:

```cpp
#define   SQUARE(x)    (x * x)
```

Dennoch erkennen wir die Schwachstellen der C-Makro Technik.

Mit `constexpr` würde man eine `square`-Funktion so schreiben:

```cpp
constexpr auto square (auto x) {
    return x * x;
};
```

oder auch

```cpp
auto squareLambda = [](auto x) constexpr {
    return x * x;
};
```

Damit sind nun folgende Anwendungen möglich:

```cpp
constexpr std::size_t a{ 1 };
constexpr std::size_t b{ 2 };
constexpr auto value{ square(a + b) };
static_assert(value == 9);                  // correct result !!!

constexpr double x{ 3.0 };
constexpr double y{ 4.0 };
constexpr auto dvalue{ squareLambda(x + y) };
static_assert(dvalue == 49.0);              // correct result !!!
```

Beachten Sie auch diese vier Deklarationen:

```cpp
constexpr auto squareOfTwo = square(2);
constexpr auto squareOfThree = square(3.0);

constexpr auto squareOfFour = squareLambda(4);
constexpr auto squareOfFive = squareLambda(5.0);
```

Es werden alle Werte vom Compiler zur Übersetzungszeit berechnet!

Wir kommen jetzt auf Klassen und Objekte zu sprechen.

## Klassen und Objekte <a name="link4"></a>

Wie Variablen, deren Wert zur Übersetzungszeit bestimmt wird,
lassen sich analog auch Objekte vom Übersetzer zur Übersetzungszeit erzeugen.
Hierfür müssen die folgenden Bedingungen erfüllt sein:

Klassen, deren Objekte zur Übersetzungszeit kreiert werden können,

  * müssen einen (oder mehrere) Konstruktor(en) haben, die mit `constexpr` deklariert sind,
  * dürfen keine virtuellen Methoden besitzen (oder erben) und
  * dürfen keine Ausnahmebehandlung verwenden.
 
Als Beispiel betrachten wir eine Klasse `Complex` für komplexe Zahlen, die Operationen mit komplexen Zahlen 
zur Übersetzungszeit unterstützt:

```cpp
01: class Complex
02: {
03: private:
04:     float m_real;
05:     float m_imag;
06: 
07: public:
08:     // c'tors
09:     constexpr Complex() : m_real{ }, m_imag{ } {}
10:     constexpr Complex(float real, float imag) : m_real{ real }, m_imag{ imag } {}
11: 
12:     // getter
13:     constexpr float real() const { return m_real; }
14:     constexpr float imag() const { return m_imag; }
15: 
16:     // operators
17:     constexpr Complex operator+ (const Complex& other) const
18:     {
19:         float real = m_real + other.m_real;
20:         float imag = m_imag + other.m_imag;
21:         return { real, imag };
22:     }
23: };
```

*Listing* 1: Klasse `Complex` mit `constexpr` Konstruktoren.

Mit folgendem Code-Fragment können wir die Klasse `Complex` testen und `Complex`-Objekte anlegen,
die vom Übersetzer erzeugt wurden:

```cpp
01: constexpr Complex c0{ };
02: constexpr Complex c1{ 1.0, 2.0 };
03: constexpr Complex c2{ 3.0, 3.0 };
04: 
05: constexpr float r1 = c1.real();
06: constexpr Complex c3 = c1 + c2;
07: constexpr float r2 = c3.real();
08:         
09: std::cout << "Real: " << c3.real() << std::endl;
10: std::cout << "Imag: " << c3.imag() << std::endl;
11: 
12: // verify compile time computing
13: static_assert (c1.real() == 1.0, "real part shoud be 1.0");
14: static_assert (c3.real() == 4.0, "real part shoud be 4.0");
15: static_assert (c3.imag() == 5.0, "imaginary part shoud be 5.0");
```

*Listing* 2: `Complex`-Objekte mit Operationen, die der Übersetzer ausführt.

Den Nachweis, dass der Übersetzer tatsächlich `Complex`-Objekte zur Übersetzungszeit anlegt,
und dies mit korrekten Werten, nehmen wir mit `static_assert`-Deklarationen vor,
siehe die Zeilen 13 bis 15 von *Listing* 2. Eine `static_assert`-Deklaration erwartet einen booleschen Ausdruck und eine Zeichenkette.
Evaluiert der boolesche Ausdruck zu `false`, wird die Zeichenkette als Fehlermeldung ausgegeben und die Übersetzung abgebrochen.

Mit einer ruhigen Hand und der Betrachtung von Tooltips kann man die Arbeit des Übersetzers auch von der Entwicklungsumgebung aus betrachten.
Mit dem *Visual Studio* sieht, um wiederum beim letzten Beispiel zu verweilen,
das Objekt `c3` so aus:

<img src="ConstExpr01.png" width="800">

*Abbildung* 1: Ein `Complex`-Objekt, erzeugt vom Übersetzer.

Eine dritte Möglichkeit besteht in der Analyse des Assembler-Codes:

<img src="constexpr_lambda_01.png" width="700">

*Abbildung* 2: Der Wert des Realteils von Objekt `c1` im Maschinencode.

*Hinweis*: Der OpCode `movss` steht für *Move or Merge Scalar Single-Precision Floating-Point Value*.

Der Wert des Realteils von Objekt `c1` ist vom Typ `float`,
dies stellt uns in der Betrachtung des Maschinencodes vor ein kleines,
aber nicht unlösbares Problem.
Mit Hilfe eines IEEE nach `float` Konvertierers
(siehe [IEEE 754 Converter](https://www.h-schmidt.net/FloatConverter/IEEE754de.html))
können wir wiederum
bestätigen, dass der Wert `1.0` &ndash; und damit `0x3f800000` &ndash;
bereits zur Übersetzungszeit im Maschinencode abgelegt ist.
Es kommt also definitiv nicht zur Laufzeit zum
Aufruf der *getter*-Methode `real()`!

<img src="constexpr_lambda_02.png" width="700">

*Abbildung* 3: IEEE-754 Konverter für Fließkommazahlen.


## `constexpr` und dynamische Speicherverwaltung <a name="link5"></a>

Zur Fragestellung &bdquo;`constexpr` und dynamische Speicherverwaltung&rdquo;
gibt es einen interessanten Aufsatz im [Netz](https://www.cppstories.com/2021/constexpr-new-cpp20)
(abgerufen am 19.12.2022).

Das dort gezeigte Beispiel wird in den aktuellen Versionen des Visual C++ Compilers unterstützt:

```cpp
01: constexpr int naiveSum(unsigned int n)
02: {
03:     auto ip = new int[n];
04:     std::iota(ip, ip + n, 1);
05:     auto tmp = std::accumulate(ip, ip + n, 0);
06:     delete[] ip;
07:     return tmp;
08: }
09: 
10: void test()
11: {
12:     constexpr int sum = naiveSum(10);
13:     std::println("Sum from 1 up to 10: {}", sum);
14: }
```

*Listing* 3: Erstellung einer CRC8 Lookup Tabelle.

*Ausgabe*:

```
Sum from 1 up to 10: 55
```



## `constexpr`-Funktionen und `constexpr`-Lambda-Funktionen <a name="link6"></a>

Mit C++&ndash;17 haben `constexpr`-Funktionen und `constexpr`-Lambda-Methoden Einzug in die Sprache gefunden.
Dazu betrachten wir am besten gleich ein Beispiel.
Wir stellen uns die Aufgabe, eine Tabelle (`std::array`) mit Potenzen natürlicher Zahlen zu befüllen,
gewissermaßen ein Nachschlagewerk für natürliche Zahlen zur Potenzdarstellung.

*Bemerkung*: `std::array`-Objekte weisen eine Subtilität auf:
Im Gegensatz zu `std::vector`-Objekten muss ihre Länge zur Übersetzungszeit bekannt sein,
ähnlich wie es bei den klassischen Arrays in der Programmiersprache C der Fall ist.
Sie sind damit ein guter Kandidat, um vom Übersetzer erzeugt und auch mit Daten gefüllt zu werden.

Derartige Tabellen sind natürlich prädestiniert, um sie mit entsprechenden Algorithmen und Funktionen einer höheren Programmiersprache zu erstellen.
In manchen Situationen &ndash; siehe zum Beispiel die Embedded Programmierung &ndash; ist es von Vorteil,
wenn diese Tabellen mit konstanten Werten bereits zum Übersetzungszeitpunkt erstellt werden,
um sie dann im ROM einer speziellen Hardware abzulegen.
Derartige Berechnungen sind für ein Zielsystem nicht nur störend, sie kosten unnütze Zeit
und haben häufig mit der eigentlichen Aufgabe nichts zu tun.

Zahlenwerte aus einem Nachschlagewerk abtippen kann natürlich auch keine Lösung sein.
Damit sind wir bei C++-Funktionen angekommen, die der Übersetzer (auf dem Entwicklungsrechner) ausführt,
und damit nicht auf dem Zielsystem, für das Maschinencode generiert wird.

```cpp
01: constexpr size_t TableSize = 5;
02: constexpr size_t Factor = 4;
03: 
04: template<size_t F>
05: constexpr auto powerTable = [] {
06: 
07:     std::array<size_t, TableSize> table = {};
08: 
09:     size_t index{ 1 };
10:     for (size_t& elem : table) {
11: 
12:         size_t tmp{ 1 };
13:         for (size_t i{}; i != F; ++i) {
14:             tmp *= index;
15:         }
16: 
17:         elem = tmp;
18:         ++index;
19:     }
20: 
21:     return table;
22: } ();
23: 
24: constexpr size_t sumUpPowerTable()
25: {
26:     size_t total{};
27: 
28:     for (size_t i{}; i != TableSize; ++i) {
29:         total += powerTable<Factor>[i];
30:     }
31: 
32:     return total;
33: }
```

*Listing* 4: `constexpr`-Funktionen und -Objekte-Funktionen in der Praxis.

Die Zeilen 4 bis 22 von *Listing* 4 haben es in sich: Prinzipiell haben wir es mit einer Lambda-Funktion zu tun, die anonym ist,
also keinen Namen besitzt! Eigentlich haben wir es mit einer Lambda-Templatefunktion zu tun,
der Template-Parameter `F` (wie &bdquo;Factor&rdquo;) spezifiziert den Faktor,
der für die Potenzierung heranzuziehen ist. Nun zu Zeile 22: Die runden Klammern `()` bewirken, dass die Lambda-Templatefunktion
bei Spezialisierung (mit einem Faktor) aufgerufen wird: Der Bezeichner `powerTable` in Zeile 5
steht also für das `std::array`-Objekt, dass von der Lambda-Funktion berechnet und zurückgeliefert wird. 

Wo wird die Lambda-Templatefunktion spezialisiert und aufgerufen?
Einen Aufruf finden wir in Zeile 29 vor: Spezialisiert mit einem `Factor` gleich 4 wird auf den Rückgabewert
&ndash; ein `std::array`-Objekt &ndash; mit dem Index-Operator `[]` auf die einzelnen Einträge des Arrays zugegriffen.
Es ist also der Index-Operator `[]` ebenfalls eine `constexpr`-Funktion, um dies hervorzuheben.

Bleiben wir bei der Funktion `sumUpPowerTable`. Sie soll exemplarisch veranschaulichen,
dass `constexpr`-Variablen und -Funktionen gewissermaßen &bdquo;schachtelbar&rdquo; sind,
also die `constexpr`-Eigenschaft bleibt so lange erhalten, wie eine `constexpr`-Funktion aus
unterlagerten `constexpr`-Funktionsaufrufen und -Variablen gebildet wird.

Neben `static_assert`-Zusicherungen können wir die Vorleistungen des Übersetzers auch mit dem Debugger verifizieren.
Um es an einem Beispiel zu betrachten. Ein Aufruf der `sumUpPowerTable`-Funktion sollte mit einem `Factor` gleich 4 
und einer Tabellengröße gleich 5 die Summe von 1 + 16 + 81 + 256 + 625 = 979 zurückliefern.
Diesen (konstanten) Wert müssten wir im OpCode des Programms vorfinden:

In *Abbildung* 2 &ndash; und bei Bedarf mit dem *Calculator* &ndash; können wir uns davon überzeugen:
Der hexadezimale Wert `3D3h` tritt in einer `MOV`-Instruktion auf, der Übersetzer hat tatsächlich alle Berechnungen zur 
Übersetzungszeit vorgenommen:

<img src="ConstExpr02.png" width="700">

*Abbildung* 2: `MOV`-Instruktion mit Operand 979 (3D3h)


## Literaturhinweise <a name="link7"></a>

Die Anregungen zu dem CRC8-Artikel stammen aus einem Aufsatz aus der Zeitschrift *IX*:

Petrautzki, Dirk. &bdquo;Nachschlagewerk: C++-Metaprogrammierung mit Templates für eingebettete Systeme&rdquo;.
*iX* Magazin für professionelle Informationstechnik, Mai 2021, S. 134 - 137.

Materialien in elektronischer Form: [Fraunhofer Applied Research Center for Wireless Sensor Technology](https://github.com/Fraunhofer-IIS-ARC-WST)

An die Stelle der *Collatz*-Zahlenfolge werden hier Lookup-Tabellen für CRC8-Berechnungen zur Übersetzungszeit untersucht.

*Hinweis*:

Ein Online-Tool zur Berechnung von CRC Lookup-Tabellen findet sich [hier](https://crccalc.com/).
Allgemeine Erläuterungen zum Verständnis der CRC-Thematik 
können auch hier nachgelesen werden:<br/>
[Understanding and implementing CRC (Cyclic Redundancy Check) calculation](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html).

Die Beispiele für `constexpr`-Funktionen und `constexpr`-Lambda-Objekte sind in diesem Aufsatz erheblich anwendungsbezogener,
siehe zum Beispiel die beiden Funktionen zur Erstellung und den Zugriff auf CRC8 Lookup Tabellen:

```cpp
01: constexpr uint8_t MY_POLYNOM = 0x07;
02: constexpr int TABLE_SIZE = 256;
03: 
04: template<uint8_t POLYNOM>
05: constexpr auto crcTable = [] {
06:   std::array<uint8_t, TABLE_SIZE> A = {};
07:   for (int i = 0; i < TABLE_SIZE; i++) {
08:     A[i] = i;
09:     for (int j = 0; j < 8; j++) {
10:       if ((A[i] & 0x80) != 0) {
11:         A[i] = (uint8_t)((A[i] << 1) ^ POLYNOM);
12:       } else {
13:         A[i] <<= 1;
14:       }
15:     }
16:   }
17:   return A;
18: }();
19: 
20: constexpr auto calcCRC(uint8_t len, const uint8_t* data) {
21:   uint8_t checksum = 0;
22:   while(len--) {
23:     checksum = crcTable<MY_POLYNOM>[*data++ ^ checksum];
24:   }
25:   return checksum;
26: }
```

*Listing* 5: Erstellung einer CRC8 Lookup Tabelle.

---

[Zurück](../../Readme.md)

---
