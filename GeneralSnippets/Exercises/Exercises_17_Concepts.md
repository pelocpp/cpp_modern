# Aufgaben zu Konzepten

[Zurück](Exercises.md)

---

[Lösungen](Exercises_17_Concepts.cpp)

---

## Aufgabe 1: Überprüfung des Vorhandenseins einer bestimmten Basisklasse

#### Vorausetzungen: Algorithmus `std::find_if`

Definition eines Konzepts zur Überprüfung auf das Vorhandensein einer bestimmten Basisklasse



Erstellen Sie ein Konzept, das für eine generische Klasse überprüft,
dass deren Template Parameter sich von einer bestimmten Basisklasse ableiten.

Eine Anwendung 

----------


Wie kann ich ein Konzept erstellen, das erfordert, dass meine parametrisierten Typen von einer Basisklasse erben?

Ich erstelle eine stark objektorientierte Klassenhierarchie und möchte,
dass die mit dieser Klassenhierarchie verbundenen Funktionen nur Instanzen von Klassen akzeptieren, die von der Basisklasse dieser Hierarchie abgeleitet sind.

---

Wir betrachten die Aufgabenstellung an einem Beispiel.
Die folgende Klasse sei als Basisklasse für eine Hierarchie von Klassen bestimmt:

```cpp
class Object
{
public:
    virtual ~Object() = default;

    virtual std::string toString() const = 0;
};
```

Offensichtlich soll mit der Klasse `Object` erzwungen werden, dass alle Kindklasse eine Methode `toString` bereitstellen.
Die Klasse `Integer` erfüllt diese Eigenschaft:

```cpp
class Integer : public Object
{
private:
    int m_value;

public:
    Integer() : Integer{ 0 } {};

    Integer(int value) : m_value{ value } {}

    std::string toString() const override
    {
        return "Integer: " + std::to_string(m_value);
    }
};
```

Nun betrachten wir eine Funktionstemplate `print`,
das die Methode `to_string()` des angegebenen Parameters `T` aufruft:

```cpp
template <typename T>
void print(const T& obj)
{
    std::cout << obj.toString() << std::endl;
}
```

Wir können im Augenblick nur &ldquo;nur mit dem Auge erkennen&rdquo;,
dass die `print`-Funkion sinnvollerweise nur mit Template Parametern `T` instanziiert werden kann,
die eine `to_string()`-Methode besitzen.

Wie können Sie das Funktionstemplate `print` schreiben, 
so dass es nur Instanzen von Klassen akzeptiert, die sich von der Klasse `Object` abgeleiten?

## Lösung:

Im Prinzip bieten sich zwei Lösungansätze an:

  * Verwendung von `std::is_base_of` aus der Type-Traits-Bibliothek
  * Verwendung von `std::derived_from` aus der Concepts-Bibliothek 

Die beiden Ansätze unterscheiden sich in der &ldquo;Vererbungsart&rdquo;,
also inwieweit beim Vererben der Zugriff auf Elemente der Basisklasse eingeschränkt wird
(Angabe von `public`, `protected` oder `private` vor dem Namen der Basisklasse).
Derartige Details oder vielleicht besser auch als Feinheiten wollen wir in dieser Aufgabe nicht betrachten.
Wir legen der Einfachheit halber die Vererbungsart `public` zu Grunde.







Beachten Sie, dass sich dieses Verhalten von std::is_base_of unterscheidet, wenn die Basisklasse
eine private oder geschützte Basis von Derived ist.






---

[Lösungen](Exercises_17_Concepts.cpp)

---

Der Link geht nicht

[An den Anfang](#Aufgaben-zu-Konzepten)

---
