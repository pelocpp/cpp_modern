# Structured Binding

[Zurück](../../Readme.md)

---

[Quellcode](StructuredBinding.cpp)

---

## Verknüpfung einer Liste von Bezeichnern mit einem Satz von Objekten (Variablen):

Das so genannte *Structured Binding* besitzt syntaktisch folgendes Aussehen:

```cpp
auto [var1, var2, ...] = <aggregate>;
```

oder

```cpp
auto [var1, var2, ...] { <aggregate> };
```

Als *Aggregat* kommen in Frage:

  * `std::pair`
  * `std::tuple`
  * `std::array`
  * Eine Struktur-Variable (`struct`)
  * Ein C-Array

Die Liste der Variablen `var1`, `var2`, ... muss in ihrer Anzahl exakt mit der Anzahl
der Variablen übereinstimmen, die in dem referenzierten Ausdruck vorhanden sind.

Der Typ `auto` kann auch in den Variationen `auto`, `const auto&`, `auto&`  oder sogar `auto&&` auftreten
(auch `const auto` ginge, macht aber in den seltensten Fällen Sinn). 

---

[Zurück](../../Readme.md)

---
