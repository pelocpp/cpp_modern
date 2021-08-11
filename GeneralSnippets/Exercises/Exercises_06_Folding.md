# Aufgaben zu Folding

[Zurück](Exercises_Ex.md)

---

## Aufgabe 1: Logische Operationen mit beliebig vielen Operanden

Die Aufgabenstellung ist identisch zur letzten Aufgabe: Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

## Aufgabe 2: Folding Expressions, `decltype` und Type-Traits am Beispiel von `sameType`

#### Vorausetzungen: `std::is_same`

Die Aufgabenstellung ist identisch zur letzten Aufgabe (ohne Zusatzaufgabe):
Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

*Zusatzfrage*:
Welchen prinzipiellen Unterschied beobachten Sie im Lösungsansatz
von Aufgabe 1 und 2?

---

[An den Anfang](#aufgaben-zu-folding)

---

## Aufgabe 3: &ldquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`

#### Voraussetzungen: Folding Expressions, Lambda Funktionen

Der Zugriff auf die einzelnen Werte eines Parameter Packs ist nicht ganz einfach.
Eine übliche Vorgehensweise ist das so genannte &ldquo;*Folding over a Comma*&rdquo;.
Hierbei handelt es sich um einen *Folding*-Ausdruck, der mit dem Komma-Operator &ndash; gebildet wird.
Der Komma-Operator bewirkt in diesem Fall einzig und allein, dass alle Werte des Parameter Packs sequentiell aufgelistet werden.

Betrachten Sie das nachfolgende Beispiel einer Implementierung der Funktion `minimum`:
Die Funktion kann eine variabel lange Liste von Parametern (mindestens zwei) entgegennehmen und liefert den minimalen Wert zurück.
Erklären Sie die Funktionsweise ihrer Realisierung. Welche Rolle spielt Zeile 14?

```cpp
01: template <typename T, typename ... TARGS>
02: auto minimum(const T& x, const T& y, const TARGS& ... args)
03: {
04:     auto m = (x < y) ? x : y;
05: 
06:     if (sizeof ... (args) > 0) {
07: 
08:         auto helper = [&](const auto& value) {
09:             if (value < m) {
10:                 m = value;
11:             }
12:         };
13: 
14:         (..., helper(args));
15:     }
16: 
17:     return m;
18: }
```

  * Testen Sie die Korrektheit der Funktion `minimum` mit einigen Testbeispielen.
  * Schreiben Sie eine zweite Funktion `maximum`, die das Maximum aller Parameter bestimmt.

---

[Lösungen](Exercises.cpp)

---

[An den Anfang](#aufgaben-zu-folding)

---

[Zurück](Exercises_Ex.md)

---
