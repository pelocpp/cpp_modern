# Lambda-Funktionen

[Zurück](../../Readme.md)

---

[Quellcode 1 - Motivation, allgemeine Beispiele](Lambda01.cpp)

[Quellcode 2 - Lambda und Closure](Lambda02.cpp)

[Quellcode 3 - Lambda und Closure: Spezialfall `this`](Lambda03.cpp)

[Quellcode 4 - Lambda und das Visitor-Pattern](Lambda04.cpp)

---

*Allgemeines*:

Es werden folgende Überlegungen der Reihe nach betrachtet:

  * Betrachtung 1:</br>Sortieren eines Vektors mit einer globalen Funktion.</br>

  * Betrachtung 2:</br>Sortieren eines Vektors mit einem Funktionsobjekt (also ohne Lambda-Methode):</br>
    Man erkennt, dass es im Prinzip einer zusätzlichen Klasse (Struktur) bedarf, um
    `std::sort` mit einer Vergleichsmethode aufrufen zu können.

  * Betrachtung 3:</br>Wie Betrachtung 2, nur mit einer lokalen Struktur:</br>
    Es wird gezeigt, dass Strukturdefinitionen auch lokal in einer Funktion möglich sind.

  * Betrachtung 4:</br>Sortieren eines Vektors mit Lambda-Methode:</br>
    Es wird eine einfache Lambda-Methode vorgestellt.

  * Betrachtung 5:</br>Blick auf die *Capture Clause*: / Zugriffsklausel</br>
    Es wird auf die Lambda-Zugriffsklausel (engl.: *Capture Clause*) eingegangen.


Aus dem engl. C++-Manual habe ich einen Überblick bzgl. der Gestaltungsmöglichkeiten der Zugriffsklausel übernommen:

| Capture Clause Example | Explanation |
|:-------------- |-----------------------------------------|
| `[]` | Capture nothing |
| `[&]` | Capture any referenced variable by reference |
| `[=]` | Capture any referenced variable by making a copy |
| `[=, &foo]` | Capture any referenced variable by making a copy, but capture variable `foo` by reference |
| `[&, foo]` | Capture any referenced variable by reference, but capture variable `foo` by making a copy |
| `[bar]` | Capture `bar` by making a copy; don't copy anything else |
| `[this]` | Capture the `this` pointer of the enclosing class |

Tabelle 1: Liste aller Optionen für die Lambda-Zugriffsklausel.


Das Feature der *Capture Clause*, den Zugriff auf Variablen der &ldquo;Umgebung&rdquo; genauer festzulegen,
ist nicht mit der Möglichkeit zu verwechseln, **innerhalb** einer *Capture Clause*
Instanzvariablen des zu einer Lambda-Funktion gehörenden Funktions-Objekts zu definieren:

```cpp
auto lambda = [counter = 10]() { ... };
```

Die `counter`-Variable ist nur **in** der Lambda-Funktion verfügbar.

Neben der Zugriffsklausel kann eine Lambda-Funktion mit zahlreichen Schlüsselwörtern *garniert* werden.
Siehe hierzu Abbildung 1:

<img src="cpp_snippets_lambda.svg" width="300">

Abbildung 1: Besonderheiten im Aufbau einer Lambda-Funktion.

---

[Zurück](../../Readme.md)

---
