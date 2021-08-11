# Aufgaben zur Initialisierung

[Zurück](Exercises_Ex.md)

---

[Lösungen](Exercises_11_Initialization.cpp)

---

## Aufgabe 1: Einheitliche Initialisierung (*Uniform Initialization*) und Initialisierungliste (`std::initializer_list<>`)

#### Vorausetzungen: Templates, `std::vector<>`

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

[Lösungen](Exercises_11_Initialization.cpp)

---

[An den Anfang](#Aufgaben-zur-Initialisierung)

---
