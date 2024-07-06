# Benutzerdefinierte Literale

[Zur�ck](../../Readme.md)

---

[Quellcode](Literals.cpp)

---

## Allgemeines

Im korrespondierenden Quellcode werden zwei M�glichkeiten in der Definition
von benutzerdefinierten Literalen aufgezeigt:

  * Literale, deren Wert zur Laufzeit (*Runtime*) berechnet wird.
  * Literale, deren Wert zur �bersetzungszeit (*Compile-Time*) berechnet wird.

Die zweite Variante ist nat�rlich zu bevorzugen.
In der Realisierung kann sie geringf�gig aufwendiger sein, die gesamte Funktionalit�t
ist auf Basis des `constexpr`-Konzepts zu implementieren!

## Literaturhinweise

Eine ausf�hrliche Beschreibung des Beispiels findet sich unter

[Benutzerdefinierte Literale: �bersetzungszeit oder Laufzeit?](https://peterloos.de/post/2021-05-16-literals/)

---

[Zur�ck](../../Readme.md)

---
