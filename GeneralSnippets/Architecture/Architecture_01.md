# Hauptmerkmale des modernen C++

[Zurück](Architecture.md)

---

## Robustheit & Sicherheit (RAII & Smart Pointer)

Modernes C++ verlagert die Speicherverwaltung grundlegend weg von rohen Zeigern, um Speicherlecks
und die Gefahr von *Dangling Pointers* zu minimieren.

  * Speicherverwaltung:<br />Modernes C++ legt Wert auf automatische Speicherverwaltung mittels *Resource Acquisition Is Initialization* (*RAII*).
    Smart Pointer (`std::unique_ptr`, `std::shared_ptr`) ersetzen klassische C-Pointer (*Raw Pointer*)
    und eliminieren so effektiv manuelle `new`/`delete`-Aufrufe,
    verhindern Speicherleaks und ungültige Zeiger (*Dangling Pointer*).
  * Stärkere Typisierung:<br />Die Sprache bevorzugt explizite Typen gegenüber riskanten impliziten Datentypkonvertierungen
    und verwendet `std::expected`,
    um das Nichtvorhandensein eines erwarteten Ergebnisses oder eines Fehlers explizit zu behandeln.
  * Reduziertes &bdquo;*Undefined Behavior*&rdquo;:<br />Die neuesten Erweiterungen in der Sprache reduzieren häufige Fehler
    durch Features wie `nullptr`, `constexpr` und stark typisierten Enums (*Strongly-typed Enums*).
  * Modernisierung im Handling von alternativen Werten:<br />
    `std::optional` behandelt fehlende Werte ohne magische Zahlen wie `-1`, `""` oder Nullzeiger.
    `std::variant` bietet sicherere Alternativen zu herkömmlichen Verfahren im Umfeld von C-Unions.
  * Typsichere Sichten: `std::span` / `std::string_view`:<br />Diese wurden in C++ 20 eingeführt und ermöglichen den sicheren Zugriff
    auf zusammenhängenden Speicher ohne Besitzverhältnisse, wodurch Zeiger- und Längenkonflikte vermieden werden.


## Hohe Performanz (*Zero-Cost* Abstraktionen)

Modernes C++ bietet Komfort ohne Laufzeiteinbußen und folgt dem Prinzip: Man zahlt nur für das, was man nutzt.

  * Verschiebesemantik (*Move Semantics*):<br />Verschiebesemantik und *RValue*-Referenzen verhindern aufwändige und unnötige tiefe Objektkopien.
    Durch das Verschieben von Objektinhalten anstatt des Kopierens wird die Performanz von C++ Programmen erheblich gesteigert.
  * Optimierungen zur Übersetzungszeit (`constexpr`):<br />Modernes C++ erweitert die Möglichkeit, Code zur Übersetzungszeit auszuführen.
    Dadurch werden Laufzeitberechnungen auf null reduziert und die Generierung hocheffizienter, optimierter Binärdateien ermöglicht.
  * Verzögerte Auswertung (*Lazy Evaluation*):<br />*Ranges* (Bereiche, `std::ranges`) ermöglichen verzögerte, zusammensetzbare Transformationen,
    die die Zwischenspeicherung von Containern minimieren.
  * Parallelität:<br />Modernes C++ bietet Unterstützung für Parallelverarbeitung.
    Integrierte Primitive wie `std::thread`, `std::atomic` und `std::future` ermöglichen eine sicherere und einfachere Multithreading-Verarbeitung.
   `std::execution::par` ermöglicht die parallele Ausführung von STL-Algorithmen ab C++17.
  * Schlüsselwort `noexcept`:<br />Das Markieren einer Methode (auch Lambda) mit `noexcept` ist 
    ein wichtiges Werkzeug für die Performance-Optimierung und die Ausnahmesicherheit (*Exception Safety*).
  * Leichtgewichtiger STL-Container `std::initializer_list<>`:<br />.Zur Steigerung der Effizienz belegt ein `std::initializer_list`-Objekt &ndash; im Gegensatz zu `std::vector` &ndash;
    in der Regel keinen dynamischen Speicher. Der Compiler erstellt stattdessen ein temporäres Array,
    das meist auf dem Stack oder im Read-Only-Speicher (statisch) liegt. Das `std::initializer_list`-Objekt selbst besteht intern meist nur aus zwei Zeigern (Anfang und Ende)
    oder einem Zeiger und einer Längenangabe. Dadurch ist es sehr performant, ein `std::initializer_list`-Objekt per Value zu übergeben.

## Ausdrucksstärke und Lesbarkeit

Die Sprache unterstützt nun Paradigmen, die den Code lesbarer machen.

  *  `auto` &ndash; Automatische Typableitung (*Automatic Type Deduction*):<br />Das Schlüsselwort `auto` macht die explizite Deklaration komplexer Typen wie z. B. Typen für Iteratoren überflüssig,
    verbessert die Lesbarkeit und beugt Fehlern vor. Dies führt häufig zu einem &bdquo;Almost Always Auto&rdquo;-Stil (*AAA*).
  * Lambda-Funktionen:<br />Anonyme Inline-Lambda-Funktionen ermöglichen das Schreiben von funktionalem Code direkt an Ort und Stelle,
    ohne separate Funktionsobjekte definieren zu müssen.
    Sie können folglich direkt im Code definiert werden, was die Callback-Logik und die Verwendung von STL-Algorithmen vereinfacht.
  * Bereichsbasierte For-Schleifen (*Range-Based For Loop*):<br />Saubere und sichere Iteration über Container,
    wodurch Indexmanipulationen und *Off-by-One*-Fehler vermieden werden.
  * &bdquo;Monadische&bdquo; Interfaces:<br />Ab C++ 23 wurden zu den Klasse `std::optional` und `std::expected` neue Operationen
    hinzugefügt: `and_then`, `or_else` und `transform`. Diese Operationen, die von Konzepten der funktionalen Programmierung inspiriert sind,
    bieten eine prägnantere und ausdrucksstärkere Möglichkeit, mit optionalen Werten (also mit `std::optional`-Objekten) zu arbeiten.
  * Structured Binding:<br />Ermöglicht das direkte Entpacken von Tupeln,
    Paaren und Strukturen in benannte Variablen (z. B. `auto [x, y] = point;`).
  * *Brace Initialization* (auch *Uniform Initialization* genannt):<br />Diese Form der Initialisierung wurde mit C++ 11 eingeführt,
    um die Objekterzeugung zu vereinheitlichen. Man kann dieselbe Syntax `{}` für fast alles verwenden &ndash; egal ob es sich um
    primitive Datentypen, Arrays, Standard-Container (wie `std::vector`) oder um Konstruktoren für Klassen/Strukturen handelt.

## Moderne Sprachmerkmale

Modernes C++ geht die traditionellen Probleme der langsamen Kompilierung und der Header-Verwaltung an.

  * Konzepte (`concept`, `requires`):<br />Verbesserung der Template-Programmierung durch benennbare Compile-Time Restriktionen für Template-Argumente,
    was zu aussagekräftigeren Fehlermeldungen und besseren Schnittstellen führt.
  * Module:<br />Moderne Alternative zu Header-Dateien (`#include`), die die Kompilierzeiten drastisch reduziert und Code besser kapselt.
  * Koroutinen (*Coroutines*):<br />Ermöglichen asynchrone Programmierung in einem synchronen, leicht lesbaren Stil.
  * Moderne Formatierung (`std::print`, `std::format`):<br />Ersetzt die veralteten Bibliotheken `iostream` und `printf` durch
    eine typsichere, schnelle und moderne Formatierungsbibliothek.

## Interoperabilität und Portabilität

Die STL ist der wesentliche Bestandteil der modernen C++&ndash;Programmierung, da sie Entwicklern ermöglicht,
sich auf die Logik der Anwendung zu konzentrieren, anstatt grundlegende Datenstrukturen selbst zu implementieren.

  * Standardbibliothek (STL):<br />Eine umfangreiche, ausgereifte Standardbibliothek für effiziente und portable Lösungen.
    Zusätzliche Bereiche der STL umfassen Zeichenkettenverarbeitung, Eingabe/Ausgabe, Utilities (wie `std::pair` oder `std::tuple`), Threading, Zeitmanagement und Dateisysteme.
  * Die STL ist auf Effizienz getrimmt und nutzt Templates für *Compile-Time*-Polymorphie, um maximale Performance zu bieten.
  * Abwärtskompatibilität:<br />Modernes C++ ist weiterhin mit C-Bibliotheken und älterem C++-Code kompatibel und ermöglicht so eine schrittweise Modernisierung.

*Zusammenfassung*:

Die Sprache *Modern C++* hat sich von Low-Level-Manipulationen hin zur High-Level-Abstraktion entwickelt,
ohne dabei an Geschwindigkeit einzubüßen. Die Sprache ist auf diese Weise sicherer und produktiver als C++98
und bleibt gleichzeitig ein Top-Kandidat für die Systemprogrammierung.

Im Jahr 2026 konzentriert sich modernes C++ auf weitere Verbesserungen der Sprache und der Bibliotheken.
C++ 26 führt *Reflection*, *Pattern Matching* und verbesserte Parallelverarbeitung ein,
um C++ an der Spitze der Sprachen für System- und Anwendungsprogrammierung zu halten.

---

[Zurück](Architecture.md)

---
