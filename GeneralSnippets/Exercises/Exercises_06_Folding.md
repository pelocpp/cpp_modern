# Aufgaben zu Folding

[Zurück](Exercises.md)

---

[Lösungen](Exercises_06_Folding.cpp)

---

## Aufgabe 1: Logische Operationen mit beliebig vielen Operanden

Die Aufgabenstellung ist identisch zur ersten Aufgabe
&bdquo;Logische Operationen mit beliebig vielen Operanden&rdquo;
aus dem Abschnitt [Variadische Templates](Exercises_05_VariadicTemplates.md):
Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

## Aufgabe 2: Folding Expressions, `decltype` und Type-Traits am Beispiel von `sameType`

#### Vorausetzungen: `std::is_same`

Die Aufgabenstellung ist identisch zur zweiten Aufgabe
&bdquo;Logische Operationen mit beliebig vielen Operanden&rdquo;
aus dem Abschnitt [Variadische Templates](Exercises_05_VariadicTemplates.md)(ohne Zusatzaufgabe):
Setzen Sie zur Lösung dieses Mal *Folding Expressions* ein.

*Zusatzfrage*:
Welchen prinzipiellen Unterschied beobachten Sie im Lösungsansatz
von Aufgabe 1 und 2?

---

[An den Anfang](#aufgaben-zu-folding)

---

## Aufgabe 3: &bdquo;*Folding over a Comma*&rdquo; am Beispiel zweier Funktionen `minimum` und `maximum`

#### Voraussetzungen: Lambda Funktionen

Der Zugriff auf die einzelnen Werte eines Parameter Packs ist nicht ganz einfach.
Eine übliche Vorgehensweise ist das so genannte &bdquo;*Folding over a Comma*&rdquo;.
Hierbei handelt es sich um einen *Folding*-Ausdruck, der mit dem Komma-Operator &ndash; gebildet wird.
Der Komma-Operator bewirkt in diesem Fall einzig und allein, dass alle Werte des Parameter Packs sequentiell aufgelistet werden.

Betrachten Sie das nachfolgende Beispiel einer Implementierung der Funktion `minimum`:
Die Funktion kann eine variabel lange Liste von Parametern (mindestens zwei) entgegennehmen und liefert den minimalen Wert zurück.
Erklären Sie die Funktionsweise ihrer Realisierung. Welche Rolle spielt Zeile 14?

```cpp
template <typename T, typename ...  TArgs>
auto minimum(const T& x, const T& y, const TArgs&... args)
{
    auto m{ (x < y) ? x : y };

    if constexpr (sizeof... (args) > 0)
    {
        auto helper = [&] (const auto& value) {
            if (value < m) {
                m = value;
            }
        };

        ( ... , helper(args) );
    }

    return m;
}
```

  * Testen Sie die Korrektheit der Funktion `minimum` mit einigen Testbeispielen.
  * Schreiben Sie eine zweite Funktion `maximum`, die das Maximum aller Parameter bestimmt.

---

[An den Anfang](#aufgaben-zu-folding)

---

## Aufgabe 4: Beliebig viele Werte zu einem `std::vector`-Objekt hinzufügen

Sowohl mit variadischen Templates als auch mit Folding lässt sich ein elegantes Funktionstemplate
`pushBackAll<T>` schreiben, das eine beliebige Anzahl von Parametern mit `push_back`
einem `std::vector`-Objekt hinzufügt.
Da diese Aufgabe in den Übungen zum Thema *Folding* enthalten ist,
realisieren Sie das Funktionstemplate mit einem *Folding* Ausdruck.

Das folgende &ndash; hoffentlich intuitive &ndash; Beispiel sollte ausführbar sein:

```cpp
#include <iostream>
#include <vector>

template <typename T, typename ...  TArgs>
void pushBackAll(std::vector<T>& vec, const TArgs&... args)
{
    (vec.push_back(args) , ...);
}

int main()
{
    std::vector<double> values;
    pushBackAll<double>(values, 30.0, 31.0, 32.0);
    for (auto elem : values) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}
```

*Ausgabe*:

```
30 31 32
```

*Zusatzaufgabe*:
Man könnte das Funktionstemplate `pushBackAll<T>` auch mit variadischen Templates 
oder auch dem Trick mit einer Initialisierungsliste
und wiederum Folding (dieses Mal &bdquo;über einem Komma&rdquo;) realisieren.
Implementieren Sie die weiteren Varianten.

---

## Aufgabe 5: Störende Trennzeichen am Ende eines Folding-Ausdrucks

Betrachten Sie die nachfolgende Funktion `printer`.
Mit Hilfe von variadischen Templates kann die Funktion eine beliebige Anzahl von Parametern entgegennehmen
und diese mit Hilfe eines Folding-Ausdrucks auf der Konsole ausgeben:

```cpp
template <typename ...ARGS>
void printer(ARGS ...args) {
    (std::cout << ... << args);
    std::cout << std::endl;
}
```

Das Folding findet hier mit dem `<<`-Operator statt (genauer: *Binary Left Folding*),
die Argumente werden ohne jegliches Trennzeichen in das `std::cout`-Objekt geschoben.
Eine Anweisung der Gestalt `printer(1, "ABC", 2, "DEF", 3, "GHI");` führt zur Ausgabe

```
1ABC2DEF3GHI
```

Möchte man die einzelnen Argumente von `printer` mit Trennzeichen auszugeben,
dürfen wir das Folding nicht mit dem `<<`-Operator durchführen.
Das so genannte &bdquo;*Folding over a Comma*&bdquo; hilft jetzt weiter,
es kommt ein *Unary Right Folding*&ndash;Ausdruck zum Einsatz:

```cpp
template <typename ...ARGS>
void printer(ARGS ...args) {
    ((std::cout << args << ", ") , ...);
    std::cout << std::endl;
}
```

*Ausgabe*:

```
1, ABC, 2, DEF, 3, GHI,
```

bei Ausführung der Anweisung

```cpp
printer(1, "ABC", 2, "DEF", 3, "GHI");
```

Wenn Sie die letzte Ausgabe genau betrachten, können Sie ein störendes Trennzeichen am Zeilenende beobachten.

*Aufgabe*:
Schreiben Sie Funktion `printer` so um, dass das letzte Trennzeichen nicht mehr ausgegeben wird!

*Zusatzfrage*:
In der Realisierung der `printer`-Funktion gibt es mehrere Variationsmöglichkeiten.
Wenn Sie Ihre Modern C++ Kenntnisse vertiefen möchten, lassen sich zum Zwecke des Übens
folgende Sprachkonzepte in eine Realisierung mit einbeziehen:

  * Initialisierungs-Liste (`std::initializer_list`) &ndash; *Achtung*: Hier gibt es eine Einschränkung bzgl. der Datentypen der Parameter beim Aufruf.
  * Range-based `for` Loop
  * *Folding*
  * &bdquo;*Folding* over a Comma&rdquo;
  * Lambda-Funktionen
  * Self-Invoking Lambda-Funktionen (*IIFE* - *Immediately Invoked Functional Expression*)

---

[Lösungen](Exercises_06_Folding.cpp)

---

[An den Anfang](#aufgaben-zu-folding)

---
