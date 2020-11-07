# Klassentemplates: Grundlagen

[Quellcode](TemplatesClassBasics01.cpp)

---

Es werden grundlegende Aspekte von Klassentemplates aufgezeigt:

  * Erstellung eines einfachen Klassentemplates (Definition der Methoden *innerhalb* des Templates)
  * Erstellung eines einfachen Klassentemplates (Definition der Methoden *außerhalb* des Templates)
  * Methodentemplates
  * Schlüsselwort `typename` innerhalb von Templates (*abhängiger Name*)
  * Methoden eines Klassentemplates überschreiben (spezialisieren)
  * Klassentemplates partiell spezialisieren


*Hinweis*:

Die vorgestellte Klasse `Optional` in den ersten Code-Snippets ist an Hand einer gleichnamigen Standardklasse entstenden,
die ab dem Standard C++ 17 auch (mit dem gleichen Namen) in der Standardklassenbibliothek vorhanden ist.
Um sie zu verwenden, bedarf es der `#include`-Anweisung

```cpp
#include <optional>
```

Es folgen die Ausgaben der jeweiligen Code-Snippets:

*Erstellung eines einfachen Klassentemplates*:

```cpp
Object has value: 0
Object has value: 1
obj = 123
Object has value: 0
Error! No value present!
Object has value: 0
Object has value: 1
obj = ABC
Object has value: 0
Error! No value present!
```

*Methodentemplates*:

```cpp
100 --> 123.456
654.321 <== 100
```

*Schlüsselwort `typename` innerhalb von Templates*:

```cpp
char:
  Num Bits:7  Signed:1  Minimum:-128  Maximum:127
unsigned char:
  Num Bits:8  Signed:0  Minimum:0  Maximum:255
short:
  Num Bits:15  Signed:1  Minimum:-32768  Maximum:32767
int:
  Num Bits:31  Signed:1  Minimum:-2147483648  Maximum:2147483647
unsigned int:
  Num Bits:32  Signed:0  Minimum:0  Maximum:4294967295
long:
  Num Bits:31  Signed:1  Minimum:-2147483648  Maximum:2147483647
long long:
  Num Bits:63  Signed:1  Minimum:-9223372036854775808  Maximum:9223372036854775807
```

*Methoden eines Klassentemplates überschreiben*:

```cpp
123
>>> Who am I? <<<
```

*Klassentemplates partiell spezialisieren*:

```cpp
123
456
123
ABC
DEF
456
uvw
xyz
```

---

[Zurück](../../Readme.md)

---


