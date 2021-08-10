# Aufgaben

[Zurück](../../Readme.md)

---

In diesem Abschnitt befindet sich eine Reihe kleinerer Aufgaben, um den vermittelten Stoff zu vertiefen.
Es wurde Wert darauf gelegt, die Aufgaben &ndash; soweit wie möglich &ndash; in ihrem Umfang klein zu gestalten,
um auf diese Weise die möglichen Einstiegshürden so niedrig wie möglich zu halten.
Zusätzlich gibt es zu jeder Aufgabe einen Lösungsvorschlag, manchmal sogar mehrere.
Auch das Studium eines Lösungsvorschlag kann hilfreich sein, um den Zugang zu einer neuen Materie zu finden!

---

  * #### [Move-Semantik](#Move-Semantik)

  * #### [Lambda Funktionen](#Lambda-Funktionen)

  * #### [STL-Algorithmen](#STL-Algorithmen)
    
  * #### [SFINAE](#SFINAE)
    
  * #### [CRTP](#CRTP)

---

### Move-Semantik

| Themenbereich | Aufgaben |
| :--- | :--- |
| [Aufgabe 1](Exercises_01_MoveSemantics.md#Aufgabe-1) | Betrachtungen einer Klasse `HugeArray` |

*Tabelle* 1: Aufgaben zur Move-Semantik.

---

### Lambda-Funktionen

| Themenbereich | Aufgaben |
| :--- | :--- |
| [Aufgabe 1](Exercises_02_Lambdas.md#Aufgabe-1:-Einfache-Realisierung-einer-Lambda-Funktion) | Einfache Realisierung einer Lambda-Funktion |
| [Aufgabe 2](Exercises_02_Lambdas.md#Aufgabe-2:-Taschenrechner-mit-Lambda-Funktionen) | Taschenrechner mit Lambda-Funktionen | 
| [Aufgabe 3](Exercises_02_Lambdas.md#Aufgabe-3:-Quiz-mit-Lambda-Funktionen) | Quiz mit Lambda-Funktionen |

*Tabelle* 2: Aufgaben zu Lambda-Funktionen.

---

### STL-Algorithmen

| Themenbereich | Aufgaben |
| :--- | :--- |
| [Aufgabe 1](Exercises_03_Algorithms.md#Aufgabe-1:-Die-Funktion-std::accumulate-in-der-Anwendung (mit Initialisierungliste)) | Die Funktion `std::accumulate` in der Anwendung (mit Initialisierungliste) |

*Tabelle* 3: Aufgaben zu STL-Algorithmen.

---

### SFINAE

| Themenbereich | Aufgaben |
| :--- | :--- |
| [Aufgabe 1](Exercises_09_SFINAE.md#Aufgabe-1:-Eine-Methode,-mehrere-Implementierungen) | Eine Methode, mehrere Implementierungen |
| [Aufgabe 2](Exercises_09_SFINAE.md#Aufgabe-2:-Detektion-von-Methoden-in-einer-Klasse) | Detektion von Methoden in einer Klasse |

*Tabelle* XX: Aufgaben zu SFINAE.


---

### CRTP

| Themenbereich | Aufgaben |
| :--- | :--- |
| [Aufgabe 1](Exercises_10_CRTP.md#Aufgabe-1:-Der-kuriose-Polymorphismus-(CRTP)-an-einem-Beispiel-betrachtet) | Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet  |

*Tabelle* XX: Aufgaben zu STL-Algorithmen.

---

Darunter ist altes Zeugs

---


In diesem Abschnitt befinden sich einige kleinere Aufgaben, um den vermittelten Stoff zu vertiefen.
Folgende Themen werden angesprochen:

  * Einheitliche Initialisierung und Initialisierungliste
  * Move-Semantik
  * Lambda Funktionen
  * Variadische Templates
  * Folding
  * Metaprogrammierung
  * Neue Utility-Klassen und -Funktionen (`std::optional`, `std::variant`, `std::invoke`, `std::visit`)
  * SFINAE
  * CRTP
  * Funktionale Programmierung
  * *Perfect Forwarding*
  * STL-Algorithmus `std::accumulate`

---

Es folgt eine tabellarische Zusammenstellung aller Themenbereiche und Aufgaben:

| Themenbereich | Aufgaben |
| :--- | :--- |
| Move-Semantik | [Aufgabe 2](#aufgabe-2): Betrachtungen einer Klasse `HugeArray` |
| Initialisierung | [Aufgabe 11](#aufgabe-11): Einheitliche Initialisierung und Initialisierungliste (`std::initializer_list<>`) |
| Lambda-Funktionen | [Aufgabe 3](#aufgabe-3): Einfache Realisierung einer Lambda-Funktionen<br/>[Aufgabe 4](#aufgabe-4): Taschenrechner mit Lambda-Funktionen<br/>[Aufgabe 5](#aufgabe-5): Quiz mit Lambda-Funktionen |
| Variadische Templates | [Aufgabe 1](#aufgabe-1): Generische Funktion `miminum`<br/>[Aufgabe 7](#aufgabe-7): Variadische Templates: Ausgabe eines `std::tuple` Objekts<br/>[Aufgabe 12](#aufgabe-12): Logische Operationen mit beliebig vielen Operanden<br/>[Aufgabe 14](#aufgabe-14): `decltype` und Type-Traits am Beispiel von `sameType`<br/>[Aufgabe 20](#aufgabe-20): Mehrere Summen, ein Ergebnis<br/>[Aufgabe 21](#aufgabe-21): Variadische Templates und Vererbung |
| Folding Expressions | [Aufgabe 13](#aufgabe-13): Logische Operationen mit beliebig vielen Operanden<br/>[Aufgabe 15](#aufgabe-15): `decltype` und Type-Traits am Beispiel von `sameType`<br/>[Aufgabe 25](#aufgabe-25): &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum` |
| `std::optional` | [Aufgabe 6](#aufgabe-6): Umwandlung von Zeichenketten in ganze Zahlen |
| `std::variant` | [Aufgabe 18](#aufgabe-18): Ein heterogener Container mit `std::variant` |
| `std::accumulate` | [Aufgabe 24](#aufgabe-24): Die Funktion `std::accumulate` in der Anwendung (mit Initialisierungliste) |
| Metaprogrammierung | [Aufgabe 8](#aufgabe-8): *Fibonacci*-Zahlen |
| Funktionale Programmierung | [Aufgabe 16](#aufgabe-16): Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben<br/>[Aufgabe 17](#aufgabe-17): `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis |
| *Perfect Forwarding* | [Aufgabe 22](#aufgabe-22): Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*<br/>[Aufgabe 23](#aufgabe-23): Ausführungszeit einer Funktion (`std::invoke`, variadische Templates und *Perfect Forwarding*) |
| SFINAE | [Aufgabe 9](#aufgabe-9): Eine Methode, mehrere Implementierungen<br/>[Aufgabe 10](#aufgabe-10): Detektion von Methoden in einer Klasse |
| CRTP | [Aufgabe 19](#aufgabe-19): Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet |

*Tabelle* 1: Zusammenstellung aller Aufgaben.

---

Und alle Aufgaben noch einmal der Reihe nach:

- [Aufgabe 1](#aufgabe-1): Generische Funktion `miminum`
- [Aufgabe 2](#aufgabe-2): Move-Semantik: Betrachtungen einer Klasse `HugeArray`
- [Aufgabe 3](#aufgabe-3): Einfache Realisierung einer Lambda-Funktionen
- [Aufgabe 4](#aufgabe-4): Taschenrechner mit Lambda-Funktionen
- [Aufgabe 5](#aufgabe-5): Quiz mit Lambda-Funktionen
- [Aufgabe 6](#aufgabe-6): `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen
- [Aufgabe 7](#aufgabe-7): Variadische Templates: Ausgabe eines `std::tuple` Objekts
- [Aufgabe 8](#aufgabe-8): Metaprogramming: *Fibonacci*-Zahlen
- [Aufgabe 9](#aufgabe-9): SFINAE: Eine Methode, mehrere Implementierungen
- [Aufgabe 10](#aufgabe-10): SFINAE: Detektion von Methoden in einer Klasse
- [Aufgabe 11](#aufgabe-11): Einheitliche Initialisierung (*Uniform Initialization*) und Initialisierungliste (`std::initializer_list<>`)
- [Aufgabe 12](#aufgabe-12): Variadische Templates: Logische Operationen mit beliebig vielen Operanden
- [Aufgabe 13](#aufgabe-13): Folding Expressions: Logische Operationen mit beliebig vielen Operanden
- [Aufgabe 14](#aufgabe-14): Variadische Templates, `decltype` und Type-Traits am Beispiel von `sameType`
- [Aufgabe 15](#aufgabe-15): Folding Expressions, `decltype` und Type-Traits am Beispiel von `sameType`
- [Aufgabe 16](#aufgabe-16): Funktionale Programmierung: Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben
- [Aufgabe 17](#aufgabe-17): Funktionale Programmierung: `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis
- [Aufgabe 18](#aufgabe-18): `std::variant`: Ein heterogener Container
- [Aufgabe 19](#aufgabe-19): Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet
- [Aufgabe 20](#aufgabe-20): Variadische Templates: Mehrere Summen, ein Ergebnis
- [Aufgabe 21](#aufgabe-21): Variadische Templates und Vererbung
- [Aufgabe 22](#aufgabe-22): Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*
- [Aufgabe 23](#aufgabe-23): Ausführungszeit einer Funktion (`std::invoke`, variadische Templates und *Perfect Forwarding*)
- [Aufgabe 24](#aufgabe-24): Die Funktion `std::accumulate` in der Anwendung
- [Aufgabe 25](#aufgabe-25): Folding Expressions: &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`

---

[Zurück](../../Readme.md)

---

[Lösungen](Exercises.cpp)

---

---

[An den Anfang](#aufgaben)

---

[Zurück](../../Readme.md)

---
