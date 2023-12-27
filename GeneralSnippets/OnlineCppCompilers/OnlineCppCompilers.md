# Online C++ Compiler

[Zur�ck](../../Readme.md)

---

## Allgemeines

Unter [List of Online C++ Compilers](https://arnemertz.github.io/online-compilers/)
findet man eine Liste mit Informationen zu verf�gbaren C++ Online Compilern und ihren wichtigsten Funktionen vor.
Auch unterst�tzen viele dieser WebSites andere Sprachen als C++,
war f�r unsere Zwecke jedoch nicht weiter von Bedeutung ist.
Je nach Version des verwendeten Compilers stehen unterschiedliche Versionen des C++&ndash;Standards bzw. &ndash;Sprachumfangs zur Verf�gung.

Neben der blo�en Kompilierung f�hren die meisten Online-Compiler auch das kompilierte Programm aus.
Die M�glichkeiten, die Kompilierung �ber Compiler-Flags zu parametrisieren,
Kommandozeilen- und/oder Laufzeitparameter an das ausgef�hrte Programm zu �bergeben und Eingaben f�r den Standard-Input bereitzustellen,
variieren zwischen den verschiedenen WebSites.

Es folgen einige Details zu drei sehr popul�ren Online C++ Compilern.

---

### Wandbox

[Wandbox](https://wandbox.org/) bietet so ziemlich alle Funktionen, die Sie sich von einem typischen Online-Compiler w�nschen,
einschlie�lich der Unterst�tzung mehrerer Dateien und verschiedener Editor-Tastenkombinationen.
Neben der Standardbibliothek werden einige zus�tzliche Bibliotheken unterst�tzt,
darunter *Boost* (bis zu 1.64), *Sprout* und *MessagePack*.
Die kompilierten Programme laufen in einer Sandbox-Umgebung,
die Datei-I/O erm�glicht. Die mitgelieferten Snapshot-Versionen von *GCC* und *Clang* erm�glichen das Spielen
mit den neuesten C++17/20&ndash;Features.

<img src="Wandbox.png" width="800">

*Abbildung* 1: Oberfl�che des Online Compilers &bdquo;Wandbox&rdquo;.

**Hinweis**:
Ein gro�artiges Feature des Wandbox Online Compilers ist seine F�higkeit,
ein Programm auf mehrere Dateien aufteilen zu k�nnen:

  * Um mehr als nur eine Quellcodedatei zu erstellen, klickt man auf das gro�e fettgedruckte &bdquo;+&rdquo;-Zeichen
  direkt �ber Zeile 1 des Quellcodefensters, direkt au�erhalb des Textfelds.
  Dadurch wird eine neue Registerkarte mit dem Namen *"noname-1"* erstellt.
  Diese Registerkarte repr�sentiert eine neue Quellcodedatei:

<img src="WandboxOptions01.png" width="280">

*Abbildung* 2: Mehrere Quellcodedateien f�r ein Programm.

  * Diese Quellcodedatei versieht man mit einem richtigen Namen.
  Man klickt dazu auf *"noname-1"*, um zu dieser Registerkarte zu wechseln,
  und klickt dann erneut auf *"noname-1"*. Der Name wird editierbar,
  nennen wir sie beispielsweise &bdquo;Time.cpp&rdquo;.

  * Wenn wir jetzt auf &bdquo;Run&rdquo; klicken, kompiliert Wandbox nur den Code in der Hauptdatei!
  Die zus�tzliche Datei &bdquo;Time.cpp&rdquo; wird nicht ber�cksichtigt.
  Um Wandbox dazu zu bringen, &bdquo;Time.cpp&rdquo; zusammen mit der Hauptdatei zu kompilieren
  und auszuf�hren (eigentlich sollten wir von *Linken* sprechen),
  m�ssen wir &bdquo;Time.cpp&rdquo; zur Compiler-Befehlszeile hinzuf�gen!

  * Dazu gibt es ein Texteingabefeld f�r &bdquo;Compiler Options:&rdquo;
  Es befindet sich in der linken Seitenleiste.
  Jede Zeile mit Optionen wird zu einem einzigen Argument f�r den Compiler.
  Wenn wir nun zus�tzliche Codedateien hinzuzuf�gen, m�ssen wir nur die Namen dieser Dateien einfach
  reinschreiben:

<img src="WandboxOptions02.png" width="280">

*Abbildung* 3: Optionen des Compilers.

Und noch ein letzer Hinweis: Zum Ausf�hren des Programms muss man nicht immer umst�ndlich
in den unteren Abschnitt des Fensters navigieren. Der Short-Cut &bdquo;*Control - Enter*&rdquo;
f�hrt dieselbe Aufgabe aus.

<img src="WandboxOptions03.png" width="650">

*Abbildung* 4: Tastatur-Shortcut zur Programmausf�hrung.

---

### Compiler Explorer (Godbolt)

[Compiler Explorer](https://godbolt.org/) ist eine &bdquo;*compile-as-you-type*&rdquo; IDE mit einer besonderen Funktion,
da sie den von den Compilern erzeugten Assemblercode darstellt.
Der resultierende Assemblercode kann dem urspr�nglichen C++-Code farblich zugeordnet werden.
*Compiler Explorer* unterst�tzt die gleichzeitige Verwendung verschiedener Quellen und mehrerer Compiler,
sodass wir den Assemblercode, der von verschiedenen Compilern, mit unterschiedlichene Optimierungsflags usw. erzeugt wird,
vergleichen k�nnen. Der Compiler-Explorer ist auf GitHub zu finden und kann lokal verwendet werden.

<img src="CompilerExplorer.png" width="800">

*Abbildung* 5: Oberfl�che des Online Compilers &bdquo;Compiler Explorer&rdquo;.

---

### Cppinsights

[Cppinsights](https://cppinsights.io/) ist weniger eine Online-IDE im herk�mmlichen Sinne,
denn sie erlaubt es nicht, kompilierte Programme auszuf�hren.
Stattdessen zeigt die IDE eine andere Version des Quellcodes, die einen Teil der Magie zeigt,
die der Compiler unter der Haube macht. Man k�nnte auch sagen, dass *Cppinsights* eine Art
&bdquo;C++ nach C++&rdquo;&ndash;Pr�compiler mit dem Ziel ist, den urspr�nglichen Quellcode besser verst�ndlich umzuwandeln.
*Cppinsights* ist ein Tool geschrieben von [Andreas Fertig](https://andreasfertig.info/).

<img src="Cppinsights.png" width="800">

*Abbildung* 6: Oberfl�che des Online Compilers &bdquo;Cppinsights&rdquo;.

---

[Zur�ck](../../Readme.md)

---
