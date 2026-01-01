# Aufgaben zur funktionalen Programmierung

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_13_FunctionalProgramming.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Umwandlung von Zeichenketten eines `std::vector`-Objekts<br/>(Voraussetzungen: Templates, Lambda-Funktionen) |
| *Aufgabe* 2 | `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis<br/>(Voraussetzungen: Kenntnisse von `decltype` und `declval`) |

*Tabelle* 1: Aufgaben zur funktionalen Programmierung.

---

## Aufgabe 1: Umwandlung von Zeichenketten eines `std::vector`-Objekts

#### Voraussetzungen: Templates, Lambda-Funktionen

In den beiden Dateien

[FunctionalProgramming01.cpp](../FunctionalProgramming/FunctionalProgramming01.cpp)

und

[FunctionalProgramming02.cpp](../FunctionalProgramming/FunctionalProgramming02.cpp)

finden Sie zwei alternative Implementierungen der drei Funktionen `map`, `filter` und `fold` vor.

**Teilaufgabe 1**:

Studieren Sie den Quellcode der beiden Realisierungen.
Welche prinzipiellen Unterschieden liegen in der Implementierung vor?

**Teilaufgabe 2**:

Es wird ein Vektor mit Zeichenketten betrachtet:

```cpp
std::vector<std::string> words = { 
    std::string("one"),
    std::string("two"),
    std::string("three")
};
```

Mit einer geeigneten Funktion der *funktionalen Programmierung* sollen
die einzelnen Zeichen aller Zeichenketten dieses Vektors in Großbuchstaben umgewandelt werden.
Welche Funktion höherer Ordnung benötigen Sie hierzu?
Schreiben Sie eine Testfunktion, die ihre Realisierung testet. 


---

## Aufgabe 2: `decltype`, `declval` und nachlaufender Rückgabetyp in der Praxis

#### Voraussetzungen: Kenntnisse von `decltype` und `declval`

Im Code-Snippet zu *Funktionaler Programmierung* haben wir die Funktion höherer Ordnung `fold` betrachtet:

```cpp
template <typename TReturn, typename InputIterator, typename TFunctor>
auto fold(InputIterator begin, InputIterator end, TFunctor&& lambda)
    // not needed, just for demonstration purposes
    -> TReturn
{
    TReturn init{};
    return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
}
```

Die `fold`-Funktion wendet
eine Lambda-Funktion mit zwei Argumenten der Reihe nach auf alle Elemente eines Containers an und
reduziert auf diese Weise die Elemente des Containers auf ein Endergebnis ("Resultat").

Interessant dabei ist, dass der Typ dieses Endergebnisses nicht gleich dem Typ der einzelnen Elemente des Containers sein muss.

**Teilaufgabe 1**:

Wenden Sie die `fold`-Funktion auf einen Vektor mit `int`-Elementen an. Das Ergebnis soll
eine Zeichenkette sein, die alle `int`-Werte des Vektors einzeln in eine Zeichenkette umwandelt und diese miteinander konkateniert.

*Beispiel*:

```cpp
std::vector<int> numbers { 1, 2, 3 } ==> "123"
```

Wie muss die dazugehörige Lambda-Funktion aussehen?

**Teilaufgabe 2**:

C++-Puristen werden bei Betrachtung der `fold`-Funktion eine kleine Redundanz erkannt haben:
Der erste Template-Parameter `TReturn` ist bei strenger Betrachung überflüssig:
Es handelt sich dabei um den Datentyp des Ergebnisses der `fold`-Operation,
aber dieser ist eigentlich an anderer Stelle bereits vorgegeben bzw. bekannt.
Richtig erkannt, der dritte Parameter der `fold`-Funktion ist eine Lambda-Funktion,
deren Rückgabewert identisch mit dem Ergebnistyp der `fold`-Operation ist.

Schreiben Sie mit dieser Erkenntnis eine neue Version der `fold`-Funktion.
Diese muss nun den Rückgabewert an Hand der Template-Parameter berechnen.
Der Rumpf der `fold`-Funktion ist infolgedessen auch kleinen Änderungen unterworfen.

```cpp
template <typename InputIterator, typename TFunctor>
auto foldEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
    // REQUIRED
    -> ???
{
   ...
}
```

*Hinweis*: Diese Teilaufgabe ist wahrlich nicht einfach, mit `decltype` und `declval` erreichen Sie das Ziel!

---

[Lösungen](Exercises_13_FunctionalProgramming.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
