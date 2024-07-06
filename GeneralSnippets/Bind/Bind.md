# `std::bind`

[Zurück](../../Readme.md)

---

[Quellcode](Bind.cpp)

---

## Allgemeines


`std::bind` ist zur Bildung von so genannten &bdquo;*Partial Application*&rdquo; Teilfunktionen vorgesehen.
Angenommen, Sie haben ein Funktionsobjekt `f`, das 3 Argumente akzeptiert:

```cpp
f(a,b,c);
```

Sie möchten nun mit Hilfe von `f` ein neues Funktionsobjekt `g` definieren,
das nur zwei Argumente akzeptiert:

```
g(a,b) := f(a, 4, b);
```

`g` ist eine so genannte &bdquo;*Partial Application*&rdquo; der Funktion `f`:
Das mittlere Argument wurde bereits angegeben, zwei weitere sind bei einem Aufruf von `g` noch festzulegen.
Hier kommt nun `std::bind` ins Spiel, um eine derartige Funktion `g` zu definieren: 

```cpp
auto g = std::bind(f, _1, 4, _2);
```

Im Quellcode finden Sie eine Umsetzung der Standardfunktion `std::pow` (mit regulär 2 Parametern)
auf eine neue Funktion vor, die nur einen Parameter besitzt.


## Literaturhinweise

Das Beispiel zu `std::bind`
stammt aus &bdquo;[`std::function` and `std::bind`: what are they, and when should they be used?](https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used)&rdquo;.

---

[Zurück](../../Readme.md)

---
