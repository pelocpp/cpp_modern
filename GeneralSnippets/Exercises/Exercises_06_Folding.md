# Aufgaben zu Folding

[Zurück](Exercises.md)

---

[Lösungen](Exercises_06_Folding.cpp)

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

[An den Anfang](#aufgaben-zu-folding)

---

## Aufgabe 4: Beliebig viele Werte zu einem `std::vector`-Objekt hinzufügen

#### Voraussetzungen: Folding Expressions

Sowohl mit variadischen Templates als auch mit Folding lässt sich ein elegantes Funktionstemplate
`pushBackAll<T>` schreiben, das eine beliebige Anzahl von Parametern mit `push_back`
einem `std::vector`-Objekt hinzufügt.
Da diese Aufgabe in den Übungen zum Thema *Folding* enthalten ist,
realisieren Sie das Funktionstemplate mit einem *Folding* Ausdruck.

Das folgende (hoffentlich intuitive) Beispiel sollte ausführbar sein:

```cpp
std::vector<double> values;
pushBackAll<double>(values, 30.0, 31.0, 32.0);
std::for_each(std::begin(values), std::end(values), [](auto elem) {
    std::cout << elem << ' ';
    }
);
```

*Ausgabe*:

```
30 31 32
```

*Zusatzaufgabe*:
Man könnte das Funktionstemplate `pushBackAll<T>` auch mit variadischen Templates 
oder auch dem Trick mit einer Initialisierungsliste
und wiederum Folding (dieses Mal &ldquo;über einem Komma&rdquo;) realisieren.
Implementieren Sie die weiteren Varianten.

---

[Lösungen](Exercises_06_Folding.cpp)

---

[An den Anfang](#aufgaben-zu-folding)

---

