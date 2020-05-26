# Funktionale Programmierung

[Quellcode](FunctionalProgramming.cpp)

---

## Allgemeines

C++ ist eine "imperative, objektorientierte Programmiersprache" und keine "funktionale Programmiersprache".
Mit den Neuerungen des so genannten "Modern C++" lassen sich aber auch
einige Aspekte der "funktionalen Programmierung" in C++ darstellen.

"Funktionen" ähneln Methoden. Aber anders als Methoden werden Funktionen bei der "funktionalen Programmierung" weitergereicht, beispielsweise als Argumente an Methoden oder als Return-Wert einer Methode.
Dies ist in C++ spätestens seit Einführung der Lambda-Funktionen elegant darstellbar.

"Rein funktionale Sprachen" ("*pure functional languages*") wie beispielsweise *Haskell* sind zustandslos und Funktionen haben keinerlei Seiteneffekte. Sie ändern keine Daten, sondern können höchstens neue Daten als Resultat einer Funktion zurückliefern.
Das ist natürlich bei C++ anders. Hier können Funktionen durchaus Daten ändern, sei es wir betrachten
den Zustand eines Objekts oder mögen es Seiteneffekte anderen Ursprungs sein.

"Rein funktionale Programmierung" eignet sich ideal zur Parallelverarbeitung sowie für mathematische Aufgaben und steht in dem Ruf,
dass auf diese Weise erstellte Programme weniger fehleranfällig sind.
Nachteilig ist, dass sich reale Objekte und Zustandsänderungen nur schwierig abbilden lassen, was die Programmierung realer Vorgänge und Geschäftsprozesse erschwert.
Dies ist eben das Terrain der objektorientierten zustandsbehafteten Programmierung.

## Funktionen höherer Ordnung

Funktionen, die entweder Funktionen als Argument annehmen oder als Ergebnis zurückgeben, werden als
*Funktionen höherer Ordnung* bezeichnet. Die Klassiker aus der funktionalen Programmierung sind die drei
Funktionen `map`, `filter` und `fold`. Diese drei Funktionen höherer Ordnung werden über eine weitere 
Funktion parametrisiert und wenden diese sukzessive auf die Elemente eines Containers an. In C++ bieten sich an dieser Stelle
speziell Lambda-Funktionen an.

  * `map` - Transformation der Elemente. Dabei entsteht eine neue Menge von Elementen (derselben Anzahl), die typischerweise
    einen anderen Datentyp haben. So können zum Beispiel Umrechnungen oder Umwandlungen durchgeführt werden.
  * `filter` - Filterung gewünschter Elemente aus einer Menge von Elementen (Container).
    Der Datentyp der Elemente bleibt derselbe, aber die Menge der Elemente des Ursprungscontainers wird reduziert.
  * `fold` - Reduktion der Elemente eines Containers auf ein Endergebnis (Resultat). Typischerweise wird eine Lambda-Funktion
    mit zwei Argumenten auf ein Element des Containers und das vorangehende Zwischenergebnis angewendet.


## Filter-Map-Reduce Pattern

"Filter-Map-Reduce" beschreibt ein Pattern, bei dem eine Menge von Daten in einer Abfolge
von bestimmten Schritten verarbeitet wird.
`reduce` ist eine andere Bezeichnung für `fold`.

## Beispiele

Siehe den dazugehörigen [Quellcode](FunctionalProgramming.cpp).

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet stammen teilweise aus

[Implementing filter and map with C++11](https://bastian.rieck.me/blog/posts/2016/filter_map_cxx11/)<br>(abgerufen am 24.05.2020).

und 

[Funktionale Programmierung](https://www.torsten-horn.de/techdocs/java-lambdas.htm/)<br>(abgerufen am 24.05.2020).







---

[Zurück](../../Readme.md)

---
