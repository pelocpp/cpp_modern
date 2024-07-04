# Teil III: Variadische Templates - Summe von Summen

[Zurück](../../Readme.md)

---

&#x21D2; [Teil IV: Variadische Templates: Mixins](VariadicTemplates_04_Mixins.md)

&#x21D0; [Teil II: Variadische Templates: Zugriff auf jedes einzelne Argument](VariadicTemplates_02_WorkingOnEveryArgument.md)

---

[Quellcode](VariadicTemplate_03_SumOfSums.cpp)

---

## Anwendungsfall "Summe von Summen"

Im Abschnitt "Zugriff auf jedes einzelne Argument" haben wir den
Parameter Pack Expansionstrick mit Hilfe von `std::initializer_list` betrachtet.

In diesem Abschnitt gehen wir hierzu auf einen Anwendungsfall ein.
Er besteht darin, die Summe der Summen der Elemente mehrerer Container zu berechnen.
Der Einfachheit halber nehmen wir zunächst an, dass alle diese Container `int`-Werte enthalten.

## Algorithmus `std::accumulate`

Bevor wir auf das variadische Template eingehen, werfen wir zunächst
einen Blick auf den C++-Algorithmus `std::accumulate`.
Er berechnet in einem Container die Summe aller Elemente im Bereich `[first, last)`,
um es in Iterator-Schreibweise auszudrücken. Als Startwert fungiert in der Regel `0`, es wäre
hier auch ein anderer Wert denkbar, nur haben wir es dann beim Resultat nicht mehr mit der Summenbildung zu tun.

*Beispiel*:

```cpp
void main() {
    std::vector<int> vec { 1, 2, 3, 4, 5  };
    int sum = std::accumulate(std::begin(vec), std::end(vec), 0);
    std::cout << "sum: " << sum << std::endl;
}
```

*Ausgabe*:

```cpp
sum: 15
```

## Summe von Summen

Auf der Basis variadischer Templates lässt sich eine Summe von Summen so berechnen:

```cpp
template<typename ... TCONTAINER>
int sumOfSums(const TCONTAINER& ... conts) {
    auto sums = std::initializer_list<int> {
        std::accumulate(std::begin(conts), std::end(conts), 0) ...
    };
    return std::accumulate(std::begin(sums), std::end(sums), 0);
}
```

Der `std::accumulate`-Algorithmus kommt hier zweimal zum Einsatz: Zum einen, um für alle
Container die jeweilige Summe der Werte eines Containers zu berechnen. Zum zweiten,
um zur Resultat-Initialisierungsliste wiederum die Summe zu berechnen, also die Summe der Summen.

Man hätte zur Aufsummierung der einzelnen Resultatwerte auch einen Container
wie etwa `std::vector` verwenden können,
aber warum dieser Overhead, wenn ein  `std::initializer_list`-Objekt
ohnehin erstellt werden muss und dies vollkommen ausreicht?
Beachten Sie außerdem, dass wir keine Kontrollstrukturen benötigen,
die immer mit einer erhöhten Wahrscheinlichkeit von Fehlern verbunden sind.

*Beispiel*:

```cpp
void main() {
    std::vector<int> vec1{ 1, 2, 3, 4, 5 };
    std::vector<int> vec2{ 6, 7, 8, 9, 10 };
    std::deque<int> queue { 11, 12, 13, 14, 15 };

    int totalSum = sumOfSums(vec1, vec2, queue);
    std::cout << "totalSum: " << totalSum << std::endl;
}
```

*Ausgabe*:

```cpp
totalSum: 120
```

Ausgabe mit *CppInsight.io*:

```cpp
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int sumOfSums<
    std::vector<int, std::allocator<int> >, 
    std::vector<int, std::allocator<int> >, 
    std::deque<int, std::allocator<int> > 
    > (
    const std::vector<int, std::allocator<int> > & __conts0,
    const std::vector<int, std::allocator<int> > & __conts1, 
    const std::deque <int, std::allocator<int> > & __conts2)
{
  const std::initializer_list<int> sums =
    std::initializer_list<int>{ 
      std::accumulate(std::begin(__conts0), std::end(__conts0), 0), 
      std::accumulate(std::begin(__conts1), std::end(__conts1), 0),
      std::accumulate(std::begin(__conts2), std::end(__conts2), 0)
  };
  return std::accumulate(
      std::begin(std::initializer_list<int>(sums)),
      std::end(std::initializer_list<int>(sums)), 
      0);
}
#endif
```

## Literaturhinweise

Das Beispiel stammt aus

[Florian Weber Using Variadic Templates cleanly](https://florianjw.de/en/variadic_templates.html)<br>(abgerufen am 11.05.2020).

---

[Zurück](../../Readme.md)

---

