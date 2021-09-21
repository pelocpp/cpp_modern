# Klasse `std::initializer_list<T>`

[Zurück](../../Readme.md)

---

[Quellcode](InitializerList.cpp)

---

Um für Konstruktoren eine variable Anzahl von Parametern (desselben Typs) zu ermöglichen,
wurde in C++ das Konzept von *Initialisierungslisten* für benutzerdefinierte Typen eingeführt.

Eine Klasse muss das einen entsprechenden Konstruktor zur Verfügung stellen, der das Klassentemplate `std::initializer_list<>`
verwendet.

Weitere Details entnehmen Sie bitte den Code-Snippets.

Ausgabe des Code-Snippets:

```cpp
25
20
a - b - c -
a - b - c -
65 - 66 - 67 -
ABC - DEF - GHI -
ABC - DEF - GHI -
RST - UVW - XYZ -
Begin of list:
a
b
c
End of list.
Begin of list:
a
b
c
End of list.
Begin of list:
65
66
67
End of list.
Begin of list:
ABC
DEF
GHI
End of list.
Begin of list:
ABC
DEF
GHI
End of list.
Begin of list:
RST
UVW
XYZ
End of list.
Hans - Sepp - Franz

James - John - Robert - Michael - William - David - Richard - Joseph - Thomas
```

---

[Zurück](../../Readme.md)

---
