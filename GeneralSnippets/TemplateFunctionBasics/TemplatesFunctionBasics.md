# Funktions-Templates: Grundlagen


[Zurück](../../Readme.md)

---

[Quellcode](TemplatesFunctionBasics.cpp)

---

## Definition eines Funktions-Templates

Ein Funktions-Template &ndash; man könnte auch von einer *generischen* Funktion sprechen &ndash;
ist ein Template / eine Schablone, um potentiell unendliche viele Funktionsüberladungen zu generieren.

*Beispiel*:

```cpp
01: // function template definition
02: template <typename T>
03: bool lessThan(const T& a, const T& b)
04: {
05:     return (a < b) ? true : false;
06: }
```

Als Template-Parameter kann im Prinzip jeder Typ verwendet werden.

Allerdings werden Einschränkungen durch das Funktions-Template *implizit* definiert,
im letzten Beispiel:

  * `T` benötigt eine Realisierung des Operators `operator< (const T&) const`.
  * Die Aufrufparameter von `lessThan` müssen den selben Typ haben,
  damit `T` &ldquo;deduziert&rdquo; werden kann.
    * `bool result = lessThan(10, 20);     // ok`
    * `bool result = lessThan(10, 20.5);   // warning or error` 


---

## Überladen von Funktions-Templates

Funktions-Templates können überladen werden:

```cpp
template <typename T>
inline const T& minimum(const T& a, const T& b) {
    return (a < b) ? a : b;
}

template <typename T>
inline const T& minimum(const T& a, const T& b, const T& c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

inline const int& minimum(const int& a, const int& b) { 
    return (a < b) ? a : b;
}
```

*Beispiel*:

```cpp
01: void main()
02: {
03:     minimum(1, 2, 3);         // Template mit 3 Argumenten
04:     minimum(1.0, 2.0);        // minimum<double> per Typ Deduktion
05:     minimum('X', 'Y');        // minimum<char> per Typ Deduktion
06:     minimum(1, 2);            // non-template Variante bevorzugt
07:     minimum<>(1, 2);          // minimum<int> per Typ Deduktion
08:     minimum<double>(1, 2);    // minimum<double> ohne Typ Deduktion
09:     // <minimum('X', 3.14);   // non-template Variante für 2 ints (compiler warning)
10: }
```

---

## Spezialisieren von Funktions-Templates


Funktions-Templates können &ndash; prinzipiell, siehe dazu aber auch den nächsten Punkt &ndash; auf die gleiche Weise 
wie Klassen-Templates spezialisiert werden.

```cpp
01: template <typename T>
02: struct Point
03: {
04:     T m_x;
05:     T m_y;
06: 
07:     Point operator+ (const Point& p) const {
08:         return { m_x + p.m_x, m_y + p.m_y }; 
09:     }
10: 
11:     T distance() const {
12:         return std::sqrt(m_x * m_x + m_y * m_y);
13:     }
14: };
15: 
16: // normal function definition
17: bool lessThan(int a, int b)
18: {
19:     return (a < b) ? true : false;
20: }
21: 
22: // function template definition
23: template <typename T>
24: bool lessThan(const T& a, const T& b)
25: {
26:     return (a < b) ? true : false;
27: }
28: 
29: // explicit function template specialization
30: template <>
31: bool lessThan<Point<double>>(const Point<double>& a, const Point<double>& b)
32: {
33:     return (a.distance() < b.distance()) ? true : false;
34: }
35: 
36: // another explicit function template specialization
37: template <>
38: bool lessThan<std::complex<double>>(const std::complex<double>& a, const std::complex<double>& b)
39: {
40:     return (std::abs(a) < std::abs(b)) ? true : false;
41: }
42: 
43: void main()
44: {
45:     bool result;
46:     result = lessThan(10, 20);
47:     // result = lessThan(10, 20.5);   // warning or error
48:     result = lessThan(10.0, 20.0);
49:     result = lessThan(Point<double>{ 1, 2 }, Point<double>{ 3, 4 });
50: 
51:     using namespace std::complex_literals;
52:     std::complex<double> z1 = 1. + 2i;
53:     std::complex<double> z2 = 1. - 2i;
54:     result = lessThan(z1, z2);
55: }
```

*Hinweis*:

Eine *partielle* Überladung von Funktions-Templates ist nicht zulässig:

```cpp
01: template <typename T, typename U>
02: void function(T a, U b) {}
03: 
04: // partial function template specialization: not allowed (!)
05: template <typename T>
06: void function<T, int>(T a, int b) {}
```

Das letzte Beispiel führt zu einer Fehlermeldung der Gestalt

```
error: non-class, non-variable partial specialization 'function<T, int>' is not allowed
```


---

## Spezialisieren von Funktions-Templates: Überladen und Spezialisieren im Vergleich


Die beiden letzten Beispiele zum Überladen und Spezialisieren von Funktions-Templates
waren sorgfältig ausgewählt worden, um das jeweilige Feature demonstrieren zu können.
Aber man beachte:

  * Spezialisierungen von Funktions-Templates nehmen nicht an der Auflösung von Funktions-Überladungen teil.

  * Das heißt, eine weniger spezifische Überladung hat Vorrang vor einer spezifischeren Template-Spezialisierung.

Siehe dazu auch
Herb Sutter in diesem Artikel [Why Not Specialize Function Templates?](http://www.gotw.ca/publications/mill17.htm).

Damit schließen wir diesen Abschnitt mit der Aussage ab:

> **Lassen Sie Vorsicht bei der Spezialisierung von Funktions-Templates walten**.


---

[Quellcode](TemplatesFunctionBasics.cpp)

---

[Zurück](../../Readme.md)

---
