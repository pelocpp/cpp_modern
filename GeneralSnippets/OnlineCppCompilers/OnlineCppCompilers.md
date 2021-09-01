# Online C++ Compiler

[Zurück](../../Readme.md)

---

## Allgemeines

Unter [List of Online C++ Compilers](https://arnemertz.github.io/online-compilers/)
findet man eine Liste mit Informationen zu verfügbaren C++ Online Compilern und ihren wichtigsten Funktionen vor.
Auch unterstützen viele dieser WebSites andere Sprachen als C++,
war für unsere Zwecke jedoch nicht weiter von Bedeutung ist.
Je nach Version des verwendeten Compilers stehen unterschiedliche Versionen des C++&ndash;Standards bzw. &ndash;Sprachumfangs zur Verfügung.

Neben der bloßen Kompilierung führen die meisten Online-Compiler auch das kompilierte Programm aus.
Die Möglichkeiten, die Kompilierung über Compiler-Flags zu parametrisieren,
Kommandozeilen- und/oder Laufzeitparameter an das ausgeführte Programm zu übergeben und Eingaben für den Standard-Input bereitzustellen,
variieren zwischen den verschiedenen WebSites.

Es folgen einige Details zu drei sehr populären Online C++ Compilern.

---

### Wandbox

[Wandbox](https://wandbox.org/) bietet so ziemlich alle Funktionen, die Sie sich von einem typischen Online-Compiler wünschen,
einschließlich der Unterstützung mehrerer Dateien und verschiedener Editor-Tastenkombinationen.
Neben der Standardbibliothek werden einige zusätzliche Bibliotheken unterstützt,
darunter *Boost* (bis zu 1.64), *Sprout* und *MessagePack*.
Die kompilierten Programme laufen in einer Sandbox-Umgebung,
die Datei-I/O ermöglicht. Die mitgelieferten Snapshot-Versionen von *GCC* und *Clang* ermöglichen das Spielen
mit den neuesten C++17/20&ndash;Features.

<img src="Wandbox.png" width="800">

*Abbildung* 1: Oberfläche des Online Compilers &ldquo;Wandbox&rdquo;.

---

### Compiler Explorer (Godbolt)

[Compiler Explorer](https://godbolt.org/) ist eine &ldquo;*compile-as-you-type*&rdquo; IDE mit einer besonderen Funktion,
da sie den von den Compilern erzeugten Assemblercode darstellt.
Der resultierende Assemblercode kann dem ursprünglichen C++-Code farblich zugeordnet werden.
*Compiler Explorer* unterstützt die gleichzeitige Verwendung verschiedener Quellen und mehrerer Compiler,
sodass wir den Assemblercode, der von verschiedenen Compilern, mit unterschiedlichene Optimierungsflags usw. erzeugt wird,
vergleichen können. Der Compiler-Explorer ist auf GitHub zu finden und kann lokal verwendet werden.

<img src="CompilerExplorer.png" width="800">

*Abbildung* 2: Oberfläche des Online Compilers &ldquo;Compiler Explorer&rdquo;.

---

### Cppinsights

[Cppinsights](https://cppinsights.io/) ist weniger eine Online-IDE im herkömmlichen Sinne,
denn sie erlaubt es nicht, kompilierte Programme auszuführen.
Stattdessen zeigt die IDE eine andere Version des Quellcodes, die einen Teil der Magie zeigt,
die der Compiler unter der Haube macht. Man könnte auch sagen, dass *Cppinsights* eine Art
&ldquo;C++ nach C++&rdquo;&ndash;Präcompiler mit dem Ziel ist, den ursprünglichen Quellcode besser verständlich umzuwandeln.
*Cppinsights* ist ein Tool geschrieben von [Andreas Fertig](https://andreasfertig.info/).

<img src="Cppinsights.png" width="800">

*Abbildung* 3: Oberfläche des Online Compilers &ldquo;Cppinsights&rdquo;.

---

[Zurück](../../Readme.md)

---
