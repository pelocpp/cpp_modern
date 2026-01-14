# Aufgaben zu Lambda-Funktionen

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_02_Lambdas.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Einfache Realisierung einer Lambda-Funktion<br/>(Voraussetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`) |
| *Aufgabe* 2 | Taschenrechner mit Lambda-Funktionen<br/>(Voraussetzungen: Container `std::map`, Klasse `std::pair`) | 
| *Aufgabe* 3 | Quiz mit Lambda-Funktionen |

*Tabelle* 1: Aufgaben zu Lambdas.

---

## Aufgabe 1: Einfache Realisierung einer Lambda-Funktion

#### Voraussetzungen: Algorithmus `std::for_each`, bei Bedarf auch `std::generate`

Erstellen Sie eine leeres Visual C++ Projekt,
fügen Sie nachstehenden Quellcode dort ein und bringen Sie das Programm zum Laufen.

Ergänzen Sie das Programm um eine Lambda-Funktion, die dieselbe Funktionalität wie Funktion `evenOrOdd` hat,
nur eben als Lambda-Funktion realisiert. Entwickeln Sie des weiteren eine Klasse `EvenOrOdd`,
die die Funktionalität von Funktion `evenOrOdd` als *ausführbares Objekt* repräsentiert.

```cpp
bool evenOrOdd(int val) {

    if ((val % 2) == 0) {
        std::cout << val << " is even." << std::endl;
        return true;
    }
    else {
        std::cout << val << " is odd." << std::endl;
        return false;
    }
}
```

Erweitern Sie Ihre Realisierung so, dass der Divisor (Nenner) variabel ist:

<img src="cpp_dividend_divisor.svg" width="300">

*Abbildung* 1: Dividend, Divisor und Quotient.

Dabei soll der Divisor

  * durch eine Variable aus dem Kontext ("*Closure*") 
  * durch eine Variable in der Zugriffsklausel ("*Capture Clause*") 

bestimmt werden.

---

## Aufgabe 2: Taschenrechner mit Lambda-Funktionen

#### Voraussetzungen: Container `std::map`, Klasse `std::pair`, Klasse `std::function`

Erstellen Sie ein `std::map`-Objekt vom Typ `std::map<char, std::function<double(double, double)>>`.
Der zweite Parameter `std::function<double(double, double)>` ist so ausgelegt,
dass er Lambda-Objekte mit zwei `double`-Parametern und Rückgabewert `double` akzeptiert.
Also zum Beispiel

```cpp
map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
```

oder gerne auch kompakter:

```cpp
map['+'] = [](double a, double b) { return a + b; };
```

Der erste Wert des `std::pair` Objekts ist eine `char`-Variable und spezifiziert
die arithmetische Operation, also eine Addition im vorliegenden Beispiel.

Erstellen Sie ein `std::map`-Objekt, dass für die 4 Grundrechenarten
entsprechende Lambda-Objekte besitzt. Schreiben Sie eine C++-Konsolen-Anwendung,
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

## Aufgabe 3: Quiz mit Lambda-Funktionen

Betrachten Sie die vier Methoden `test_01`, `test_02`, `test_03` und `test_04`:
Erraten Sie die Ausgabe? Begründen Sie Ihre Antworten.

*Quiz 1*:

```cpp
#include <iostream>

int main ()
{
    int variable{ 1 };
    auto lambda{
        [variable]() mutable {
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
#include <iostream>

int main ()
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
#include <iostream>

int main ()
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
#include <iostream>
#include <functional>

void invoke(const std::function<void(void)>& fn)
{
    fn();
}

int main ()
{
    int i{ };

    auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

    invoke(count);
    invoke(count);
    invoke(count);
}
```

---

[Lösungen](Exercises_02_Lambdas.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
