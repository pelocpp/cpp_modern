# Aufgaben zu variadischen Templates

[Zurück](Exercises.md)

---

[Lösungen](Exercises_05_VariadicTemplates.cpp)

---

## Aufgabe 1: Logische Operationen mit beliebig vielen Operanden

Schreiben Sie zwei Funktionen `andAll` und `orAll`, die eine variable Anzahl von `bool`-Parametern
logisch UND oder logisch ODER verknüpfen. Mögliche Testbeispiele können so aussehen:

```cpp
#include <iostream>

int main() 
{
    bool result { andAll(true, false, true) };
    std::cout << std::boolalpha << result << std::endl;

    result = andAll(true, true, true, true, true, true, true, true, true, true);
    std::cout << std::boolalpha << result << std::endl;
}
```

*Ausgabe*:

```
false
true
```

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---

## Aufgabe 2: `decltype` und Type-Traits am Beispiel von `sameType`

#### Vorausetzungen: `std::is_same`

Schreiben Sie eine Funktionsschablone `sameType`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert. Der Rückgabewert vom Typ `bool` ist `true`, wenn alle Argumente vom selben Typ
sind, andernfalls `false`.
 
*Beispiel*:

```cpp
#include <iostream>

int main() 
{
    bool result;
    result = sameType(43, false, "hello");
    std::cout << std::boolalpha << result << std::endl;
    
    result = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result << std::endl;
}
```

*Ausgabe*:

```
false
true
```

*Zusatzaufgabe*:

Für die logischen Operationen `&&` (`and`) und `||` (`or`) gibt es in höheren Programmiersprachen (C, C++, Java und andere)
das Feature der so genannten "*Short-Circuit-Evaluation*": Ist in dem Ausdruck *condition1 || condition2*
bereits Bedingung *condition1* wahr, so ist der gesamte Ausdruck wahr. Ebenso ist der Ausdruck *condition1 && condition2*
falsch, wenn Bedingung *condition1* falsch ist.
Das Programm führt dann nicht mehr die Bewertung der noch fehlenden Bedingungen durch.

Können Sie das Feature "*Short-Circuit-Evaluation*" in Ihrer Realisierung der Funktion `sameType` anwenden?

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---

## Aufgabe 3: Generische Funktion `miminum`

#### Vorausetzungen: Utility-Funktion `std::common_type`

Schreiben Sie eine Funktion `miminum`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert und das Minimum aller Werte berechnet.

Sie dürfen dabei die Annahme zu Grunde legen, dass für alle Argumente
die Funktion `std::common_type` definiert ist.

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---

## Aufgabe 4: Ausgabe eines `std::tuple` Objekts

#### Vorausetzungen: `std::tuple<T>`, Non-Type Template Parameter

Ein `std::tuple` ist ein Objekt, das eine Sammlung von beliebigen Elementen enthalten kann.
Jedes Element kann dabei von einem anderen Typ sein. Mit der Funktion `std::get<size_t index>()` erhält
man eine Referenz auf das Element an der angegebenen Position `index` im Tupel.

Schreiben Sie eine generische Funktion `printTuple`, die die Elemente eines Tupels, durch Komma `','` getrennt,
auf der Konsole ausgibt.

*Beispiel*:

```cpp
auto tuple {std::make_tuple(1, std::string("Modern C++"), false, 3.14159) };
printTuple(tuple);
```

*Ausgabe*:

```
[1, Modern C++, 0, 3.14159]
```

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---

## Aufgabe 5: Viele Wege führen zum gleichen Ergebnis: Summenbildung natürlicher Zahlen

Ziel dieser Übung ist es, mehrere Möglichkeiten
in der Definition variadischer Templates (Klassenschablone, Funktionsschablone)
zu erlernen. Dazu betrachten wir die Summation einer beliebigen Anzahl von Summanden
auf Basis variadischer Templates in mehreren Varianten.

Studieren Sie die folgenden vier Anweisungen genau:

```cpp
int result1 = sum1<1, 2, 3, 4, 5>::result;
int result2 = sum2(1, 2, 3, 4, 5);
int result3 = sum3<1, 2, 3, 4, 5>();
int result4 = sum4<1, 2, 3, 4, 5>{};
```

*Ausgabe*:

```
15
15
15
15
```

Bei genauem Hinsehen erkennen Sie zunächst, ob es sich bei `sum1`, `sum2`, `sum3`  und `sum4` um eine
Klassen- oder Funktionsschablone handelt!
Wie könnte eine Realisierung aussehen, um die Anweisungen zu implementieren?

*Zusatzaufgabe* 1: Betrachten Sie die einzelnen Realisierungen und überlegen Sie,
welche davon `constexpr`-fähig sind!

*Zusatzaufgabe* 1: Betrachten Sie Ihre Realisierung mit dem
Tool [cppinsights.io](https://cppinsights.io/).
Vollziehen Sie die jeweiligen Umsetzung der Anweisung `sumX(1, 2, 3, 4, 5)`
in C++-Anweisungen *ohne* variadische Templates nach!

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---

## Aufgabe 6: Variadische Templates und Vererbung

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

[Lösungen](Exercises_05_VariadicTemplates.cpp)

---

[An den Anfang](#Aufgaben-zu-variadischen-Templates)

---
