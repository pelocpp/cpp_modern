# Typumwandlungen

[Zur�ck](../../Readme.md)

---

[Quellcode](Casts.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [Implizite Konvertierungen](#link2)
  * [Explizite Konvertierungen: C-Style](#link3)
  * [Explizite C++ Konvertierungen](#link4)
  * [Die `static_cast`-Operation](#link5)
  * [Die `reinterpret_cast`-Operation](#link6)
  * [Die `const_cast`-Operation](#link7)
  * [*C-Style-Casts* und *New-Style-Casts*](#link8)
  * [Die `dynamic_cast`-Operation](#link9)
  * [Literatur](#link10)


---

## Einleitung <a name="link1"></a>

<img src="cpp_casts.svg" width="450">

*Abbildung* 1: �berblick �ber die unterschiedlichen Typkonvertierungsm�glichkeiten in C/C++

---

WEITER:

https://web.archive.org/web/20160316114647/http://pvtuts.com/cpp/cpp-type-conversions

https://stackoverflow.com/questions/1609163/what-is-the-difference-between-static-cast-and-c-style-casting#:~:text=In%20short%3A,much%20better%20using%20C%2B%2B%20casts.


https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/

https://stackoverflow.com/questions/103512/why-use-static-casttx-instead-of-tx


---

## Implizite Konvertierungen <a name="link2"></a>

Eine implizite Konvertierung wird vom Compiler automatisch durchgef�hrt, wenn ein Ausdruck in einen seiner kompatiblen Typen konvertiert werden muss.

Beispielsweise k�nnen Konvertierungen zwischen primitiven Datentypen implizit erfolgen.

```cpp
01: long a = 5;      // int implicitly converted to long 
02: double b = 123l; // long implicitly converted to double
```

*Maschinencode*:

```asm
                long a = 5;      // int implicitly converted to long 
00007FF67026C74A  mov         dword ptr [rbp+44h],5  
                double b = 123l; // long implicitly converted to double
00007FF67026C751  movsd       xmm0,mmword ptr [__real@405ec00000000000 (07FF670503070h)]  
00007FF67026C759  movsd       mmword ptr [rbp+68h],xmm0
```

Implizite primitive Konvertierungen k�nnen auch zur Laufzeit durchgef�hrt werden:

```cpp
```

*Maschinencode*:

```asm
                int a = 5;    
00007FF67026C75E  mov         dword ptr [rbp+84h],5  
                long b = 123l; 
00007FF67026C768  mov         dword ptr [rbp+0A4h],7Bh  

                // implicit conversions, done by the machine code
                long n = a;      // int implicitly converted to long 
00007FF67026C772  mov         eax,dword ptr [rbp+84h]  
00007FF67026C778  mov         dword ptr [rbp+0C4h],eax  
                double m = b; // long implicitly converted to double
00007FF67026C77E  cvtsi2sd    xmm0,dword ptr [rbp+0A4h]  
00007FF67026C786  movsd       mmword ptr [rbp+0E8h],xmm0
```

Hier erkennen wir, dass beispielsweise bei der Konvertierung von ganzzahligen Werten nach Gleitpunktwerten
Konvertierungsroutinen zur Laufzeit ausgef�hrt werden m�ssen. Dies kostet Laufzeit!

Diese impliziten primitiven Konvertierungen lassen sich weiter in zwei Arten unterteilen:
*Promotion* und *Demotion* (in etwa &bdquo;*Heraufstufung*&bdquo; und &bdquo;*Herabstufung*&bdquo;).

Eine *Promotion* erfolgt, wenn ein Ausdruck implizit in einen gr��eren Typ konvertiert wird,
und eine *Demotion* erfolgt, wenn ein Ausdruck in einen kleineren Typ konvertiert wird.

```cpp
01: // Promotion
02: long   a = 123;   // int promoted to long
03: double b = 123l;  // long promoted to double
```

Da eine *Demotion* zu Informationsverlust f�hren kann, erzeugen diese Konvertierungen
bei den meisten Compilern eine Warnung:

```cpp
01: // Demotion
02: int  a = 10.5;   // warning: possible loss of data
03: bool b = 123;    // warning: possible loss of data
```

*Output-Window*:

```
warning C4244: 'initializing': conversion from 'double' to 'int', possible loss of data
warning C4305: 'initializing': truncation from 'int' to 'bool'
```

Wenn der potenzielle Informationsverlust beabsichtigt ist,
kann man die Warnung durch eine &bdquo;*explizite*&rdquo; Konvertierung unterdr�cken.

Dies f�hrt uns zum n�chsten Abschnitt:

## Explizite Konvertierungen: C-Style <a name="link3"></a>

Die erste explizite Konvertierung (im engl. &bdquo;*Type Cast*&rdquo;)
ist der aus C �bernommene und wird allgemein als *C-Style-Cast* bezeichnet.

Der gew�nschte Datentyp wird einfach in Klammern links neben dem zu konvertierenden Ausdruck platziert:

```cpp
01: // C-style cast
02: int  a = (int) 123.456;  // double demoted to int
03: bool b = (bool) 123;     // int demoted to char
```


Der *C-Style-Cast* eignet sich f�r die meisten Konvertierungen zwischen primitiven Datentypen.

Bei Konvertierungen zwischen Klassen und Zeigern kann er jedoch zu m�chtig sein.

Um eine bessere Kontrolle �ber die verschiedenen m�glichen Konvertierungsarten zu erhalten,
wurden in C++ vier neue Casts eingef�hrt, die sogenannten *Named Casts* oder *New-Style-Casts*.



## Explizite C++ Konvertierungen <a name="link4"></a>

Die Namen der vier *New-Style-Casts* lauten 

```cpp
static_cast<new_type> (expression) 
reinterpret_cast<new_type> (expression) 
const_cast<new_type> (expression) 
dynamic_cast<new_type> (expression)
```

Wie zu sehen ist, folgt auf den Namen des Casts der neue Typ in spitzen Klammern
und anschlie�end der zu konvertierende Ausdruck in Klammern.

Diese Casts erm�glichen eine pr�zisere Kontrolle �ber die Konvertierung,
was wiederum dem Compiler das Erkennen von Konvertierungsfehlern erleichtert.

*Bemerkung*:<br />
Der *C-Style-Cast* umfasst in einer Definition den `static_cast`, den `reinterpret_cast`
und den `const_cast`.
Bei falscher Anwendung f�hrt dieser Cast daher h�ufiger zu subtilen Konvertierungsfehlern.

### Die `static_cast`-Operation <a name="link5"></a>

Die `static_cast`-Operation f�hrt Konvertierungen zwischen kompatiblen Typen durch.

Er �hnelt dem *C-Style-Cast*, ist aber restriktiver.

Beispielsweise erlaubt der *C-Style-Cast*, dass ein Integer-Zeiger auf eine `char`-Variable zeigt:

```cpp
// C-Style-Cast
char c = 10;       // 1 byte
int* p = (int*)&c; // 4 bytes, compikles, works ?!?
```

Da dies zu einem 4-Byte-Zeiger f�hrt, der auf 1 Byte allokierten Speicher verweist,
f�hrt das Schreiben in diesen Zeiger entweder zu einem Laufzeitfehler oder �berschreibt angrenzenden Speicher:

```cpp
*p = 5;            // run-time error: stack corruption
```

Im Gegensatz zum Cast im *C-Style* erm�glicht der statische Cast dem Compiler, zu �berpr�fen,
ob die *Pointer*- und *Pointee*-Datentypen kompatibel sind,
wodurch der Programmierer diese falsche Zeigerzuweisung w�hrend der Kompilierung erkennen kann:

```cpp
01: // static_cast
02: char c = 10;                    // 1 byte
03: int* p = static_cast<int*>(&c); // 4 bytes
```

Der Compiler reagiert mit der Fehlermeldung <i>Invalid type conversion: 'static_cast': cannot convert from 'char *' to 'int *'</i>.

### Die `reinterpret_cast`-Operation <a name="link6"></a>

Um eine Zeigerkonvertierung zu erzwingen, verwendet man stattdessen die `reinterpret_cast`-Operation.
Dieser arbeitet im Hintergrund auf dieselbe Weise wie der *C-Style-Cast*:

```cpp
01: // reinterpret_cast
02: char c = 10;                           // 1 byte
03: int* p = reinterpret_cast<int*>(&c);   // 4 bytes // compiles
```

Die `reinterpret_cast`-Operation verarbeitet Konvertierungen zwischen bestimmten, nicht verwandten Typen, beispielsweise von einem Zeigertyp in einen anderen, inkompatiblen Zeigertyp.

Er f�hrt lediglich eine bin�re Kopie der Daten durch, ohne das zugrunde liegende Bitmuster zu ver�ndern oder zu interpretieren.

Beachten Sie, dass das Ergebnis einer solchen Low-Level-Operation systemspezifisch und daher nicht portierbar ist.

Diese Cast-Operation  sollte mit Vorsicht verwendet werden, wenn sie sich nicht vollst�ndig vermeiden l�sst.


Ein zweites Beispiel:

```cpp
01: struct MyStruct
02: {
03:     char x1;
04:     char x2;
05:     char x3;
06:     char x4;
07: };
08: 
09: {
10:     struct MyStruct s{ 'A' , 'B' , 'C' , '\0' };
11: 
12:     // reinterpret struct as char* pointer :-) 
13:     char* ptr = reinterpret_cast<char*>(&s);
14: 
15:     std::println("{}", ptr);
16: }
```

*Ausgabe*:

```
ABC
```


### Die `const_cast`-Operation <a name="link7"></a>

Der dritte C++-Cast ist die `const_cast`-Operation.
Sie wird haupts�chlich verwendet, um den `const`-Modifikator einer Variablen hinzuzuf�gen oder zu entfernen.

```cpp
01: const int constVar = 123;
02: int* nonConstIp = const_cast<int*>(&constVar); // removes const
```

Obwohl die `const_cast`-Operation die �nderung des Wertes einer Konstanten erm�glicht,
handelt es sich dabei immer noch um ung�ltigen Code, der einen Laufzeitfehler verursachen kann.

Dies k�nnte beispielsweise der Fall sein, wenn sich die Konstante in einem Bereich des *Read-Only*-Speichers befindet:

```cpp
*nonConstIp = 10; // potential run-time error
```

Die `const_cast`-Operation wird h�ufig dann verwendet,
wenn eine Funktion ein nicht konstantes Zeigerargument annimmt, obwohl sie den Zeiger nicht �ndert:

```cpp
01: void print(int* ptr)
02: {
03:     std::println("{}", *ptr);
04: }
```

Der Funktion kann dann mithilfe einer  `const_cast`-Operation eine konstante Variable �bergeben werden:

```cpp
01: const int constVar = 123;
02: 
03: // print(&constVar);                  // error: cannot convert argument 1 from 'const int*' to 'int*'
04: 
05: print(const_cast<int*>(&constVar));   // compiles, runs
```

---

### *C-Style-Casts* und *New-Style-Casts* <a name="link8"></a>

Beachten Sie, dass der *C-Style-Cast* den `const`-Modifikator ebenfalls entfernen kann.
Da diese Konvertierung jedoch im Hintergrund erfolgt, sind *New-Style-Casts* vorzuziehen.

Ein weiterer Grund f�r die Verwendung von *New-Style-Casts* ist,
dass sie im Quellcode leichter zu finden sind als ein *C-Style-Cast*.

Das ist wichtig, da Typkonvertierungsfehler schwer zu entdecken sein k�nnen.

Ein dritter Grund f�r die Verwendung von *C-Style-Casts* ist deren unkomfortable Schreibweise.

Da explizite Konvertierungen in vielen F�llen vermieden werden k�nnen, wurde dies bewusst so gew�hlt,
dass Entwickler nach einer anderen L�sung suchen.

---

### Die `dynamic_cast`-Operation <a name="link9"></a>

WEITER:

https://web.archive.org/web/20160316114647/http://pvtuts.com/cpp/cpp-type-conversions

---

## Literatur <a name="link10"></a>

---

ALTES ZEUGS

Es wird an mehreren Beispielen die Funktionsweise folgender C++-Typumwandlungen gezeigt:

  * `static_cast`
  * `dynamic_cast`
  * `const_cast`
  * `reinterpret_cast`

Der `static_cast`-Operator ist dazu gedacht, implizit erlaubte Typumwandlungen durchzuf�hren,
die zur �bersetzungszeit stattfinden.

Interessanter ist der `dynamic_cast`-Operator. Er wird zur Laufzeit ausgef�hrt
(von trivialen �berpr�fungen zur �bersetzungszeit einmal abgesehen).

Seine St�rke sind *downcast*-Typwandlungen (*upcast*-Typwandlungen sind trivial).
Kann zur Laufzeit die Typwandlung *nicht* durchgef�hrt werden, liefert der Operator
einen `nullptr` zur�ck. Dies kann man zur Laufzeit abfragen.

Der `const_cast`-Operator wird verwendet,
um die `const`-Eigenschaft von Variablen zu entfernen.

Dies sollte man eigentlich nur im Ausnahmefall machen, denn die urspr�ngliche Vergabe des `const`-Attributs
sollte ja einen Sinn gehabt haben.

Der `reinterpret_cast`-Cast ist der freiz�gigste Cast-Operator von allen: Er *re-interpretiert* eine Variable / ein Objekt
im Sinne des gew�nschten Datentyps. Diese Operation betrifft die Interpretation von Bits (also der Repr�sentation einer Variablen / eines Objekts im Speicher),
ist folglich extrem maschinenabh�ngig und sollte nur selten bzw. sehr bewusst eingesetzt werden.

**Ausgabe** zu `static_cast`-Beispiel:

```cpp
2
This is Base!
This is Derived!
This is Derived!
This is Derived!
This is Derived!
```

**Ausgabe** zu `dynamic_cast`-Beispiel:

```cpp
1
2
3
4
```

**Ausgabe** zu `const_cast`-Beispiel:

```cpp
This is Derived!
This is Derived!
dynamic_cast failed!
This is Base!
```

**Ausgabe** zu `reinterpret_cast`-Beispiel:

```cpp
65
A
ABC
```

---

[Zur�ck](../../Readme.md)

---
