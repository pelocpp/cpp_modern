# Algorithmus `std::transform`

[Zurück](../../Readme.md)

---

[Quellcode](Transform.cpp)

---

## Allgemeines

Im Wesentlichen wendet `std::transform` eine Funktion (z.B. Lambda-Funktion) auf jedes Element eines Bereichs (Container) an,
um mit den Rückgabewerten dieser Funktion einen neuen Container zu füllen:

<img src="cpp_snippet_transform_01.svg" width="300">

*Abbildung* 1: `std::transform` auf einem Bereich.

*Hinweis*: Für das Befüllen des neuen Containers (das Ergebnis der &bdquo;Transformation&rdquo;)
benötigt man in jedem Fall eine Komfortfunktion, um mit den anfänglich leeren Containern 
richtig umzugehen! Für `std::vector`-Objekte bietet sich die `std::back_inserter`-Funktion an,
für `std::map`-Objekte die `std::inserter` Funktion,
siehe hierzu auch den [Quellcode](Transform.cpp) des Beispiels.

Die Funktion `std::transform` hat eine zweite Überladung, die zwei Bereiche entgegennimmt und
auf jedes Paar von zwei Elementen, die aus den beiden Eingabebereichen stammen, eine Funktion anwendet,
um mit dem Resultatwert wiederum einen weiteren Container zu befüllen:

<img src="cpp_snippet_transform_02.svg" width="350">

*Abbildung* 2: `std::transform` auf zwei Bereichen.

---

[Zurück](../../Readme.md)

---
