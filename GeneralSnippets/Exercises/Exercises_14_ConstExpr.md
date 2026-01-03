# Aufgaben zu `constexpr`

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Maximum dreier Werte<br/>(Voraussetzungen: `constexpr`, Lambdas und teilweise Templates) |
| *Aufgabe* 2 | Maximum beliebig vieler Werte<br/>(Voraussetzungen: `constexpr`, Lambdas, variadische Templates und Folding) |
| *Aufgabe* 3 | Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit<br/>(Voraussetzungen: `decltype`, `std::is_same`) |

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
das Ergebnis bereits zur Übersetzungszeit berechnet.

*Beispiel*:

```cpp
constexpr auto result = maximum(1, 2, 3);
```

Aus dem Maschinencode des Programms können wir ablesen,
dass der Übersetzer den Wert 3 bereits berechnet hat:

```
constexpr auto result = maximum(1, 2, 3);
00007FF6CEF273CC  mov dword ptr [result1], 3   // <= value 3 resides in machine code  
```

##### Zusatzfrage:

Welche unterschiedlichen Möglichkeiten gibt es in der Deklaration der Schnittstelle der `maximum`-Funktion?
Diskutieren bzw. erläutern Sie die Unterschiede der jeweiligen Deklaration.

---

## Aufgabe 2: Maximum beliebig vieler Werte

#### Voraussetzungen: `constexpr`, Lambdas, variadische Templates und Folding

Als Ergänzung der letzten Aufgabe wollen wir nicht die Fragestellung außer Acht lassen,
ob sich die Realisierung der `maximum`-Funktion nicht auch auf beliebig viele Parameter erweitern lässt?

Natürlich geht das, nur ist in diesem Fall das Repertoire der einzusetzenden Modern C++ Sprachmittel größer.

Schreiben Sie eine Funktion `maximum`, die den maximalen Wert aller übergebenen Parameter berechnet
und als Ergebnis zurückliefert:

```cpp
constexpr int m{ maximum(1, 5, 3, 9, 2) };
```

Für die Übergabe beliebig vieler Argumente an die `maximum`-Funktion verwenden Sie eine Parameterdeklaration
mit variadischen Templates. Alternativ können Sie auch mit `auto` arbeiten.

Die explizite Berechnung des größten Werts auf der Grundlage eines Parameter Packs kann mit *Folding* erfolgen.
Es bietet sich ein Spezialfall dieser Technik an, das so genannte &bdquo;*Folding over a Comma*&rdquo;.

---

## Aufgabe 3: Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit

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
