# Aufgaben zur Initialisierung

[Zurück](Exercises.md)

---

[Lösungen](Exercises_11_Initialization.cpp)

---

## Aufgabe 1: *Uniform Initialization* und Initialisierungliste

#### Vorausetzungen: Templates, `std::vector<>`, `std::initializer_list<>`

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen:

```cpp
template <typename T>
class MyContainer {
private:
    std::vector<T> m_data;

public:
    void operator()() {
        std::cout << "  [";
        for (auto data : m_data) {
            std::cout << data << ' ';
        }
        std::cout << ']' << std::endl;
    }
};

int main () {
    return 0;
}
```

Ergänzen Sie die Klasse `MyContainer` in der Weise,
dass Sie folgende Konstruktoren zur Verfügung haben:

  * Standardkonstruktor
  * Konstruktor mit zwei Argumenten des Typs `T`
  * Konstruktor mit Initialisierungsliste des Typs `T`

Testen Sie Ihre Realisierung mit folgenden Anweisungen:

```cpp
// using MyContainer with int
MyContainer<int> container1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
container1();

// using MyContainer with std::string
MyContainer<std::string> container2{ "range", "-", "based", "for", "loop" };
container2();
```

Prüfen Sie nun, welche Instanziierung welchen Konstruktor aufruft:

  * Instanz `MyContainer<int> container3;`
  * Instanz `MyContainer<int> container4{ };`
  * Instanz `MyContainer<int> container5(1, 2);`
  * Instanz `MyContainer<int> container6{1, 2};`

Entfernen Sie nun nach und nach einen Konstruktor, um auf diese Weise zu erkennen,
welche dieser Konstruktoren auch auf andere Konstruktoren ausweichen können!

---

## Aufgabe 2: Zeitvergleich im Gebrauch von Vektoren und Initialisierunglisten

Die Übergabe einer Liste von Daten desselben Typs
an eine Funktion (Methode) könnte man in C++ prinzipiell auf 2 Weisen
realisieren:
Mit einem Parameter des Typs `std::vector<>` oder `std::initializer_list<>`.

Man würde sogar beim Aufruf einer solchen Methode nicht einmal einen Unterschied
in der Schreibnweise erkennen,
wenn die Daten der Liste *in-place* beim Aufruf platziert werden:

```cpp
transferData({ "A", "B", "C", "D", "E", "F", /* ... */ "X", "Y", "Z" });
```

Ungeachtet der Schreibweise gibt es aber einen signifikanten Unterschied
im Gebrauch eines `std::initializer_list<>`- oder `std::vector<>`-Objekts:

  * `std::vector<>` &ndash; Daten liegen auf dem Heap.
  * `std::initializer_list<>` &ndash; Daten liegen auf dem Stack.

Prinzipiell ist der Einsatz der dynamischen Speicherverwaltung Laufzeit-intensiver,
da Methoden der Freispeicherverwaltung involviert sind (`new`, `delete`).

Realisieren Sie zwei Überladungen einer Methode `transferData`,
jeweils mit einem Parameter des Typs `std::initializer_list<>` bzw. `std::vector<>`.
Rufen Sie die beiden Methoden mit einer Liste von `std::string`-Objekten auf
und stellen Sie einen Zeitvergleich an:

```cpp
transferData({
    "A", "B", "C", "D", "E", "F", "G", "H", "I",
    "J", "K", "L", "M", "N", "O", "P", "Q", "R",
    "S", "T", "U", "V", "W", "X", "Y", "Z"
});
```

Welches Laufzeitergebnis können Sie beobachten?

*Hinweis*: Man könnte argumentieren, dass der Einsatz von `std::string`-Objekten
zusätzliche Rechenzeit bzgl. der dynamischen Freispeicherverwaltung generiert.
Dies ist **nicht** der Fall, da in unserem Beispiel (kurze Zeichenkette)
die SSO (*Small String Optimization*) vorhanden ist!

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

[An den Anfang](#Aufgaben-zur-Initialisierung)

---
