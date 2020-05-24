# Funktionale Programmierung

[Quellcode](FunctionalProgramming.cpp)

---

## Allgemeines

C++ ist eine "imperative, objektorientierte Programmiersprache" und keine "funktionale Programmiersprache".
Mit den Neuerungen des so genannten "Modern C++" lassen sich aber auch
einige Aspekte der "funktionalen Programmierung" in C++ darstellen.

"Funktionen" ähneln Methoden. Aber anders als Methoden werden Funktionen bei der "funktionalen Programmierung" weitergereicht, beispielsweise als Argumente an Methoden oder als Return-Wert einer Methode.
Dies ist in C++ spätestens seid Einführung der Lambda-Funktionen elegant möglich.

"Rein funktionale Sprachen" ("pure functional Language") wie beispielsweise Haskell sind zustandslos und Funktionen haben keinerlei Seiteneffekte. Sie ändern keine Daten, sondern können höchstens neue Daten returnieren. Das ist bei C++ anders. Hier können Funktionen durchaus Daten ändern.

"Rein funktionale Programmierung" eignet sich ideal zur Parallelverarbeitung sowie für mathematische Aufgaben, und steht in dem Ruf, dass so erstellte Programme weniger Fehler enthalten sollen.
Nachteilig ist, dass sich reale Objekte und Zustandsänderungen nur schwierig abbilden lassen, was die Programmierung realer Vorgänge und Geschäftsprozesse erschwert. Dies ist mit objektorientierter zustandsbehafteter Programmierung wesentlich leichter realisierbar.

## Funktionen höherer Ordnung

Funktionen, die entweder Funktionen als Argument annehmen oder als Ergebnis zurückgeben können, werden als
*Funktionen höherer Ordnung* vezeichnet. Die Klassiker aus der funktionalen Prohgrammierung sind die drei
Funktionen `map`, `filter` und `fold`. Diese drei Funktionen höherer Ordnung werden über eine Funktion parametrisiert
und wenden diese sukzessive aus die Elemente eines Containers an. In C++ bieten sich an dieser Stelle
speziell die Lambda-Funktionen an.

  * `map` - Transformation der Elemente. Dabei entsteht eine neue Menge von Elementen (derselben Anzahl), die typischerweise
    einen anderen Datentyp haben. So können zum Beispiel Umrechnungen, Extraktionen oder Umwandlungen durchgeführt werden.
  * `filter` - Filterung gewünschter Elemente aus einer Menge von Elementen (Container).
    Der Datentyp der Elemente bleibt derselbe, aber die Menge der Elemente wird reduziert.
  * `fold` - Reduktion der Elemente eines Containers auf ein Endergebnis (Resultat). Typischerweise wird eine Lambda-Funktion
    mit zwei Argumenten auf ein Element des Containers und das vorangehende Zwischenergebnis angewendet.


## Filter-Map-Reduce Pattern

"Filter-Map-Reduce" beschreibt ein Pattern, bei dem eine Menge von Daten in einer Abfolge von bestimmten Schritten verarbeitet werden.
Reduce ist eine andere Bezeichnung für fold, die ebenfalls gerne für diese Funktionalität herangezogen wird.

## Beispiele

Siehe dazu den dazugehörigen [Quellcode](FunctionalProgramming.cpp).

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Code-Snippet stammen teilweise aus

[Implementing filter and map with C++11](https://bastian.rieck.me/blog/posts/2016/filter_map_cxx11/)<br>(abgerufen am 24.05.2020).

und 

[Funktionale Programmierung](https://www.torsten-horn.de/techdocs/java-lambdas.htm/)<br>(abgerufen am 24.05.2020).







---

[Zurück](../../Readme.md)

---
