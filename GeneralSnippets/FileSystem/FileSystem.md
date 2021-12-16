# C++17 File System

[Zurück](../../Readme.md)

---

[Quellcode](FileSystem.cpp)

---

## Allgemeines

Die Bibliothek für das C++17 File System befindet sich in der Header-Datei `<filesystem>`.
Es wird der Namensraum `std::filesystem` verwendet.

Im wesentlichen werden in dieser Bibliothek die folgenden Kernaspekte eines Dateihandlings abgedeckt:

  * Die `path` Klasse
  * Die `directory_entry` Klasse
  * Iteratoren für Verzeichnisse
  * Support-Funktionen:
    *  Informationsfunktionen zu `path`-Objekten
    *  Dateimanipulationen: Kopieren, Verschieben, Erstellen, Symbolische Links
    *  Zeitstempel
    *  Berechtigungen
    *  Speicherplatz / Dateigröße
    *  ...

In den Beispiele dieses Code-Snippets werden folgende Teilaspakte des C++17 Filesystems veranschaulicht:

  * `path`-Objekt analysieren
  * Iterieren über ein `path`-Objekt
  * Dateigröße berechnen
  * rekursives Traversieren eines Verzeichnisses

---

#### Hinweis:

Viele der Funktionen, die auf einem `path`-Objekt arbeiten, gibt es in zwei Versionen:

  * Eine Version, die eine `filesystem_error`-Ausnahme im Fehlerfall auslöst.
  * Eine zweite Version, die ein `error_code`-Objekt verwaltet (systemspezifisch).

---

## Literatur:

Offizielle C++-Referenz: [cppreference.com](https://en.cppreference.com/w/cpp/filesystem)

C++17 Filesystem: [C++17 Filesystem](https://www.codingame.com/playgrounds/5659/c17-filesystem)

Bartek's coding blog:  [C++17 in details: File System](https://www.bfilipek.com/2017/08/cpp17-details-filesystem.html)

---

## Beispiele:

In vielen Beispielen im Web wird für den Namensraum `std::filesystem` ein Alias-Bezeichner `fs` einfgeführt:

```cpp
namespace fs = std::filesystem;
```


###### Analyse `path`-Objekt:

```cpp
Examine :
exists() = 1
root_name() = "C:"
root_path() = "C:\\"
relative_path() = "Development\\GitRepositoryCPlusPlus\\Cpp_GeneralSnippets\\GeneralSnippets"
parent_path() = "C:\\Development\\GitRepositoryCPlusPlus\\Cpp_GeneralSnippets"
filename() = "GeneralSnippets"
stem() = "GeneralSnippets"
extension() = ""

Examine C:\Development\GitRepositoryCPlusPlus\Readme_Ssh.txt:
exists() = 1
root_name() = "C:"
root_path() = "C:\\"
relative_path() = "Development\\GitRepositoryCPlusPlus\\Readme_Ssh.txt"
parent_path() = "C:\\Development\\GitRepositoryCPlusPlus"
filename() = "Readme_Ssh.txt"
stem() = "Readme_Ssh"
extension() = ".txt"

Examine C:\:
exists() = 1
root_name() = "C:"
root_path() = "C:\\"
relative_path() = ""
parent_path() = "C:\\"
filename() = ""
stem() = ""
extension() = ""

Examine C:\Usersss:
```

###### `path`-Objekt Iteration:

```cpp
part: 0 = "C:"
part: 1 = "\\"
part: 2 = "Development"
part: 3 = "GitRepositoryCPlusPlus"
part: 4 = "Readme_Ssh.txt"

part: 0 = "C:"
part: 1 = "\\"
part: 2 = "Development"
part: 3 = "GitRepositoryCPlusPlus"
part: 4 = "Readme_Ssh.txt"
```

###### Dateigröße berechnen

```cpp
Size of File: 326
```

###### Rekursives Traversieren eines Verzeichnisses

```cpp
Examine C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\CompositePattern:
"CompositePattern.vcxproj", 8046
"CompositePattern.vcxproj.filters", 2603
"CompositePattern.vcxproj.user", 168
"ConceptualExample.cpp", 5989
[+] "Debug"
    "CompositePattern.log", 145
    [+] "CompositePattern.tlog"
        "CL.command.1.tlog", 8986
        "CL.read.1.tlog", 141586
        "CL.write.1.tlog", 15782
        "CompositePattern.lastbuildstate", 188
        "link.command.1.tlog", 2928
        "link.read.1.tlog", 5790
        "link.write.1.tlog", 1894

    "ConceptualExample.obj", 337447
    "Directory.obj", 253940
    "Example.obj", 171620
    "File.obj", 211037
    "FileComponent.obj", 869
    "FileSystemExample.obj", 171658
    "FileSystemExample01.obj", 171826
    "FileSystemExample02.obj", 987421
    "FileSystemExample03.obj", 752601
    "Program.obj", 37515
    "vc142.idb", 322560
    "vc142.pdb", 1232896

"Directory.cpp", 1032
"Directory.h", 737
"File.cpp", 816
"File.h", 676
"FileComponent.h", 453
"FileSystemExample01.cpp", 1152
"FileSystemExample02.cpp", 3489
"FileSystemExample03.cpp", 2012
"Program.cpp", 987
[+] "Resources"
    "CompositePattern.png", 24524
    "CompositePattern_02.jpg", 43563
    "CompositePattern_02.png", 19732
    "dp_composite_pattern.png", 17626
    "Readme.md", 3514
```

---

[Zurück](../../Readme.md)

---
