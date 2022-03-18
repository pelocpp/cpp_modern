# Aufgaben

[Zurück](../../Readme.md)

---

In diesem Abschnitt finden Sie eine Reihe kleinerer Aufgaben vor, um den vermittelten Stoff zu vertiefen.
Es wurde Wert darauf gelegt, die Übungen &ndash; soweit möglich &ndash; in ihrem Umfang möglichst kurz zu gestalten,
um auf diese Weise die Einstiegshürde so niedrig wie machbar zu halten.

Zusätzlich gibt es zu jeder Aufgabe einen Lösungsvorschlag, manchmal sogar mehrere.
Auch das Studium eines Lösungsvorschlags kann hilfreich sein, um den Zugang zu einer neuen Thematik zu finden!

---

  * ### [Move-Semantik](#Aufgaben-zur-Move-Semantik)

  * ### [Lambda Funktionen](#Aufgaben-zu-Lambda-Funktionen)

  * ### [Initialisierung](#Aufgaben-zur-Initialisierung)

  * ### [Smart Pointer](#Aufgaben-zu-Smart-Pointer)

  * ### [STL-Algorithmen](#Aufgaben-zu-STL-Algorithmen)

  * ### [Variadische Templates](#Aufgaben-zu-variadischen-Templates)
    
  * ### [Folding](#Aufgaben-zu-Folding)
    
  * ### [constexpr](#Aufgaben-zu-constexpr)
    
  * ### [Utility Klassen](#Aufgaben-zu-Utility-Klassen)
    
  * ### [Metaprogrammierung](#Aufgaben-zur-Metaprogrammierung)
 
  * ### [Expression Templates](#Aufgaben-zu-Expression-Templates)
    
  * ### [*Perfect Forwarding*](#Aufgaben-zu-Perfect-Forwarding)
    
  * ### [Funktionale Programmierung](#Aufgaben-zur-funktionalen-Programmierung)
    
  * ### [SFINAE](#Aufgaben-zu-SFINAE)
    
  * ### [CRTP](#Aufgaben-zu-CRTP)
      
---

### Aufgaben zur Move-Semantik

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_01_MoveSemantics.md#aufgabe-1-verschiebe-semantik-am-beispiel-einer-benutzerdefinierten-klasse) | Verschiebe-Semantik am Beispiel einer benutzerdefinierten Klasse |
| [Aufgabe 2](./Exercises_01_MoveSemantics.md#aufgabe-2-verschiebe-semantik-am-beispiel-einer-klasse-hugearray-betrachtet) | Verschiebe-Semantik am Beispiel einer Klasse `HugeArray` betrachtet |

*Tabelle* 1: Aufgaben zur Move-Semantik.

---

### Aufgaben zu Lambda-Funktionen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_02_Lambdas.md#aufgabe-1-einfache-realisierung-einer-lambda-funktion) | Einfache Realisierung einer Lambda-Funktion<br/>(Vorausetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`) |
| [Aufgabe 2](./Exercises_02_Lambdas.md#aufgabe-2-taschenrechner-mit-lambda-funktionen) | Taschenrechner mit Lambda-Funktionen<br/>(Vorausetzungen: Container `std::map`, Klasse `std::pair`) | 
| [Aufgabe 3](./Exercises_02_Lambdas.md#aufgabe-3-quiz-mit-lambda-funktionen) | Quiz mit Lambda-Funktionen |

*Tabelle* 2: Aufgaben zu Lambda-Funktionen.

---

### Aufgaben zur Initialisierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_11_Initialization.md#aufgabe-1-uniform-initialization-und-initialisierungliste) | *Uniform Initialization* und Initialisierungliste<br/>(Vorausetzungen: Templates, `std::vector<>`, `std::initializer_list<>`) |

*Tabelle* 3: Aufgaben zur Initialisierung.

---

### Aufgaben zu Smart Pointer

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_15_SmartPointers.md) | Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| [Aufgabe 2](Exercises_15_SmartPointers.md) | Noch ein Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| [Aufgabe 3](Exercises_15_SmartPointers.md) | Betrachtungen eines &ldquo;nicht besitzenden&rdquo; Zeigers<br/>(Vorausetzungen: `std::shared_ptr<>`, `std::weak_ptr<>`) |

*Tabelle* 3: Aufgaben zu Smart Pointer.

---

### Aufgaben zu STL-Algorithmen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_03_Algorithms.md) | Die Funktion `std::accumulate` in der Anwendung (mit Initialisierungliste)<br/>(Voraussetzungen: `std::accumulate`, `std::initializer_list`) |
| [Aufgabe 2](Exercises_03_Algorithms.md) | *Fibonacci*-Zahlen<br/>(Voraussetzungen: Algorithmen `std::generate`, `std::for_each`, Lambda-Funktionen, Structured Binding) |

*Tabelle* 4: Aufgaben zu STL-Algorithmen.

---

### Aufgaben zu variadischen Templates

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_05_VariadicTemplates.md) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](Exercises_05_VariadicTemplates.md) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](Exercises_05_VariadicTemplates.md) | Generische Funktion `miminum`<br/>(Vorausetzungen: Utility-Funktion `std::common_type`) |
| [Aufgabe 4](Exercises_05_VariadicTemplates.md) | Ausgabe eines `std::tuple` Objekts<br/>(Vorausetzungen: `std::tuple`, Non-Type Template Parameter) |
| [Aufgabe 5](Exercises_05_VariadicTemplates.md) | Viele Wege führen zum gleichen Ergebnis: Summenbildung natürlicher Zahlen |
| [Aufgabe 6](Exercises_05_VariadicTemplates.md) | Variadische Templates und Vererbung |
| [Aufgabe 7](Exercises_05_VariadicTemplates.md) | Berechnung der Gesamtlänge beliebig vieler Zeichenketten<br/>(Vorausetzungen: `std::initializer_list`) |

*Tabelle* 5: Aufgaben zu variadischen Templates.

---

### Aufgaben zu Folding

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_06_Folding.md#aufgabe-1-logische-operationen-mit-beliebig-vielen-operanden) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](./Exercises_06_Folding.md#aufgabe-2-folding-expressions-decltype-und-type-traits-am-beispiel-von-sameType) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](./Exercises_06_Folding.md#aufgabe-3-folding-over-a-comma-am-beispiel-zweier-funktionen-minimum-und-maximum) | &ldquo;Folding over a Comma&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`<br/>(Voraussetzungen: Lambda Funktionen) |
| [Aufgabe 4](./Exercises_06_Folding.md#aufgabe-4-beliebig-viele-Werte-zu-einem-std-vector-objekt-hinzufügen) | Beliebig viele Werte zu einem `std::vector`-Objekt hinzufügen |
| [Aufgabe 5](./Exercises_06_Folding.md#aufgabe-5-störende-trennzeichen-am-ende-eines-folding-ausdrucks) | Störende Trennzeichen am Ende eines Folding-Ausdrucks |

*Tabelle* 6: Aufgaben zu Folding.

---

### Aufgaben zu `constexpr`

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_14_ConstExpr.md) | Auswertung von variadische Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit<br/>(Voraussetzungen: `decltype`, `std::is_same`) |

*Tabelle* 7: Aufgaben zu `constexpr`.

---

### Aufgaben zu Utility Klassen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_04_UtilityClasses.md) | `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen<br/>(Vorausetzungen: Templates Grundlagen, `std::optional`, `if constexpr`) |
| [Aufgabe 2](Exercises_04_UtilityClasses.md) | `std::variant`: Ein heterogener Container<br/>(Vorausetzungen: `std::variant`, `std::visit`, `std::vector`) |

*Tabelle* 8: Aufgaben zu Utility Klassen.

---

### Aufgaben zur Metaprogrammierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_07_Metaprogramming.md) | Konvertierung binärer Zahlen in Dezimalzahlen |
| [Aufgabe 2](Exercises_07_Metaprogramming.md) | *Fibonacci*-Zahlen |

*Tabelle* 9: Aufgaben zur Metaprogrammierung.

---

### Aufgaben zu Expression Templates

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_08_ExpressionTemplates.md) | Das Skalarprodukt zweier Vektoren |

*Tabelle* 10: Aufgaben zu Expression Templates.

---

### Aufgaben zu *Perfect Forwarding*

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_12_PerfectForwarding.md) | Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding* |
| [Aufgabe 2](Exercises_12_PerfectForwarding.md) | Ausführungszeit einer Funktion<br/>(Voraussetzungen: `std::invoke`, variadische Templates und *Perfect Forwarding*) |

*Tabelle* 11: Aufgaben zum *Perfect Forwarding*.

---

### Aufgaben zur funktionalen Programmierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_13_FunctionalProgramming.md) | Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben<br/>(Vorausetzungen: Templates, Lambda-Funktionen) |
| [Aufgabe 2](Exercises_13_FunctionalProgramming.md) | `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis<br/>(Vorausetzungen: Kenntnisse von `decltype` und `declval`) |

*Tabelle* 12: Aufgaben zum funktionaler Programmierung.

---

### Aufgaben zu SFINAE

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_09_SFINAE.md) | Eine Funktion mit bestimmten Parametertypen |
| [Aufgabe 2](Exercises_09_SFINAE.md) | Eine Methode, unterschiedliche Implementierungen<br/>(Vorausetzungen: Templates, `decltype` und `std::declval`) |
| [Aufgabe 3](Exercises_09_SFINAE.md) | Detektion von Methoden in einer Klasse<br/>(Vorausetzungen: Templates, `decltype` und `std::declval`) |
| [Aufgabe 4](Exercises_09_SFINAE.md) | Eine Methode, unterschiedliche Implementierungen zum Zweiten<br/>(Vorausetzungen: `std::array`) |

*Tabelle* 13: Aufgaben zu SFINAE.

---

### Aufgaben zu CRTP

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](Exercises_10_CRTP.md) | Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet<br/>(Voraussetzungen: Polymorphismus, Templates)  |

*Tabelle* 14: Aufgaben zu CRTP.

---

[An den Anfang](#aufgaben)

---

[Zurück](../../Readme.md)

---
