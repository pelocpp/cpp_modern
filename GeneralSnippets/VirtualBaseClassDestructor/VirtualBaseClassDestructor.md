# Virtueller Destruktor

[Zurück](../../Readme.md)

---

[Quellcode](VirtualBaseClassDestructor.cpp)

---

## Allgemeines

Virtuelle Destruktoren sind nützlich, wenn Sie möglicherweise eine Instanz einer abgeleiteten Klasse
über einen Zeiger auf die Basisklasse löschen. Wir betrachten das folgende Beispiel:

```cpp
01: class Base
02: {
03: public:
04:     ~Base()
05:     {
06:         // do some important cleanup in class Base
07:         std::println("d'tor Base");
08:     }
09: 
10:     // some virtual methods
11:     virtual void doSomething() {}
12: };
```

und eine davon abgeleitete Klasse `Derived`:

```cpp
01: class Derived : public Base
02: {
03: public:
04:     ~Derived()
05:     {
06:         // do some important cleanup in class Derived
07:         std::println("d'tor Derived");
08:     }
09: };
```

Wir verwenden beide Klassen `Base` und `Derived` nun wie folgt:

```cpp
Base* b = new Derived();
delete b; // here's the problem!
```

Welche Ausgaben in der Konsole erwarten Sie? Sie werden überrascht sein:

```
d'tor Base
```

Da der Destruktor von `Base` nicht virtuell ist und `b` ein `Base*`-Zeiger ist,
der auf ein von `Base` abgeleitetes Objekt zeigt, hat die Anweisung `delete b` ein undefiniertes Verhalten.

In den meisten Implementierungen wird der Aufruf des Destruktors wie jeder nicht virtuelle Code aufgelöst,
was bedeutet, dass der Destruktor der Basisklasse aufgerufen wird,
jedoch nicht der der abgeleiteten Klasse, was zu Ressourcenleaks führen kann!

Zusammenfassend lässt sich sagen, dass Destruktoren einer Basisklasse immer virtuell deklariert sein sollten,
wenn sie auf Grund eines polymorphen Szenarios aufgerufen werden sollten.

Wenn Sie in unserem Beispiel den Destruktor von `Base` in 

```
01: virtual ~Base()
02: {
03:     // do some important cleanup in class Base
04:     std::println("d'tor Base");
05: }
```

abändern, also nur das Schlüsselwort `virtual` hinzufügen, lautet die Programmausgabe wie gewünscht

```
d'tor Derived
d'tor Base
```

---

[Zurück](../../Readme.md)

---
