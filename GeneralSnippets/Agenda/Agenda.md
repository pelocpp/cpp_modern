# Agenda &ldquo;C++&ndash;Seminar f&uuml;r Fortgeschrittene&rdquo;

[Zurück](../../Readme.md)

---

## Literatur


## Aufbau einer Klasse
  * Parameter&uuml;bergabemechanismus (*call-by-value* / *call-by-reference*)
  * Big-Three
  * &Uuml;berladen von Operatoren
  * Klassenvariablen/-methoden (`static`)


## Move-Semantics:
  * Big-Three   
  * RValue/LValue   
  * Big-Five   
  * Rule of Zero   
  * Memory Leaks Detection


## Lambdas
  * Funktoren   
  * Zugriffsklauseln   
  * Closure von Lambdas   
  * STL-Algorithmen mit Lambda-Ausdr&uuml;cken


## Vererbung:
  * `override`, `virtual`, `final`
  * Polymorphismus   
  * Interface / Schnittstellen   
  * Abstrakte Klassen   
  * Mehrfachvererbung (Schnittstellen)


## Standard Template Library (STL)
  * Template Klassen (Container)   
  * Iteratoren   
  * Algorithmen
  * Neuerungen ab C++11/14/17


## Verschiedenes:
  * Initialisierung (&ldquo;Uniform Initialization&ldquo;)
  * Default-Initialisierung f&uuml;r Member-Variablen
  * Initialisierungslisten (`std::initializer_list`)
  * Schl&uuml;sselwort `auto`   
  * Schl&uuml;sselwort `explicit` 
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


## Template-Funktionen und Klassen
  * Allgemeines / einf&uuml;hrendes Beispiel
  * Value Templates 
  * Member Function Template (Method Template)   
  * Explizite Template Spezialisierung   
  * Partielle Template Spezialisierung   


## STL-Algorithmen
  * `std::accumulate`
  * `std::transform`


## Variadische Templates
  * `std::tuple` (Vorrausetzung)
  * Allgemeines / einf&uuml;hrende Beispiele
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
  * Automatischer R&uuml;ckgabetyp (Trailing Return Type Deduction)


## Folding
  * Grundlagen


## Metaprogramming
  * Basics   
  * List Processing


## Expression Templates
  * Allgemeines   
  * Beispiel Klasse `Matrix`


## Functional Programming
  * Allgemeines   
  * Funktionen h&ouml;herer Ordnung `filter`, `map` und `fold`


## FileSystem Library
  * Klassen `path` und `directory_entry`
  * Iteratoren für Verzeichnisse


## Reguläre Ausdrücke
  * Allgemeines   
  * Klasse `std::regex`


## Ergänzungen zu Zeichenketten
  * `std::string_view`
  * SSO (Small String Optimization)


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
  * Future & Promise   
  * PackagedTask   
  * Exception Forwarding
  * C++ 20: Latsches und Barries
  * C++ 20: Parallelisierung von STL-Algorithmen


## C++ 20: Ausblick
  * Concepts
  * Ranges
  * Coroutines

---

[Zurück](../../Readme.md)

---
