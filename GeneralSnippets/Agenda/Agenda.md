# Agenda &ldquo;C++&ndash;Seminar für Fortgeschrittene&rdquo;

[Zurück](../../Readme.md)

---

## Aufbau einer Klasse
  * Parameterübergabemechanismus (*call-by-value* / *call-by-reference*)
  * Big-Three
  * Überladen von Operatoren
  * Klassenvariablen/-methoden (`static`)


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
  * `override`, `virtual`, `final`
  * Polymorphismus
  * Interface / Schnittstellen
  * Abstrakte Klassen
  * Mehrfachvererbung (Schnittstellen)


## Verschiedenes
  * Initialisierung (&ldquo;Uniform Initialization&ldquo;)
  * Default-Initialisierung für Member-Variablen
  * Initialisierungslisten (`std::initializer_list`)
  * Structured Binding
  * Range-based Loop


## Smart Pointer
  * Unique Pointer
  * Shared Pointer
  * Weak Pointer


## `constexpr`
  * Variablen
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


## Standard Template Library (STL)
  * Container
  * Iteratoren
  * Algorithmen
  * Funktionen, Funktoren und Lambdas
  * Neuerungen ab C++&ndash;11/14/17


## STL-Algorithmen
  * `std::generate`
  * `std::accumulate`
  * `std::transform`
  * Das *Erase-Remove*-Idiom


## Variadische Templates
  * `std::tuple` (Vorausetzung)
  * Allgemeines / einführende Beispiele
  * Zugriff auf jedes einzelne Argument
  * Anwendungsfall &ldquo;Summe von Summen&rdquo;
  * Mixins
  * Emplace-Technik


## Vertiefungen zu Templates
  * Perfect Forwarding (Universal Reference)
  * `constexpr_if`
  * `std::apply`
  * `std::invoke`
  * Template Template Parameter
  * Static Polymorphism
  * `decltype` und `std::declval`
  * Automatischer Rückgabetyp (Trailing Return Type Deduction)


## Folding
  * Grundlagen
  * Folding &ldquo;über einem Komma&rdquo;


## Metaprogramming
  * Grundlagen
  * Wiederholungsanweisung, bedingte Anweisung und Rückgabewert
  * List Processing


## Expression Templates
  * Allgemeines
  * Beispiel Klasse `Matrix`


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

---

[Zurück](../../Readme.md)

---
