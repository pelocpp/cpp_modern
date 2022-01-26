# Agenda Seminar &ldquo;Modern C++&rdquo;

[Zurück](../../Readme.md)

---

## Move-Semantik:
  * &ldquo;Big-Three&rdquo;
  * RValue/LValue
  * &ldquo;Big-Five&rdquo;
  * &ldquo;Rule of Zero&rdquo; 
  * Memory Leaks Detection


## `auto`
  * Vereinbarung von Variablen / *Automatic Type Deduction*
  * Neuartige Möglichkeit in der Definition von Funktionen / *Function Return Type Deduction*
  * Funktionsdefinition mit *Trailing Return Type*
  * Verlust von `const` und `&` (Referenz) bei `auto`
  * Typableitung bei Template Parametern / *Template Parameter Type Deduction*
  * `decltype(auto)`


## Lambdas
  * Historische Betrachtung (Funktionen, Funktoren, Lambdas)
  * *Capture*-Klausel
  * *Closure* von Lambdas
  * STL-Algorithmen mit Lambda-Ausdrücken
  * Generische Lambdas


## Vererbung
  * Virtueller Methodenaufrufmechanismus
  * Interface- / Schnittstellen-Konzept
  * Abstrakte Klassen
  * Polymorphismus
  * Schlüsselwörter `override`, `virtual`, `final`
  * Mehrfachvererbung (Schnittstellen)


## Initialisierung
  * Initialisierung (&ldquo;Uniform Initialization&ldquo;)
  * Default-Initialisierung für Member-Variablen
  * Initialisierungslisten (`std::initializer_list`)


## Verschiedenes
  * Structured Binding
  * Range-based `for`&ndash;Loop
  * C++ Standard-Attribute
  * Argument-Dependent Name Lookup (ADL) / *Koenig*-Lookup


## Intelligente Zeiger (*Smart Pointer*)
  * Zeiger mit einem Besitzer: `std::unique_ptr`
  * Intelligenter Zeiger mit Referenzzählung: `std::shared_ptr`
  * Spezieller intelligenter Zeiger in Verbindung mit `std::shared_ptr`: `std::weak_ptr`


## `constexpr`
  * `constexpr` Variablen
  * Klassen / benutzerdefinerte Datentypen mit `constexpr` Konstruktoren
  * `constexpr`-Funktionen und `constexpr`-Lambda-Funktionen
  * Konstante `std::array<>`-Objekte, initialisiert mit variadischen Templates


## Benutzerdefinierte Literale
  * Beispiel Klasse `Color`
  * Benutzerdefinierte Literale und `constexpr`


## Klassentemplates und Funktionstemplates
  * Allgemeines / einführende Beispiele
  * Type Parameter / Value Parameter
  * Member Function Template (Method Template)
  * Partielle und explizite Template Spezialisierung
  * Two-Phase Name Lookup


## Standard Template Library (STL)
  * Container
  * Iteratoren
  * Algorithmen
  * Funktionen, Funktoren und Lambdas
  * Neuerungen ab C++&ndash;11/14/17


## Type-Traits
  * `decltype` und `std::declval`


## STL-Algorithmen
  * `std::generate`
  * `std::accumulate`
  * `std::transform`
  * `std::back_inserter` (Iterator)
  * Das *Erase-Remove*-Idiom


## Variadische Templates
  * Allgemeines / einführende Beispiele
  * Anwendungsfall: Zugriff auf jedes einzelne Argument
  * Anwendungsfall: &ldquo;Summe von Summen&rdquo;
  * Anwendungsfall: Mixins
  * Anwendungsfall: *emplace*-Technik


## Vertiefungen zu (variadischen) Templates
  * *Perfect Forwarding* (*Universal Reference*)
  * `constexpr_if`
  * `std::apply`
  * `std::invoke`
  * Template Template Parameter
  * Static Polymorphism


## Folding
  * Grundlagen
  * Folding &ldquo;über einem Komma&rdquo;


## Metaprogramming
  * Grundlagen
  * Wiederholungsanweisung, bedingte Anweisung und Rückgabewert
  * List Processing


## Expression Templates / Lazy Evaluation
  * Allgemeines
  * Beispiel Klasse `Matrix`
  * Beispiel &ldquo;Konkatenation von Zeichenketten&rdquo;

## Functional Programming
  * Allgemeines
  * Funktionen höherer Ordnung `filter`, `map` und `fold`


## FileSystem Library
  * Klassen `path` und `directory_entry`
  * Iteratoren für Verzeichnisse


## Reguläre Ausdrücke
  * Allgemeines
  * Klasse `std::regex`


## Ergänzungen zu Zeichenketten
  * `std::string_view`
  * SSO (Small String Optimization)
  * Leerzeichen am Anfang und Ende einer Zeichenkette entfernen (`std::find_if`, `erase` und `base`)


## Neue Utility Klassen
  * `std::common_type`

  * `std::array`

  * `std::optional`
  * `std::variant`
  * `std::any`

  * `std::pair`
  * `std::tuple` 


## SFINAE (&ldquo;Substitution failure is not an error&ldquo;)
  * Allgemeines
  * Beispiel


## CRTP (&ldquo;Curiously recurring template pattern&ldquo;)
  * Allgemeines
  * Beispiel &ldquo;Mixins&rdquo;


## Multithreading
  * RAII (Allgemeines / Beispiel `ofstream`/ Beispiel *Clipboard*)
  * `std::thread` (&ldquo;Simple Threading&rdquo;)
  * Atomare Operationen
  * Mutual Exclusion / Locks (ScopedLock, UniqueLock und Condition_Variable)
  * Async (`std::async`)
  * Future & Promise (`std::promise` und `std::future`)
  * Die Klasse `std::std::packaged_task`
  * Exception Forwarding
  * C++&ndash;20: Verriegelungen (*Latches*) und Barrieren (*Barriers*)
  * C++&ndash;20: Parallelisierung von STL-Algorithmen


## C++&ndash;20: Ausblick
  * Concepts
  * Ranges
  * Coroutines
  * `std::format`
  * Spaceship Operator `<=>`

---

[Zurück](../../Readme.md)

---
