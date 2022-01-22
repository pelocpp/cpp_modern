# Argument-Dependent Name Lookup (ADL) / Koenig-Lookup

[Zurück](../../Readme.md)

---

[Quellcode](ArgumentDependentNameLookup.cpp)

---

## Überblick

*Argument-Dependent Name Lookup* (*ADL*), auch als *Koenig-Lookup* bezeichnet,
hat zur Folge, dass der Bezeichner einer Funktion (oder ein Operator), die ohne Angabe ihres Namensraums aufgerufen wird,
auch in Namensräumen gesucht wird,
in denen der Typ des Arguments bzw. der Argumente definiert ist.
Deshalb wird diese Suche auch als *Argument-Dependent Name Lookup* bezeichnet, kurz ADL.

Ein Beispiel hierzu:

```cpp
namespace MyNamespace
{
    class MyClass {};
    void doSomething(MyClass) {}
    void doSomething() {}
}

namespace ArgumentDependentNameLookup
{
    void test_01()
    {
        MyNamespace::MyClass obj;

        // doSomething();    // Error: 'doSomething': identifier not found

        MyNamespace::doSomething();    // works

        doSomething(obj);              // works too
    }
}
```

Im obigen Beispiel gibt es weder eine `using`-Deklaration noch eine `using`-Direktive,
aber dennoch identifiziert der Compiler den nicht qualifizierten Namen `doSomething(obj)` korrekt
als die im Namensraum `MyNamespace` deklarierte Funktion, indem er den Koenig-Lookup anwendet.

Der zweite, parameterlose Aufruf von `doSomething()` schlägt zur Übersetzungszeit fehl,
da der Compiler den Bezeichner `doSomething` nicht findet.
Offensichtlich findet kein Koenig-Lookup statt.

*Koenig-Lookup* bzw. *Argument-Dependent Name Lookup* weist den Compiler an,
nicht nur den lokalen Gültigkeitsbereich (Namensraum) zu betrachten, sondern auch die Namensräume,
die den Typ des Arguments / der Argumente enthalten.

Somit findet der Compiler im obigen Code, dass das Objekt `obj`, das das Argument einer Überladung der Funktion `doSomething()` ist,
zum Namespace `MyNamespace` gehört. Es sucht also in diesem Namensraum nach der Deklaration von `doSomething(obj)`.

### Wozu wurde der Koenig-Lookup eingeführt?

Ein einfaches Beispiel für ADL in C++ stellt die Benutzung der Stream-Klassen dar:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hallo, Welt!" << std::endl;
}
```

In diesem Beispiel wird der Stream-Operator `operator<<` verwendet, er ist im Namensraum `std` definiert.

Im Gegensatz zu `std::cout` und `std::endl` wird er aber ohne eine Qualifizierung mit `std::` aufgerufen,
das Beispiel ist dennoch übersetzungsfähig! Ohne die Verwendung von ADL wäre das Beispiel **nicht** übersetzungsfähig!

Man müsste ohne ADD das Beispiel entweder in den `std`-Namensraum verlegen (ergibt keinen Sinn)
oder den Operator `<<` explizit importieren:

```cpp
using std::operator<<;
```

Dies ist ebenfalls nicht anstrebenswert genauso wenig wie ein Verzicht auf die Infix-Schreibweise:

```cpp
std::operator<<(std::cout, "Hello World").operator<<(std::endl);
```

---

[Zurück](../../Readme.md)

---
