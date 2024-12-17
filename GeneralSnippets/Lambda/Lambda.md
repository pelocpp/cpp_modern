# Lambda-Objekte

[Zurück](../../Readme.md)

---

[Quellcode 1 - Motivation, allgemeine Beispiele](Lambda01.cpp)<br />
[Quellcode 2 - Lambda und Closure](Lambda02.cpp)<br />
[Quellcode 3 - Lambda und Closure: Spezialfall `this`](Lambda03.cpp)<br />

---

## Inhalt

  * [Allgemeines](#link1)
  * [Weitere Besonderheiten im Aufbau eines Lambda-Objekts](#link2)
  * [IIFE - Immediately Invoked Functional Expressions](#link3)
  * [Generalized Lambda Captures](#link4)

---

## Allgemeines <a name="link1"></a>

*Tabelle* 1 vermittelt einen Überblick bzgl. der Gestaltungsmöglichkeiten der
Zugriffsklausel (*Capture Clause*):

| Zugriffsklausel | Erläuterung |
|:- |:-|
| `[]` | Nichts zu erfassen. |
| `[&]` | Jede referenzierte Variable wird per Referenz erfasst / angesprochen. |
| `[=]` | Jede referenzierte Variable wird durch eine Kopie erfasst / angesprochen. |
| `[=, &foo]` | Jede referenzierte Variable wird durch eine Kopie erfasst / angesprochen, mit Ausnahme von `foo`, das per Referenz erfasst / angesprochen wird. |
| `[&, foo]` | Jede referenzierte Variable wird per Referenz erfasst / angesprochen, mit Ausnahme von `foo`, das durch eine Kopie erfasst / angesprochen wird. |
| `[this]` | Erfasst den `this`-Zeiger der umschließenden Klasse. |

*Tabelle* 1: Liste aller Optionen für die Lambda-Zugriffsklausel.


Das Feature der *Capture Clause*, den Zugriff auf Variablen der &bdquo;Umgebung&rdquo; genauer festzulegen,
ist nicht mit der Möglichkeit zu verwechseln, **innerhalb** einer *Capture Clause*
Instanzvariablen des zu einer Lambda-Funktion gehörenden Funktions-Objekts zu definieren:

```cpp
auto lambda = [counter = 10]() { ... };
```

Die `counter`-Variable ist nur **in** der Lambda-Funktion verfügbar.

---

## Weitere Besonderheiten im Aufbau eines Lambda-Objekts <a name="link2"></a>

Neben der Zugriffsklausel kann ein Lambda-Objekt mit zahlreichen Schlüsselwörtern *garniert* werden.
Siehe hierzu *Abbildung* 1:

<img src="cpp_snippets_lambda.svg" width="300">

*Abbildung* 1: Besonderheiten im Aufbau eines Lambda-Objekts.

---

## IIFE - Immediately Invoked Functional Expressions <a name="link3"></a>

In C++ ist ein &bdquo;*Immediately Invoked Function Expression*&rdquo; (*IIFE*) ein Ausdruck,
mit dem man eine Funktion unmittelbar nach ihrer Erstellung ausführen kann.

Diese Technik wurde aus Sprachen wie JavaScript übernommen und wird normalerweise verwendet,
um Code in einem lokalen Bereich zu kapseln und sofort auszuführen.

---

## Generalized Lambda Captures <a name="link4"></a>

C++ 11 bietet im Kontext der Capture-Klausel nur die Möglichkeit *by-value*- oder *by-reference* an, 
um auf Variablen im umgebenden Scope zuzugreifen.

Es fehlt also die Möglichkeit, mit der Move-Semantik Variablen / Objekte in ein Lambda-Objekt zu verschieben
(*by-move*).

Anstatt dieses Feature explizit zu ergänzen,
führte C++ 14 das so genannte *Generalized Lambda Capture* Feature ein,
auch bekannt als *Init*-Capture.

---

[Zurück](../../Readme.md)

---
