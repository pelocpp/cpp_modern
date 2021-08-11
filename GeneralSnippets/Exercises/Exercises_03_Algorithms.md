# Aufgaben zu STL-Algorithmen

[Zurück](Exercises_Ex.md)

---

## Aufgabe 1: Die Funktion `std::accumulate` in der Anwendung (Initialisierungliste)

#### Voraussetzungen: `std::accumulate`, `std::initializer_list`

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

---

[Lösungen](Exercises.cpp)

---

[An den Anfang](#Aufgaben-zu-STL-Algorithmen)

---
