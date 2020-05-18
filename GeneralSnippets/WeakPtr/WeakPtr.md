# Weak Pointer: Klasse `std::weak_ptr`

Die Funktionsweise der Wrapper-Klasse wird an zwei Beispielen aufgezeigt.

Das erste Beispiel erläutert vor allem den Zusammenhang zwischen den beiden Klassen
`std::weak_ptr` und `std::shared_ptr`.

Ausgabe des Code-Fragments:

```cpp
Begin-of-program
Begin-of-Scope
Usage count shared_ptr:     1
Usage count shared_ptr:     1
Is weak ptr expired:        false
Usage count shared_ptr:     2
Usage count shared_ptr:     2
*sharedPtr:                 123
Is weak ptr expired:        false
End-of-Scope
Is weak ptr expired:        true
Don't get the resource!
End-of-program
```


Interessant ist der Weak-Pointer bei zyklischen Referenzen:

<img src="cycle.jpg" width="500">

Beachten Sie die Ausgabe des zweiten Code-Snippets: Hier haben wir es mit
einer zyklischen Referenz von Shared-Pointern zu tun. Im einen Fall werden
alle beteiligten Zeiger freigegeben, im anderen auf Grund der zyklischen Referenzen nicht.

```cpp
c'tor ParentNode
c'tor RightNode
c'tor LeftNode

d'tor LeftNode
```

oder

```cpp
c'tor ParentNode
c'tor RightNode
c'tor LeftNode

d'tor LeftNode
d'tor RightNode
d'tor ParentNode
```

---

[Zurück](../../Readme.md)

---
