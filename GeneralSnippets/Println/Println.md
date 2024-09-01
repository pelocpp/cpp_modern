# The Return of &bdquo;`printf`&rdquo;: `std::print(ln)` in C++ 23

[Zurück](../../Readme.md)

---

[Quellcode](Println.cpp)

---

## Überblick

&bdquo;`printf`&rdquo;: Wer hat sie nicht vermisst? Die C-Bibliotheksfunktion war uns doch &ndash; trotz all ihrer Schwächen &ndash; 
sehr ans Herz gewachsen.

<img src="StdPrintln.png" width="400">

<sup>(Credits: Found in [std::print in C++23](https://vitaut.net/posts/2023/print-in-cpp23/) from *Victor Zverovic*)</sup>

*Abbildung* 1: The Return of &bdquo;`printf`&rdquo;: `std::print` ab C++ 23.

In C++ 23 ist sie zurückgekehrt, und wenn wir so wollen: Stärker denn je zuvor!
Typsicherheit, Erweiterbarkeit, Unterstützung von Unicode und Performanz sind 
einige der Stärken der neuen Funktionen `std::print` und  `std::println`.
Darüber hinaus weisen sie große Ähnlichkeiten zu `printf` auf!

---

## Dokumentation

Eine genaue Beschreibung der Formatzeichenkette findet man in der
&bdquo;[Standard Format Specification](https://en.cppreference.com/w/cpp/utility/format/spec)&rdquo; wieder.
Aus diesem Grund macht es wenig Sinn, hier die Spezifikation zu wiederholen.

Ich versuche, mit einer Reihe möglichst ausdrucksstarker Beispiele die wesentlichen Features der `std::print(ln)`
Funktion vorzustellen:

  * Teil 1: Standardformatspezifikation
  Für elementare Datentypen und Stringtypen basiert die Formatspezifikation auf der Formatspezifikation von Python.

  * Teil 2: `std::print` mit benutzerdefinierten Typen verwenden
  Neben den elementaren Datentypen kann man auch `std::print` für benutzerdefinierte Typen einsetzen.


Um `std::print` für einen benutzerdefinierten Datentyp benötigt man
das Klassentemplate `std::formatter<T, CharT>`:

Die einzelnen Schritte sehen nun so aus:


  * Definieren Sie eine Spezialisierung der Klasse `std::formatter<T, CharT>` im Namensraum `std`.
  * Implementieren Sie die Methode `parse()`, um den Teil der Formatzeichenfolge zu analysieren, der dem aktuellen Argument entspricht. Wenn die Spezialisierung der Klasse `std::formatter<T, CharT>` von einem anderen Formatierer erbt, kann diese Methode weggelassen werden.
  * Implementieren Sie die Methode `format()`, um das Argument zu formatieren und die Ausgabe über `format_context` zu schreiben.

Sie finden auch hierzu im Beispielcode eine Reihe von Beispielen vor.


---

## Beispiele

### Ausgabe elementarer Datentypen


*Beispiel*:

```cpp
01: test()
02: {
03:     std::println("Hello, world!");
04: }
```

*Ausgabe*:

```
Hello, world!
```

---

*Beispiel*:

```cpp
01: test()
02: {
03:     int value{ 123 };
04:     std::println("Value: {}", value);
05: }
```

*Ausgabe*:

```
Value: 123
```

---

*Beispiel*:

```cpp
01: void test()
02: {
03:     int firstValue{ 123 };
04:     int secondValue{ 456 };
05: 
06:     std::println("First Value: {}, Second Value: {}", firstValue, secondValue);
07:     std::println("First Value: {0}, Second Value: {1}", firstValue, secondValue);
08: }
```

*Ausgabe*:

```
First Value: 123, Second Value: 456
First Value: 123, Second Value: 456
```

---

*Beispiel*: *Fill and Align*

```cpp
01: void test()
02: {
03:     int value{ 123 };
04: 
05:     std::println("{}", value);             // "123"
06:     std::println("{0}", value);            // "123"
07:     std::println("{:10}", value);          // "       123"
08:     std::println("!{:_<10}!", value);      // "!123_______!"
09:     std::println("!{:_>10}!", value);      // "!_______123!"
10: }
```

*Ausgabe*:

```
123
123
       123
!123_______!
!_______123!
```

---

*Beispiel*: *Fill, Align and Precision*

```cpp
01: void test()
02: {
03:     int value{ 123 };
04: 
05:     std::println("{}", value);             // "123"
06:     std::println("{:d}", value);           // "123"
07:     std::println("{:010}", value);         // "0000000123"
08:     std::println("{:010d}", value);        // "0000000123"
09:     std::println("{:0}", value);           // "123"
10:     std::println("{:+}", value);           // "+123"
11:     std::println("{:+}", -value);          // "-123"
12:     std::println("{:+10}", value);         // "      +123"
13:     std::println("{:+10}", -value);        // "      -123"
14:     std::println("{:+010}", value);        // "+000000123"
15:     std::println("{:+010}", -value);       // "-000000123"
16: }
```

*Ausgabe*:

```
123
123
0000000123
0000000123
123
+123
-123
      +123
      -123
+000000123
-000000123
```

---


*Beispiel*: *Fill, Align and Precision*

```cpp
01: void test()
02: {
03:     float pi{ 3.1415926535f };
04: 
05:     std::println("{}", pi);                // "3.1415927"
06:     std::println("{0}", pi);               // "3.1415927"
07:     std::println("{:15f}", pi);            // "       3.141593"    (width = 15)
08:     std::println("{:{}f}", pi, 15);        // "       3.141593"    (width = 15)
09:     std::println("{:.12f}", pi);           // "3.141592741013"     (precision = 12)
10:     std::println("{:.{}f}", pi, 3);        // "3.142"              (precision = 3)
11:     std::println("{:15.12f}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
12:     std::println("{:{}.{}f}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
13: }
```

*Ausgabe*:

```
3.1415927
3.1415927
       3.141593
       3.141593
3.141592741013
3.142
 3.141592741013
 3.141592741013
```

---


*Beispiel*: *Fill, Align and Precision*

```cpp
01: static void test_07()
02: {
03:     double pi{ 3.1415926535f };
04: 
05:     std::println("{}", pi);                // "3.1415927"
06:     std::println("{0}", pi);               // "3.1415927"
07:     std::println("{:15g}", pi);            // "       3.141593"    (width = 15)
08:     std::println("{:{}g}", pi, 15);        // "       3.141593"    (width = 15)
09:     std::println("{:.12g}", pi);           // "3.141592741013"     (precision = 12)
10:     std::println("{:.{}g}", pi, 3);        // "3.142"              (precision = 3)
11:     std::println("{:15.12g}", pi);         // " 3.141592741013"    (width = 15, precision = 12)
12:     std::println("{:{}.{}g}", pi, 15, 12); // " 3.141592741013"    (width = 15, precision = 12)
13: }

```

*Ausgabe*:

```
3.1415927410125732
3.1415927410125732
        3.14159
        3.14159
3.14159274101
3.14
  3.14159274101
  3.14159274101
```

---


*Beispiel*: *Sign, #, and different Formats*

```cpp
01: static void test_08()
02: {
03:     std::println("Hexadecimal:  {:x}", 6);      // "Hexadecimal:  6"
04:     std::println("Hexadecimal:  {:x}", 30);     // "Hexadecimal: 1e"
05:     std::println("Hexadecimal:  {:X}", 30);     // "Hexadecimal: 1E"
06:     std::println("Hexadecimal:  {:#x}", 30);    // "Hexadecimal: 0x1e"
07:     std::println("Hexadecimal:  {:#X}", 30);    // "Hexadecimal: 0X1E"
08:     std::println("Hexadecimal:  {:15x}", 6);    // "Hexadecimal:               6"   (width = 15)
09:     std::println("Hexadecimal:  {:#15X}", 30);  // "Hexadecimal:            0X1E"   (width = 15)
10: 
11:     std::println("Octal:        {:o} ", 12);    // "Octal:       14"
12:     std::println("Octal:        {:#o} ", 12);   // "Octal:       014"
13:     std::println("Octal:        {:#o}", 4);     // "Octal:       04"
14: 
15:     std::println("Binary:       {:b} ", 31);    // "Binary:      11111"
16:     std::println("Binary:       {:#b} ", 31);   // "Binary:      0b11111"
17:     std::println("Binary:       {:#B}", 7);     // "Binary:      0B111"
18:     std::println("Binary:       {:#15b} ", 31); // "Binary:              0b11111"   (width = 15)
19:     std::println("Binary:       {:#15B}", 7);   // "Binary:                0B111"   (width = 15)
20: }
```

*Ausgabe*:

```
Hexadecimal:  6
Hexadecimal:  1e
Hexadecimal:  1E
Hexadecimal:  0x1e
Hexadecimal:  0X1E
Hexadecimal:                6
Hexadecimal:             0X1E
Octal:        14
Octal:        014
Octal:        04
Binary:       11111
Binary:       0b11111
Binary:       0B111
Binary:               0b11111
Binary:                 0B111
```


### Ausgabe elementarer Datentypen











*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```









*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```









*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```








*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```










---

## Literaturhinweise:

Die Anregungen zu den Beispielen stammen teilweise bzw. in modifizierter Form aus

[`std::format` in C++ 20](https://www.heise.de/developer/artikel/std-format-in-C-20-4919132.html)

von Rainer Grimm und Peter Gottschling.

---

[Zurück](../../Readme.md)

---
