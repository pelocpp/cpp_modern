# Verwendung von `is_transparent`

[Zurück](../../Readme.md)

---

[Quellcode](IsTransparent.cpp)

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

## Demonstration / Vergleich von transparentem und nicht transparentem Komparator

Wir verwenden die Klasse `std::set`.
Der Standard `std::less<std::string>` ist nicht transparent, `std::less<>` (also `std::less<void>`) dagegen schon:

```cpp
01: class Key
02: {
03: private:
04:     std::string m_s;
05: 
06: public:
07:     Key(const std::string& s) : m_s{ s }
08:     {
09:         std::println("-> No Conversion: std::string& -> Key");
10:     }
11: 
12:     Key(const char* cp) : m_s{ cp }
13:     {
14:         std::println("-> Conversion: const char* -> Key");
15:     }
16: 
17:     friend bool operator<(const Key& a, const Key& b) { return a.m_s < b.m_s; }
18:     friend bool operator<(const Key& a, const char* b) { return a.m_s < b; }
19:     friend bool operator<(const char* a, const Key& b) { return a < b.m_s; }
20: };
21: 
22: void test()
23: {
24:     std::set<Key> normal;
25:     normal.insert("one");                         // conversion (necessary)
26:     std::puts("find in normal std::set:");
27:     auto pos1 = normal.find("one");               // conversion
28: 
29:     std::set<Key, std::less<>> transparent;
30:     transparent.insert("one");                    // conversion (necessary)
31:     std::puts("find in transparent std::set:");
32:     auto pos2 = transparent.find("one");          // no output, no conversion
33: }
```

---

## Implementierung eines transparenten Komparators

Die Implementierung eines transparenten Komparators erfordert die Definition eines Funktionsobjekts mit einem `is_transparent`-Typ
sowie Überladungen für den Aufrufoperator `operator()`, um unterschiedliche Typen vergleichen zu können.

Hier ist ein vereinfachtes Beispiel unter Verwendung von `std::set`:

```cpp
01: struct MyCompare
02: {
03:     using is_transparent = void;   // add / remove comment
04: 
05:     bool operator() (const std::string& a, const std::string& b) const
06:     {
07:         return a < b;
08:     }
09: 
10:     bool operator() (const std::string& a, const char* b) const  // add / remove comment
11:     {
12:         return a < b;
13:     }
14: 
15:     bool operator() (const char* a, const std::string& b) const  // add / remove comment
16:     {
17:         return a < b;
18:     }
19: };
20: 
21: void test()
22: {
23:     std::set<std::string, MyCompare> strings;
24: 
25:     strings.insert("one");
26:     strings.insert("two");
27: 
28:     auto pos = strings.find("one");
29: }
```

---

## Literaturhinweise <a name="link7"></a>

Die Anregungen zu den Code-Snippets finden sich unter anderem unter in

[Leveraging the Power of Transparent Comparators in C++](https://johnfarrier.com/transparent-comparators-in-c23/)

und

[Modern C++ In-Depth — Transparent Comparisons](https://medium.com/factset/modern-c-in-depth-transparent-comparisons-afef5900535b)

und

[is_transparent: How to search a C++ set with another type than its key](https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/)

vor.

---

[Zurück](../../Readme.md)

---
