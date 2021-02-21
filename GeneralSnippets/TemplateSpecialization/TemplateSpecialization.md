# Template Spezialisierung (Template Specialization)

[Zurück](../../Readme.md)

---

[Quellcode](TemplateSpecialization.cpp)

---

## Template Spezialisierung

Unter Template Spezialisierung (Template Specialization) versteht mal die Möglichkeit,
dass eine Schablone (ein Template) Sonderfälle behandelt.
Manchmal könnte ein generischer Algorithmus für eine bestimmte Art von Sequenz (Container) viel effizienter arbeiten
(z.B. wenn man Iteratoren mit wahlfreiem Zugriff - *random-access* - verwendet).
Daher ist es sinnvoll, den Algorithmus und damit das Template auf diesen Fall zu spezialisieren,
während für alle anderen Fälle der langsamere, aber allgemeinere Ansatz verwendet wird.

Performance ist ein häufiger Grund für die Templatespezialisierung, aber nicht der einzige.
Man kann beispielsweise eine Schablone auch spezialisieren, um mit bestimmten Objekten zu arbeiten,
die nicht der normalen Schnittstelle entsprechen, die von der generischen Vorlage erwartet wird.
Diese Betrachtungen bzw. Ausnahmefälle können mit zwei Arten der Templatespezialisierung behandelt werden:
der expliziten Template Spezialisierung und der teilweise (partielle) Template Spezialisierung
("*explicit template specialization*" und "*partial template specialization*").

## Explizite Template Spezialisierung

Mit der expliziten Template Spezialisierung können Sie eine bestimmte Implementierung
für eine bestimmte Kombination von Templateparametern schreiben.

Beispiel: 

```cpp
template<typename T>
class GenericSorter
{
public:
    static void sort(std::vector<T>& values)
    {
        /* ... */
    };
};
```

Wenn wir eine schnellere (oder andere spezialisierte) Möglichkeit haben,
speziell mit Vektoren von `char`-Variablen (Zeichen) umzugehen,
dann kann man die Klasse `GenericSorter` explizit spezialisieren:

```cpp
template<>
class GenericSorter<char>
{
public:
    static void sort(std::vector<char>& values)
    {
        /* ... */
    };
};
```

Der Compiler wählt dann die am besten geeignete Schablone aus:

```cpp
std::vector<int>  vi;
std::vector<char> vc;

GenericSorter<int>::sort(vi);   // calls sort<std::vector<int>>
GenericSorter<char>::sort(vc);  // calls specialized sort<std::vector<char>>
```

## Partielle Template Spezialisierung

Für Klassen Templates (nicht: Funktionstemplates / Funktionsschablonen) kann man Teilspezialisierungen definieren,
die nicht alle Parameter der primären (nicht spezialisierten) Klassenvorlage ersetzen müssen.

Betrachten wir dazu das folgende Beispiel. Die erste Vorlage ist die primäre Klassenvorlage:

```cpp
template<typename T1, typename T2, int I>
class A {};                               // #1
```

Wir können `A` für den Fall spezialisieren, dass `T2` ein `T1*` ist:

```cpp
template<typename T, int I>
class A<T, T*, I> {};                     // #2
```

Oder für den Fall, dass `T1` ein Zeiger ist:

```cpp
template<typename T1, typename T2, int I>
class A<T1*, T2, I> {};                   // #3
```

Oder für den Fall, dass `T1` ein `int` ist und `T2` ein beliebiger Zeiger ist und `I` gleich 5 ist::

```cpp
template<typename T>
class A<int, T*, 5> {};                   // #4
```

Oder für den Fall, dass `T2` ein Zeiger ist:

```cpp
template<typename T1, typename T2, int I>
class A<T1, T2*, I> {};                   // #5
```

In den Deklarationen 2 bis 5 werden Teilspezialisierungen der primären Vorlage deklariert.
Der Compiler wählt dann die entsprechende Vorlage aus:


```cpp
A<int, int, 1>   a1;  // uses #1

A<int, int*, 1>  a2;  // uses #2, T is int,
                      //          I is 1

A<int, char*, 5> a3;  // uses #4, T is char

A<int, char*, 1> a4;  // uses #5, T1 is int,
                      //          T2 is char,
                      //          I is 1

A<int*, int*, 2> a5;  // ambiguous:
                      // matches #3 and #5
```

---

Die Anregungen zu den Beispielen dieses Code Snippets stammen aus

[Template Specialization and Overloading](http://www.gotw.ca/gotw/049.htm)

---

[Zurück](../../Readme.md)

---
