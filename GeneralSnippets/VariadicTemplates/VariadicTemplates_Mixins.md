# Variadische Templates: Mixins

## Einleitung

Parameter Packs können auch bei der Vererbung eingesetzt werden,
um die Menge der Basisklassen zu definieren,
von denen eine Unterklasse abgeleitet werden soll. Neben dem Begriff *Mixin*
spricht man hier auch von der so genannten *variadischen Vererbung* (*"Variadic" Inheritance*).

## Mixins

Wir betrachten das Ganze am besten an einem Beispiel:

```cpp
// need some classes with default constructors
class A { public: A() = default; };
class B { public: B() = default; };
class C { public: C() = default; };

template <typename ... TS>
class X : public TS...
{
public:
    X(const TS&... mixins) : TS(mixins)... {}
};

void main() {
    A a;
    B b;
    C c;
    X<A, B> xAB(a, b);
    // X<B, A> xBA;   // Error, needs arguments
    X<C> xC(c);
    X<> xNoBases;
}
```

Das Parameter Pack `TS` wird so erweitert, dass jeder darin enthaltene Typ zu einer Basisklasse von `X` wird.
Beachte jedoch, dass die Reihenfolge, in der sie angegeben werden, von Bedeutung ist,
da das Ändern der Reihenfolge zu einem anderen Typ führt - wie unterschiedlich dieser auch sein mag.

---

*Hinweis*:

Bei Mehrfachvererbung gilt:
"Die Reihenfolge der Ableitung ist relevant, um die Reihenfolge der Standardinitialisierung
durch Konstruktoren und der Bereinigung durch Destruktoren zu bestimmen".

---

Aus diesem Grund ist die hier vorgestellte Technik eine ziemlich fragile Methode
zum Spezifizieren von Basisklassen. Sie kann jedoch nützlich sein,
wenn sie als Teil einer Template-Implementierung verwendet wird,
die derlei Abhängigkeiten ausschließen kann.

Betrachen wir den Konstruktor der Klasse X noch einmal detaillierter.
Es sind **zwei** Parameter Pack Expansionen vorhanden:

```cpp
X(const TS&... mixins) : TS(mixins)... {}
```

Das Muster wird für jedes Argument im Parameter Pack einmal instanziiert, also:
Bei beiden oben genannten Erweiterungen wird `TS` durch jeden Typ aus dem Parameterpaket ersetzt,
und `mixins` fungiert als Platzhalter für den jeweiligen Parameternamen.

*Beispiel*:

Der Konstruktor einer Klasse

```cpp
X<A,B,C>
```

wird effektiv erweitert zu


```cpp
X(const A& a, const B& b, const C& c) : A(a), B(b), C(c) {}
```

Wir können uns davon auch mit dem Tool *CppInsight.io* überzeugen:

```cpp
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class X<A, B, C> : public A, public B, public C
{
    public: 
    inline X(const A & __mixins0, const B & __mixins1, const C & __mixins2) :
        A(__mixins0) , B(__mixins1), C(__mixins2) {}
};
#endif
```

Wir können also in C++ eine Klasse erstellen, die von einer beliebigen Anzahl von Basisklassen erbt.
Eine **class C: public T...** wird folglich in eine Klasse `C` wie folgt "transformiert": **class C: public A, public B**.

## Eine Anwendung zu Mixins

Als Beispiel betrachten wir eine *Repository*-Klasse im Sinne eines Assoziativ-Speichers. 
Das Repository-Objekt soll über ein oder mehrere so genannte so genannte *Slots* verfügen,
auf die mit einem Schlüssel (*Key*) zugegriffen werden kann. Ferner enthält ein Slot einen Wert.

Die genaue Intention im Aussehen eines `Repository`-Objekts entnehmen Sie bitte Abbildung 1:

<img src="cpp_snippets_mixins_01.png" width="500">

Abbildung 1: `Repository`-Klasse mit Schlüssel-Wert-Paaren, die via Vererbung verfügbar gemacht werden.

Wir stellen im Folgenden zwei Implementierungen gegenüber:

  * klassischer Ansatz
  * Ansatz mit Mixins

#### Klassischer Realisierung

###### Realisierung:

```cpp
class SlotA
{
public:
    int value;
};

class SlotB
{
public:
    std::string value;
};

// Note: private inheritance, no one can access
// the slots other than Repository itself
class MyRepository : private SlotA, private SlotB
{
public:
    void setSlotA(const int& value)
    {
        // Access the base-class's value: since we have multiple bases
        // with a 'value' field, we need to "force" the access to SlotA.
        SlotA::value = value;
    }

    int getSlotA() 
    {
        return SlotA::value;
    }

    void setSlotB(const std::string& b)
    {
        SlotB::value = b;
    }

    std::string getSlotB()
    {
        return SlotB::value;
    }
};
```

###### Testrahmen:

```cpp
void main() {
    MyRepository repo;

    repo.setSlotA(123);
    std::cout << repo.getSlotA() << std::endl; // printing 123

    repo.setSlotB(std::string("ABC"));
    std::cout << repo.getSlotB() << std::endl; // printing "ABC"
}
```

Man kann unschwer die Nachteile dieser Realisierung erkennen: Für jeden Slot muss man eine eigene Slot-Klasse
definieren. Und zum zweiten muss man für jeden dieser Slots eine separate *getter*- und *setter*-Methode implementieren. 
Die kann man nur als "Copy-Paste"-Programmierung bezeichnen, es muss andere Lösungswege geben.

#### Ansatz mit Mixins

###### Realisierung:

```cpp
template <typename T>
class Slot
{
protected:
    T& get()
    {
        return m_value;
    }

    void set(const T& value) // Same encapsulation.
    {
        m_value = value;
    }

private:
    T m_value;
};

template <typename... Slots>
class Repository : private Slots...  // inherit private from our slots...
{
public:
    template <typename T> // select type
    T& get()
    {
        return Slot<T>::get(); // select base class
    }

    template <typename T>
    void set(const T& value)
    {
        Slot<T>::set(value);
    }
};
```

###### Testrahmen:

```cpp
using MyRepo = Repository< Slot<int>, Slot<std::string> >;

void test_04() {
    MyRepo repo;

    repo.set<std::string>("XYZ");
    repo.set(987); // note type deduction: we pass an int, so it writes to the int slot

    std::cout << repo.get<int>() << std::endl; // printing 987
    std::cout << repo.get<std::string>() << std::endl; // printing "XYZ"
}
```

Dieser zweite Ansatz in der Implementierung einer Klasse `RepositoryEx` nimmt Gestalt an, aber wir sind noch nicht fertig!
Wenn Sie versuchen, zwei `int`-Slots anzulegen, wird ein Kompilierungsfehler ausgegeben:
"*Basisklasse 'Slot' wurde mehrmals als direkte Basisklasse angegeben*".

#### Verbesserung des Mixins-Ansatzes

Wir müssen unsere `Slot`-Klasse um einen zusätzlichen Template Parameter erweiteren (Typ für Schlüssel mit Standardwert).
In Abbildung 2 können wir die Modifikationen erkennen. Wollen wir zwei Slot-Einträge
desselben Typs haben (siehe Typ `std::string` in Abbildung 2), dann sind diese beiden
Einträge durch eine zusätzlichen Schlüsseltyp zu unterscheiden.

<img src="cpp_snippets_mixins_02.png" width="600">

Abbildung 2: Modifikationen am Konzept der Klasse `Slot`.

Dies zieht allerdings eine Änderung der Repository-Methoden nach sich:

###### Realisierung:

```cpp
struct DefaultSlotKey; // forward definition sufficient

template <typename T, typename Key = DefaultSlotKey>
class SlotEx
{
protected:
    T& get()
    {
        return m_value;
    }

    void set(const T& value)
    {
        m_value = value;
    }

private:
    T m_value;
};

template <typename... Slots>
class RepositoryEx : private Slots...  // inherit private from our slots...
{
public:
    template <typename T, typename Key = DefaultSlotKey>
    T& get()
    {
        return SlotEx<T, Key>::get(); // select base class
    }

    template <typename T, typename Key = DefaultSlotKey>
    void set(const T& value)
    {
        SlotEx<T, Key>::set(value);
    }
};
```

###### Testrahmen:

```cpp
// again forward definition sufficient, definition not needed
struct Key1;
struct Key2;

// repository definition with keys
using MyRepoEx = RepositoryEx
    <
    SlotEx<int>,
    SlotEx<std::string, Key1>,
    SlotEx<std::string, Key2>
    >;

void test_06() {
    MyRepoEx repo;

    repo.set(12345); // note type deduction: we pass an int, so it writes to the int slot
    repo.set<std::string, Key1>("AAA");
    repo.set<std::string, Key2>("BBB");

    std::cout << repo.get<int>() << std::endl; // printing 12345
    std::cout << repo.get<std::string, Key1>() << std::endl; // printing "AAA"
    std::cout << repo.get<std::string, Key2>() << std::endl; // printing "BBB"
}
```

#### Realisierung einer `emplace`-Methode

Das vorliegende Beispiel eignet sich sehr gut, um eine `emplace`-Methode zu ergänzen.
Die `emplace`-Methode kennen wir bereits von der Container-Klasse `std::vector`:

`emplace` erstellt ein Objekt an Ort und Stelle, so dass im `std::vector`-Objekt kein temporäres Hilfsobjekt
angelegt werden muss. `emplace` wird direkt mit Argumenten für einen geeignenten Konstruktor
des gewünschten Objekts aufgerufen. In diesem Fall vermeiden wir es also, ein unnötiges
temporäres Objekt zu erstellen und wieder zu zerstören.

Um den geigneten Konstruktor des Zielobjekts zu "finden", verwendet `emplace`
eine variable Anzahl von Argumenten mit unterschiedlichen Typen und leitet sie an den korrespondierenden Konstruktor weiter.
Eine variable Anzahl von Argumenten und Typen muss Sie an etwas erinnern ... variadische Templates!
Damit stellen wir nun unsere Realisierung einer variadischen `emplace`-Methode
sowie ihre Entsprechung in der `Slot`-Klasse vor.
Es genügt die beiden `emplace`-Methoden zu betrachten, der Rest der Implementierung
ändert sich nicht:

###### Realisierung (Klasse `SlotEx`):

```cpp
template <typename... Args>
void emplace(const Args&... args)
{
    m_value = T(args...); // assignement operator (might use move semantics)
}
```

###### Realisierung (Klasse `RepositoryEx`):

```cpp
template <typename T, typename Key = DefaultSlotKey, typename... Args>
void emplace(const Args&... args)
{
    SlotEx<T, Key>::emplace(args...);
}
```

###### Testrahmen:

```cpp
class Person {
private:
    std::string m_firstName;
    std::string m_lastName;
    int m_age;
public:
    Person() : m_firstName(std::string("")), m_lastName(std::string("")), m_age(0) {}

    Person(const std::string& firstName, const std::string& lastName, const int age)
    : m_firstName(firstName), m_lastName(lastName), m_age(age) {}

    Person& operator= (const Person& person) {
        // prevent self-assignment
        if (this == &person)
            return *this;

        // assign right side
        m_firstName = person.m_firstName;
        m_lastName = person.m_lastName;
        m_age = person.m_age;

        return *this;
    }

    Person& operator= (Person&& person) noexcept  { 
        // prevent self-assignment
        if (this == &person)
            return *this;

        // assign right side
        m_firstName = person.m_firstName;
        m_lastName = person.m_lastName;
        m_age = person.m_age;

        // reset source  object, ownership has been moved
        person.m_firstName.clear();
        person.m_lastName.clear();
        person.m_age = 0;

        return *this;
    }

    std::string operator()() { 
    std::ostringstream oss; 
    oss << m_firstName << " " << m_lastName << " [" << m_age << "]"; 
    return  oss.str();
    }
};

void test_07() {
    using MyRepo = RepositoryEx
    <
    SlotEx<Person>,
    SlotEx<std::string>
    >;

    MyRepo repo;

    repo.emplace<std::string>(5, 'A');
    std::cout << repo.get<std::string>() << std::endl; // printing "AAAAA"

    repo.emplace<Person>(std::string("Hans"), std::string("Mueller"), 21);
    std::cout << repo.get<Person>()() << std::endl; // printing "Hans Mueller [21]"
}
```


## Literaturhinweise:

Die Anregungen zu den Beispielen auf diesem Abschnitt sind entnommen aus

[Practical uses for variadic templates](https://crascit.com/2015/03/21/practical-uses-for-variadic-templates/)<br>(abgerufen am 12.05.2020).

und

[Jean Guegant' Blog](https://jguegant.github.io/blogs/tech/thread-safe-multi-type-map.html)<br>(abgerufen am 12.05.2020).
