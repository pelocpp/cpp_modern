# Programmierung zur �bersetzungszeit mit `constexpr`

[Zur�ck](../../Readme.md)

---

[Quellcode](ConstExpr.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Variablen](#link2)
  * [Klassen mit `constexpr` Konstruktoren](#link3)
  * [`constexpr` und dynamische Speicherverwaltung](#link4)
  * [`constexpr`-Funktionen und `constexpr`-Lambda-Funktionen](#link5)
  * [Literaturhinweise](#link6)

---

## Allgemeines <a name="link1"></a>

Die Berechnung von Ausdr�cken zur �bersetzungszeit wurde mit C++&ndash;17 auf ein neues Niveau angehoben.
L�ngst haben wir es nicht mehr mit nur konstanten Literalen oder einfachen Ausdr�cken,
bestehend aus einer Summation oder Multiplikation, zu tun.
In C++&ndash;17 k�nnen zur �bersetzungszeit Variablen, Funktionen und auch ganze Klassen bzw. deren Objekte mit entsprechenden Konstruktoren
zur �bersetzungszeit ausgef�hrt bzw. erzeugt werden.

Von Interesse ist dieser Aspekt in der Anwendung zum Beispiel f�r die *Embedded Programmierung*, wenn es darum geht, 
m�glichst viele Daten vom �bersetzer berechnen zu lassen, um diese mit Hilfe des Kompilats in das *ROM* (*Read-Only-Memory*)
einer speziellen Hardware zu packen.

Die syntaktischen Einsatzm�glichkeiten konstanter Ausdr�cke mit `constexpr` sind sehr vielf�ltiger Natur.
Wir stellen einige signifikante Beispiele vor:

  * Variablen,
  * Klassen / benutzerdefinierte Datentypen mit `constexpr` Konstruktoren,
  * Klassentemplates mit `constexpr` Konstruktoren,
  * `constexpr`-Funktionen und `constexpr`-Lambda-Objekte und
  * Konstante `std::array<>`-Objekte, initialisiert mit variadischen Templates 

## Variablen <a name="link2"></a>

Bei Deklaration einer Variablen mit dem Schl�sselwort `constexpr` wird diese zu einem konstanten Ausdruck:

```cpp
constexpr double Pi = 3.14159265359;
```

F�r Variablen, die mit `constexpr` definiert sind, gelten folgende Regeln, die mehr oder minder naheliegend oder einleuchtend sind:

  * Die Variable ist implizit `const`.
  * Die Variable muss vorbelegt werden.
  * Der Vorbelegungswert muss ein konstanter Ausdruck sein

Vielmehr gibt es zum Themenbereich &bdquo;Variablen&rdquo; nicht zu sagen, wir kommen jetzt auf Klassen und Objekte zu sprechen.

## Klassen mit `constexpr` Konstruktoren <a name="link3"></a>

Wie Variablen, deren Wert zur �bersetzungszeit bestimmt wird,
lassen sich analog auch Objekte vom �bersetzer zur �bersetzungszeit erzeugen.
Hierf�r m�ssen die folgenden Bedingungen erf�llt sein:

Klassen, deren Objekte zur �bersetzungszeit kreiert werden k�nnen,

  * m�ssen einen (oder mehrere) Konstruktor(en) haben, die mit `constexpr` deklariert sind,
  * d�rfen keine virtuellen Methoden besitzen (oder erben) und
  * d�rfen keine Ausnahmebehandlung verwenden.
 
Als Beispiel betrachten wir eine Klasse `Complex` f�r komplexe Zahlen, die Operationen mit komplexen Zahlen 
zur �bersetzungszeit unterst�tzt:

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

Mit folgendem Code-Fragment k�nnen wir die Klasse `Complex` testen und `Complex`-Objekte anlegen,
die vom �bersetzer erzeugt wurden:

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

*Listing* 2: `Complex`-Objekte mit Operationen, die der �bersetzer ausf�hrt.

Den Nachweis, dass der �bersetzer tats�chlich `Complex`-Objekte zur �bersetzungszeit anlegt,
und dies mit korrekten Werten, nehmen wir mit `static_assert`-Deklarationen vor,
siehe die Zeilen 13 bis 15 von *Listing* 2. Eine `static_assert`-Deklaration erwartet einen booleschen Ausdruck und eine Zeichenkette.
Evaluiert der boolesche Ausdruck zu `false`, wird die Zeichenkette als Fehlermeldung ausgegeben und die �bersetzung abgebrochen.

Mit einer ruhigen Hand und der Betrachtung von Tooltips kann man die Arbeit des �bersetzers auch von der Entwicklungsumgebung aus betrachten.
Mit dem *Visual Studio* sieht, um wiederum beim letzten Beispiel zu verweilen,
das Objekt `c3` so aus:

<img src="ConstExpr01.png" width="800">

*Abbildung* 1: Ein `Complex`-Objekt, erzeugt vom �bersetzer.

Eine dritte M�glichkeit besteht in der Analyse des Assembler-Codes:

<img src="constexpr_lambda_01.png" width="700">

*Abbildung* 2: Der Wert des Realteils von Objekt `c1` im Maschinencode.

*Hinweis*: Der OpCode `movss` steht f�r *Move or Merge Scalar Single-Precision Floating-Point Value*.

Der Wert des Realteils von Objekt `c1` ist vom Typ `float`,
dies stellt uns in der Betrachtung des Maschinencodes vor ein kleines,
aber nicht unl�sbares Problem.
Mit Hilfe eines IEEE nach `float` Konvertierers
(siehe [IEEE 754 Converter](https://www.h-schmidt.net/FloatConverter/IEEE754de.html))
k�nnen wir wiederum
best�tigen, dass der Wert `1.0` &ndash; und damit `0x3f800000` &ndash;
bereits zur �bersetzungszeit im Maschinencode abgelegt ist.
Es kommt also definitiv nicht zur Laufzeit zum
Aufruf der *getter*-Methode `real()`!

<img src="constexpr_lambda_02.png" width="700">

*Abbildung* 3: IEEE-754 Konverter f�r Flie�kommazahlen.


## `constexpr` und dynamische Speicherverwaltung <a name="link4"></a>

Zur Fragestellung &bdquo;`constexpr` und dynamische Speicherverwaltung&rdquo;
gibt es einen interessanten Aufsatz im [Netz](https://www.cppstories.com/2021/constexpr-new-cpp20)
(abgerufen am 19.12.2022).

Das dort gezeigte Beispiel wird in den aktuellen Versionen des Visual C++ Compilers unterst�tzt:

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



## `constexpr`-Funktionen und `constexpr`-Lambda-Funktionen <a name="link5"></a>

Mit C++&ndash;17 haben `constexpr`-Funktionen und `constexpr`-Lambda-Methoden Einzug in die Sprache gefunden.
Dazu betrachten wir am besten gleich ein Beispiel.
Wir stellen uns die Aufgabe, eine Tabelle (`std::array`) mit Potenzen nat�rlicher Zahlen zu bef�llen,
gewisserma�en ein Nachschlagewerk f�r nat�rliche Zahlen zur Potenzdarstellung.

*Bemerkung*: `std::array`-Objekte weisen eine Subtilit�t auf:
Im Gegensatz zu `std::vector`-Objekten muss ihre L�nge zur �bersetzungszeit bekannt sein,
�hnlich wie es bei den klassischen Arrays in der Programmiersprache C der Fall ist.
Sie sind damit ein guter Kandidat, um vom �bersetzer erzeugt und auch mit Daten gef�llt zu werden.

Derartige Tabellen sind nat�rlich pr�destiniert, um sie mit entsprechenden Algorithmen und Funktionen einer h�heren Programmiersprache zu erstellen.
In manchen Situationen &ndash; siehe zum Beispiel die Embedded Programmierung &ndash; ist es von Vorteil,
wenn diese Tabellen mit konstanten Werten bereits zum �bersetzungszeitpunkt erstellt werden,
um sie dann im ROM einer speziellen Hardware abzulegen.
Derartige Berechnungen sind f�r ein Zielsystem nicht nur st�rend, sie kosten unn�tze Zeit
und haben h�ufig mit der eigentlichen Aufgabe nichts zu tun.

Zahlenwerte aus einem Nachschlagewerk abtippen kann nat�rlich auch keine L�sung sein.
Damit sind wir bei C++-Funktionen angekommen, die der �bersetzer (auf dem Entwicklungsrechner) ausf�hrt,
und damit nicht auf dem Zielsystem, f�r das Maschinencode generiert wird.

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
der f�r die Potenzierung heranzuziehen ist. Nun zu Zeile 22: Die runden Klammern `()` bewirken, dass die Lambda-Templatefunktion
bei Spezialisierung (mit einem Faktor) aufgerufen wird: Der Bezeichner `powerTable` in Zeile 5
steht also f�r das `std::array`-Objekt, dass von der Lambda-Funktion berechnet und zur�ckgeliefert wird. 

Wo wird die Lambda-Templatefunktion spezialisiert und aufgerufen?
Einen Aufruf finden wir in Zeile 29 vor: Spezialisiert mit einem `Factor` gleich 4 wird auf den R�ckgabewert
&ndash; ein `std::array`-Objekt &ndash; mit dem Index-Operator `[]` auf die einzelnen Eintr�ge des Arrays zugegriffen.
Es ist also der Index-Operator `[]` ebenfalls eine `constexpr`-Funktion, um dies hervorzuheben.

Bleiben wir bei der Funktion `sumUpPowerTable`. Sie soll exemplarisch veranschaulichen,
dass `constexpr`-Variablen und -Funktionen gewisserma�en &bdquo;schachtelbar&rdquo; sind,
also die `constexpr`-Eigenschaft bleibt so lange erhalten, wie eine `constexpr`-Funktion aus
unterlagerten `constexpr`-Funktionsaufrufen und -Variablen gebildet wird.

Neben `static_assert`-Zusicherungen k�nnen wir die Vorleistungen des �bersetzers auch mit dem Debugger verifizieren.
Um es an einem Beispiel zu betrachten. Ein Aufruf der `sumUpPowerTable`-Funktion sollte mit einem `Factor` gleich 4 
und einer Tabellengr��e gleich 5 die Summe von 1 + 16 + 81 + 256 + 625 = 979 zur�ckliefern.
Diesen (konstanten) Wert m�ssten wir im OpCode des Programms vorfinden:

In *Abbildung* 2 &ndash; und bei Bedarf mit dem *Calculator* &ndash; k�nnen wir uns davon �berzeugen:
Der hexadezimale Wert `3D3h` tritt in einer `MOV`-Instruktion auf, der �bersetzer hat tats�chlich alle Berechnungen zur 
�bersetzungszeit vorgenommen:

<img src="ConstExpr02.png" width="700">

*Abbildung* 2: `MOV`-Instruktion mit Operand 979 (3D3h)


## Literaturhinweise <a name="link6"></a>

Die Anregungen zu dem CRC8-Artikel stammen aus einem Aufsatz aus der Zeitschrift *IX*:

Petrautzki, Dirk. &bdquo;Nachschlagewerk: C++-Metaprogrammierung mit Templates f�r eingebettete Systeme&rdquo;.
*iX* Magazin f�r professionelle Informationstechnik, Mai 2021, S. 134 - 137.

Materialien in elektronischer Form: [Fraunhofer Applied Research Center for Wireless Sensor Technology](https://github.com/Fraunhofer-IIS-ARC-WST)

An die Stelle der *Collatz*-Zahlenfolge werden hier Lookup-Tabellen f�r CRC8-Berechnungen zur �bersetzungszeit untersucht.

*Hinweis*:

Ein Online-Tool zur Berechnung von CRC Lookup-Tabellen findet sich [hier](https://crccalc.com/).
Allgemeine Erl�uterungen zum Verst�ndnis der CRC-Thematik 
k�nnen auch hier nachgelesen werden:<br/>
[Understanding and implementing CRC (Cyclic Redundancy Check) calculation](http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html).

Die Beispiele f�r `constexpr`-Funktionen und `constexpr`-Lambda-Objekte sind in diesem Aufsatz erheblich anwendungsbezogener,
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

[Zur�ck](../../Readme.md)

---
