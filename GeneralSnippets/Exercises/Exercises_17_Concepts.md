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

Nun betrachten wir ein Funktionstemplate `print`,
das die Methode `to_string()` an einem Objekt `obj` des angegebenen Parametertyps `T` aufruft:

```cpp
template <typename T>
void print(const T& obj)
{
    std::cout << obj.toString() << std::endl;
}
```

Wir können im Augenblick nur &bdquo;mit dem Auge&rdquo; erkennen,
dass die `print`-Funktion sinnvollerweise nur mit (benutzerdefinierten) Datentypen instanziiert werden kann,
die eine `toString()`-Methode besitzen.

Wie können Sie das Funktionstemplate `print` umschreiben, 
so dass es nur Instanzen von Klassen akzeptiert, die sich von der Klasse `Object` ableiten?

*Hinweise zur Lösung*:

Im Prinzip bieten sich zwei Lösungansätze an:

  * Verwendung von `std::is_base_of` aus der Type-Traits-Bibliothek.
  * Verwendung von `std::derived_from` aus der Concepts-Bibliothek .

Die beiden Ansätze unterscheiden sich nur in der &bdquo;Vererbungsart&rdquo;,
also inwieweit beim Vererben der Zugriff auf Elemente der Basisklasse eingeschränkt wird.
Dies betrifft die Angabe von `public`, `protected` oder `private` vor dem Namen der Basisklasse.
Derartige Details oder Feinheiten wollen wir in dieser Aufgabe nicht näher betrachten,
dieser Hinweis ist nur der Vollständigkeit halber gegeben.
Der Einfachheit halber legen wir die Vererbungsart `public` zu Grunde.

---

[An den Anfang](#aufgaben-zu-konzepten)

---

## Aufgabe 2: Überprüfung des Datentyps von Funktionsparametern

#### Vorausetzungen: `concept`, `requires`

In den Übungen zu variadischen Templates hatten wir zwei Funktionen `andAll` und `orAll`
betrachtet:

```cpp
bool result = andAll(true, false, true);
```

Die beiden Funktionen lassen sich unterschiedlich realisieren.
In allen Fällen tritt als Parameter jedoch ein *Parameter Pack* in Erscheinung,
da gefordert war, dass eine *beliebige* Anzahl von `bool`-Parametern an die Funktionen
übergeben werden kann.

Erweitern Sie die vorhandenen Lösungen so, dass neben der reinen Funktionalität
auch der Datentyp der Aktualparameter überprüft wird. Es sind nur Werte
des Typs `bool` zulässig. Ein Aufruf von 

```cpp
bool result = andAll(1, 2, 3);
```

soll eine &ndash; soweit möglich &ndash; verständliche Fehlermeldung erzeugen,
also nicht übersetzbar sein!

*Hinweis zur Lösung*:<br />
Die Technik des *Foldings* kann auch auch *Konzepte* angewendet werden. 

---

[An den Anfang](#aufgaben-zu-konzepten)

---

## Aufgabe 3: Konzepte und Schnittstellen im Vergleich

#### Vorausetzungen: `concept`, `requires`, `virtual`

Betrachten wir folgendes Funktionstemplate:

```cpp
template <typename T>
int count(T& t)
{
    int count{};

    t.reset();
    while (t.hasNext()) {
        t.next();
        count++;
    }

    return count;
}
```

Um das Funktionstemplate `count` instanziieren zu können, benötigen wir eine Klasse,
die eine bestimmte Schnittstelle unterstützt. Welche Schnittstelle?
Das erkennen wir nur beim genauen Betrachten des Rumpfes von `count`:
Es müssen drei Methoden `hasNext`, `next` und `reset` mit der jeweils richtigen Signatur
vorhanden sein.

Eine Überprüfung dieses Sachverhalts könnte man in C++ mit
dem Schnittstellenkonzept erzielen:

```cpp
class IntegerIterable
{
public:
    virtual bool hasNext() const = 0;
    virtual int next() = 0;
    virtual void reset() = 0;
};
```

Diesen Schnittstellentyp kann man nun als Parameter von Funktionen verwenden
(wir haben es dann nicht einmal mehr mit einem Funktionstemplate zu tun):

```cpp
int count(IntegerIterable& t)
{
   ...
}
```

Diese Vorgehensweise ist aber so nicht immer erwünscht.
Einer von mehreren Gründen, der dagegegen spricht, ist der Umstand,
dass virtuelle Methoden zur Laufzeit nicht so performant wie direkte Methodenaufrufe sind.

Definieren Sie &ndash; in Gestalt eines alternativen Ansatzes &ndash; 
ein Konzept `IsIterable`, das die drei Methoden `hasNext`, `next` und `reset` festschreibt.

Testen Sie Ihre Realisierung des Konzepts, indem Sie eine Klasse `IterableArray` schreiben,
die das Konzept erfüllt.

---

## Aufgabe 4: Berechnung der Gesamtlänge beliebig vieler Zeichenketten

#### Vorausetzungen: `requires`, `std::initializer_list`

Schreiben Sie eine Funktion `totalLength`, die eine variable Anzahl von `std::string`-Parametern besitzt.
Als Rückgabewert liefert sie die Gesamtlänge aller Zeichenketten zurück.
Ein mögliches Testbeispiel sieht so aus:

```cpp
const std::string s1{ "111" };
const std::string s2{ "AAAAA" };
const std::string s3{ "!!!" };
size_t len{ totalLength(s1, s2, s3) };
std::cout << len << std::endl;
```

*Ausgabe*:

```cpp
11
```

*Hinweis*: In der Implementierung der `totalLength`-Funktion kann ein `std::initializer_list`-Objekt behilflich sein!

---

[Lösungen](Exercises_17_Concepts.cpp)

---

[An den Anfang](#aufgaben-zu-konzepten)

---
