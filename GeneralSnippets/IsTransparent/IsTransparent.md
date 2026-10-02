# Verwendung von `is_transparent`

[Zurück](../../Readme.md)

---

[Quellcode](Tuple.cpp)

---

## Allgemeines

`is_transparent` ist ein Marker-Typ in einem Vergleichsobjekt, der dem Container signalisiert,
dass er die Methoden `find`, `lower_bound` und weitere auch mit Argumenten anderen Typs als dem des Schlüsseltyps (Schlüssel-Wert) aufrufen darf,
ohne vorher ein **temporäres** Schlüsselobjekt zu erzeugen.

---

## Komparatoren (*Comparators*)

In C++ ist ein Komparator eine Funktion oder ein Funktionsobjekt, das zur Festlegung der Reihenfolge von Elementen dient.
Er spielt eine Rolle bei Algorithmen wie `sort` sowie bei Containern wie `std::set` und `std::map`,
wo er die eindeutige Positionierung der Elemente anhand eines bestimmten Kriteriums bestimmt.

Typischerweise nimmt ein Komparator zwei Argumente desselben Typs entgegen und gibt einen booleschen Wert zurück,
der angibt, ob das erste Argument dem zweiten vorangehen soll.
So könnte beispielsweise ein einfacher Komparator für Ganzzahlen eine Sortierreihenfolge vom kleinsten zum größten Wert festlegen:

```cpp
bool compare(int a, int b) {
    return a < b;
}
```

---

## Transparente Komparatoren

Transparente Komparatoren erweitern die herkömmliche Definition, indem sie Vergleiche zwischen verschiedenen Typen ermöglichen,
ohne dass für jede Typkombination Überladungen definiert werden müssen.

Ein transparenter Komparator deklariert innerhalb seiner Definition einen speziellen Typ namens `is_transparent`.
Diese Kennzeichnung (Marker) ermöglicht es dem Komparator, bei Operationen mit unterschiedlichen Operandentypen zum Einsatz zu kommen &ndash; vorausgesetzt,
die Typen sind für den jeweiligen Vergleich kompatibel.

---

## Demonstration / Vergleich von transparentem und nicht transparentem Komparators

Wir verwenden die Klasse `std::set`.
Der Standard `std::less<std::string>` ist nicht transparent, `std::less<>` (also `std::less<void>`) dagegen schon:

```cpp
```

---

## Implementierung eines transparenten Komparators

Die Implementierung eines transparenten Komparators erfordert die Definition eines Funktionsobjekts mit einem `is_transparent`-Typ
sowie Überladungen für den Aufrufoperator `operator()`, um unterschiedliche Typen vergleichen zu können.

Hier ist ein vereinfachtes Beispiel unter Verwendung von `std::set`:

---

## Literaturhinweise <a name="link7"></a>

Die Anregungen zu diesem Code-Snippet finden sich unter anderem unter in

[Leveraging the Power of Transparent Comparators in C++](https://johnfarrier.com/transparent-comparators-in-c23/)

und

[Modern C++ In-Depth — Transparent Comparisons](https://medium.com/factset/modern-c-in-depth-transparent-comparisons-afef5900535b)

und

[is_transparent: How to search a C++ set with another type than its key](https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/)

wieder.

---

[Zurück](../../Readme.md)

---
