# Lambda-Objekte

[Zur�ck](../../Readme.md)

---

[Quellcode 1 - Motivation, allgemeine Beispiele](Lambda01.cpp)<br />
[Quellcode 2 - Lambda und Closure](Lambda02.cpp)<br />
[Quellcode 3 - Lambda und Closure: Spezialfall `this`](Lambda03.cpp)<br />
[Quellcode 4 - Lambda und das Visitor-Pattern](Lambda04.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Zugriffsklausel / Capture Clause](#link2)
  * [Weitere Besonderheiten im Aufbau eines Lambda-Objekts](#link3)
  * [IIFE - Immediately Invoked Functional Expressions](#link4)

---

## Allgemeines <a name="link1"></a>

Es werden folgende �berlegungen der Reihe nach betrachtet:

  * Betrachtung 1:</br>Sortieren eines Vektors mit einer globalen Funktion.</br>

  * Betrachtung 2:</br>Sortieren eines Vektors mit einem Funktionsobjekt (also ohne Lambda-Methode):</br>
    Man erkennt, dass es im Prinzip einer zus�tzlichen Klasse (Struktur) bedarf, um
    `std::sort` mit einer Vergleichsmethode aufrufen zu k�nnen.

  * Betrachtung 3:</br>Wie Betrachtung 2, nur mit einer lokalen Struktur:</br>
    Es wird gezeigt, dass Strukturdefinitionen auch lokal in einer Funktion m�glich sind.

  * Betrachtung 4:</br>Sortieren eines Vektors mit Lambda-Methode:</br>
    Es wird ein einfaches Lambda-Objekt vorgestellt.


---

## Zugriffsklausel / Capture Clause <a name="link2"></a>

*Tabelle* 1 vermittelt einen �berblick bzgl. der Gestaltungsm�glichkeiten der Zugriffsklausel:

| Zugriffsklausel | Erl�uterung |
|:- |:-|
| `[]` | Nichts zu erfassen. |
| `[&]` | Jede referenzierte Variable wird per Referenz erfasst / angesprochen. |
| `[=]` | Jede referenzierte Variable wird durch eine Kopie erfasst / angesprochen. |
| `[=, &foo]` | Jede referenzierte Variable wird durch eine Kopie erfasst / angesprochen, mit Ausnahme von `foo`, das per Referenz erfasst / angesprochen wird. |
| `[&, foo]` | Jede referenzierte Variable wird per Referenz erfasst / angesprochen, mit Ausnahme von `foo`, das durch eine Kopie erfasst / angesprochen wird. |
| `[this]` | Erfasst den `this`-Zeiger der umschlie�enden Klasse. |

*Tabelle* 1: Liste aller Optionen f�r die Lambda-Zugriffsklausel.


Das Feature der *Capture Clause*, den Zugriff auf Variablen der &bdquo;Umgebung&rdquo; genauer festzulegen,
ist nicht mit der M�glichkeit zu verwechseln, **innerhalb** einer *Capture Clause*
Instanzvariablen des zu einer Lambda-Funktion geh�renden Funktions-Objekts zu definieren:

```cpp
auto lambda = [counter = 10]() { ... };
```

Die `counter`-Variable ist nur **in** der Lambda-Funktion verf�gbar.

---

## Weitere Besonderheiten im Aufbau eines Lambda-Objekts <a name="link3"></a>

Neben der Zugriffsklausel kann ein Lambda-Objekt mit zahlreichen Schl�sselw�rtern *garniert* werden.
Siehe hierzu *Abbildung* 1:

<img src="cpp_snippets_lambda.svg" width="300">

*Abbildung* 1: Besonderheiten im Aufbau eines Lambda-Objekts.

---

## IIFE - Immediately Invoked Functional Expressions <a name="link4"></a>

In C++ ist ein &bdquo;*Immediately Invoked Function Expression*&rdquo; (*IIFE*) ein Ausdruck,
mit dem man eine Funktion unmittelbar nach ihrer Erstellung ausf�hren kann.

Diese Technik wurde aus Sprachen wie JavaScript �bernommen und wird normalerweise verwendet,
um Code in einem lokalen Bereich zu kapseln und sofort auszuf�hren.


---

[Zur�ck](../../Readme.md)

---
