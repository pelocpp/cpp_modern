# Agenda Seminar &bdquo;Modern C++&rdquo;

[Zurück](../../Readme.md)

---

## Verschiebe-Semantik (*Move*-Semantik)
  * *Move*-Semantik einsetzen um laufzeitintensives Kopieren durch schnelles Verschieben zu ersetzen
  * *Move*-Semantik einsetzen um Daten zu verschieben, die nicht kopierbar sind
  * *RValues* und *LValues*
  * Verschiebe-Semantik (*Move*&ndash;*Semantic*) erklärt
  * Verschiebe-Semantik mit dem *Swap-Idiom* realisiert
  * &bdquo;Rule of Three&rdquo;, &bdquo;Rule of Five&rdquo; und &bdquo;Rule of Zero&rdquo; 


## `auto`
  * Vereinbarung von Variablen / *Automatic Type Deduction*
  * Neuartige Möglichkeit in der Definition von Funktionen / *Function Return Type Deduction*
  * Funktionsdefinition mit *Trailing Return Type*
  * Verlust von `const` und `&` (Referenz) bei `auto`
  * `decltype(auto)`
  * Möglichkeiten des Gebrauchs von `auto` im Vergleich


## Lambdas
  * Historische Betrachtung (Funktionen, aufrufbare Objekte, Lambdas)
  * *Capture*-Klausel
  * *Closure* von Lambdas
  * Lambdas und `std::function<T>`
  * Zusammenhang Lambda-Objekt und aufrufbares Objekt
  * IIFE &ndash; *Immediately Invoked Functional Expression*


## Generische Funktionen (inkl. Lambdas)
  * Übersicht
  * *Automatic Type Deduction* bei generischen Lambda Ausdrücken
  * Lambda Ausdrücke mit `template`-Header
  * *Perfect Forwarding* mit generischen Lambdas
  * Rekursive Lambda Ausdrücke
  * *Currying* in C++


## Konzepte (*Concepts*) und Einschränkungen (*Requirements*) für Funktionen
  * Konzept von &bdquo;C++ Concepts&rdquo;: `concept`
  * `requires`-Klausel
  * Benutzerdefinierte Einschränkungen (*user-defined requirements*)


## Initialisierung
  * Initialisierung (&bdquo;Brace Initialization&rdquo; bzw. &bdquo;Uniform Initialization&rdquo;)
  * Initialisierungslisten (`std::initializer_list`)


## Verschiedenes
  * Structured Binding
  * Range-based `for`&ndash;Loop
  * *Copy/Move Elision*
  * *Placement New*: Trennung von Speicherallokation und Objektkonstruktion
  * Vererbung: Schlüsselwörter `override`, `virtual`, `final`
  * Argument-Dependent Name Lookup (ADL) / *Koenig*-Lookup


## Intelligente Zeiger (*Smart Pointer*)
  * Zeiger mit einem Besitzer: `std::unique_ptr`
  * Intelligenter Zeiger mit Referenzzählung: `std::shared_ptr`
  * Spezieller intelligenter Zeiger in Verbindung mit `std::shared_ptr`: `std::weak_ptr`
  * Memory Leaks Detection

## `constexpr`
  * Funktionen mit `constexpr` verwenden um teure Berechnungen in die Übersetzungszeit zu verschieben
  * `constexpr` erklärt
  * Klassen / benutzerdefinierte Datentypen mit `constexpr` Konstruktoren
  * `constexpr`-Funktionen und `constexpr`-Lambda-Funktionen
  * `const`, `constexpr`, `consteval` und `constinit`


## Benutzerdefinierte Literale
  * Beispiel eines Literals `0xFF0000_rgb`
  * Benutzerdefinierte Literale und `constexpr`


## Funktions- und Klassen-Templates
  * Einführende Beispiele
  * Klassen-Templates mit mehreren Parametern
  * Definition von Methoden eines Klassen-Templates
  * Eine Methode eines Klassen-Templates spezialisieren
  * Klassen-Templates und Non-Type Parameter
  * Member Function Template (Method Template)
  * Ein Template mit Template-Parametern
  * Default-Werte für Template-Parameter
  * Alias Template
  * Partielle und explizite Template Spezialisierung
  * Übersetzungsmodelle für Templates
  * Two-Phase Name Lookup
  * Überladen und Spezialisieren von Funktions-Templates
  * Spezialisieren von Funktions-Templates


## Standard Template Library (STL)
  * STL-Container, -Iteratoren, -Algorithmen und aufrufbare Objekte
  * Von sequentiellen auf ungeordnete assoziative Container umsteigen, um die Laufzeit zu verbessern
  * Algorithmen
  * STL-Algorithmen und Lambdas


## Ausgewählte STL-Algorithmen
  * `std::generate`
  * `std::accumulate`
  * `std::transform`
  * `std::back_inserter` (Iterator-Adapter)
  * Das *Erase-Remove*-Idiom


## Metaprogramming
  * Grundlagen
  * Wiederholungsanweisung, bedingte Anweisung und Rückgabewert


## &bdquo;Type Traits&rdquo;
  * Eigenschaften von Datentypen zur Übersetzungszeit betrachten / ändern
  * `decltype` und `std::declval`
  * `Iterator::value_type` und `Iterator::iterator_category`
  * `std::remove_reference` und `std::remove_const` erkärt


## Konzepte (*Concepts*) und Einschränkungen (*Requirements*) für Klassen
  * Konzept von &bdquo;C++ Concepts&rdquo;: `concept`
  * `requires`-Klausel nach der Template-Parameterliste
  * Eingeschränkte Template Parameter


## Variadische Templates
  * Allgemeines / Einführende Beispiele
  * Anwendungsfall: Zugriff auf jedes einzelne Argument
  * Anwendungsfall: Mixins
  * Anwendungsfall: *emplace*-Technik
  * *Perfect Forwarding* (*Universal Reference*)
  * `constexpr if`
  * `std::invoke`


## Folding-Ausdrücke
  * Grundlagen
  * Folding &bdquo;über einem Komma&rdquo;

  
## Funktionale Programmierung mit C++
  * Grundlagen
  * *Pure* Funktionen
  * Funktionen höherer Ordnung
  * Ein Beispiel mit STL und *Ranges*

  
## Expression Templates / Lazy Evaluation
  * Allgemeines / Erläuterung
  * Beispiel Klasse `Matrix`


## Ergänzungen zu Zeichenketten
  * Klasse `std::string_view`
  * SSO (*Small String Optimization*)


## Neue Utility Klassen
  * `std::array`, `std::to_array` und `std::span`:<br />Speicher- und Laufzeitcharakteristik eines C-Arrays mit der Schnittstelle eines C++-Vektors verbinden
  * `std::optional`
  * `std::variant`
  * `std::any`
  * `std::pair`
  * `std::tuple`
  * `std::reference_wrapper` und `std::ref`
  * `std::common_type`
  * Vertiefungen zu `std::variant`: Das *Visitor*-Konzept mit `std::visit` und das sog. *Overload*&ndash;Pattern


## Ausnahmesicherheit / *Exception Safety*
  * Keine Ausnahmesicherheit (*No Exception Safety*)
  * Elementare Ausnahmesicherheit (*Basic Exception Safety*)
  * Starke Ausnahmesicherheit (*Strong Exception Safety*)
  * *No-throw*-Garantie (*No-throw guarantee*)


## *Type Erasure* &ndash; statischer versus dynamischer Polymorphismus
  * Was ist *Type Erasure*
  * Implementierung des *Type Erasure* Idioms
  * Ergänzung um Konzepte (`concept`) 
  * Vergleich (Performanzbetrachtung) von statischem Polymorphismus (Templates) mit dynamischem Polymorphismus (virtueller Methodenaufrufmechanismus)
  * Beispiel &bdquo;Buchhandlung&rdquo;
  

## CRTP (&bdquo;Curiously recurring template pattern&rdquo;)
  * Allgemeines
  * Beispiel &bdquo;Mixins&rdquo;


## Multithreading / Concurrency
  * RAII
  * Nebenläufige Ausführung: Klasse `std::thread`
  * Mutexe und Sperrmechanismen
  * Nochmals nebenläufige Ausführung: Funktion `std::async` und Thread-Pool
  * Futures und Promises: Klassen `std::future` und `std::promise`
  * Funktionen verpacken: Klasse `std::packaged_task`
  * Nochmals nebenläufige Ausführung: Klasse `std::jthread`
  * Die Klassen `std::stop_source`, `std::stop_token` und `std::stop_callback`
  * Verriegelungen und Barrieren: Klassen `std::latch` und `std::barrier`
  * Semaphore: Klassen `std::binary_semaphore` und `std::counting_semaphore`
  * Parallelisierung von STL-Algorithmen
  * Anwendungsbeispiel: Das Erzeuger-Verbraucher Problem
  * Anwendungsbeispiel: Event Loop - Ereigniswarteschlange


## C++&ndash;23: Odds and Ends
  * Modularisierte Standardbibliothek
  * The Return of &bdquo;`printf`&rdquo;: `std::print(ln)` in C++ 23
  * C++ Standard-Attribute
  * Klasse `std::source_location`
  * Funktion `std::to_underlying`

## C++&ndash;23: Ausblick
  * Concepts
  * Ranges
  * Coroutines
  * Module
  * `std::format`
  * Spaceship Operator `<=>`

---

[Zurück](../../Readme.md)

---
