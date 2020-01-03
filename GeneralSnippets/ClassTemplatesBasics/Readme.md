# Klassentemplates: Grundlagen

Es werden die Grundlagen von Klassentemplates an einem einfachen Beispiel aufgezeigt.

*Hinweis*:

Die vorgestellte Klasse `Optional` ist ab dem Standard C++ 17 auch in der C++-Standardklassenbibliothek vorhanden.

Um sie zu verwenden, bedarf es der `#include`-Anweisung

#include <optional>

Das Code-Snippet führt zur Ausgabe

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
Error! No value present
```
