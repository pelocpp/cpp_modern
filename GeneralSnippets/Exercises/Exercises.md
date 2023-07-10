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

  * ### [Generische Lambda Funktionen](#Aufgaben-zu-generischen-Lambda-Funktionen)

  * ### [Initialisierung](#Aufgaben-zur-Initialisierung)

  * ### [Smart Pointer](#Aufgaben-zu-Smart-Pointer)

  * ### [STL-Algorithmen](#Aufgaben-zu-STL-Algorithmen)

  * ### [constexpr](#Aufgaben-zu-constexpr)
    
  * ### [Variadische Templates](#Aufgaben-zu-variadischen-Templates)
    
  * ### [Folding](#Aufgaben-zu-Folding)
    
  * ### [Utility Klassen](#Aufgaben-zu-Utility-Klassen)
    
  * ### [Metaprogrammierung](#Aufgaben-zur-Metaprogrammierung)
 
  * ### [Expression Templates](#Aufgaben-zu-Expression-Templates)
    
  * ### [*Perfect Forwarding*](#Aufgaben-zu-Perfect-Forwarding)
    
  * ### [Funktionale Programmierung](#Aufgaben-zur-funktionalen-Programmierung)
    
  * ### [SFINAE](#Aufgaben-zu-SFINAE)
    
  * ### [CRTP](#Aufgaben-zu-CRTP)

  * ### [Konzepte](#Aufgaben-zu-Konzepten)
      
---

### Aufgaben zur Move-Semantik

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_01_MoveSemantics.md#aufgabe-1-verschiebe-semantik-am-beispiel-einer-benutzerdefinierten-klasse) | Verschiebe-Semantik am Beispiel einer benutzerdefinierten Klasse |
| [Aufgabe 2](./Exercises_01_MoveSemantics.md#aufgabe-2-verschiebe-semantik-am-beispiel-einer-klasse-hugearray-betrachtet) | Verschiebe-Semantik am Beispiel einer Klasse `HugeArray` betrachtet |

*Tabelle* 1: Aufgaben zur Move-Semantik.

---

### Aufgaben zu Lambda Funktionen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_02_Lambdas.md#aufgabe-1-einfache-realisierung-einer-lambda-funktion) | Einfache Realisierung einer Lambda-Funktion<br/>(Vorausetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`) |
| [Aufgabe 2](./Exercises_02_Lambdas.md#aufgabe-2-taschenrechner-mit-lambda-funktionen) | Taschenrechner mit Lambda-Funktionen<br/>(Vorausetzungen: Container `std::map`, Klasse `std::pair`) | 
| [Aufgabe 3](./Exercises_02_Lambdas.md#aufgabe-3-quiz-mit-lambda-funktionen) | Quiz mit Lambda-Funktionen |

*Tabelle* 2: Aufgaben zu Lambda Funktionen.

---

### Aufgaben zu generischen Lambda Funktionen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_16_GenericLambdas.md#aufgabe-1-personensuche) | Personensuche<br/>(Vorausetzungen: Algorithmus `std::find_if`) |

*Tabelle* 3: Aufgaben zu generischen Lambda Funktionen.

---

### Aufgaben zur Initialisierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_11_Initialization.md#aufgabe-1-uniform-initialization-und-initialisierungliste) | *Uniform Initialization* und Initialisierungliste<br/>(Vorausetzungen: Templates, `std::vector<>`, `std::initializer_list<>`) |
| [Aufgabe 2](./Exercises_11_Initialization.md#aufgabe-2-zeitvergleich-im-gebrauch-von-vektoren-und-initialisierunglisten) | Zeitvergleich<br/>(Vorausetzungen: `std::vector<>`, `std::initializer_list<>`) |

*Tabelle* 4: Aufgaben zur Initialisierung.

---

### Aufgaben zu Smart Pointer

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_15_SmartPointers.md#aufgabe-1-quiz-zu-smart-pointer) | Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| [Aufgabe 2](./Exercises_15_SmartPointers.md#aufgabe-2-noch-ein-quiz-zu-smart-pointer) | Noch ein Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| [Aufgabe 3](./Exercises_15_SmartPointers.md#aufgabe-3-beobachtungen-eines-zyklus-von-smart-pointer-objekten) | Betrachtungen eines Zyklus von `std::shared_ptr<>`-Objekten<br/>(Vorausetzungen: `std::shared_ptr<>`, ggf. `std::weak_ptr<>`) |
| [Aufgabe 4](./Exercises_15_SmartPointers.md#aufgabe-4-betrachtungen-eines-nicht-besitzenden-zeigers) | Betrachtungen eines &ldquo;nicht besitzenden&rdquo; Zeigers<br/>(Vorausetzungen: `std::shared_ptr<>`, `std::weak_ptr<>`) |

*Tabelle* 5: Aufgaben zu Smart Pointer.

---

### Aufgaben zu STL-Algorithmen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_03_Algorithms.md#aufgabe-1-der-algorithmus-stdaccumulate-in-der-anwendung) | Der Algorithmus `std::accumulate` in der Anwendung<br/>(Voraussetzungen: `std::accumulate`, `std::initializer_list`) |
| [Aufgabe 2](./Exercises_03_Algorithms.md#aufgabe-2-fibonacci-zahlen) | *Fibonacci*-Zahlen<br/>(Voraussetzungen: Algorithmen `std::generate`, `std::for_each`, Lambda-Funktionen, Structured Binding) |

*Tabelle* 6: Aufgaben zu STL-Algorithmen.

---

### Aufgaben zu `constexpr`

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_14_ConstExpr.md#aufgabe-1-return-type-resolver) | *Return Type Resolver*<br/>(Voraussetzungen: Templates, `std::is_same` und `constexpr`) |
| [Aufgabe 2](./Exercises_14_ConstExpr.md#aufgabe-2-auswertung-von-variadische-templates-decltype-und-type-traits-am-beispiel-von-sametype-zur-übersetzungszeit) | Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit<br/>(Voraussetzungen: `decltype`, `std::is_same`) |

*Tabelle* 7: Aufgaben zu `constexpr`.

---

### Aufgaben zu variadischen Templates

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_05_VariadicTemplates.md#aufgabe-1-logische-operationen-mit-beliebig-vielen-operanden) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](./Exercises_05_VariadicTemplates.md#aufgabe-2-decltype-und-type-traits-am-beispiel-von-sametype) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](./Exercises_05_VariadicTemplates.md#aufgabe-3-generische-funktion-miminum) | Generische Funktion `miminum`<br/>(Vorausetzungen: Utility-Funktion `std::common_type`) |
| [Aufgabe 4](./Exercises_05_VariadicTemplates.md#aufgabe-4-ausgabe-eines-stdtuple-objekts) | Ausgabe eines `std::tuple` Objekts<br/>(Vorausetzungen: `std::tuple`, Non-Type Template Parameter) |
| [Aufgabe 5](./Exercises_05_VariadicTemplates.md#aufgabe-5-viele-wege-führen-zum-gleichen-ergebnis-summenbildung-natürlicher-zahlen) | Viele Wege führen zum gleichen Ergebnis: Summenbildung natürlicher Zahlen |
| [Aufgabe 6](./Exercises_05_VariadicTemplates.md#aufgabe-6-variadische-templates-und-vererbung) | Variadische Templates und Vererbung |

*Tabelle* 8: Aufgaben zu variadischen Templates.

---

### Aufgaben zu Folding

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_06_Folding.md#aufgabe-1-logische-operationen-mit-beliebig-vielen-operanden) | Logische Operationen mit beliebig vielen Operanden |
| [Aufgabe 2](./Exercises_06_Folding.md#aufgabe-2-folding-expressions-decltype-und-type-traits-am-beispiel-von-sameType) | `decltype` und Type-Traits am Beispiel von `sameType`<br/>(Vorausetzungen: `std::is_same`) |
| [Aufgabe 3](./Exercises_06_Folding.md#aufgabe-3-folding-over-a-comma-am-beispiel-zweier-funktionen-minimum-und-maximum) | &ldquo;Folding over a Comma&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`<br/>(Voraussetzungen: Lambda Funktionen) |
| [Aufgabe 4](./Exercises_06_Folding.md#aufgabe-4-beliebig-viele-Werte-zu-einem-stdvector-objekt-hinzufügen) | Beliebig viele Werte zu einem `std::vector`-Objekt hinzufügen |
| [Aufgabe 5](./Exercises_06_Folding.md#aufgabe-5-störende-trennzeichen-am-ende-eines-folding-ausdrucks) | Störende Trennzeichen am Ende eines Folding-Ausdrucks |

*Tabelle* 9: Aufgaben zu Folding.

---

### Aufgaben zu Utility Klassen

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_04_UtilityClasses.md#aufgabe-1-stdvisit-und-generische-lambdas) | `std::visit` und generische Lambdas<br/>(Vorausetzungen: `if constexpr`, `decltype`, `std::variant`, `std::visit`, Type Traits) |
| [Aufgabe 2](./Exercises_04_UtilityClasses.md#aufgabe-2-visitor-entwurfsmuster-mit-stdvariant-und-stdvisit) | Visitor-Entwurfsmuster mit `std::variant` und `std::visit`<br/>(Vorausetzungen: `std::variant`, `std::visit`, `std::vector`, variadische Templates) |
| [Aufgabe 3](./Exercises_04_UtilityClasses.md#aufgabe-2-stdoptional-umwandlung-von-zeichenketten-in-ganze-zahlen) | `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen<br/>(Vorausetzungen: Templates Grundlagen, `std::optional`, `if constexpr`) |
| [Aufgabe 4](./Exercises_04_UtilityClasses.md#aufgabe-3-stdvariant-ein-heterogener-container) | `std::variant`: Ein heterogener Container<br/>(Vorausetzungen: `std::variant`, `std::visit`, `std::vector`) |

*Tabelle* 10: Aufgaben zu Utility Klassen.

---

### Aufgaben zur Metaprogrammierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_07_Metaprogramming.md#aufgabe-1-bestimmung-des-maximums-aus-einer-folge-von-ganzen-positiven-zahlen) | Bestimmung des Maximums aus einer Folge von ganzen, positiven Zahlen |
| [Aufgabe 2](./Exercises_07_Metaprogramming.md#aufgabe-2-konvertierung-binärer-zahlen-in-dezimalzahlen) | Konvertierung binärer Zahlen in Dezimalzahlen |
| [Aufgabe 3](./Exercises_07_Metaprogramming.md#aufgabe-3-fibonacci-zahlen) | *Fibonacci*-Zahlen |
| [Aufgabe 4](./Exercises_07_Metaprogramming.md#aufgabe-4-selektiver-zugriff-auf-ein-parameter-pack-von-datentypen) | Selektiver Zugriff auf ein Parameter Pack von Datentypen |

*Tabelle* 11: Aufgaben zur Metaprogrammierung.

---

### Aufgaben zu Expression Templates

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_08_ExpressionTemplates.md#aufgabe-1-das-skalarprodukt-zweier-vektoren) | Das Skalarprodukt zweier Vektoren |

*Tabelle* 12: Aufgaben zu Expression Templates.

---

### Aufgaben zu *Perfect Forwarding*

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_12_PerfectForwarding.md#aufgabe-1-einfaches-beispiel-zu-variadischen-templates-und-perfect-forwarding) | Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding* |
| [Aufgabe 2](./Exercises_12_PerfectForwarding.md#aufgabe-2-ausführungszeit-einer-Funktion) | Ausführungszeit einer Funktion<br/>(Voraussetzungen: `std::invoke`, variadische Templates und *Perfect Forwarding*) |

*Tabelle* 13: Aufgaben zum *Perfect Forwarding*.

---

### Aufgaben zur funktionalen Programmierung

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_13_FunctionalProgramming.md#aufgabe-1-umwandlung-von-zeichenketten-eines-stdvector-objekts) | Umwandlung von Zeichenketten eines `std::vector`-Objekts<br/>(Vorausetzungen: Templates, Lambda-Funktionen) |
| [Aufgabe 2](./Exercises_13_FunctionalProgramming.md#aufgabe-2-decltype-declval-und-nachlaufender-rückgabetyp-in-der-praxis) | `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis<br/>(Vorausetzungen: Kenntnisse von `decltype` und `declval`) |

*Tabelle* 14: Aufgaben zur funktionalen Programmierung.

---

### Aufgaben zu SFINAE

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_09_SFINAE.md#aufgabe-1-eine-funktion-mit-bestimmten-parametertypen) | Eine Funktion mit bestimmten Parametertypen |
| [Aufgabe 2](./Exercises_09_SFINAE.md#aufgabe-2-eine-methode-unterschiedliche-implementierungen) | Eine Methode, unterschiedliche Implementierungen<br/>(Vorausetzungen: Templates, `decltype` und `std::declval`) |
| [Aufgabe 3](./Exercises_09_SFINAE.md#aufgabe-3-detektion-von-methoden-in-einer-klasse) | Detektion von Methoden in einer Klasse<br/>(Vorausetzungen: Templates, `decltype` und `std::declval`) |
| [Aufgabe 4](./Exercises_09_SFINAE.md#aufgabe-4-eine-methode-unterschiedliche-implementierungen-zum-zweiten) | Eine Methode, unterschiedliche Implementierungen zum Zweiten<br/>(Vorausetzungen: `std::array`) |

*Tabelle* 15: Aufgaben zu SFINAE.

---

### Aufgaben zu CRTP

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_10_CRTP.md#aufgabe-1-der-kuriose-polymorphismus-crtp-an-einem-beispiel-betrachtet) | Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet<br/>(Voraussetzungen: Polymorphismus, Templates)  |

*Tabelle* 16: Aufgaben zu CRTP.

---

### Aufgaben zu Konzepten

| Aufgabe | Beschreibung |
| :- | :- |
| [Aufgabe 1](./Exercises_17_Concepts.md#aufgabe-1-überprüfung-des-vorhandenseins-einer-bestimmten-basisklasse) | Überprüfung des Vorhandenseins einer bestimmten Basisklasse<br/>(Vorausetzungen: `concept`, `requires`) |
| [Aufgabe 2](./Exercises_17_Concepts.md#aufgabe-2-überprüfung-des-datentyps-von-funktionsparametern) | Überprüfung des Datentyps von Funktionsparametern<br/>(Vorausetzungen: `concept`, `requires`) |
| [Aufgabe 3](./Exercises_17_Concepts.md#aufgabe-3-konzepte-und-schnittstellen-im-vergleich) | Konzepte und Schnittstellen im Vergleich<br/>(Vorausetzungen: `concept`, `requires`, `virtual`, `override`) |
| [Aufgabe 4](./Exercises_17_Concepts.md#aufgabe-4-berechnung-der-gesamtlänge-beliebig-vieler-zeichenketten) | Berechnung der Gesamtlänge beliebig vieler Zeichenketten<br/>(Vorausetzungen: `requires`, `std::initializer_list`) |

*Tabelle* 17: Aufgaben zu Konzepten.

---

[An den Anfang](#aufgaben)

---

[Zurück](../../Readme.md)

---
