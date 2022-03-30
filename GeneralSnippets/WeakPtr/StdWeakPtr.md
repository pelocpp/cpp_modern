# Weak Pointer: Klasse `std::weak_ptr`

[Zurück](../../Readme.md)

---

[Quellcode](StdWeakPtr.cpp)

---

## &ldquo;It's about ownership&rdquo;

###### Exklusiver Besitz: `std::unique_ptr<T>`

###### Geteilter Besitz: `std::shared_ptr<T>`

#### Temporärer Besitz: `std::weak_ptr<T>`

---

Die Funktionsweise der Wrapper-Klasse wird an zwei Beispielen aufgezeigt.

Das erste Beispiel erläutert vor allem den Zusammenhang zwischen den beiden Klassen
`std::weak_ptr` und `std::shared_ptr`.

*Hinweis*:

Man beachte den Unterschied in der Anwendung der beiden Anweisungen

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(123);
```

oder

```cpp
std::shared_ptr<int> ptr1 = std::shared_ptr<int>(new int{ 123 });
```

Im ersten Fall wird für den dynamischen Speicherbereich *und* den Control-Block
*ein* gemeinsamer Speicherbereich angelegt &ndash; im zweiten Fall sind dies zwei getrennte Speicherbereiche.

Dies kann man im Debugger beobachten, die Freigabezeitpunkte der Speicherbereiche sind unterschiedlich:

<img src="WeakPointer_01.PNG" width="500">

*Abbildung* 1: Der Control-Block enthält beide Speicherbereiche.

<img src="WeakPointer_02.PNG" width="400">

*Abbildung* 2: Der Control-Block enthält nicht das eigentlich dynamisch angelegte Objekt. 

In *Abbildung* 1 erkennt man, dass trotz eigentlich erfolgter Freigabe des dynamisch angelegten Objekts
dieses noch vom Debugger angezeigt wird. Die tatsächliche Freigabe erfolgt zu einem späteren Zeitpunkt.

## Zyklische Referenzen

Interessant ist der Weak-Pointer bei zyklischen Referenzen:

<img src="cpp_snippets_cyclic_references.svg" width="700">

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
