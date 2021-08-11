# Aufgaben zur Metaprogrammierung

[Zurück](Exercises_Ex.md)

---

[Lösungen](Exercises_07_Metaprogramming.cpp)

---

## Aufgabe 1: Konvertierung binärer Zahlen in natürliche Zahlen.

Das Binärsystem, auch Dual- oder Zweiersystem genannt, ist ein Zahlensystem, das nur zwei verschiedene
Ziffern &ndash; in der Regel 0 und 1 &ndash; zur Darstellung von Zahlen benutzt. Die Ziffernfolge 1101 zum
Beispiel stellt nicht wie im Dezimalsystem die Tausendeinhunderteins dar, sondern die Dreizehn, denn
im Binärsystem berechnet sich der Wert durch

1101<sub>2</sub> = 1 &times; 2<sup>3</sup> + 1 &times; 2<sup>2</sup> + 0 &times; 2<sup>1</sup> + 1 &times; 2<sup>0</sup> = 13<sub>10</sub>

Schreiben Sie eine Funktionsschablone `Binary`, die den Wert einer ganzen Zahl in Binärdarstellung in
das Dezimalsystem konvertiert.

*Beispiele*:

```cpp
constexpr size_t one = Binary<1>::value;
constexpr size_t three = Binary<11>::value;
constexpr size_t five = Binary<101>::value;
constexpr size_t seven = Binary<111>::value;
constexpr size_t nine = Binary<1001>::value;
```

*Ausgabe*:

```
1
3
5
7
9
```

*Hinweis*: Erstellen Sie zunächst eine reguläre C-Funktion, die die gewünschte Umwandlung durchführt und
rekursiv implementiert ist! Nun ist ein einfaches, diese C-Funktion in ein C++-Klassentemplate umzuwandeln!

---

## Aufgabe 2: *Fibonacci*-Zahlen

In der Mathematik bilden die *Fibonacci*-Zahlen eine Folge,
so dass jede Zahl die Summe der beiden vorhergehenden Zahlen ist, beginnend mit 0 und 1. 
Für die *n*.-te Fibonacci F<sub>*n*</sub> bedeutet das F<sub>*n*</sub> = F<sub>*n*-1</sub> + F<sub>*n*-2</sub>,
wobei F<sub>0</sub> = 0 und F<sub>1</sub> = 1 gelten.
Die durch Fibonacci-Zahlen gebildete Sequenz wird als *Fibonacci*-*Sequenz* bezeichnet.

Schreiben Sie eine Funktionsschablone `Fibonacci`, die *Fibonacci*-Zahlen zur Übersetzungszeit berechnet.

*Beispiele*:

```cpp
std::cout << 1 << ":  " << Fibonacci<1>::value << std::endl;
std::cout << 2 << ":  " << Fibonacci<2>::value << std::endl;
std::cout << 5 << ":  " << Fibonacci<5>::value << std::endl;
std::cout << 10 << ": " << Fibonacci<10>::value << std::endl;
std::cout << 15 << ": " << Fibonacci<15>::value << std::endl;
std::cout << 20 << ": " << Fibonacci<20>::value << std::endl;
```

*Ausgabe*:

```
1:  1
2:  1
5:  5
10: 55
15: 610
20: 6765
```

---

[Lösungen](Exercises_07_Metaprogramming.cpp)

---

[An den Anfang](#Aufgaben-zur-Metaprogrammierung)

---
