# Aufgaben zur Initialisierung

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | *Brace Initialization* und Initialisierungliste<br/>(Voraussetzungen: Templates, `std::vector<>`, `std::initializer_list<>`) |
| *Aufgabe* 2 | Ein Zeitvergleich<br/>(Voraussetzungen: `std::vector<>`, `std::initializer_list<>`) |

*Tabelle* 1: Aufgaben zur Initialisierung.

---

[Lösungen](Exercises_11_Initialization.cpp)

---

## Aufgabe 1: *Brace Initialization* und Initialisierungliste

#### Voraussetzungen: Templates, `std::vector<>`, `std::initializer_list<>`

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen:

```cpp
#include <iostream>
#include <vector>

class IntegerContainer
{
private:
    std::vector<int> m_data;

public:
    // c'tors
};

int main ()
{
}
```

Ergänzen Sie die Klasse `IntegerContainer` in der Weise,
dass Sie folgende Konstruktoren zur Verfügung haben:

  * Standardkonstruktor
  * Konstruktor mit zwei Argumenten des Typs `int`
  * Konstruktor mit Initialisierungs-Liste des Typs `int`

Testen Sie Ihre Realisierung mit folgenden Anweisungen:

```cpp
IntegerContainer container1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
IntegerContainer container2;
IntegerContainer container3{};
IntegerContainer container4(1, 2);
```

Prüfen Sie nun, welche Instanziierung welchen Konstruktor aufruft:

  * Instanz `IntegerContainer container1;`
  * Instanz `IntegerContainer container2{ };`
  * Instanz `IntegerContainer container3(1, 2);`
  * Instanz `IntegerContainer container4{1, 2};`

Entfernen Sie nun wahlweise einen Konstruktor, um auf diese Weise zu erkennen,
welche dieser Konstruktoren auch auf andere Konstruktoren ausweichen können!

---

## Aufgabe 2: Zeitvergleich im Gebrauch von Vektoren und Initialisierungslisten

Die Übergabe einer Liste von Daten desselben Typs
an eine Funktion (Methode) könnte man in C++ prinzipiell auf zwei Weisen
realisieren: Mit einem Parameter des Typs `std::vector<>` oder `std::initializer_list<>`.

Man würde sogar beim Aufruf einer solchen Methode nicht einmal einen Unterschied
in der Schreibweise erkennen,
wenn die Daten der Liste *in-place* beim Aufruf platziert werden:

```cpp
transferData({ "A", "B", "C", "D", "E", "F", /* ... */ "X", "Y", "Z" });
```

Ungeachtet der Schreibweise gibt es aber einen signifikanten Unterschied
im Gebrauch eines `std::initializer_list<>`- bzw. `std::vector<>`-Objekts:

  * `std::vector<>` &ndash; Daten liegen auf dem *Heap*.
  * `std::initializer_list<>` &ndash; Daten liegen auf dem *Stack*.

Prinzipiell ist der Einsatz der dynamischen Speicherverwaltung Laufzeit-intensiver,
da Methoden der Freispeicherverwaltung involviert sind (`new`, `delete`).

Realisieren Sie zwei Überladungen einer Methode `transferData`,
jeweils mit einem Parameter des Typs `std::initializer_list<>` bzw. `std::vector<>`.
Rufen Sie die beiden Methoden mit einer Liste von `std::string`-Objekten auf
und stellen Sie einen Laufzeitvergleich an:

```cpp
transferData({
    "A", "B", "C", "D", "E", "F", "G", "H", "I",
    "J", "K", "L", "M", "N", "O", "P", "Q", "R",
    "S", "T", "U", "V", "W", "X", "Y", "Z"
});
```

Welches Ergebnis können Sie beobachten?

*Hinweis*: Man könnte argumentieren, dass der Einsatz von `std::string`-Objekten
zusätzliche Rechenzeit bzgl. der dynamischen Freispeicherverwaltung in Anspruch nimmt.
Dies ist in unserem Beispiel **nicht** der Fall, da hier auf Grund der kurzen Zeichenketten
die SSO (*Small String Optimization*) zum Einsatz gelangt!

Zum Messen der Zeit können Sie folgende Code-Snippets verwenden:

```cpp
void printResults(
    std::string tag,
    std::chrono::high_resolution_clock::time_point startTime,
    std::chrono::high_resolution_clock::time_point endTime)
{
    std::cout
        << tag
        << std::fixed
        << std::setprecision(6)
        << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count()
        << " msecs."
        << std::endl;
}
...
const auto startTime{ std::chrono::high_resolution_clock::now() };
... // <== do work
const auto endTime{ std::chrono::high_resolution_clock::now() };
printResults("std::initializer_list: ", startTime, endTime);
```

---

[Lösungen](Exercises_11_Initialization.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
