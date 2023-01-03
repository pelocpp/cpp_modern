# Aufgaben

[Zurück](../../Readme.md)

---

In diesem Abschnitt befinden sich einige kleinere Aufgaben, um den vermittelten Stoff zu vertiefen.
Folgende Themen werden angesprochen:

  * Einheitliche Initialisierung und Initialisierungliste
  * Move-Semantik
  * Lambda Funktionen
  * Variadische Templates
  * Folding
  * Metaprogrammierung
  * Neue Utility-Klassen und -Funktionen (`std::optional`, `std::variant`, `std::invoke`, `std::visit`)
  * SFINAE
  * CRTP
  * Funktionale Programmierung
  * *Perfect Forwarding*
  * STL-Algorithmus `std::accumulate`

---

Es folgt eine tabellarische Zusammenstellung aller Themenbereiche und Aufgaben:

| Themenbereich | Aufgaben |
| :--- | :--- |
| Move-Semantik | [Aufgabe 2](#aufgabe-2): Betrachtungen einer Klasse `HugeArray` |
| Initialisierung | [Aufgabe 11](#aufgabe-11): Einheitliche Initialisierung und Initialisierungliste (`std::initializer_list<>`) |
| Lambda-Funktionen | [Aufgabe 3](#aufgabe-3): Einfache Realisierung einer Lambda-Funktion<br/>[Aufgabe 4](#aufgabe-4): Taschenrechner mit Lambda-Funktionen<br/>[Aufgabe 5](#aufgabe-5): Quiz mit Lambda-Funktionen |
| Variadische Templates | [Aufgabe 1](#aufgabe-1): Generische Funktion `miminum`<br/>[Aufgabe 7](#aufgabe-7): Variadische Templates: Ausgabe eines `std::tuple` Objekts<br/>[Aufgabe 12](#aufgabe-12): Logische Operationen mit beliebig vielen Operanden<br/>[Aufgabe 14](#aufgabe-14): `decltype` und Type-Traits am Beispiel von `sameType`<br/>[Aufgabe 20](#aufgabe-20): Mehrere Summen, ein Ergebnis<br/>[Aufgabe 21](#aufgabe-21): Variadische Templates und Vererbung |
| Folding Expressions | [Aufgabe 13](#aufgabe-13): Logische Operationen mit beliebig vielen Operanden<br/>[Aufgabe 15](#aufgabe-15): `decltype` und Type-Traits am Beispiel von `sameType`<br/>[Aufgabe 25](#aufgabe-25): &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum` |
| `std::optional` | [Aufgabe 6](#aufgabe-6): Umwandlung von Zeichenketten in ganze Zahlen |
| `std::variant` | [Aufgabe 18](#aufgabe-18): Ein heterogener Container mit `std::variant` |
| `std::accumulate` | [Aufgabe 24](#aufgabe-24): Die Funktion `std::accumulate` in der Anwendung (mit Initialisierungliste) |
| Metaprogrammierung | [Aufgabe 8](#aufgabe-8): *Fibonacci*-Zahlen |
| Funktionale Programmierung | [Aufgabe 16](#aufgabe-16): Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben<br/>[Aufgabe 17](#aufgabe-17): `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis |
| *Perfect Forwarding* | [Aufgabe 22](#aufgabe-22): Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*<br/>[Aufgabe 23](#aufgabe-23): Ausführungszeit einer Funktion (`std::invoke`, variadische Templates und *Perfect Forwarding*) |
| SFINAE | [Aufgabe 9](#aufgabe-9): Eine Methode, mehrere Implementierungen<br/>[Aufgabe 10](#aufgabe-10): Detektion von Methoden in einer Klasse |
| CRTP | [Aufgabe 19](#aufgabe-19): Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet |

*Tabelle* 1: Zusammenstellung aller Aufgaben.

---

Und alle Aufgaben noch einmal der Reihe nach:

- [Aufgabe 1](#aufgabe-1): Generische Funktion `miminum`
- [Aufgabe 2](#aufgabe-2): Move-Semantik: Betrachtungen einer Klasse `HugeArray`
- [Aufgabe 3](#aufgabe-3): Einfache Realisierung einer Lambda-Funktionen
- [Aufgabe 4](#aufgabe-4): Taschenrechner mit Lambda-Funktionen
- [Aufgabe 5](#aufgabe-5): Quiz mit Lambda-Funktionen
- [Aufgabe 6](#aufgabe-6): `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen
- [Aufgabe 7](#aufgabe-7): Variadische Templates: Ausgabe eines `std::tuple` Objekts
- [Aufgabe 8](#aufgabe-8): Metaprogramming: *Fibonacci*-Zahlen
- [Aufgabe 9](#aufgabe-9): SFINAE: Eine Methode, mehrere Implementierungen
- [Aufgabe 10](#aufgabe-10): SFINAE: Detektion von Methoden in einer Klasse
- [Aufgabe 11](#aufgabe-11): Einheitliche Initialisierung (*Uniform Initialization*) und Initialisierungliste (`std::initializer_list<>`)
- [Aufgabe 12](#aufgabe-12): Variadische Templates: Logische Operationen mit beliebig vielen Operanden
- [Aufgabe 13](#aufgabe-13): Folding Expressions: Logische Operationen mit beliebig vielen Operanden
- [Aufgabe 14](#aufgabe-14): Variadische Templates, `decltype` und Type-Traits am Beispiel von `sameType`
- [Aufgabe 15](#aufgabe-15): Folding Expressions, `decltype` und Type-Traits am Beispiel von `sameType`
- [Aufgabe 16](#aufgabe-16): Funktionale Programmierung: Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben
- [Aufgabe 17](#aufgabe-17): Funktionale Programmierung: `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis
- [Aufgabe 18](#aufgabe-18): `std::variant`: Ein heterogener Container
- [Aufgabe 19](#aufgabe-19): Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet
- [Aufgabe 20](#aufgabe-20): Variadische Templates: Mehrere Summen, ein Ergebnis
- [Aufgabe 21](#aufgabe-21): Variadische Templates und Vererbung
- [Aufgabe 22](#aufgabe-22): Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*
- [Aufgabe 23](#aufgabe-23): Ausführungszeit einer Funktion (`std::invoke`, variadische Templates und *Perfect Forwarding*)
- [Aufgabe 24](#aufgabe-24): Die Funktion `std::accumulate` in der Anwendung
- [Aufgabe 25](#aufgabe-25): Folding Expressions: &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`

---

[Zurück](../../Readme.md)

---

[Lösungen](Exercises.cpp)

---

## Aufgabe 1

#### Inhalt: Generische Funktion `miminum`

#### Vorausetzungen: Variadische Templates, Utility-Funktion `std::common_type`

Schreiben Sie eine Funktion `miminum`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert und das Minimum aller Werte berechnet.

Sie dürfen dabei die Annahme zu Grunde legen, dass für alle Argumente
die Funktion `std::common_type` definiert ist.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 2

#### Inhalt: Move-Semantik 

#### Vorausetzungen: Siehe Inhalt

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

[An den Anfang](#aufgaben)

---

## Aufgabe 3

#### Inhalt: Lambda-Funktionen 

#### Vorausetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen.

Ergänzen Sie das Programm um eine Lambda-Funktion, die dieselbe Funktionalität wie Funktion `even` hat,
nur eben als Lambda-Funktion realisiert. Entwickeln Sie des weiteren eine Klasse `Even`,
die die Funktionalität von Funktion `even` als *Funktor* repräsentiert (so genanntes *ausführbares Objekt*,
das den `()`-Operator implementiert):

```cpp
inline void even(const int val) {
    if (!(val % 2)) {
        std::cout << val << std::endl;
    }
}
```

Erweitern Sie Ihre Realisierung so, dass der Divisor (Nenner) variabel ist:

<img src="cpp_dividend_divisor.svg" width="300">

*Abbildung* 1: Dividend, Divisor und Quotient.

Dabei soll der Divisor

  * durch eine Variable aus dem Kontext ("*scope*") 
  * durch eine Variable in der Zugriffsklausel

bestimmt werden.

---

[An den Anfang](#aufgaben)

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
std::cout << "Result: " << op1 << ' ' << op << ' ' << op2 << " = " << result << '.' << std::endl;
```

*Ausgabe*:

```cpp
Enter first Operand: 1.5
Enter second Operand: 2.7
Enter operation (+, -, *, /): +
Result: 1.5 + 1.5 = 4.2.
```

---

[An den Anfang](#aufgaben)

---

## Aufgabe 5

#### Inhalt: Quiz mit Lambda-Funktionen

#### Vorausetzungen: Lambda-Funktionen.

Betrachten Sie die vier Methoden `test_01`, `test_02`, `test_03` und `test_04`:
Erraten Sie die Ausgabe? Begründen Sie Ihre Antworten.

*Quiz 1*:

```cpp
void test_01()
{
    int variable{ 1 };

    auto lambda{ [variable]() mutable {
        std::cout << "Variable: " << variable << std::endl;
        variable++;
        }
    };

    // invoke lambda three times
    lambda();
    lambda();
    lambda();

    std::cout << "Variable: " << variable << std::endl;
}
```

*Quiz 2*:

```cpp
void test_02()
{
    auto L = [val = 10]() mutable { std::cout << val++ << std::endl; };
    L();
    L();
    L();
    L();
    L();
    auto LC = L;
    LC();
    LC();
    LC();
    L();
}
```

*Quiz 3*:

```cpp
void test_03()
{
    int i{ };
    
    // create a lambda named 'count'
    auto count{ [i]() mutable { std::cout << ++i << std::endl; } };
    
    // invoke lambda
    count();
    
    // create a copy of lambda 'count'
    auto otherCount{ count };
    
    // invoke both lambda 'count' and the copy
    count();
    otherCount();
}
```

*Quiz 4*:

```cpp
void invoke(const std::function<void(void)>& fn)
{
    fn();
}

void test_04()
{
    int i{ };

    auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

    invoke(count);
    invoke(count);
    invoke(count);
}
```

---

[An den Anfang](#aufgaben)

---

## Aufgabe 6

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

Realisieren Sie die Funktion analog zur Funktion `toInt`. Für `T` sollen die integralen Datentypen
`short`, `int`, `long` und `long long` als Template Argumente möglich sein.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 7

#### Inhalt: Variadische Templates: Ausgabe eines `std::tuple` Objekts

#### Vorausetzungen: `std::tuple<>`, Non-Type Template Parameter

Ein `std::tuple` ist ein Objekt, das eine Sammlung von beliebigen Elementen enthalten kann.
Jedes Element kann dabei von einem anderen Typ sein. Mit der Funktion `std::get<size_t index>()` erhält
man eine Referenz auf das Element an der angegebenen Position `index` im Tupel.

Schreiben Sie eine generische Funktion `printTuple`, die die Elemente eines Tupels, durch Komma `','` getrennt,
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

[An den Anfang](#aufgaben)

---

## Aufgabe 8

#### Inhalt: Metaprogramming

#### Vorausetzungen: Siehe Inhalt

In der Mathematik bilden die *Fibonacci*-Zahlen eine Folge,
so dass jede Zahl die Summe der beiden vorhergehenden Zahlen ist, beginnend mit 0 und 1. 
Für die n.-te Fibonacci F<sub>n</sub> bedeutet das F<sub>n</sub> = F<sub>n-1</sub> + F<sub>n-2</sub>,
wobei F<sub>0</sub> = 0, F<sub>1</sub> = 1 gilt.
Die durch Fibonacci-Zahlen gebildete Sequenz wird als *Fibonacci*-*Sequenz* bezeichnet.

Schreiben Sie eine Funktionsschablone `Fibonacci`, die *Fibonacci*-Zahlen zur Übersetzungszeit berechnet.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 9

#### Inhalt: SFINAE: Eine Methode, mehrere Implementierungen

#### Vorausetzungen: `std::array`

Arrays treten in C++ - unter anderem aus historischen Gründen - mehrfach in Erscheinung:
Als klassisches Array im Stile von C oder als Objekte der Klasse `std::array`.

Schreiben Sie eine Funktion `first`, die eine Referenz des ersten Arrayelements zurückliefert.
Bei klassischen C-Arrays sollte dies die Anfangsadresse des Arrays sein, bei `std::array`
das Iterator-Objekt `begin`.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 10

#### Inhalt: SFINAE: Detektion von Methoden in einer Klasse

#### Vorausetzungen: Templates, `decltype` und `std::declval`

Das *Detection Idiom* (zu deutsch etwa &ldquo;Erkennungsidiom&rdquo;)
ermöglicht die Introspektion eines C++-Klassentyps zur Übersetzungszeit.
Einfacher ausgedrückt: Mithilfe dieses Idioms können wir überprüfen, ob eine Klasse eine bestimmte Methode
oder ein Element eines bestimmten Namens enthält &ndash; und das zur Übersetzungszeit.

Studieren Sie hierzu das folgende Klassentemplate `MethodDetector`:
Welchen Namen hat die Methode, die hier offensichtlich gesucht wird?
Welche Rolle spielen `decltype` und `std::declval` bei der Suche?

```cpp
01: template <typename T>
02: struct MethodDetector {
03: 
04:     template <typename U, typename TEST = decltype(std::declval<U>().get())>
05:     static constexpr bool detect(int) {
06:         return true;
07:     }
08: 
09:     template <typename U>
10:     static constexpr bool detect(...) {
11:         return false;
12:     }
13: 
14:     static constexpr bool value = MethodDetector::detect<T>(int{});
15: };
```

Es folgen einige Hinweise:<br/>

  * Im Klassentemplate gibt es zwei Methoden namens `detect`:
    Der Rückgabewert ist in beiden Fällen `bool`! 
    Die zweite Überladung akzeptiert bzgl. der aktuellen Parameter &ldquo;alles&rdquo;,
    was durch das Symbol der Ellipses `'...'` zum Ausdruck gebracht wird.

  * Die erste `detect`-Methode besitzt einen `int`-Parameter.
    Dies führt dazu, dass die erste `detect`-Methode gegenüber der zweiten `detect`-Methode, bevorzugt wird,
    wenn sie mit einem `int`-Wert aufgerufen wird.
    Diese Überladung kommt aber nur dann in die engere Auswahl,
    wenn der Ausdruck innerhalb von `decltype`, also die Berechnung des zweiten Template-Parameters `TEST`,
    fehlerfrei aufgelöst werden kann.

  * Je nachdem, für welche Überladung der Übersetzer sich entscheidet, liefert `detect` den Wert `true` oder `false` zurück.
    Die Klassenvariable `value` in Zeile 14 nimmt diesen Wert an.

**Aufgabe**:

Im folgenden sind zwei Klassen `FirstStruct` und `SecondStruct` definiert,
die unterschiedliche Methoden haben (`get` bzw. `getter`):

```cpp
struct FirstStruct {
    int get() { return 123; };
};

struct SecondStruct {
    int getter() { return 456; };
};
```

  * Welche Ausgabe erwarten Sie bei der Ausführung der folgenden beiden Anweisungen?
  * Erklären Sie detailliert, warum sich das Programm so verhält?
  * Welche Regel gilt bei der Auflösung von Funktionsschablonen im Falle von Mehrdeutigkeiten?

```cpp
std::cout
    << "FirstStruct:  "
    << std::boolalpha
    << MethodDetector<FirstStruct>::value
    << std::endl;

std::cout
    << "SecondStruct: "
    << std::boolalpha
    << MethodDetector<SecondStruct>::value
    << std::endl;
```

*Ausgabe*:

```cpp
FirstStruct:  true
SecondStruct: false
```

**Zusatzaufgabe 1**:

Im Lösungsteil finden Sie eine Variation in der Definition der ersten `detect`-Methode vor.
Beschreiben Sie ihre Funktionsweise!

*Antwort*:<br/>
In der ersten Überladung der Variation beachte man,
dass der Ausdruck innerhalb von `decltype` eine Sequenz ist (siehe den Komma-Operator `','`)!
Der Typ des Ausdrucks ist damit gleich dem des letzten Elements in der Sequenz und damit ebenfalls gleich `bool`.

**Zusatzaufgabe 2**:

Wie müsste eine Klasse `MethodDetectorEx` implementiert werden,
die eine Klasse überprüfen kann, ob sie  eine Methode namens `get` mit zwei Parametern des Typs `int` besitzt?
Realisieren und testen Sie eine entsprechende Klasse `MethodDetectorEx`.

*Abschließender Hinweis*: Die Anregungen zu dieser Aufgabe stammen teilweise aus
[C++ Detection Idiom Through the Years](https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php).

---

[An den Anfang](#aufgaben)

---

## Aufgabe 11

#### Inhalt: Einheitliche Initialisierung (*Uniform Initialization*) und Initialisierungliste (`std::initializer_list<>`)

#### Vorausetzungen: Templates, `std::vector<>`, `std::map<>`

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

[An den Anfang](#aufgaben)

---

## Aufgabe 12

#### Inhalt: Variadische Templates: Logische Operationen mit beliebig vielen Operanden

#### Vorausetzungen: Variadische Templates

Schreiben Sie zwei Funktionen `andAll` und `orAll`, die eine variable Anzahl von `bool`-Parametern
logisch UND oder logisch ODER verknüpfen. Mögliche Testbeispiele können so aussehen:

```cpp
bool result = andAll(true, false, true);
std::cout << std::boolalpha << result << std::endl;

result = andAll(true, true, true, true, true, true, true, true, true, true);
std::cout << std::boolalpha << result << std::endl;
```

*Ausgabe*:

```cpp
false
true
```

---

[An den Anfang](#aufgaben)

---

## Aufgabe 13

#### Inhalt: Folding Expressions: Logische Operationen mit beliebig vielen Operanden

#### Vorausetzungen: Variadische Templates

Die Aufgabenstellung ist identisch zur letzten Aufgabe: Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 14

#### Inhalt: Variadische Templates, `decltype` und Type-Traits am Beispiel von `sameType`

#### Vorausetzungen: Templates

Schreiben Sie eine Funktionsschablone `sameType`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert. Der Rückgabewert vom Typ `bool` ist `true`, wenn alle Argumente vom selben Typ
sind, andernfalls `false`.
 
*Beispiel*:

```cpp
int main() {
    bool result;
    result = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result << std::endl;

    result = sameType(1, 2, 3, 4, '?', 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result << std::endl;
    return 1;
}
```

*Ausgabe*:

```cpp
true
false
```

*Zusatzaufgabe*:

Für die logischen Operationen `&&` (`and`) und `||` (`or`) gibt es in höheren Programmiersprachen (C, C++, Java und andere)
das Feature der so genannten "*Short-Circuit-Evaluation*": Ist in dem Ausdruck *condition1 || condition2*
bereits Bedingung *condition1* wahr, so ist der gesamte Ausdruck wahr. Ebenso ist der Ausdruck *condition1 && condition2*
falsch, wenn Bedingung *condition1* falsch ist.
Das Programm führt dann nicht mehr die Bewertung der noch fehlenden Bedingungen durch.

Können Sie das Feature "*Short-Circuit-Evaluation*" in Ihrer Realisierung der Funktion `sameType` anwenden?

---

[An den Anfang](#aufgaben)

---

## Aufgabe 15

#### Inhalt: Folding Expressions, `decltype` und Type-Traits am Beispiel von `sameType`

#### Vorausetzungen: Templates

Die Aufgabenstellung ist identisch zur letzten Aufgabe (ohne Zusatzaufgabe):
Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

*Zusatzfrage*:
Welchen prinzipiellen Unterschied beobachten Sie im Lösungsansatz
von Aufgabe 13 und 15?

---

[An den Anfang](#aufgaben)

---

## Aufgabe 16

#### Inhalt: Funktionale Programmierung &ndash; Umwandlung von Zeichenketten eines `std::vector`-Objekts von Klein- in Großbuchstaben

#### Vorausetzungen: Templates, Lambda-Funktionen

In den beiden Dateien

[FunctionalProgramming01.cpp](../FunctionalProgramming/FunctionalProgramming01.cpp)

und

[FunctionalProgramming02.cpp](../FunctionalProgramming/FunctionalProgramming02.cpp)

finden Sie zwei alternative Implementierungen der drei Funktionen `map`, `filter` und `fold` vor.

**Teilaufgabe 1**:

Studieren Sie den Quellcode der beiden Realisierungen.
Welche prinzipiellen Unterschieden liegen in der Implementierung vor?

**Teilaufgabe 2**:

Es wird ein Vektor mit Zeichenketten betrachtet:

```cpp
std::vector<std::string> words = { 
    std::string("one"),
    std::string("two"),
    std::string("three")
};
```

Mit einer geeigneten Funktion der *funktionalen Programmierung* sollen
die einzelnen Zeichen aller Zeichenketten dieses Vektors in Großbuchstaben umgewandelt werden.
Welche Funktion höherer Ordnung benötigen Sie hierzu?
Schreiben Sie eine Testfunktion, die ihre Realisierung testet. 

---

[An den Anfang](#aufgaben)

---

## Aufgabe 17

#### Inhalt: Funktionale Programmierung &ndash; `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis

#### Vorausetzungen: Kenntnisse von `decltype` und `declval`

Im Code-Snippet zu *Funktionaler Programmierung* haben wir die Funktion höherer Ordnung `fold` betrachtet:

```cpp
template <typename TReturn, typename InputIterator, typename TFunctor>
auto fold(InputIterator begin, InputIterator end, TFunctor&& lambda)
    // not needed, just for demonstration purposes
    -> TReturn
{
    TReturn init{};
    return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
}
```

Die `fold`-Funktion wendet
eine Lambda-Funktion mit zwei Argumenten der Reihe nach auf alle Elemente eines Containers an und
reduziert auf diese Weise die Elemente des Containers auf ein Endergebnis ("Resultat").

Interessant dabei ist, dass der Typ dieses Endergebnisses nicht gleich dem Typ der einzelnen Elemente des Containers sein muss.

**Teilaufgabe 1**:

Wenden Sie die `fold`-Funktion auf einen Vektor mit `int`-Elementen an. Das Ergebnis soll
eine Zeichenkette sein, die alle `int`-Werte des Vektors einzeln in eine Zeichenkette umwandelt und diese miteinander konkateniert.

*Beispiel*:

```cpp
std::vector<int> numbers { 1, 2, 3 } ==> "123"
```

Wie muss die dazugehörige Lambda-Funktion aussehen?

**Teilaufgabe 2**:

C++-Puristen werden bei Betrachtung der `fold`-Funktion eine kleine Redundanz erkannt haben:
Der erste Template-Parameter `TReturn` ist bei strenger Betrachung überflüssig:
Es handelt sich dabei um den Datentyp des Ergebnisses der `fold`-Operation,
aber dieser ist eigentlich an anderer Stelle bereits vorgegeben bzw. bekannt.
Richtig erkannt, der dritte Parameter der `fold`-Funktion ist eine Lambda-Funktion,
deren Rückgabewert identisch mit dem Ergebnistyp der `fold`-Operation ist.

Schreiben Sie mit dieser Erkenntnis eine neue Version der `fold`-Funktion.
Diese muss nun den Rückgabewert an Hand der Template-Parameter berechnen.
Der Rumpf der `fold`-Funktion ist infolgedessen auch kleinen Änderungen unterworfen.

```cpp
template <typename InputIterator, typename TFunctor>
auto foldEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
    // REQUIRED
    -> ???
{
   ...
}
```

*Hinweis*: Diese Teilaufgabe ist wahrlich nicht einfach, mit `decltype` und `declval` erreichen Sie das Ziel!

---

[An den Anfang](#aufgaben)

---

## Aufgabe 18

#### Inhalt: Heterogener Container

#### Vorausetzungen: `std::variant`, `std::visit`, `std::vector`

Für STL-Container in C++ gilt prinzipiell die Anwort auf die Frage "Kann ich einen `std::vector` so verwenden,
dass er Variablen mehr als einen Typs enthält?": Nein!

Diese Aussage ist mit Erscheinen der Klasse `std::variant` etwas in Wanken geraten.
Ein Variant ist in C++ eine Datenstruktur, die zur Laufzeit Variablen unterschiedlichen Typs aufnehmen kann:

```cpp
std::variant<int, double, std::string> myVariant;
```

Also zum Beispiel

```cpp
myVariant = 1; // initially it's an integer
```

Um wiederum zur Laufzeit ermitteln zu können, welche Variable welchen Typs sich in einem Variant befindet,
gibt es die so genannten *Besucher*- / *Visitor*-Objekte:

Ein generischer, nicht-modifizierender Besucher, der das Variant-Objekt nicht verändert, könnte so definiert werden:

```cpp
struct AllInOneVisitor
{
    template <class T>
    void operator()(const T& value) { std::cout << value << std::endl; }
};
```

Um nun ein Variant-Objekt besuchen zu können, gibt es die Standard-Methode `std::visit`:

```cpp
std::variant<int, std::string> myVariant;
myVariant = 123;
std::visit(MyPrintVisitor{}, myVariant);
```

Mit diesem Code-Fragment erhalten wir die Ausgabe `123`.

Versuchen Sie, mit diesen Vorüberlegungen das Code-Fragment

```cpp
std::vector<std::variant<int, std::string>> heterogeneousVec;

heterogeneousVec.emplace_back(12);
heterogeneousVec.emplace_back(std::string("34"));
heterogeneousVec.emplace_back(56);
heterogeneousVec.emplace_back(std::string("78"));

// print them
for (const auto& var : heterogeneousVec) {
    std::visit(MyPrintVisitor{}, var);
}
```

zum Laufen zu bringen.

In einem weiteren Schritt wollen wir diesen Vektor in einer Klasse als Member-Variable ablegen.
Erstellen Sie eine Klasse `HeterogeneousContainer`.

```cpp
HeterogeneousContainer<int, std::string> heterogeneousCont;

heterogeneousCont.Values().emplace_back(12);
heterogeneousCont.Values().emplace_back(std::string("34"));
heterogeneousCont.Values().emplace_back(56);
heterogeneousCont.Values().emplace_back(std::string("78"));

// print them
heterogeneousCont.visit(lambdaAllInOneVisitor);
std::cout << std::endl;
```

Versuchen nun wiederum, dieses Code-Fragment zum Laufen zu bekommen.
Die Methoden `Values` liefert eine Referenz des in der Klasse `HeterogeneousContainer`
gekapselten `std::vector<std::variant<...>`-Objekts zurück.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 19

#### Inhalt:  Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet

#### Voraussetzungen: Polymorphismus, Templates

Polymorphismus ist die Fähigkeit, mehrere Implementierungen für dieselbe Schnittstelle zu unterstützen.
Virtuelle Methoden ermöglichen es abgeleiteten Klassen, Implementierungen aus einer Basisklasse überschreiben.
Wir sprechen hier von der klassischen Form des Polymorphismus, auch als *Late-Bindung* bezeichnet,
weil die Entscheidung, eine bestimmte Methode aufzurufen, zur Laufzeit erfolgt.
Das Gegenteil dazu ist die so genannte "frühe Bindung" (*Early-Bindung*),
die zur Übersetzungszeit stattfindet.

Ein großer Unterschied zwischen beiden Techniken besteht in der Laufzeit des Programms.
Das frühe Binden, das zur Übersetzungszeit stattfindet, ermöglicht es dem Übersetzer,
die Adressen der Methoden direkt im Compilat zu generieren (es eigentlich der *Linker*, auf den wir hier nicht näher eingehen wollen).
Das späte Binden erzwingt den Aufruf einer Methode indirekt über eine Tabelle mit Methodenadressen (*vtable*, *virtual function pointer table*),
die zur Laufzeit adressiert wird. Je nachdem, wie häufig virtuelle Methoden aufgerufen werden,
können die Auswirkungen auf die Laufzeit erheblich sein.

In dieser Übung wollen wir einen Laufzeitvergleich zwischen dem klassischen Polymorphismus
und einer Variation davon, dem "*Curiously Recurring Template Pattern (CRTP)*" anstellen.

Betrachten Sie hierzu das folgende Code-Fragment. Es besteht aus der einfachsten Form einer Hierarchie
von zwei Klassen. Die Methoden besitzen eine triviale Implementierung mit dem Ziel, den C++-Optimizer davon abzuhalten,
die Methodenrümpfe gänzlich wegzuoptimieren. Bei zu trivialen Beispielen erzielen vergleichende Benchmark-Tests
keine seriösen Aussagen.

Stellen Sie das Beispiel-Programm auf CRTP-konforme Klassen um.
Analysieren Sie mit entsprechenden Wiederholungsanweisungen, welchen Unterschied Sie in der Laufzeit der beiden
Testprogramme feststellen können.

*Hinweis*:
Damit Sie die erwünschten Ergebnisse beobachten können, müssen Sie in Ihren Programmeinstellungen
zwingend den "Release"-Modus und die "x64"-Konfiguration eingestellt haben.

Damit zum Beispiel: Sie finden eine Basisklasse `Image` und eine davon abgeleitete Klasse `PngImage` vor.
Die Basisklasse `Image` definiert drei abstrakte Methoden `draw`, `drawPixel` und `getNumPixels`.
Diese werden in der abgeleiteten Klasse mit einiger "Fantasie" der Gestalt überschrieben,
dass sie der C++-Optimierer nicht gänzlich wegoptimieren kann.
Kopieren Sie das Code-Fragment in ihre Entwicklungsumgebung und führen Sie es aus.
Gegebenenfalls müssen Sie die Konstante `MaxIterations` anpassen, damit Sie auf Ihrem Rechner
eine adäquate Laufzeit erzielen.

Realisieren Sie anschließend zwei Klassen `ImageCRTP` und `PngImageCRTP` unter Beachtung
des CRTP-Patterns. Vergleichen Sie die Laufzeiten der beiden Programme. Welche Beobachtung machen Sie?


```cpp
using Clock = std::chrono::high_resolution_clock;
constexpr long MaxIterations = 10000;
constexpr bool Verbose = false;
constexpr int Width = 400;
constexpr int Height = 400;

// classical approach: base class for image types
class Image {
protected:
    long m_width;
    long m_height;

public:
    // c'tor
    Image(int width, int height) : m_width{ width }, m_height{ height } {}

public:
    // public interface
    virtual void draw() = 0;
    virtual void drawPixel(int position) = 0;
    virtual long getNumPixels() = 0;
};

class PngImage : public Image {
private:
    long m_numPixels;
    long m_currPixel;

public:
    PngImage() : Image{ 0, 0 }, m_currPixel(0) { setNumPixels(); }
    PngImage(int width, int height) : Image{ width, height } { setNumPixels(); }

    virtual void draw() override {
        // just to prevent optimizer to optimize "too much" some sloppy stuff
        m_currPixel = 0;
        int numPixels = getNumPixels();
        int currPosition = getCurrPixel();
        while (currPosition != numPixels) {
            drawPixel(currPosition);
            incCurrPixel();
            currPosition = getCurrPixel();
        }
    }

    virtual void drawPixel(int position) override {
        if (Verbose) {
            std::cout << "draw pixel at position " << position << std::endl;
        }
    }

    virtual long getNumPixels() override {
        return m_numPixels;
    }

private:
    // private helper methods
    void setNumPixels() {
        m_numPixels = m_width * m_height;
    }

    long getCurrPixel() {
        return m_currPixel;
    }

    void incCurrPixel() {
        m_currPixel++;
    }
};

// driver code for classical polymorphism benchmark
void test_classic_benchmark()
{
    std::cout << "Classical Polymorphism Benchmark: " << std::endl;

    Image* pImage = new PngImage(Width, Height);

    auto start = Clock::now();

    // call draw several times to make sure performance is visible 
    for (int i = 0; i < MaxIterations; ++i) {
        pImage->draw();
    }

    long pixels = pImage->getNumPixels();
    std::cout << "Pixels: " << pixels << std::endl;

    auto end = Clock::now();
    std::cout << "Time taken: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " microseconds" << std::endl;
}
```

Da es gerade bei dieser Übung immer wieder zu überraschenden Ergebnissen kommt, hier die Resultate
meines Rechners:

```
Classical Polymorphism Benchmark:
Pixels: 160000
Time taken: 2014668 microseconds
CRTP Benchmark:
Pixels: 160000
Time taken: 402634 microseconds
```

---

[An den Anfang](#aufgaben)

---

## Aufgabe 20

#### Inhalt: Variadische Templates: Mehrere Summen, ein Ergebnis

#### Voraussetzungen: Variadische Templates

Ziel dieser Übung ist es, mehrere Möglichkeiten
in der Definition variadischer Templates (Klassenschablone, Funktionsschablone)
zu erlernen. Dazu betrachten wir die Summation einer beliebigen Anzahl von Summanden
auf der Basis von variadischen Templates in mehreren Varianten.

Betrachten Sie die folgenden drei Anweisungen genau:

```cpp
int result1 = sum1<1, 2, 3, 4, 5>::result;
int result2 = sum2(1, 2, 3, 4, 5);
int result3 = sum3<1, 2, 3, 4, 5>();
```

Bei genauem Hinsehen erkennen Sie, ob es sich bei `sum1`, `sum2` und `sum3` um eine
Klassen- oder Funktionsschablone handelt!
Wie könnte eine Realisierung aussehen, um die Anweisungen zu implementieren?

Betrachten Sie Ihre Realisierung mit dem Tool [cppinsights.io](https://cppinsights.io/).
Vollziehen Sie die jeweiligen Umsetzung der Anweisung `sumX(1, 2, 3, 4, 5)`
in C++-Anweisungen *ohne* variadische Templates nach!

---

[An den Anfang](#aufgaben)

---

## Aufgabe 21

#### Inhalt: Variadische Templates und Vererbung

#### Voraussetzungen: Siehe Inhalt

Der Mechanismus variadischer Templates ist auch auf die Vererbung anwendbar.
Studieren Sie dazu folgende Definition einer Klasse `X`:

```cpp
template <typename ... Bases>
class X : public Bases ...
{
public:
    X(const Bases& ... b) : Bases(b)...  {}
};
```

In der nachfolgenden Testmethode finden Sie drei Instanziierungen der Klasse `X` vor:

```cpp
void test()
{
    X o1;

    X<std::string> o2("ABCDEF");
    std::cout << o2.size() << std::endl;  // size is same as length

    X<std::string, std::vector<std::string>> o3("ABCDEF", { "123", "456" });

    std::cout << o3.length() << std::endl;
    std::cout << o3.std::vector<std::string>::size() << std::endl;     // (1)
    std::cout << o3.std::string::size() << std::endl;                  // (2)
    // std::cout << o3.size() << std::endl;  // ambiguous access of 'size'
}
```

  * Welche Ausgaben erwarten Sie  bei Ausführung der Testmethode?
  * Betrachten Sie die Übersetzung der Testmethode mit dem Tool [cppinsights.io](https://cppinsights.io/).
  * Warum ist die in Kommentar gesetzte Anweisung nicht übersetzungsfähig?
  * Erläutern Sie die Syntax der beiden Anweisungen mit den Kommentaren (1) und (2)

---

[An den Anfang](#aufgaben)

---

## Aufgabe 22

#### Inhalt: Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*

#### Voraussetzungen: Siehe Inhalt

Schreiben Sie eine Funktion `list`, die eine variable Anzahl Parameter unterschiedlichen Typs besitzt.
Ein Aufruf der `list`-Funktion gibt jeden Parameter auf der Konsole mit einem anschließenden Zeilenumbruch aus.

*Beispiel*:

```cpp
int n = 123;
const double pi = 3.14;

list(10, "abc", n, pi, 2.4, std::string("ABC"), 99.99f);
```

*Ausgabe*:

```cpp
10
abc
123
3.14
2.4
ABC
99.99
```

*Ergänzung*:

Wie müssen Sie Ihre Realisierung ändern, so dass die Ausgabe von `list` im letzten Beispiel so aussieht:


```cpp
1: 10
2: abc
3: 123
4: 3.14
5: 2.4
6: ABC
7: 99.99
```

---

[An den Anfang](#aufgaben)

---

## Aufgabe 23

#### Inhalt: Ausführungszeit einer Funktion (`std::invoke`, variadische Templates und *Perfect Forwarding*)

#### Voraussetzungen: Siehe Inhalt

Schreiben Sie eine Funktion, die die Ausführungszeit einer weiteren Funktion messen kann.
Diese Funktion soll dabei eine beliebige Anzahl von Formalparametern haben können.

Die Zeitdauer messen wir im einfachsten Fall in Millisekunden.
In einer etwas anspruchsvolleren Lösung ist es auch denkbar, die Zeitmessung in unterschiedlichen Zeitformaten
durchführen zu können (z.B. Sekunden, Millisekunden, Mikrosekunden usw.).

*Hinweise*:

Um die Ausführungszeit einer Funktion zu messen, benötigen wir zunächst die aktuelle Zeit vor dem Aufruf der
Funktion. Führen Sie nach dieser ersten Zeitmessung die eigentliche Funktion aus,
rufen Sie dann die aktuelle Uhrzeit erneut ab und bestimmen Sie die Differenz von den beiden Zeitpunkten.

Einen aktuellen Zeitpunkt können Sie mit der Klasse `std::chrono::high_resolution_clock` ermitteln:

```cpp
std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
```

Für die Differenzbildung zweier Zeitwerte müssen wir die größtmögliche Auflösung `std::chrono::nanoseconds` zugrunde legen,
zum Beispiel:

```cpp
std::chrono::nanoseconds diff = end - start;
```

Um dann wieder zur gewünschten Maßeinheit zurückzugelangen, gibt es die `std::chrono::duration_cast` Methode:

```cpp
std::chrono::duration_cast<std::chrono::milliseconds>(diff);
```

Das Hauptprogramm für diese Übung könnte so aussehen:

```cpp
void g(int a, double b)
{
    // simulate some work (function with parameters)
    std::cout << "calling g with parameters " << a << " and " << b << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void main() 
{
    std::chrono::milliseconds time = ExecutionTimer::duration(g, 10, 20.0);
    std::cout << time.count() << " msecs." << std::endl;
}
```

Die Klasse `ExecutionTimer` mit einer statischen Methode `duration` führt in diesem Beispiel die Funktion `g` aus
und misst ihre Ausführungszeit.

---

## Aufgabe 24

#### Inhalt: Die Funktion `std::accumulate` in der Anwendung (Initialisierungliste)

#### Voraussetzungen: `std::accumulate`

Schreiben Sie zwei Funktionen `andAll` und `orAll`, die eine variable Anzahl von `bool`-Parametern
logisch UND oder logisch ODER verknüpfen. Mögliche Testbeispiele können so aussehen:

```cpp
bool result = andAll({ true, false, true });
std::cout << std::boolalpha << result << std::endl;

result = orAll({ false, false, false, false, false, false, false, false, false, true });
std::cout << std::boolalpha << result << std::endl;
```

Setzen zur Lösung der Aufgabe den STL-Algorithmus `std::accumulate` ein!

*Ausgabe*:

```cpp
false
true
```

## Aufgabe 25

#### Inhalt: &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`

#### Voraussetzungen: Folding Expressions, Lambda Funktionen

Der Zugriff auf die einzelnen Werte eines Parameter Packs ist nicht ganz einfach.
Eine übliche Vorgehensweise ist das so genannte &ldquo;*Folding over a Comma*&rdquo;.
Hierbei handelt es sich um einen *Folding*-Ausdruck, der mit dem Komma-Operator &ndash; gebildet wird.
Der Komma-Operator bewirkt in diesem Fall einzig und allein, dass alle Werte des Parameter Packs sequentiell aufgelistet werden.

Betrachten Sie das nachfolgende Beispiel einer Implementierung der Funktion `minimum`:
Die Funktion kann eine variabel lange Liste von Parametern (mindestens zwei) entgegennehmen und liefert den minimalen Wert zurück.
Erklären Sie die Funktionsweise ihrer Realisierung. Welche Rolle spielt Zeile 14?

```cpp
01: template <typename T, typename ... TARGS>
02: auto minimum(const T& x, const T& y, const TARGS& ... args)
03: {
04:     auto m = (x < y) ? x : y;
05: 
06:     if (sizeof ... (args) > 0) {
07: 
08:         auto helper = [&](const auto& value) {
09:             if (value < m) {
10:                 m = value;
11:             }
12:         };
13: 
14:         (..., helper(args));
15:     }
16: 
17:     return m;
18: }
```

  * Testen Sie die Korrektheit der Funktion `minimum` mit einigen Testbeispielen.
  * Schreiben Sie eine zweite Funktion `maximum`, die das Maximum aller Parameter bestimmt.

---

[An den Anfang](#aufgaben)

---

[Zurück](../../Readme.md)

---
