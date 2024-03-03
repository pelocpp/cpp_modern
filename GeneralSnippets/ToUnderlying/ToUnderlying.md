# Typwandlung `std::to_underlying`

[Zurück](../../Readme.md)

---

[Quellcode](ToUnderlying.cpp)

---

## Allgemeines

Die Funktion `std::to_underlying` vereinfacht die Konvertierung einer Aufzählung
in den zugrunde liegenden Typ.


*Beispiel*:

```cpp
01: enum class Color : char {
02:     Red   = 'R',
03:     Green = 'G',
04:     Blue  = 'B'
05: };
06: 
07: enum class Weekdays : int {
08:     Monday     = 1,
09:     Tuesday    = 2,
10:     Wednesday  = 3,
11:     Thursday   = 4,
12:     Friday     = 5,
13:     Saturday   = 6,
14:     Sunday     = 7,
15: };
16: 
17: static void test_01()
18: {
19:     Color color{ Color::Blue };
20:     auto colorCode{ std::to_underlying(color) };
21:     static_assert(std::is_same<decltype(colorCode), char>::value);
22:     std::println("Color Code: {}", colorCode);
23: 
24:     Weekdays day{ Weekdays::Friday };
25:     int dayCode{ std::to_underlying(day) };
26:     static_assert(std::is_same<decltype(dayCode), int>::value);
27:     std::println("Weekday Code: {}", dayCode);
28: }
```

*Ausgabe*:

```
Color Code: B
Weekday Code: 5
```

---

[Zurück](../../Readme.md)

---
