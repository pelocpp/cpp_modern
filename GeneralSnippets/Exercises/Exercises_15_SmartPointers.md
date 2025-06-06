# Aufgaben zu Smart Pointer

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_15_SmartPointers.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| *Aufgabe* 2 | Noch ein Quiz zu Smart Pointer<br/>(Vorausetzungen: `std::shared_ptr<>`) |
| *Aufgabe* 3 | Betrachtungen eines &bdquo;nicht besitzenden&rdquo; Zeigers<br/>(Vorausetzungen: `std::shared_ptr<>`, `std::weak_ptr<>`) |

*Tabelle* 1: Aufgaben zu Smart Pointer.

---

## Aufgabe 1: Quiz zu Smart Pointer

#### Vorausetzungen: `std::shared_ptr<>`

Studieren Sie das folgende Code-Fragement genau.
Welchen Wert hat der Referenzzähler des Objekts `pC` in der letzten Zeile?

```cpp
01: class X {};
02: 
03: std::shared_ptr<X> pA;
04: std::shared_ptr<X> pB;
05: std::shared_ptr<X> pC;
06: 
07: pA = std::make_shared<X>();
08: pB = pA; 
09: pC = std::move(pA);
10: pB = nullptr;
```

---

## Aufgabe 2: Noch ein Quiz zu Smart Pointer

#### Vorausetzungen: `std::shared_ptr<>`

Studieren Sie das folgende Code-Fragement genau.

  * Welchen Wert erwarten Sie in der Ausgabe von Zeile 19?
  * Wie erklären Sie sich das vorliegende Laufzeitverhalten des Programms?
  * Welcher prinzipielle Programmierfehler liegt in diesem Code-Fragment vor?

```cpp
01: class X
02: {
03: public:
04:     X() : m_value{ 123 } {}
05:     int getValue() const { return m_value; }
06: 
07: private:
08:     int m_value;
09: };
10: 
11: std::shared_ptr<X> pA{ new X{} };
12: std::shared_ptr<X> pB;
13: std::shared_ptr<X> pC;
14: 
15: pB = pA;
16: pC = std::shared_ptr<X>{ pB.get() };
17: pC = nullptr; 
18: int value = (*pB).getValue();
19: std::cout << "Value: " << value << std::endl;
```

---

## Aufgabe 3: Betrachtungen eines &bdquo;nicht besitzenden&rdquo; Zeigers

#### Voraussetzungen: `std::shared_ptr<>` und `std::weak_ptr<>`

Wir betrachten in dieser Übungsaufgabe die Situation, dass wir zu einem Objekt
(hier: dynamisch allokierte Variable vom Typ `int`)
eine Zeigervariable haben möchten, aber nicht um den Preis, dass wir damit
einen Anspruch auf Eigentum erheben.
Natürlich könnten wir einen klassischen &bdquo;raw&rdquo; Zeiger verwenden,
um die Idee eines &bdquo;nicht besitzenden&rdquo; Zeigers auszudrücken,
aber in Zeiten von *Modern C++* ist das keine opportune Lösung.
Außerdem bestünde dann die Gefahr, dass der tatsächliche Eigentümer des referenzierten Objekts beschließen könnte,
dieses freizugeben.
Wenn wir dann den &bdquo;nicht besitzenden&rdquo; Zeiger dereferenzieren, käme es zu einem Absturz.

Studieren Sie vor dem geschilderten Hintergrund das folgende Szenario:

  * Wie erklären Sie sich das vorliegende Laufzeitverhalten dieses Code-Fragments?
  * Welcher prinzipielle Programmierfehler liegt in diesem Code-Fragment vor?

```cpp
#include <iostream>
#include <memory>

class UnsafeWatcher {
private:
    int* m_ptr;

public:
    UnsafeWatcher() : m_ptr{ nullptr } {}

    void watch(const std::shared_ptr<int>& sp)
    {
        m_ptr = sp.get();
    }

    int currentValue() const
    {
        return *m_ptr;
    }
};

int main()
{
    UnsafeWatcher watcher;

    {
        std::shared_ptr<int> sp{ std::make_shared<int>(123) };
        watcher.watch(sp);
        std::cout << "Value: " << watcher.currentValue() << std::endl;
    }

    std::cout << "Value: " << watcher.currentValue() << std::endl;
}
```

---

Alternativ zum letzten Beispiel könnten wir in der Klasse `UnsafeWatcher` eine `std::shared_ptr`-Variable verwenden.
Damit würden wir aber zu einem Besitzer des Zeigers und verlassen den Ansatz eines &bdquo;nicht besitzenden&rdquo; Zeigers!
Auch dies wollen wir mit einem Beispiel untermauern:

```cpp
#include <iostream>
#include <memory>

class HeavyAndSafeWatcher {
private:
    std::shared_ptr<int> m_ptr;

public:
    HeavyAndSafeWatcher() {}

    void watch(const std::shared_ptr<int>& sp)
    {
        m_ptr = sp;
    }

    int currentValue() const
    {
        return *m_ptr;  // m_ptr is always alive!
    }
};

int main()
{
    HeavyAndSafeWatcher watcher;

    {
        std::shared_ptr<int> sp{ std::make_shared<int>(123) };
        watcher.watch(sp);
        std::cout << "Value: " << watcher.currentValue() << std::endl;
    }

    std::cout << "Value: " << watcher.currentValue() << std::endl;
}
```

*Aufgabe*: 

  * Vergleichen und erklären Sie das Laufzeitverhalten der beiden Code-Fragmente (Klassen `UnsafeWatcher` und `HeavyAndSafeWatcher`)?
  * Schreiben Sie das letzte Code-Fragment so um, dass die `HeavyAndSafeWatcher`-Klasse
    einen nicht-besitzenden Zeiger besitzt, der Zugang zu einem korrespondierenden `std::shared_ptr`-Objekt hat und in der Lage ist, 
    dessen Kontrollblock abzufragen und zu entscheiden, ob das referenzierte Objekt noch existiert oder nicht.

*Hinweis*: 

Die gesuchte primitive Operation ist *multithreading sicher*!
Sie liefert eine besitzende Referenz (`std::shared_ptr`-Variable) auf das
referenzierte Objekt zurück, wenn dieses noch existiert, oder zeigt andernfalls einen Fehler an.

Man könnte auch die Formulierung wählen, dass wir auf der Suche nach einer &bdquo;Fahrkarte&rdquo;
für ein `std::shared_ptr`-Objekt sind.
Das Ticket selbst steht für einen nicht-besitzenden Zeiger,
man kann es zu einem späteren Zeitpunkt gegen ein `std::shared_ptr`-Objekt eintauschen &ndash; sofern
das referenzierte Objekt noch existiert.

---

[Lösungen](Exercises_15_SmartPointers.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
