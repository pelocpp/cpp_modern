# Weak Pointer

Die Funktionsweise der Wrapper-Klasse wird an einem Beispiel aufgezeigt.

Interessant ist der Weak-Pointer bei zyklischen Referenzen:

<img src="cycle.jpg" width="500">

Beachten Sie die Ausgabe des zweiten Code-Snippets: Hier haben wir es mit
einer zyklischen Referenz von Smart-Pointern zu tun. Im einen Fall werden
alle beteiligten Zeiger freigegeben, im anderen auf Grund der zyklischen Referenz nicht.

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