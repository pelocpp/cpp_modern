# Verwendung von `is_transparent`

[Zurück](../../Readme.md)

---

[Quellcode](Tuple.cpp)

---

## Allgemeines

is_transparent ist ein Marker-Typ im Vergleichsobjekt, der dem Container signalisiert, dass er find, lower_bound & Co. auch mit Argumenten anderer Typen als dem Schlüsseltyp aufrufen darf, ohne vorher ein temporäres Schlüsselobjekt zu erzeugen.



---

## Komparatoren (*Comparators*)

In C++ ist ein Komparator eine Funktion oder ein Funktionsobjekt, das zur Festlegung der Reihenfolge von Elementen dient.
Er spielt eine starke Rolle bei Algorithmen wie `sort` sowie bei Containern wie `std::set` und `std::map`,
wo er die eindeutige Positionierung der Elemente anhand eines bestimmten Kriteriums bestimmt.

Typischerweise nimmt ein Komparator zwei Argumente desselben Typs entgegen und gibt einen booleschen Wert zurück,
der angibt, ob das erste Argument dem zweiten vorangehen soll.
So könnte beispielsweise ein einfacher Komparator für Ganzzahlen eine Sortierreihenfolge vom kleinsten zum größten Wert festlegen.

```cpp
bool compare(int a, int b) {
    return a < b;
}
```


---

## Transparente Komparatoren

Transparente Komparatoren erweitern die herkömmliche Definition, indem sie Vergleiche zwischen verschiedenen Typen ermöglichen,
ohne dass für jede Typkombination Überladungen definiert werden müssen.

Diese Funktionalität nutzt die mit C++14 eingeführten Möglichkeiten der Typableitung, insbesondere durch den Einsatz polymorpher Funktionsobjekte.

Ein transparenter Komparator deklariert innerhalb seiner Definition einen speziellen Typ namens `is_transparent`.
Diese Kennzeichnung ermöglicht es dem Komparator, bei Operationen mit unterschiedlichen Operandentypen zum Einsatz zu kommen &ndash; vorausgesetzt,
die Typen sind für den jeweiligen Vergleich kompatibel.

---

Implementierung eines transparenten Komparators

Die Implementierung eines transparenten Komparators erfordert die Definition eines Funktionsobjekts mit einem `is_transparent`-Typ
sowie Überladungen für `operator()`, die unterschiedliche Typen vergleichen können.

Hier ist ein vereinfachtes Beispiel unter Verwendung von `std::set`:


---

## Literaturhinweise <a name="link7"></a>

Die Anregungen zu diesem Code-Snippet finden sich unter anderem unter

[std::optional](https://sodocumentation.net/cplusplus/topic/2423/std--optional)<br>(abgerufen am 23.05.2020).

[Modern C++ Features – std::optional](https://arne-mertz.de/2018/06/modern-c-features-stdoptional/)<br>(abgerufen am 23.05.2020).

[Quick tip: How to return std::optional from a function](https://techoverflow.net/2019/06/13/quick-tip-how-to-return-stdoptional-from-a-function/)<br>(abgerufen am 23.05.2020).

Zu den Erweiterungen ab C++ 23 &ndash; neue monadische Funktionen &ndash; gibt es die folgenden beiden interessanten Artikel:

[How to Use Monadic Operations for `std::optional` in C++ 23](https://www.cppstories.com/2023/monadic-optional-ops-cpp23/)<br>(abgerufen am 08.04.2026).

[Daily bit(e) of C++ | Monadic interface for `std::optional`](https://medium.com/@simontoth/daily-bit-e-of-c-monadic-interface-for-std-optional-fd1a9349960c)<br>(abgerufen am 08.04.2026).

---

[Zurück](../../Readme.md)

---



// https://johnfarrier.com/transparent-comparators-in-c23/

// https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/

// https://medium.com/factset/modern-c-in-depth-transparent-comparisons-afef5900535b

