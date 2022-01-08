# Aufgaben zu Expression Templates

[Zurück](Exercises.md)

---

[Lösungen](Exercises_08_ExpressionTemplates.cpp)

---

## Aufgabe 1: Das Skalarprodukt zweier Vektoren

Das *skalare* Produkt &ndash; auch *inneres* Produkt genannt &ndash; ist eine mathematische Verknüpfung
von zwei Vektoren, bei der eine Zahl als Resultat herauskommt.
Für zwei Vektoren
*a* = (*a*<sub>1</sub>, *a*<sub>2</sub>, *a*<sub>3</sub>, ..., *a*<sub>n</sub>) 
und
*b* = (*b*<sub>1</sub>, *b*<sub>2</sub>, *b*<sub>3</sub>, ..., *b*<sub>n</sub>)
berechnet sich das Ergebnis zu
*a*<sub>1</sub> * *b*<sub>1</sub> + *a*<sub>2</sub> * *b*<sub>2</sub> + ... + *a*<sub>n</sub> * *b*<sub>n</sub>.

In einem sehr einfachen Ansatz könnte man in C++ das skalare Produkt zweier Vektoren `a` und `b`,
wenn man diese in `std::vector<T>`-Objekten ablegt (sei `T` gleich `float` oder `double`), so berechnen:

```cpp
T product{};
for (size_t i{}; i != a.size(); ++i) {
    product += (a[i]) * (b[i]);
}
```

Diese Realisierung hat allerdings zur Folge, dass &ndash; am Beispiel zweier Vektoren der Länge 5 detaillierter betrachtet &ndash;
folgende Rechenschritte zur Ausführung gelangen:

```
T product = 0;
product += a[0] * b[0];
product += a[1] * b[1];
product += a[2] * b[2];
product += a[3] * b[3];
product += a[4] * b[4];
```

Wäre es nicht effizienter, wenn wir die Berechnung mit einer Realisierung anstreben könnten,
die ohne die vielen (temporären) Additionen auf die Ergebnisvariable `product` auskommt?
Also ganz einfach durch einen Ausdruck der Gestalt

```
T product = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] + a[4] * b[4];
```

Bei Vektoren mit im Vorneherein bekannter fester Länge könnte man diesen Ausdruck einfach wie gezeigt hinschreiben.
Wie sieht es aus, wenn die Vektorenlänge zwar ebenfalls zur Übersetzungszeit bekannt ist,
aber eben durch einen Bezeichner &ndash; sagen wir `N` &ndash; allgemein (zur Übersetzungszeit) gehalten wird?
Mit Hilfe von &ldquo;Loop Unrolling&rdquo; bzw. C++ *Metaprogramming* kann man einen Ausdruck

```
T product = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + ... a[N-1] * b[N-1];
```

vom Übersetzer erzeugen lassen!

*Aufgabe*: Erstellen Sie eine Klasseschablone `ScalarProduct`, die mit Hilfe von &ldquo;Loop Unrolling&rdquo;
dieses Ziel erreicht.

---

[An den Anfang](#Aufgaben-zu-Expression-Templates)

---
