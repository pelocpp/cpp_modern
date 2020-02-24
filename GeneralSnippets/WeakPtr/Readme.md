# Weak Pointer

Die Funktionsweise der Wrapper-Klasse wird an einem Beispiel aufgezeigt.

Interessant ist der Weak-Pointer bei zyklischen Referenzen:

<img src="cycle.jpg" width="300">

Ausgabe des Code-Snippets:

```cpp
Begin-of-program
Begin-of-program
Begin-of-Scope
Usage count shared_ptr: 1
Usage count shared_ptr: 1
Is weak ptr expired: false
Usage count shared_ptr: 2
Usage count shared_ptr: 2
*sharedPtr: 0
Is weak ptr expired: false
End-of-Scope
Is weak ptr expired: true
Don't get the resource!
End-of-program
```

Beachten Sie die Ausgabe des zweiten Code-Snippets: Hier haben wir es mit
einer zyklischen Referenz von Smart-Pointern zu tun:

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