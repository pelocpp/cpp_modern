# Aufgaben zur STL


[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_03_STL.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Löschen aller ungeraden Elemente eines sequenziellen Containers<br/>(Voraussetzungen: STL-Container `std::vector<int>`, Methode `erase`, STL-Algorithmus `std::remove_if`) |
| *Aufgabe* 2 | *Fibonacci*-Zahlen<br/>(Voraussetzungen: Algorithmen `std::generate`, `std::for_each`, Lambda-Funktionen, Structured Binding) |
| *Aufgabe* 3 | Der Algorithmus `std::accumulate` in der Anwendung<br/>(Voraussetzungen: `std::accumulate`, `std::initializer_list`) |

*Tabelle* 1: Aufgaben zur STL.

---

## Aufgabe 1: Löschen aller ungeraden Elemente in einem sequenziellen STL-Container

#### Voraussetzungen: STL-Container `std::vector<int>`, Methode `erase`, STL-Algorithmus `std::remove_if`

*Teilaufgabe* 1:

Wir studieren in dieser Aufgabe das folgende kleine Programm
zum Testen der `erase`-Methode an einem `std::vector<int>`-Objekt.
Es sollen alle geraden Elemente eines `std::vector<int>`-Objekts entfernt werden:

```cpp
01: void test ()
02: {
03:     std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
04: 
05:     // erase all even numbers
06:     for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
07:     {
08:         if (*it % 2 == 0) {
09:             vec.erase(it);
10:         }
11:     }
12: }
```

Welchen Inhalt hat der STL-Container `vec` Ihrer Meinung nach am Ende der `test`-Funktion?
Bringen Sie das Programm zum Laufen. Geben Sie den Inhalt des `std::vector<int>`-Containers am Ende der `test`-Funktion
in der Konsole aus. Welche Beobachtungen machen Sie bei der Ausführung des Programms?

*Teilaufgabe* 2:

Welche Änderungen sind an der `test`-Funktion notwendig, so dass die Ausführung korrekt verläuft.
Es ist durchaus möglich, die `for`-Wiederholungsschleife beizubehalten.
Was fällt Ihnen an diesem Beispiel betrachtet zum Thema &bdquo;ungültige Iteratoren&rdquo; ein?

*Teilaufgabe* 3:
Für die Aufgabenstellung eignet sich auch eine Verwendung des STL-Algorithmus `std::remove_if`.
Schreiben Sie die `test`-Funktion so um, dass der STL-Algorithmus `std::remove_if` zum Einsatz kommt.

*Teilaufgabe* 4:
Mit Teilaufgabe 2 und 3 stehen sich nun zwei Lösungen gegenüber:

  * Lösung mit einer `for`-Kontrollstruktur und wiederholtem Aufruf der `erase`-Methode.
  * Lösung mit STL-Algorithmus `std::remove_if` und einmaligem Aufruf der `erase`-Methode.

Schreiben Sie ein kleines Testprogramm, in dem Sie die beiden Realisierungen in einer Wiederholungsschleife aufrufen.
Zum Messen der Zeit verwenden Sie eine Klasse `ScopedTimer`,
deren Quellcode Sie [hier](https://github.com/pelocpp/cpp_modern/blob/master/GeneralSnippets/ScopedTimer/ScopedTimer.h) finden.
Welche Beobachtungen können Sie in Bezug auf die Ausführungszeiten des Vergleichs machen?

---

## Aufgabe 2: *Fibonacci*-Zahlen

#### Voraussetzungen: Algorithmen `std::generate`, Lambda-Funktionen, Structured Binding

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

## Aufgabe 3: Der Algorithmus `std::accumulate` in der Anwendung

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

[Lösungen](Exercises_03_STL.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
