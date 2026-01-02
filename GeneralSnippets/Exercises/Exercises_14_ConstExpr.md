# Aufgaben zu `constexpr`

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Maximum dreier Werte<br/>(Voraussetzungen: `constexpr`, Lambdas und teilweise Templates) |
| *Aufgabe* 2 | Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit<br/>(Voraussetzungen: `decltype`, `std::is_same`) |

*Tabelle* 1: Aufgaben zu `constexpr`.

---

## Aufgabe 1: Maximum dreier Zahlen

#### Voraussetzungen: `constexpr`, Lambdas und teilweise Templates

Schreiben Sie eine Funktion `maximum`, die zu drei vorgegebenen Zahlen die größte Zahl ermittelt und als Rückgabewert zurückliefert.
Natürlich kommen hier `if`-Anweisungen ins Spiel, es gibt aber durchaus mehrere Möglichkeiten, das Ziel zu erreichen.

Die `maximum`-Funktion soll für alle elementaren Datentypen, die man vergleichen kann, aufrufbar sein.
Inwieweit beim Aufruf der `maximum`-Funktion alle drei Parameter denselben Datentyp haben müssen
oder &bdquo;geringfügige&rdquo; Unterschiede erlaubt sind,
ist Ihrer Entscheidung überlassen.

Die Funktion soll den Qualifizierer `constexpr` besitzen.
Überprüfen Sie Ihre Realisierung darauf hin, dass `maximum` bei konstanten Argumenten oder bei mit `constexpr` deklarierten Variablen
das Ergebnis bereits zur Übersetzungszeit berechnet wird.

*Beispiel*:

```cpp
constexpr auto result = maximum(1, 2, 3);
```

Aus dem Maschinencode des Programms können wir ablesen,
dass der Übersetzer den Wert 3 bereits berechnet hat:

```
constexpr auto result = maximum(1, 2, 3);
00007FF6CEF273CC  mov dword ptr [result1],3  
```

##### Zusatzfrage:

Welche unterschiedlichen Möglichkeiten gibt es in der Deklaration der Schnittstelle der `maximum`-Funktion?
Diskutieren bzw. erläutern Sie die Unterschiede der jeweiligen Deklaration.

---

## Aufgabe 1: *Return Type Resolver*

#### Voraussetzungen: Templates, `std::is_same`, `auto` und `constexpr`

Betrachten Sie die beiden folgenden Quellcodezeilen:

```cpp
int   from_string(const char* str) { return std::stoi(str); }
float from_string(const char* str) { return std::stof(str); }
```

Erklären Sie, warum und welchen Übersetzungsfehler Sie enthalten?

Wir sind im Abschnitt &bdquo;Überladung von Methoden/Operatoren&rdquo; angekommen und hier
beim Spezialfall &bdquo;Eine Überladung einer Funktion kann sich nicht nur durch ihren Rückgabetyp von einer anderen Funktion unterscheiden.&rdquo; angekommen.

Unter dem Stichwort *Return Type Resolver* findet sich eine Lösung dieses Problems &ndash;
natürlich mit einem anderen Realisierungsansatz als dem des fälschlichen Überladens einer Funktion.
Schreiben Sie eine Klasse `FromString`, die auf geschickte Weise den Typkonvertierungsoperator `operator()` überlädt,
um so das folgende Codefragment übersetzen zu können:

```cpp
int n{ FromString{ "123" } };
float f{ FromString{ "45.67f" } };
double d{ FromString{ "89.123" } };

std::cout << n << std::endl;
std::cout << f << std::endl;
std::cout << d << std::endl;
```

*Ausgabe*:

```
123
45.67
89.123
```

*Hilfestellung*:
In der Lösung kommen ein Klassentemplate, *Type Traits* und `constexpr` zum Einsatz.


##### 1. Zusatzfrage:

Testen Sie die Lösung an folgendem, zweiten Codefragment:

```cpp
auto n1{ FromString{ "123" } };
auto f1{ FromString{ "45.67f" } };
auto d1{ FromString{ "89.123" } };
```

  * Ist dieses Codefragment übersetzungsfähig?
  * Wenn ja, wie erklären Sie sich die Ausführung des Programm?
  * Warum ist eine Anweisung der Gestalt `std::cout << n1` nicht übersetzungsfähig?

##### 2. Zusatzfrage:

Wie ließe sich das letze Codefragment umformulieren, um das gewünschte Ziel zu erreichen?

---

## Aufgabe 2: Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit

#### Voraussetzungen: `std::is_same`

Schreiben Sie eine Funktionsschablone `sameType`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert. Der Rückgabewert vom Typ `bool` ist `true`, wenn alle Argumente vom selben Typ
sind, andernfalls `false` *und* ist zur Übersetzungszeit zu berechnen.

*Beispiel*:

```cpp
#include <iostream>

int main() 
{
    constexpr bool result1{ sameType(43, false, "hello") };
    std::cout << std::boolalpha << result1 << std::endl;

    constexpr bool result2{ sameType(1, 2, 3, 4, 5, 6, 7, 8, 9) };
    std::cout << std::boolalpha << result2 << std::endl;
}
```

*Ausgabe*:

```cpp
false
true
```

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
