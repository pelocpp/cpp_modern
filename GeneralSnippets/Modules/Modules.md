# Module

[Zurück](../../Readme.md)

---

[Quellcode *Modules.cpp*](Modules.cpp)<br />
[Quellcode *HelloWorldProgram.ixx*](HelloWorldProgram.ixx)<br />
[Quellcode *HelloWorldProgram.cpp*](HelloWorldProgram.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [Nachteile bei der Verwendung von klassischen Header-Dateien](#link2)
  * [Unterschiede im Gebrauch von klassischen Header-Dateien und dem C++ Modul-Konzept](#link3)
  * [Hinweise zu den Dateiendungen](#link4)
  * [ODR &ndash; &bdquo;One Definition Rule&rdquo;](#link5)
  * [Architektur des Modul-Konzepts](#link6)
  * [Import der Standard-Bibliothek STL](#link7)
  * [Ein einfaches Beispiel](#link8)
  * [Modul Partitionen](#link9)
  * [Literaturhinweise](#link10)

---

## Einleitung  <a name="link1"></a>

Im klassischen C++ besteht ein (objekt-orientiertes) Programm aus Header-Dateien,
die Schnittstellen enthalten (Dateiendung *.h*) und Implementierungsdateien,
die den dazugehörigen Programmcode enthalten (Dateiendung *.cpp*).

Ab C++ 20 gibt es das Sprachmittel der *Module*: Darunter versteht man Softwarekomponenten,
die Schnittstelle und Implementierung zusammenfassen (können).
Sie werden unabhängig voneinander übersetzt und können danach von anderen Programmteilen verwendet werden.

---

## Nachteile bei der Verwendung von klassischen Header-Dateien <a name="link2"></a>

Das klassische Modell in der Realisierung eines C++&ndash;Programms
mit einer Aufteilung in Header- und Implementierungsdateien weist einige Nachteile auf:


  * Die Aufteilung in Header- und Implementierungsdatei führt zu doppelt so vielen Dateien im Vergleich dazu,
  wenn man Schnittstelle und Implementierung beispielsweise in einer einzigen Datei ablegen würde.

  * Die Aufteilung einer Funktionalität auf zwei Dateien kann zu Inkonsistenzen führen,
  wenn die Deklaration in der Header-Datei nicht mit derjenigen in der Implementierungsdatei übereinstimmt.

  * Header-interne Definitionen mit `#define` sind in allen nachfolgenden Übersetzungseinheiten
  sichtbar. Das kann Konflikte auslösen (mehrfache Definition eines konstanten Werts `Pi` beispielsweise).

  * Das Inkludieren einer Header-Datei wird mit Makros gesteuert (`#include`).
  Andere Makros wiederum überwachen, dass der Inhalt einer Header-Datei
  nicht zweimal berücksichtigt wird (`#pragma once`).
  Aber auch wenn der Compiler den Inhalt einer Datei beim zweiten Lesen ignoriert (&bdquo;passives Parsen&rdquo;),
  muss er dennoch das zweite Inkludieren dieser Header-Datei
  bis zum Ende durchführen, um zu wissen, wann er wieder in den aktiven Modus des Übersetzens umschalten muss.
  Unnötige lange Compilationszeiten sind die Folge.

  * Header-Dateien müssen bei jeder Übersetzung vom Compiler analysiert (übersetzt) werden.
  Dies verursacht bisweilen lange Übersetzungszeiten.

  * Es kann eine Rolle spielen, in welcher Reihenfolge Header-Dateien mit `#include` eingebunden werden.

  * In einer Header-Datei kann es in Klassendefinitionen mit `private` gekennzeichnete Bereiche geben.
  Diese sind für die Benutzung einer Schnittstelle von außen nicht
  von Bedeutung, sogar unerwünscht. Details von *privater* Natur können vor dem Anwender bei
  Verwendung von Header-Dateien nicht versteckt werden. Aus Sicht eines sauberen
  *objektorientierten Entwurfs/Designs* ist dies wirklich ein unschöner Nebeneffekt.


---

## Unterschiede im Gebrauch von klassischen Header-Dateien und dem C++ Modul-Konzept <a name="link3"></a>

Ein C++&ndash;Modul ist eine eigene Übersetzungseinheit. Hiermit lassen sich folgende Schwächen
des `#include`-Konzepts bereinigen:


  * Schnittstelle und Realisierung einer Klasse lassen sich in einer einzigen (Modul-)Datei ablegen.

  * Schnittstelle und Realisierung einer Klasse kann man mit dem neuen Modul-Konzept auch in zwei Dateien ablegen.
  Dies zieht wiederum die Nachteile in der Verwaltung zweier Dateien nach sich, führt bei
  größeren Modulen jedoch zu einer verbesserten Übersichtlichkeit.  

  * Module kennen das Problem wiedersprüchlicher `#define`-Definitionen nicht.

  *  Bei Modulen liegt das (binäre) Ergebnis nach deren erster bzw. einmaliger Übersetzung vor (Ähnlichkeit zu einem &bdquo;*precompiled*&rdquo; Header vorhanden).
  Auf diese Weise wird Übersetzungszeit eingespart.

  * Module können in beliebiger Reihenfolge importiert werden.

  * In Modulen sind  mit `private` gekennzeichnete Bereiche nicht nach außen sichtbar.



---

## Hinweise zu den Dateiendungen <a name="link4"></a>

Es haben sich bzgl. der verschiedenen Hersteller von C++ Sprachübersetzern unterschiedlichen Endungen für
bestimmte Dateien etabliert:

* Modul-Datei: Dateiendung <b>.mpp</b> &ndash; Visual Studio C++ Compiler: <b>.ixx</b>.

* Built Module Interface (*BMI*) Datei: Dateiendung <b>.bmi</b> &ndash; Visual Studio C++ Compiler: <b>.ifc</b>.


### IFC-Spezifikation


Die IFC-Spezifikation zielt darauf ab, ein binäres Format zur Beschreibung der Semantik von C++-Programmen (oder Programmfragmenten) auf einer hohen Abstraktionsebene formal zu definieren,
bevor es auf Maschinencode oder Ähnliches heruntergebrochen wird.

Dieses Format soll eine persistente Form der speicherinternen Programmdarstellung (*Internal Program Representation*, *IPR*) von C++-Programmen bieten,
die ursprünglich von *Gabriel Dos Reis* und *Bjarne Stroustrup* entwickelt wurde.

Daher folgt es denselben Prinzipien wie die IPR:

  * Vollständigkeit: Stellt die Semantik aller Standard-C++-Konstrukte dar.

  * Allgemeingültigkeit: Geeignet für jede Art von Anwendung, anstatt auf einen bestimmten Anwendungsbereich ausgerichtet zu sein.

  * Regularität: Imitiert keine Unregelmäßigkeiten der C++-Sprache; es werden allgemeine Regeln verwendet, anstatt lange Listen mit Sonderfällen.

  * Typbezogenheit: Jeder Ausdruck hat einen Typ.

  * Minimalität: Keine redundanten Werte, und eine Traversierung beinhaltet keine redundanten Indirektionen.

  * Compilerneutralität: Nicht an einen bestimmten Compiler gebunden.

  * Skalierbarkeit: Kann Hunderttausende von Codezeilen auf gängigen Maschinen darstellen.


Eine detaillierte Beschreibung der IFC-Spezifikation findet man [hier](https://github.com/microsoft/ifc-spec?tab=readme-ov-file#ifc-format-specification).


---

## ODR &ndash; &bdquo;One Definition Rule&rdquo; <a name="link5"></a>


*ODR* ist die Abkürzung für eine wichtige Regel in der C++&ndash;Entwicklung: Die *One Definition Rule*.

Sie besagt, dass keine Übersetzungseinheit mehr als eine Definition einer beliebigen
Variablen, Funktion, eines Klassentyps, Aufzählungstyps, etc. enthalten sollte.

Ein einfaches Beispiel für einen *ODR*-Verstoß:<br />
Eine Übersetzungseinheit (*.cpp*-Datei) inkludiert zwei Header-Dateien,
die beide eine Klasse mit identischem Namen definieren.

Der Compiler würde dann mit einer Fehlermeldung (z.B. *&bdquo;Class Type Redefinition&rdquo;*) reagieren.

Verstöße gegen die *ODR*-Regel werden vom Compiler diagnostiziert und mit entsprechenden Fehlermeldungen versehen.
In manchen Fällen kann der Übersetzer bei Verstößen gegen diese Regel auch schweigen.

Diese möglicherweise unentdeckten *ODR*-Verstöße können zu sehr subtilen Nebenwirkungen und Fehlern in einem Programm führen.

Das neue C++ Modul-Konzept verhindert *ODR*-Verstöße bzw. kann immer mit entsprechenden Fehlermeldungen reagieren.

---

## Architektur des Modul-Konzepts <a name="link6"></a>

Eine Moduldatei wird zunächst in eine *Binary Module Interface* (BMI)-Datei und eine Objektdatei übersetzt.

<img src="cpp_modules_02.svg" width="600">

*Abbildung* 1: Übersetzungsweg bei Verwendung von Moduldateien.

Bevor wir etwas mehr ins Detail gehen, schauen wir uns an, was „hinter den Kulissen“ passiert, wenn ein C++-Modul importiert wird
und was der grundlegende Unterschied zur Einbindung von Header-Dateien ist.

Wie in *Abbildung* 1 dargestellt, ist das Importieren eines Moduls 
keine Kopier- bzw. Einfügeoperation wie beim Einfügen des Inhalts einer Header-Datei.

Wenn der Compiler auf eine Moduldatei stößt &ndash; im Fall von *Abbildung* 1 die Datei mit dem Namen *Library.ixx* &ndash;,
die von einer Übersetzungseinheit (hier: *Main.cpp*) importiert wird,
wird die Moduldatei zuerst in eine *Built Module Interface* (*BMI*)-Datei und eine Objektdatei übersetzt.

Das *BMI*-File ist eine Datei im Dateisystem, die die Metadaten für das Modul enthält
und die exportierte Schnittstelle von *Library.ixx* beschreibt.

Der Compiler erzeugt auch eine Objektdatei (*Library.obj*), die der Linker benötigt,
um eine ausführbare Datei (*Main.exe*) zu erstellen.

Grundsätzlich ist also bei der Verwendung von Modulen ein zusätzlicher Verarbeitungsschritt erforderlich,
um die temporären Dateien *BMI*-Datei und Objektdatei zu generieren.

Der große Vorteil ist jedoch, dass dieser Schritt nur *einmal* ausgeführt werden muss,
unabhängig davon, wie viele Übersetzungseinheiten das Modul importieren.

Wenn Sie beispielsweise überall in Ihrem Programm 

```cpp
import <iostream>
```

anstelle von

```cpp
#include <iostream>
```

verwenden, vermeiden Sie, Tausende von Codezeilen aus dem <iostream>-Header immer wieder zu kompilieren.

Dies bedeutet aber auch, dass wir eine strikte chronologische Reihenfolge haben:<br />
Beim Importieren eines Moduls wird eine zeitliche Abfolge erstellt,
d.h. der Compiler muss das Modul zuerst verarbeiten, um die *BMI*-Datei zu erhalten,
bevor er die Übersetzungseinheiten kompiliert, die das Modul importieren.


---

## Import der Standard-Bibliothek STL <a name="link7"></a>

Mit der Anweisung

```cpp
import std;
```

wird die STL in die aktuelle Übersetzungseinheit importiert.

Dies hat gegenüber der Vorgehensweise mit `#include`&ndash;Direktiven und entsprechenden Header-Dateien
den Vorteil, dass sich die Kompilierungszeiten je nach Größe des Programms erheblich verkürzen.

Dazu wird allerdings &ndash; in Bezug auf den Visual C++ Compiler &ndash; eine Datei `std.ixx` 
im Programm benötigt. Diese muss man nicht selbst erstellen, sie ist in einer Visual C++ Installation
in folgendem Verzeichnis vorhanden:

<pre>
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.35.32215\modules\std.ixx
</pre>

---

## Ein einfaches Beispiel <a name="link8"></a>

Das nachfolgende Programmfragment (*Code-Listing* 1) zeigt die Einbindung eines Moduls
`hello_world` mit der `import`-Anweisung. 
Das Modul exportiert einen Namensraum `MyHelloWorld`.
Auf diese Weise stehen eine globale Variable `globalData` und eine globale Funktion `sayHello`
zur Verfügung.
Ein Aufruf von `main()` gibt

<pre>
Hello Module! Data is 123
</pre>

auf der Standardausgabe `std::cout` aus. Dabei muss in `main()` keine `#include`-Anweisung
vorhanden sein: Das Modul bringt alles Notwendige mit:


```cpp
01: // File: HelloWorldProgram.cpp
02: 
03: import hello_world;
04: 
05: int main()
06: {
07:     MyHelloWorld::globalData = 123;
08: 
09:     MyHelloWorld::sayHello();
10: 
11:     return 0;
12: }
```

*Code-Listing* 1: Einbindung eines Moduls.


```cpp
01: // File: HelloWorldProgram.ixx
02: 
03: export module hello_world;
04: 
05: import std;
06: 
07: export namespace MyHelloWorld
08: {
09:     int globalData{};
10: 
11:     void sayHello()
12:     {
13:         std::printf("Hello Module! Data is %d\n", globalData);
14:     }
15: }

```

*Code-Listing* 2: Definition/Implementierung eines Moduls.


Der Effekt des Importierens eines Moduls besteht darin, die in dem Modul deklarierten
exportierten Entitäten (hier: Namensraum `MyHelloWorld`) für die importierende Übersetzungseinheit sichtbar zu machen.


---

## Modul Partitionen <a name="link9"></a>

Genau wie bei C++&ndash;Headerdateien müssen Module nicht zwingend aufgeteilt werden,
also deren Inhalt nicht auf mehrere Dateien verteilt werden.
Trotzdem können große Quelldateien unhandlich werden, sodass C++&ndash;Module auch eine Möglichkeit bieten,
ein einzelnes Modul in verschiedene Übersetzungseinheiten zu unterteilen.
Diese Unterteilungen werden als *Partitionen* bezeichnet.

Eine *Partition* wiederum kann aus einer oder aus mehreren Dateien bestehen.
Hierbei unterscheidet man *Module Interface Units* und *Module Implementation Units*:

Eine *Module Interface Unit* kann es nur einmal geben, die dazugehörigen
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

*Code-Listing* 4: Primäre Modulschnittstelle: Modul `modern_cpp`. 


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
01: // Module Implementation Partition: File SharedPtr.cpp
02: module modern_cpp:shared_ptr;
03: 
04: namespace SharedPointer {
05: 
06:     void test_shared_ptr ()
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
22:     test_shared_ptr ();
23:     test_02_shared_ptr ();
24:     test_03_shared_ptr ();
25: }
```

*Code-Listing* 6: Modulimplementierungspartition / &bdquo;*Module Implementation Partition*&rdquo;: Partition `:shared_ptr`.


---

## Literaturhinweise <a name="link10"></a>

Die Anregungen zu diesem Code-Snippet finden sich teilweise in

[Understanding C++ Modules: Part 1: Hello Modules, and Module Units](https://vector-of-bool.github.io/2019/03/10/modules-1.html)<br>(abgerufen am 22.04.2023)

vor. Eine andere, empfehlenswerte Beschreibung stammt von Simon Toth:

[C++20 Modules &ndash; Complete Guide](https://itnext.io/c-20-modules-complete-guide-ae741ddbae3d)<br>(abgerufen am 22.04.2023)


---

[Zurück](../../Readme.md)

---
