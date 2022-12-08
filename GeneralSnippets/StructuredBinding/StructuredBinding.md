# Structured Binding

[Zurück](../../Readme.md)

---

[Quellcode](StructuredBinding.cpp)

---

##### Verknüpfung einer Liste von Bezeichnern mit einem Satz von Objekten (Variablen):

Das so genannte *Structured Binding* besitzt syntaktisch folgendes Aussehen:

```cpp
auto [var1, var2, ...] = <pair, tuple, struct, or array expression>;
```

Die Liste der Variablen `var1`, `var2`, ... muss in ihrer Anzahl exakt mit der Anzahl
der Variablen übereinstimmen, die in dem referenzierten Ausdruck vorhanden sind.

Der Ausdruck `<pair, tuple, struct, or array expression>` kann sein:

  * Ein `std::pair`-Objekt
  * Ein `std::tuple`-Objekt
  * Eine `struct`-Variable
  * Ein Feld fester Länge

Der Typ `auto` kann auch in den Variationen `auto`, `const auto&`, `auto&`  oder sogar `auto&&` auftreten
(auch `const auto` ginge, macht aber in den seltensten Fällen Sinn). 

---

[Zurück](../../Readme.md)

---
