# Agenda Seminar &bdquo;Modern C++&rdquo;

[Zurück](../../Readme.md)

---

## Verschiebe-Semantik
  * *RValues* und *LValues*
  * Verschiebe-Semantik (*Move*&ndash;*Semantics*)
  * &bdquo;Big-Three&rdquo;, &bdquo;Big-Five&rdquo; und &bdquo;Rule of Zero&rdquo; 


## `auto`
  * Vereinbarung von Variablen / *Automatic Type Deduction*
  * Neuartige Möglichkeit in der Definition von Funktionen / *Function Return Type Deduction*
  * Funktionsdefinition mit *Trailing Return Type*
  * Verlust von `const` und `&` (Referenz) bei `auto`
  * `decltype(auto)`
  * `auto` versus `decltype`
  * `auto` versus `decltype(auto)`
  * Typableitung bei Template Parametern / *Template Parameter Type Deduction*
  * Möglichkeiten des Gebrauchs von `auto` im Vergleich


## Lambdas
  * Historische Betrachtung (Funktionen, aufrufbare Objekte, Lambdas)
  * *Capture*-Klausel
  * *Closure* von Lambdas
  * Lambdas und `std::function<T>`
  * Zusammenhang Lambda-Objekt und aufrufbares Objekt
  * IIFE -Immediately Invoked Functional Expression (Lambda)


## Generische Lambda Ausdrücke
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
  * Default-Initialisierung für Member-Variablen
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
  * `constexpr` Variablen
  * Klassen / benutzerdefinerte Datentypen mit `constexpr` Konstruktoren
  * `constexpr`-Funktionen und `constexpr`-Lambda-Funktionen
  * `const`, `constexpr`, `consteval` und `constinit`


## Benutzerdefinierte Literale
  * Beispiel Klasse `Color`
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
  * Container
  * Iteratoren
  * Algorithmen
  * Funktionsobjekte und Lambdas


## STL-Algorithmen
  * `std::generate`
  * `std::accumulate`
  * `std::transform`
  * `std::back_inserter` (Iterator-Adapter)
  * STL-Algorithmen und Lambda-Ausdrücke
  * Das *Erase-Remove*-Idiom


## Metaprogramming
  * Grundlagen
  * Wiederholungsanweisung, bedingte Anweisung und Rückgabewert
  * List Processing


## &bdquo;Type Traits&rdquo;
  * Eigenschaften von Datentypen zur Übersetzungszeit betrachten / ändern
  * `decltype` und `std::declval`
  * `Iterator::value_type` und `Iterator::iterator_category`
  * `std::remove_reference`


## Konzepte (*Concepts*) und Einschränkungen (*Requirements*) für Klassen
  * Konzept von &bdquo;C++ Concepts&rdquo;: `concept`
  * `requires`-Klausel nach der Template-Parameterliste
  * Eingeschränkte Template Parameter


## Variadische Templates
  * Allgemeines / Einführende Beispiele
  * Anwendungsfall: Zugriff auf jedes einzelne Argument
  * Anwendungsfall: &bdquo;Summe von Summen&rdquo;
  * Anwendungsfall: Mixins
  * Anwendungsfall: *emplace*-Technik


## Vertiefungen zu (variadischen) Templates
  * *Perfect Forwarding* (*Universal Reference*)
  * `constexpr_if`
  * `std::apply`
  * `std::invoke`


## Folding
  * Grundlagen
  * Folding &bdquo;über einem Komma&rdquo;

  
## Funktionale Programmierung mit C++
  * Grundlagen
  * *Pure* Funktionen
  * Funktionen höherer Ordnung
  * Ein Beispiel mit STL und *Ranges*

  
## Expression Templates / Lazy Evaluation
  * Allgemeines
  * Beispiel Klasse `Matrix`
  * Beispiel &bdquo;Konkatenation von Zeichenketten&rdquo;


## Ergänzungen zu Zeichenketten
  * `std::string_view`
  * SSO (Small String Optimization)
  * Leerzeichen am Anfang und Ende einer Zeichenkette entfernen (`std::find_if`, `erase` und `base`)


## Neue Utility Klassen
  * `std::array`, `std::to_array` und `std::span`
  * `std::optional`
  * `std::variant`
  * `std::any`
  * `std::pair`
  * `std::tuple`
  * `std::reference_wrapper` und `std::ref`
  * `std::common_type`
  * Vertiefungen zu `std::variant`: Das Visitor-Konzept mit `std::visit` und das sog. *Overload*&ndash;Pattern


## SFINAE (&bdquo;Substitution failure is not an error&rdquo;)
  * Allgemeines
  * Beispiel


## CRTP (&bdquo;Curiously recurring template pattern&rdquo;)
  * Allgemeines
  * Beispiel &bdquo;Mixins&rdquo;


## Multithreading
  * RAII (Allgemeines / Beispiel `ofstream`/ Beispiel *Clipboard*)
  * `std::thread` (&bdquo;Simple Threading&rdquo;)
  * Atomare Operationen
  * Mutual Exclusion / Locks (ScopedLock, UniqueLock und Condition_Variable)
  * Async (`std::async`)
  * Future & Promise (`std::promise` und `std::future`)
  * Die Klasse `std::std::packaged_task`
  * Exception Forwarding
  * C++&ndash;20: Verriegelungen (*Latches*) und Barrieren (*Barriers*)
  * C++&ndash;20: Parallelisierung von STL-Algorithmen


## C++&ndash;23: Odds and Ends
  * Modularisierte Standardbibliothek
  * C++ Standard-Attribute
  * Klasse `std::source_location`
  * Funktion `std::to_underlying`

## C++&ndash;23: Ausblick
  * Concepts
  * Ranges
  * Coroutines
  * Modules
  * `std::format`
  * Spaceship Operator `<=>`

---

[Zurück](../../Readme.md)

---
