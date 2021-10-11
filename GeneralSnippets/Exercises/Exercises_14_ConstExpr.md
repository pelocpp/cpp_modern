# Aufgaben zu `constexpr`

[Zurück](Exercises.md)

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

## Aufgabe 1: Auswertung von variadische Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit

#### Vorausetzungen: `std::is_same`

Schreiben Sie eine Funktionsschablone `sameType`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert. Der Rückgabewert vom Typ `bool` ist `true`, wenn alle Argumente vom selben Typ
sind, andernfalls `false` *und* ist zur Übersetzungszeit zu berechnen.
 
*Beispiel*:

```cpp
int main() 
{
    constexpr bool result1 = sameType(43, false, "hello");
    std::cout << std::boolalpha << result1 << std::endl;

    constexpr bool result2 = sameType(1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << std::boolalpha << result2 << std::endl;
    return 1;
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

[An den Anfang](#Aufgaben-zur-constexpr)

---
