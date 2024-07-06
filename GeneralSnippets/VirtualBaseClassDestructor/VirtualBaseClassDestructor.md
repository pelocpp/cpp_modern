# Virtueller Destruktor

[Zur�ck](../../Readme.md)

---

[Quellcode](VirtualBaseClassDestructor.cpp)

---

## Allgemeines

Virtuelle Destruktoren sind n�tzlich, wenn Sie m�glicherweise eine Instanz einer abgeleiteten Klasse
�ber einen Zeiger auf die Basisklasse l�schen. Wir betrachten das folgende Beispiel:

```cpp
class Base
{
public:
    ~Base()
    {
        // do some important cleanup in class Base
        std::cout << "d'tor Base" << std::endl;
    }

    // some virtual methods
    virtual void doSomething() {}
};
```

und eine davon abgeleitete Klasse `Derived`:

```cpp
class Derived : public Base
{
public:
    ~Derived()
    {
        // do some important cleanup in class Derived
        std::cout << "d'tor Derived" << std::endl;
    }
};
```

Wir verwenden beide Klassen `Base` und `Derived` nun wie folgt:

```cpp
Base* b = new Derived();
delete b; // here's the problem!
```

Welche Ausgaben in der Konsole erwarten Sie? Sie werden �berrascht sein:

```
d'tor Base
```

Da der Destruktor von `Base` nicht virtuell ist und `b` ein `Base*`-Zeiger ist,
der auf ein von `Base` abgeleitetes Objekt zeigt, hat die Anweisung `delete b` ein undefiniertes Verhalten.

In den meisten Implementierungen wird der Aufruf des Destruktors wie jeder nicht virtuelle Code aufgel�st,
was bedeutet, dass der Destruktor der Basisklasse aufgerufen wird,
jedoch nicht der der abgeleiteten Klasse, was zu Ressourcenleaks f�hren kann!

Zusammenfassend l�sst sich sagen, dass Destruktoren einer Basisklasse immer virtuell deklariert sein sollten,
wenn sie auf Grund eines polymorphen Szenarios aufgerufen werden sollten.

Wenn Sie in unserem Beispiel den Destruktor von `Base` in 

```
virtual ~Base()
{
    // do some important cleanup in class Base
    std::cout << "d'tor Base" << std::endl;
}
```

ab�ndern, also nur das Schl�sselwort `virtual` hinzuf�gen, lautet die Programmausgabe wie gew�nscht

```
d'tor Derived
d'tor Base
```

---

[Zur�ck](../../Readme.md)

---
