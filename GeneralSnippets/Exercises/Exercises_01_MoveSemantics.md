# Aufgaben zur Move-Semantik

[Zurück](Exercises.md)

---

[Lösungen](Exercises_01_MoveSemantics.cpp)

---

## Aufgabe 1: Verschiebe-Semantik am Beispiel einer benutzerdefinierten Klasse

Die Verschiebe-Semantik erfordert für Klassen, die sie unterstützen wollen,
eine Implementierung des *Move*-Konstruktors (Verschiebe-Konstruktor) und der *Move*-Wertzuweisung (Verschiebe-Wertzuweisung).
Standard-Klassen aus der STL bringen diese beiden Methoden bereits mit
und damit eben die Fähigkeit des *Verschiebens*.
Wir wollen diese Eigenschaft an einem Beispiel näher unter die Lupe nehmen.
Bringen Sie dazu das folgende Beispiel zum Laufen:

```cpp
#include <iostream>
#include <vector>

class Person {
private:
    std::string m_name;         // name of person
    std::vector<int> m_values;  // some arbitrary person values

public:
    Person() {}
    Person(const std::string& name) : m_name{ name } {}

    void addValue(int value) {
        m_values.push_back(value);
    }

    friend std::ostream& operator<< (std::ostream& os, const Person& cust) {
        os << "{ " << cust.m_name << ": ";
        for (auto val : cust.m_values) {
            os << val << ' ';
        }
        os << "}";
        return os;
    }
};

int main()
{
    // create a person with some initial values
    Person dagobert{ "Dagobert Duck" };
    for (int value : { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) {
        dagobert.addValue(value);
    }

    // print person
    std::cout << "Person: " << dagobert << std::endl;

    // insert person into a collection
    std::vector<Person> persons;
    persons.push_back(dagobert);

    // print person again
    std::cout << "Person: " << dagobert << std::endl;
}
```

Der Ausgabe-Operator `<<` der Klasse `Person` wird in dem Beispiel-Codefragment zweimal aufgerufen.
Betrachten Sie die Ausgaben im Detail.

Offensichtlich wird von der Instanz `dagobert` im Container-Objekt `persons` durch den Aufruf von `push_back`
eine Kopie angelegt.
Wie könnten Sie bewirken, dass die vorliegende `dagobert`-Instanz in das Container-Objekt *verschoben* wird?
Es ist zu diesem Zweck nur eine einzige Zeile des vorliegenden Quellcodes abzuändern!
Welche Auswirkung auf das `dagobert`-Objekt können Sie jetzt bei Ausführung des Programms beobachten?

*Zusatzaufgabe*:
Die Verschiebe-Semantik wird von benutzerdefinierten Klassen nur *automatisch* bereitgestellt,
wenn keine der &bdquo;Big-Five&rdquo;-Methoden in der Klasse explizit vorhanden ist.
Demonstrieren Sie diese Aussage, indem Sie die Klasse `Person` geeignet um eine einzige Quellcodezeile ergänzen.

---

[An den Anfang](#Aufgaben-zur-Move-Semantik)

---

## Aufgabe 2: Verschiebe-Semantik am Beispiel einer Klasse `HugeArray` betrachtet

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen.
Analysieren Sie das Code-Fragment: An Hand der Testausgaben sollte man erkennen,
dass ein großes Objekt (Klasse `HugeArray`) insgesamt 5 Mal neu angelegt oder umkopiert wird. Dies soll nun verhindert werden:

  * Fügen Sie der Klasse `HugeArray` eine Definition des Move-Konstruktors und des Move-Wertzuweisungsoperators hinzu.
    Implementieren Sie die beiden Methoden entsprechend. Wieviele echte Kopiervorgänge können Sie nun noch beobachten? (Anwort: 2).
  * Studieren Sie die Testfunktion `testExercise` genau: Ein einer Stelle können Sie durch Einfügen eines
    `std::move`-Aufrufs einen weiteren Kopiervorgang einsparen!
  * Betrachten Sie die Testfunktion `testExercise` ein zweites Mal genau:
    An einer anderen Stelle lässt sich noch ein Kopiervorgang einsparen, allerdings nicht mit einem `std::move`-Aufruf,
    sondern mit einer anderen Laufzeit-Optimierungstechnik!
  * Vergleichen Sie die Laufzeiten der Testfunktion vor und nach dem Hinzufügen der Move-Semantik. 
    Welche Beobachtung machen Sie?

*Beispielprogramm*:

```cpp
#include <iostream>
#include <chrono>

class HugeArray {
private:
    size_t m_len;
    int* m_data;

public:
    HugeArray();        // default c'tor
    HugeArray(size_t);  // user-defined c'tor
    ~HugeArray();       // d'tor

    // copy semantics
    HugeArray(const HugeArray&);  // copy c'tor
    HugeArray& operator=(const HugeArray&);  // copy assignment
};

HugeArray::HugeArray() : m_len(0), m_data(nullptr) {
    std::cout << "default c'tor" << std::endl;
}

HugeArray::HugeArray(size_t len) : m_len(len), m_data(new int[len]) {
    std::cout << "c'tor (size_t):  " << len << " allocated" << std::endl;
}

HugeArray::~HugeArray() {
    std::cout << "d'tor:           " << m_len << " relased" << std::endl;
    delete[] m_data;
}

// copy semantics
HugeArray::HugeArray(const HugeArray& other) {
    std::cout << "COPY c'tor:      " << other.m_len << " allocated" << std::endl;
    m_len = other.m_len;
    m_data = new int[other.m_len];
    std::copy(other.m_data, other.m_data + m_len, m_data);
}

HugeArray& HugeArray::operator=(const HugeArray& other) {
    std::cout << "COPY assignment: " << other.m_len << " assigned" << std::endl;
    if (this != &other) {
        delete[] m_data;
        m_len = other.m_len;
        m_data = new int[m_len];
        std::copy(other.m_data, other.m_data + m_len, m_data);
    }
    return *this;
}

int main () {
    std::cout << "Start:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<HugeArray> myVec;
    HugeArray bArray(10000000);
    HugeArray bArray2(bArray);
    myVec.push_back(bArray);
    bArray = HugeArray(20000000);
    myVec.push_back(HugeArray(30000000));
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    std::cout << "Done [" << diff.count() << " msecs]" << std::endl;
}
```

---

[Lösungen](Exercises_01_MoveSemantics.cpp)

---

[An den Anfang](#Aufgaben-zur-Move-Semantik)

---
