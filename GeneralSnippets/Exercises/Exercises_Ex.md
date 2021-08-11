# Aufgaben

[Zurück](../../Readme.md)

---

In diesem Abschnitt finden Sie eine Reihe kleinerer Aufgaben vor, um den vermittelten Stoff zu vertiefen.
Es wurde Wert darauf gelegt, die Übungen &ndash; soweit möglich &ndash; in ihrem Umfang möglichst kurz zu gestalten,
um auf diese Weise die Einstiegshürde so niedrig wie machbar zu halten.

Zusätzlich gibt es zu jeder Aufgabe einen Lösungsvorschlag, manchmal sogar mehrere.
Auch das Studium eines [Lösungsvorschlags](Exercises.cpp) kann hilfreich sein, um den Zugang zu einer neuen Thematik zu finden!

---



  * ### [Move-Semantik](#section_crtp)

  * ### [Lambda Funktionen](#Lambda-Funktionen)

  * ### [Initialisierung](#Initialisierung)

  * ### [STL-Algorithmen](#STL-Algorithmen)

  * ### [Variadische Templates](#Variadische-Templates)
    
  * ### [Folding](#Folding)
    
  * ### [Utility Klassen](#Utility-Klassen)
    
  * ### [Metaprogrammierung](#Metaprogrammierung)
    
  * ### [*Perfect Forwarding*](#Perfect-Forwarding)
    
  * ### [Funktionale Programmierung](#Funktionale-Programmierung)
    
  * ### [SFINAE](#SFINAE)
    
  * ### [CRTP](#CRTP)
    
---

### Move-Semantik

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_01_MoveSemantics.md) | Betrachtungen einer Klasse `HugeArray` |

*Tabelle* 1: Aufgaben zur Move-Semantik.

---

### Lambda-Funktionen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_02_Lambdas.md) | Einfache Realisierung einer Lambda-Funktion<br/>(Vorausetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`) |
| [Aufgabe 2](Exercises_02_Lambdas.md) | Taschenrechner mit Lambda-Funktionen<br/>(Vorausetzungen: Container `std::map`, Klasse `std::pair`) | 
| [Aufgabe 3](Exercises_02_Lambdas.md) | Quiz mit Lambda-Funktionen |

*Tabelle* 2: Aufgaben zu Lambda-Funktionen.

---

### Initialisierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_11_Initialization.md) | Einheitliche Initialisierung (*Uniform Initialization*) und Initialisierungliste (`std::initializer_list<>`)<br/>(Vorausetzungen: Templates, `std::vector<>`) |

*Tabelle* 3: Aufgaben zur Initialisierung.

---

### STL-Algorithmen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_03_Algorithms.md) | Die Funktion `std::accumulate` in der Anwendung (mit Initialisierungliste)<br/>(Voraussetzungen: `std::accumulate`, `std::initializer_list`) |

*Tabelle* 4: Aufgaben zu STL-Algorithmen.

---


std::is_same

### Variadische Templates

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_05_VariadicTemplates.md) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](Exercises_05_VariadicTemplates.md) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](Exercises_05_VariadicTemplates.md) | Generische Funktion `miminum`<br/>(Vorausetzungen: Utility-Funktion `std::common_type`) |
| [Aufgabe 4](Exercises_05_VariadicTemplates.md) | Ausgabe eines `std::tuple` Objekts<br/>(Vorausetzungen: `std::tuple<T>`, Non-Type Template Parameter) |
| [Aufgabe 5](Exercises_05_VariadicTemplates.md) | Mehrere Summen, ein Ergebnis |
| [Aufgabe 6](Exercises_05_VariadicTemplates.md) | Variadische Templates und Vererbung |

*Tabelle* 5: Aufgaben zu variadischen Templates.

---

### Folding

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_06_Folding.md) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](Exercises_06_Folding.md) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](Exercises_06_Folding.md) | &ldquo;Folding over a Comma&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`<br/>(Voraussetzungen: Folding Expressions, Lambda Funktionen) |

*Tabelle* 6: Aufgaben zu Folding.

---

### Utility Klassen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_04_UtilityClasses.md) | `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen<br/>(Vorausetzungen: Templates Grundlagen, `std::optional`, `if constexpr`) |
| [Aufgabe 2](Exercises_04_UtilityClasses.md) | `std::variant`: Ein heterogener Container<br/>(Vorausetzungen: `std::variant`, `std::visit`, `std::vector`) |

*Tabelle* 7: Aufgaben zu Utility Klassen.

---

### Metaprogrammierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_07_Metaprogramming.md) | *Fibonacci*-Zahlen |

*Tabelle* 8: Aufgaben zur Metaprogrammierung.

---

### *Perfect Forwarding*

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_12_PerfectForwarding.md) | Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding* |
| [Aufgabe 2](Exercises_12_PerfectForwarding.md) | Ausführungszeit einer Funktion<br/>(Voraussetzungen: `std::invoke`, variadische Templates und *Perfect Forwarding*) |

*Tabelle* 9: Aufgaben zum *Perfect Forwarding*.

---

### Funktionale Programmierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_13_FunctionalProgramming.md) | Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben<br/>(Vorausetzungen: Templates, Lambda-Funktionen) |
| [Aufgabe 2](Exercises_13_FunctionalProgramming.md) | `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis<br/>(Vorausetzungen: Kenntnisse von `decltype` und `declval`) |

*Tabelle* 10: Aufgaben zum funktionaler Programmierung.

---

### SFINAE

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_09_SFINAE.md) | Eine Methode, mehrere Implementierungen<br/>(Vorausetzungen: `std::array`) |
| [Aufgabe 2](Exercises_09_SFINAE.md) | Detektion von Methoden in einer Klasse<br/>(Vorausetzungen: Templates, `decltype` und `std::declval`) |

*Tabelle* 11: Aufgaben zu SFINAE.

---



### CRTP{#section_crtp}

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_10_CRTP.md) | Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet<br/>(Voraussetzungen: Polymorphismus, Templates)  |

*Tabelle* 12: Aufgaben zu CRTP.

---

[Lösungen](Exercises.cpp)

---

[An den Anfang](#aufgaben)

---

[Zurück](../../Readme.md)

---

<!-- Links Definitions -->

[Listing 1]: #section_crtp
[Listing 2]: #listing_02_josephus_interface
