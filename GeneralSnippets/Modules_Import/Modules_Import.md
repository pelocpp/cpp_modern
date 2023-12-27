# Module

[Zur�ck](../../Readme.md)

---

[Quellcode](Modules_Import.cpp)

---

## Einleitung

Im klassischen C++ besteht ein (objekt-orientiertes) Programm aus Header-Dateien,
die Schnittstellen enthalten (Dateiendung *.h*) und Implementierungsdateien,
den den dazugeh�rigen Programmcode enthalten (Dateiendung *.cpp*).

Ab C++ 20 gibt es das Sprachmittel der *Module*: Darunter versteht man Softwarekomponenten,
die Schnittstelle und Implementation zusammenfassen (k�nnen).
Sie werden unabh�ngig voneinander �bersetzt und k�nnen danach von anderen Programmteilen verwendet werden.

---

## Unterschiede zwischen Header-Dateien und Modulen

Ein Modul ist eine eigene �bersetzungseinheit.
Das klassische Modell der Aufteilung in Header- und Implementierungsdateien weist einige Nachteile auf:

  * Die Aufteilung in Header- und Implementierungsdatei f�hrt zu doppelt so vielen Dateien im Vergleich dazu,
  wenn man Schnittstelle und Implementation beispielsweise in einer einzigen (Modul-)Datei ablegt.

  * Eine Aufteilung einer Funktionalit�t auf zwei Dateien kann zu Inkonsistenzen f�hren, wenn die Deklaration in der
  Header-Datei nicht mit derjenigen in der Implementierungsdatei �bereinstimmt. Bei
  Modulen kann dieses Problem nicht auftreten.

  * Header-interne Definitionen mit `#define` sind in allen nachfolgenden �bersetzungseinheiten
  sichtbar. Das kann Konflikte ausl�sen. Module vermeiden dieses Problem.

  * Das Inkludieren einer Header-Dateien wird mit Makros gesteuert (`#include`).
  Andere Makros wiederum �berwachen, dass der Inhalt einer Header-Datei
  nicht zweimal ber�cksichtigt wird (`#pragma once`).
  Aber auch wenn der Compiler den Inhalt ignoriert (&bdquo;passives Parsen&rdquo;),
  muss er dennoch das zweite Inkludieren dieser Header-Datei
  bis zum Ende durchf�hren, um zu wissen, wann er wieder in den aktiven Modus des �bersetzens umschalten muss.
  Unn�tige l�ngere Compilationszeiten sind die Folge.

  * Header-Dateien m�ssen bei jeder �bersetzung vom Compiler analysiert werden. Bei
  Modulen liegt das bin�re Ergebnis nach deren einmaliger �bersetzung vor (&bdquo;*precompiled*&rdquo; Header).
  Auf diese Weise wird �bersetzungszeit eingespart.

  * Es kann eine Rolle spielen, in welcher Reihenfolge Header-Dateien mit `#include` eingebunden werden.
  Module k�nnen in beliebiger Reihenfolge importiert werden.

  * In einer Header-Datei kann es in Klassendefinitionen mit `private` gekennzeichnete Bereiche geben.
  Diese sind f�r die Benutzung einer Schnittstelle von au�en nicht
  von Bedeutung, sogar unerw�nscht. Details von *privater* Natur k�nnen vor dem Anwender bei
  Verwendung von Header-Dateien nicht wirklich versteckt werden.
  In Modulen sind solche Bereiche nach au�en nicht sichtbar.


---

## Import der Standard-Bibliothek STL mit Visual C++

Obwohl dies nicht im C++ 20-Standard festgelegt ist,
erm�glicht es die Erstellung eines C++ Programms mit dem Visual C++ Compiler,
dass die C++&ndash;Standardbibliothek als Modul mit dem Namen &bdquo;**std**&rdquo; importiert werden kann.

Dies hat gegen�ber der Vorgehensweise mit `#include`&ndash;Direktiven und entsprechenden Header-Dateien
den Vorteil, dass sich die Kompilierungszeiten je nach Gr��e des Programms erheblich verk�rzen.

#### Anweisung `import std;`

Mit der Anweisung

<pre>
import std;
</pre>

wird die STL in die aktuelle �bersetzungseinheit importiert.

Dazu wird allerdings &ndash; in Bezug auf den Visual C++ Compiler &ndash; eine Datei `std.ixx` 
im Programm ben�tigt. Diese muss man nicht selbst erstellen, sie ist in einer Visual C++ Installation
in folgendem Verzeichnis vorhanden:

<pre>
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.35.32215\modules\std.ixx
</pre>


<b>Update</b>:
Ab Visual Studio 17.6.2 (m�glicherweise auch einige Versionen darunter) ist das explizite
Hinzuf�gen der `std.ixx`-Datei zum Projekt **nicht** mehr erforderlich!


Wenn wir den Quellcode der Datei `std.ixx` betrachten, erkennen wir im nachfolgenden Ausschnitt
in Zeile 17 die Definition des Modulnamens `std`:

<pre>
01: // Copyright (c) Microsoft Corporation.
02: // SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
03: 
04: // This named module expects to be built with classic headers, not header units.
05: #define _BUILD_STD_MODULE
06: 
07: module;
08: 
09: // The subset of "C headers" [tab:c.headers] corresponding to
10: // the "C++ headers for C library facilities" [tab:headers.cpp.c]
11: #include <assert.h>
12: #include <ctype.h>
13: ...
14: #include <wchar.h>
15: #include <wctype.h>
16: 
<b>17: export module std;</b>
18: 
19: #pragma warning(push)
20: #pragma warning(disable : 5244) // '#include <meow>' in the purview of module 'std' appears erroneous.
21: 
22: // "C++ library headers" [tab:headers.cpp]
23: #include <algorithm>
24: #if _HAS_STATIC_RTTI
25: #include <any>
26: #endif // _HAS_STATIC_RTTI
27: #include <array>
28: #include <atomic>
29: ...
30: #include <variant>
31: #include <vector>
32: #include <version>
33: 
34: // "C++ headers for C library facilities" [tab:headers.cpp.c]
35: #include <cassert>
36: #include <cctype>
37: ...
38: #include <cwchar>
39: #include <cwctype>
40: 
41: #pragma warning(pop)
</pre>

---

## Ein einfaches Beispiel

Das nachfolgende Programmfragment (*Code-Listing* 1) zeigt die Einbindung eines Moduls
`hello_world` mit der `import`-Anweisung. 
Das Modul exportiert einen Namensraum `MyHelloWorld`.
Auf diese Weise stehen eine globale Variable `globalData` und eine globale Funktion `sayHello`
zur Verf�gung.
Ein Aufruf von `main()` gibt

<pre>
Hello Module! Data is 123
</pre>

auf der Standardausgabe `std::cout` aus. Dabei muss in `main()` keine `#include`-Anweisung
vorhanden sein: Das Modul bringt alles Notwendige mit:


```cpp
01: /// Program.cpp
02: import hello_world;
03: 
04: int main()
05: {
06:     MyHelloWorld::globalData = 123;
07: 
08:     MyHelloWorld::sayHello();
09: }
```

*Code-Listing* 1: Einbindung eines Moduls.


```cpp
01: /// HelloWorld.ixx
02: export module hello_world;
03: 
04: import std;
05: 
06: export namespace MyHelloWorld
07: {
08:     int globalData{};
09: 
10:     void sayHello()
11:     {
12:         std::cout << "Hello Module! Data is " << globalData << std::endl;
13:     }
14: }
```

*Code-Listing* 2: Definition/Implementierung eines Moduls.


Der Effekt des Importierens eines Moduls besteht darin, die in dem Modul deklarierten
exportierten Entit�ten (hier: Namensraum `MyHelloWorld`) f�r die importierende �bersetzungseinheit sichtbar zu machen.


---

## Modul Partitionen

Genau wie bei C++&ndash;Headerdateien m�ssen Module nicht zwingend aufgeteilt werden,
also deren Inhalt nicht auf mehrere Dateien verteilt werden.
Trotzdem k�nnen gro�e Quelldateien unhandlich werden, sodass C++&ndash;Module auch eine M�glichkeit bieten,
ein einzelnes Modul in verschiedene �bersetzungseinheiten zu unterteilen.
Diese Unterteilungen werden als *Partitionen* bezeichnet.

Eine *Partition* wiederum kann aus einer oder aus mehreren Dateien bestehen.
Hierbei unterscheidet man *Module Interface Units* und *Module Implementation  Units*:

Eine *Module Interface Unit* kann es nur einmal geben, die dazugeh�rigen
*Module Implementation Units* wiederum lassen sich auf mehrere Dateien aufteilen:


```cpp
01: /// Program.cpp
02: import modern_cpp;
03: 
04: import std;
05: 
06: int main()
07: {
08:     main_shared_ptr(); 
09:     main_unique_ptr();
10:     main_weak_pointer();
11:     ...
12:     return 0;
13: }
```

*Code-Listing* 3: Hauptprogramm.


```cpp
/// Module_Modern_Cpp.ixx
export module modern_cpp;

export import :shared_ptr;
export import :unique_ptr;
export import :weak_ptr;
....
```

*Code-Listing* 4: Prim�re Modulschnittstelle: Modul `modern_cpp`. 


```cpp
01: /// Module Interface Partition: File Module_SharedPtr.ixx
02: export module modern_cpp:shared_ptr;
03: 
04: import std;
05: 
06: export void main_shared_ptr();
```

*Code-Listing* 5: Modulschnittstellenpartition / &bdquo;*Module Interface Partition*&rdquo;: Partition `:shared_ptr`.


```cpp
01: /// Module Implementation Partition: File SharedPtr.cpp
02: module modern_cpp:shared_ptr;
03: 
04: namespace SharedPointer {
05: 
06:     void test_01_shared_ptr ()
07:     { ...
08:     }
09: 
10:     void test_02_shared_ptr () 
11:     { ...
12:     }
13: 
14:     void test_03_shared_ptr ()
15:     { ...
16:     }
17: }
18: 
19: void main_shared_ptr()
20: {
21:     using namespace SharedPointer;
22:     test_01_shared_ptr ();
23:     test_02_shared_ptr ();
24:     test_03_shared_ptr ();
25: }
```

*Code-Listing* 6: Modulimplementierungspartition / &bdquo;*Module Implementation Partition*&rdquo;: Partition `:shared_ptr`.


---

## Literaturhinweise:

Die Anregungen zu diesem Code-Snippet finden sich teilweise in

[Understanding C++ Modules: Part 1: Hello Modules, and Module Units](https://vector-of-bool.github.io/2019/03/10/modules-1.html)<br>(abgerufen am 22.04.2023)

vor. Eine andere, empfehlenswerte Beschreibung stammt von Simon Toth:

[C++20 Modules &ndash; Complete Guide](https://itnext.io/c-20-modules-complete-guide-ae741ddbae3d)<br>(abgerufen am 22.04.2023)


---

[Zur�ck](../../Readme.md)

---
