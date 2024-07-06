# Benutzerdefinierte Literale

[Zurück](../../Readme.md)

---

[Quellcode](Literals.cpp)

---

## Allgemeines

Im korrespondierenden Quellcode werden zwei Möglichkeiten in der Definition
von benutzerdefinierten Literalen aufgezeigt:

  * Literale, deren Wert zur Laufzeit (*Runtime*) berechnet wird.
  * Literale, deren Wert zur Übersetzungszeit (*Compile-Time*) berechnet wird.

Die zweite Variante ist natürlich zu bevorzugen.
In der Realisierung kann sie geringfügig aufwendiger sein, die gesamte Funktionalität
ist auf Basis des `constexpr`-Konzepts zu implementieren!

## Literaturhinweise

Eine ausführliche Beschreibung des Beispiels findet sich unter

[Benutzerdefinierte Literale: Übersetzungszeit oder Laufzeit?](https://peterloos.de/post/2021-05-16-literals/)

---

[Zurück](../../Readme.md)

---
