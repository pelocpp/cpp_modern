# Variadische Templates: Visitor

[Zurück](../../Readme.md)

---

&#x21D0; [Teil IV: Variadische Templates: Mixins](VariadicTemplates_04_Mixins.md)

---

[Quellcode](VariadicTemplate_05_Visitor.cpp)

---

## Standard-Klasse std::visit und eine Funktion make_visitor

Eine Beschreibung dieses Beispiels findet sich unter <https://pabloariasal.github.io/2018/06/26/std-variant/>.
Neben der Beschreibung gibt es eine weitere C++-Definition zu beachten:

### *Why doesn't overloading work for derived classes*

Oder an folgendem Beispiel betrachtet:

```cpp
 using namespace std;
    class B {
    public:
        int f(int i) { cout << "f(int): "; return i + 1; }
        // ...
    };
    class D : public B {
    public:
        double f(double d) { cout << "f(double): "; return d + 1.3; }
        // ...
    };
    int main()
    {
        D* pd = new D;
        cout << pd->f(2) << '\n';
        cout << pd->f(2.3) << '\n';
        delete pd;
    }
```

Die Ausgabe lautet

```cpp
f(double): 3.3
f(double): 3.6
```

und nicht wie möglicherweise erwartet:

```cpp
f(int): 3
f(double): 3.6
```

Warum das so ist, kann unter dem letzten Link nachgelesen werden.
Damit erklären sich die vielen `using`-Anweisungen in dem Lösungsvorschlag.


## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Abschnitt sind entnommen aus

[std::variant doesn't Let Me Sleep](https://pabloariasal.github.io/2018/06/26/std-variant/)<br>(abgerufen am 22.05.2020).

oder

[How To Use std::visit With Multiple Variants](https://www.bfilipek.com/2018/09/visit-variants.html/)<br>(abgerufen am 22.05.2020).

---

[Zurück](../../Readme.md)

---
