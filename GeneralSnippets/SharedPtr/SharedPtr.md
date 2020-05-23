# Shared Pointer: Klasse `std::shared_ptr`

[Quellcode](SharedPtr.cpp)

---

An Hand von zwei Beispielen wird die Arbeitsweise der `std::shared_ptr`-Klasse demonstriert.

Ausgabe des ersten Code-Snippets:

```cpp
ptr1:       123
*ip:        124
*ptr1:      124
use_count:  3
use_count:  3
use_count:  3
value:      124
value:      124
value:      124
```

Ausgabe des zweiten Code-Snippets:

```cpp
outer scope: 1
inner scope: 2
outer scope: 1
```

---

[Zurück](../../Readme.md)

---

