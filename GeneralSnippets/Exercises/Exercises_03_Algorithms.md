# Aufgaben zu STL-Algorithmen

[Zurück](Exercises.md)

---

[Lösungen](Exercises_03_Algorithms.cpp)

---

## Aufgabe 1: Der Algorithmus `std::accumulate` in der Anwendung

#### Voraussetzungen: `std::accumulate`, `std::initializer_list` (Initialisierungliste)

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

[An den Anfang](#Aufgaben-zu-STL-Algorithmen)

---

## Aufgabe 2: *Fibonacci*-Zahlen

#### Vorausetzungen: Algorithmen `std::generate`, Lambda-Funktionen, Structured Binding

In der Mathematik bilden die *Fibonacci*-Zahlen eine Folge,
so dass jede Zahl die Summe der beiden vorhergehenden Zahlen ist, beginnend mit 0 und 1. 
Für die *n*.-te Fibonacci F<sub>*n*</sub> bedeutet das F<sub>*n*</sub> = F<sub>*n*-1</sub> + F<sub>*n*-2</sub>,
wobei F<sub>0</sub> = 0 und F<sub>1</sub> = 1 gelten.
Die durch Fibonacci-Zahlen gebildete Sequenz wird als *Fibonacci*-*Sequenz* bezeichnet.

Verwenden Sie in dieser Aufgabe den Algorithmus `std::generate` mit einer geeigneten Lambda-Funktion,
um die *Fibonacci*-Zahlen zu berechnen. Die Größe des Containers, der an `std::generate` 
in den ersten beiden Parametern übergeben wird (Start- und Ende-Iterator), entscheidet, 
wieviele *Fibonacci*-Zahlen berechnet werden.

Die ersten zwei Werte 0 und 1 der Zahlenfolge können Sie in einem `std::pair`-Objekt ablegen: `std::pair{0,1}`.
Von Aufruf zu Aufruf der Lambda-Funktion können Sie dieses Objekt geeignet modifizieren:

  * Das erste Element des neuen Paares ist das zweite Element des alten Paares.
  * Das zweite Element des neuen Paares ist die Summe der beiden Elemente des alten Paares.

Wie müssen Sie diese Lambda-Funktion definieren, so dass das `std::pair`-Objekt veränderbar ist?

*Hinweis*: Die ersten 20 *Fibonacci*-Zahlen lauten

```
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181
```

---

[Lösungen](Exercises_03_Algorithms.cpp)

---

[An den Anfang](#Aufgaben-zu-STL-Algorithmen)

---
