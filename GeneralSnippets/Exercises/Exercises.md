# Aufgaben

In diesem Abschnitt befinden sich einige kleinere Aufgaben, um den vermittelten Stoff zu vertiefen.

- [Aufgabe 1](#aufgabe-1): Generische Funktion `miminum`.
- [Aufgabe 2](#aufgabe-2): Move-Semantik.
- [Aufgabe 3](#aufgabe-3): Lambda-Funktionen.
- [Aufgabe 4](#aufgabe-4): Taschenrechner mit Lambda-Funktionen.
- [Aufgabe 5](#aufgabe-5): `std::optional`.
- [Aufgabe 6](#aufgabe-6): Variadische Templates.
- [Aufgabe 7](#aufgabe-7): Metaprogramming.
- [Aufgabe 8](#aufgabe-8): SFINAE: Eine Methode, mehrere Implementierungen (typabhängig).
- [Aufgabe 9](#aufgabe-9): SFINAE: Detektion von Methoden in einer Klasse.

---

[Lösungen](Exercises.cpp)

---

## Aufgabe 1

#### Inhalt: Generische Funktion `miminum`

#### Vorausetzungen: Variadische Templates, Utility-Funktion `std::common_type`.

Schreiben Sie eine Funktion `miminum`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert und das Minimum aller Werte berechnet.

Sie dürfen dabei die Annahme zu Grunde legen, dass für alle Argumente
die Funktion `std::common_type` definiert ist.

---

## Aufgabe 2

#### Inhalt: Move-Semantik 

#### Vorausetzungen: keine.

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen.
Analysieren Sie das Code-Fragment: An Hand der Testausgaben sollte man erkennen,
dass ein großes Objekt (Klasse `HugeArray`) insgesamt 5 Mal neu angelegt oder umkopiert wird. Dies soll nun verhindert werden:

  * Fügen Sie der Klasse `HugeArray` eine Definition des Move-Konstruktors und des Move-Wertzuweisungsoperators hinzu.
    Implementieren Sie die beiden Methoden entsprechend. Wieviele echte Kopiervorgänge können Sie nun noch beobachten? (Anwort: 2).
  * Studieren Sie die Testfunktion `testExercise` genau: Ein einer Stelle können Sie durch Einfügen eines
    `std::move`-Aufrufs einen weiteren Kopiervorgang einsparen!
  * Vergleichen Sie die Laufzeiten der Testfunktion vor und nach dem Hinzufügen der Move-Semantik. 
    Welche Beobachtung machen Sie?

*Beispielprogramm*:

```cpp
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

void testExercise() {
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

## Aufgabe 3

#### Inhalt: Lambda-Funktionen 

#### Vorausetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`.

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen.

Ergänzen Sie das Programm um eine Lambda-Funktion, die dieselbe Funktionalität wie Funkion `even` hat,
nur eben als Lambda-Funktion realisiert. Entwickeln Sie des weiteren eine Klasse `Even`,
die die Funktionalität von Funkion `even` als *Funktor* repräsentiert (so genannten *ausführbares Objekt*,
das den `()`-Operator implementiert):

```cpp
inline void even(const int val) {
    if (!(val % 2)) {
        std::cout << val << std::endl;
    }
}
```

Erweitern Sie Ihre Realisierung so, dass der Divisor (Nenner) variabel ist:

<img src="cpp_dividend_divisor.png" width="300">

Abbildung 1: Dividend, Divisor und Quotient.

Dabei soll der Divisor

  * durch eine Variable aus dem Kontext ("*scope*") 
  * durch eine Variable in der Zugriffsklausel

bestimmt werden.

---

## Aufgabe 4

#### Inhalt: Taschenrechner mit Lambda-Funktionen

#### Vorausetzungen: Container `std::map`, Klasse `std::pair`

Erstellen Sie ein `std::map`-Objekt vom Typ `std::map<char, std::function<double(double, double)>>`.
Der zweite Parameter `std::function<double(double, double)>` ist so ausgelegt,
dass er Lambda-Funktionen mit 2 `double`-Parametern und Rückgabewert `double` akzeptiert.
Also zum Beispiel

```cpp
map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
```

oder gerne auch kompakter:

```cpp
map['+'] = [](double a, double b) { return a + b; };
```

Der erste Wert des `std::pair` Objekts ist eine `char`-Variable und spezifiert die arithmetische Operation,
also eine Addition im vorliegenden Beispiel.

Erstellen Sie ein `std::map`-Objekt, dass für die 4 Grundrechenarten
entsprechende Lambda-Funktionen besitzt. Schreiben Sie eine C++-Konsolen-Anwendung,
die 2 `double`-Werte von der Konsole einliest und die entsprechenden Grundrechenarten ausführt.
Ein Testrahmen für Ihre Anwendungen könnte so aussehen:

```cpp
std::map<char, std::function<double(double, double)>> calculator = createCalculator();
double op1, op2;
char op;

std::cout << "Enter first Operand: ";
std::cin >> op1;
std::cout << "Enter second Operand: ";
std::cin >> op2;
std::cout << "Enter operation (+, -, *, /): ";
std::cin >> op;

// do the math
double result = calculator[op](op1, op2);
std::cout << "Result: " << op1 << ' ' << op << ' ' << op1 << " = " << result << '.' << std::endl;
```

*Ausgabe*:

```cpp
Enter first Operand: 1.5
Enter second Operand: 2.7
Enter operation (+, -, *, /): +
Result: 1.5 + 1.5 = 4.2.
```

---

## Aufgabe 5

#### Inhalt: `std::optional`, `if constexpr`

#### Vorausetzungen: Templates Grundlagen

Schreiben Sie eine Funktion `std::optional<int> toInt(std::string)`.
Der Rückgabewert vom Typ `std::optional<int>` darf nur dann einen gültigen `int`-Wert enthalten,
wenn sich die Zeichenkette `s` komplett in eine ganze Zahl umwandeln lässt.

Schreiben Sie eine zweite Funktion `toNumber`:

```cpp
template <typename T>
std::optional<T> toNumber(std::string s);
```

Realisieren Sie die Funkion analog zur Funktion `toInt`. Für `T` sollen die integralen Datentypen
`short`, `int`, `long` und `long long` als Template Argumente möglich sein.

---

## Aufgabe 6

#### Inhalt: Variadische Templates

#### Vorausetzungen: `std::tuple`.

Ein `std::tuple` ist ein Objekt, das eine Sammlung von beliebigen Elementen enthalten kann.
Jedes Element kann dabei von einem anderen Typ sein. Mit der Funktion `std::get<size_t Index>` erhält
man eine Referenz auf das Element an der angegebenen Position `Index` im Tupel.

Schreiben Sie eine generische Funktion `printTuple`, die die Elemente eines Tupels, durch Komma ',' getrennt,
auf der Konsole ausgibt.

*Beispiel*:

```cpp
auto tuple = std::make_tuple(1, std::string("Modern C++"), false, 3.14159);
printTuple(tuple);
```

*Ausgabe*:

```cpp
[1, Modern C++, 0, 3.14159]
```

---

## Aufgabe 7

#### Inhalt: Metaprogramming

#### Vorausetzungen: Keine.

In der Mathematik bilden die *Fibonacci*-Zahlen eine Folge,
so dass jede Zahl die Summe der beiden vorhergehenden Zahlen ist, beginnend mit 0 und 1. 
Für die n.-te Fibonacci F<sub>n</sub> bedeutet das F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>,
wobei F<sub>0</sub> = 0, F<sub>1</sub> = 1 gilt.
Die durch Fibonacci-Zahlen gebildete Sequenz wird als *Fibonacci*-*Sequenz* bezeichnet.

Schreiben Sie eine Schablone `Fibonacci`, die *Fibonacci*-Zahlen zur Übersetzungszeit berechnet.

---

## Aufgabe 8

#### Inhalt: SFINAE: Eine Methode, mehrere Implementierungen (typabhängig).

#### Vorausetzungen: `std::array`

Arrays treten in C++ - unter anderem aus historischen Gründen - mehrfach in Erscheinung:
Als klassisches Array im Stile von C oder als Objekte der Klasse `std::array`.

Schreiben Sie eine Funktion first, die eine Referenz des ersten Arrayelements zurückliefert.
Bei klassischen C-Arrays soll dies die Anfangsadresse des Arrays sein, bei `std::array`
das Iterator-Objekt `begin`.

## Aufgabe 9

#### Inhalt: SFINAE: Detektion von Methoden in einer Klasse.

#### Vorausetzungen: XXX.

Das *Detection Idiom* (zu deutsch etwas "Erkennungsidiom")
ermöglicht die Introspektion eines C++-Klassentyps zur Übersetzungszeit.
Mithilfe dieses Idioms können wir überprüfen, ob eine bestimmte Klasse eine Methode, einen Typaliasnamen
oder ein Element eines bestimmten Namens enthält.

Schreiben Sie eine Funktionsschablobe `testGet<T>`, die `true` oder `false` in Abhängigkeit davon zurückliefert,
ob der Klassentyp `T` eine Methode des Namens `get` besitzt oder nicht.

*Hinweis*:
Erstellen Sie eine Klasseschablone, zum Beispiel `TestMethod`.
Fügen Sie dieser Klasse eine Deklaration der Gestalt

```cpp
static constexpr bool value = testGet<T>(int());
```

hinzu. `testGet` wird mit einer anonymen Funktion aufgerufen,
deren Rückgabewert ein `int`-Parameter ist.

---

[Zurück](../../Readme.md)

---
