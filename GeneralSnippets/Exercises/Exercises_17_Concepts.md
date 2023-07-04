# Aufgaben zu Konzepten

[Zurück](Exercises.md)

---

[Lösungen](Exercises_17_Concepts.cpp)

---

## Aufgabe 1: Überprüfung des Vorhandenseins einer bestimmten Basisklasse

#### Vorausetzungen: `concept`, `requires`

Erstellen Sie ein Konzept, das für ein Klassentemplate überprüft,
dass deren Template Parameter sich von einer bestimmten Basisklasse ableiten.

Wir betrachten die Aufgabenstellung an einem Beispiel.
Die folgende Klasse `Object` sei als Basisklasse für eine Hierarchie von Klassen bestimmt &ndash;
Ähnlichkeiten zur Programmiersprache C# sind rein zufälliger Natur:

```cpp
class Object
{
public:
    virtual ~Object() = default;

    virtual std::string toString() const = 0;
};
```

Offensichtlich soll mit der Klasse `Object` erzwungen werden, dass alle Kindklassen eine Methode `toString` bereitstellen.
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

*Hinweise zur Lösung*:

Im Prinzip bieten sich zwei Lösungansätze an:

  * Verwendung von `std::is_base_of` aus der Type-Traits-Bibliothek.
  * Verwendung von `std::derived_from` aus der Concepts-Bibliothek .

Die beiden Ansätze unterscheiden sich nur in der &ldquo;Vererbungsart&rdquo;,
also inwieweit beim Vererben der Zugriff auf Elemente der Basisklasse eingeschränkt wird.
Dies betrifft die Angabe von `public`, `protected` oder `private` vor dem Namen der Basisklasse.
Derartige Details oder vielleicht besser auch als Feinheiten wollen wir in dieser Aufgabe nicht näher betrachten.
Wir legen der Einfachheit halber die Vererbungsart `public` zu Grunde.

---

## Aufgabe 2: Überprüfung des Datentyps der Parameter einer Funktion

#### Vorausetzungen: `concept`, `requires`

In den Übungen zu variadischen Templates hatten wir zwei Funktionen `andAll` und `orAll`
betrachtet:

```cpp
bool result = andAll(true, false, true);
```

Die beiden Funktionen lassen sich unterschiedlich realisieren.
In allen Fällen tritt als Parameter jedoch ein *Parameter Pack* in Erscheinung,
da gefordert war, dass eine beliebige Anzahl von `bool`-Parametern übergeben werden kann.

Erweitern Sie die vorhandenen Lösungen so, dass neben der reinen Funktionalität
auch der Datentyp der Aktualparameter überprüft wird.
Ein Aufruf von 


```cpp
bool result = andAll(1, 2, 3);
```

soll eine &ndash; soweit möglich &ndash; verständliche Fehlermeldung erzeugen,
also nicht übersetzbar sein!

*Hinweis zur Lösung*:

Die Technik des *Foldings* kann auch auch *Constraints* angewendet werden. 

---

[Lösungen](Exercises_17_Concepts.cpp)

---

[An den Anfang](#Aufgaben-zu-Konzepten)

---
