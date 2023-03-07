# Einheitliche Initialisierung

[Zurück](../../Readme.md)

---

*Hinweis*:

Siehe dazu auch das Sprachfeature [Default-Initialisierung für Member-Variablen](../../GeneralSnippets/DefaultInitialization/DefaultInitialization.md).

---

[Quellcode](UniformInitialization.cpp)

---

Die Initialisierung mit geschweiften Klammern '{' und '}' ist ab der Version C++&ndash;11
eine einheitliche Methode zum Initialisieren von Daten.
Sie wird auch als &ldquo;*Uniform Initialization*&rdquo; oder als &ldquo;*Brace Initialization*&rdquo; bezeichnet.

<img src="cpp_init.gif" width="400">

Abbildung 1: C++ und Initialisierung: *Relax*!

---

Es lassen sich mit geschweiften Klammern ("*Uniform Initialization*") alle möglichen Arten einer Variablen-Initialisierung (auch Objekte)
mit einer einheitlichen Schreibweise initialisieren.
Am besten studiert man die einzelnen Möglichkeiten an Hand der folgenden Systematisierung:

  * Variablen elementaren Datentyps: Initialisierung mit datentyp-spezifischem Null-Wert
  * Variablen elementaren Datentyps: Allgemeine Initialisierung
  * Benutzerdefinierte Datentypen: Strukturen
  * Benutzerdefinierte Datentypen: Klassen
  * Standard STL Container
  * Dynamisch allokierte Felder
  * Statisch allokierte (bzw. definierte) Felder
  * Geschachtelte Strukturen / *Brace Elision* (Entfernen von Klammern)


#### Resümee

Das Feature der *einheitlichen Initialisierung* bringt zwei Vorteile mit sich:

  * Es lassen sich nun manche Konstrukte initialisieren, bei denen das bisher nicht möglich war:
    * STL-Containerobjekte
    * Arrays, die mit `new` allokiert wurden
    * C-Arrays, die Member-Variablen sind
  * Die Einheitlichkeit der neuen Initialisierungssyntax bringt es mit sich, dass man
    bei konsequentem Einsatz der geschweiften Klammern für die Initialisierung nun leichter
    zwischen Funktionsaufrufen und Initialisierungen unterscheiden kann:

<pre>
    <b>{ ... }</b> ==> Konstruktor-Aufruf
    <b>( ... )</b> ==> Funktions-/Methoden-Aufruf
</pre>


---

## Variablen elementaren Datentyps: Initialisierung mit datentyp-spezifischem Null-Wert

```cpp
int n{};                 // n equals 0
float f{};               // f equals 0.0
double d{};              // d equals 0.0
unsigned long l{};       // l equals 0
size_t i{};              // i equals 0
```

---

## Variablen elementaren Datentyps: Allgemeine Initialisierung

```cpp
int n{ 1 };                // n equals 1
float f{ 1.5f };           // f equals 1.5
double d{ 2.5 };           // d equals 2.5
```

---

## Benutzerdefinierte Datentypen: Strukturen

Bei einer Struktur führt die einheitliche Initialisierung eine direkte Initialisierung ihrer Membervariablen durch:

```cpp
struct Struct
{
    int m_i;
    int m_j;
};

void main()
{
    struct Struct obj1 {};        // obj1.m_i => 0, obj1.m_j => 0
    struct Struct obj2 { 1, 2 };  // obj2.m_i => 1, obj2.m_j => 2
    struct Struct obj3 { 3 };     // obj3.m_i => 3, obj3.m_j => 0
}
```

Es ist auch möglich, einer Struktur einen Konstruktor hinzuzufügen.
In diesem Fall resultiert die *Brace Initialization* in einem Aufruf an einen Konstruktor:

```cpp
struct StructWithCTor
{
    int m_i;
    int m_j;

    StructWithCTor(int i, int j) : m_i{ i }, m_j{ j } {}
};

void main()
{
    struct StructWithCTor obj { 5, 6 };        // obj.m_i => 5, obj.m_j => 6
}
```

---

## Benutzerdefinierte Datentypen: Klassen

Bei Klassen führt die *Brace Initialization* zum Aufruf eines Konstruktors.

```cpp
class Class
{
private:
    int m_a;
    int m_b;

public:
    Class(int a, int b) : m_a{ a }, m_b{ b } {}
};

void main()
{
    Class obj{ 11, 12 };  // obj.m_a => 11, obj.m_b => 12
}
```

---


## Standard STL Container

```cpp
std::vector<int> myArray{ 1, 2, 3, 4, 5 };

std::map<std::string, int> myMap
{
    { "Hans", 1958 },
    { "Sepp", 1956 } 
};
```

Diese Beispiele stehen zum Teil in Zusammenhang mit der Thematik der *Initialisierungs-Liste*.
Im Beispiel des `std::map`-Objekts werden die inneren geschweiften Klammern auf einen
Konstruktoraufruf von `std::pair` abgebildet (*einheitliche Initialisierung*).
Die äußeren geschweiften Klammern erzeugen in diesem Beispiel eine Liste des Typs

```cpp
std::initializer_list<std::pair<std::string, int>>
```

welche dann als Argument für den Aufruf des Sequenzkonstruktors der Klasse `std::map` dient.

---

## Dynamisch allokierte Felder

```cpp
int* pi = new int[5]{ 1, 2, 3, 4, 5 };
```


---

## Statisch allokierte (bzw. definierte) Felder

```cpp
int intArray[]{ 1, 2, 3, 4, 5 };
```

---

## Geschachtelte Strukturen / *Brace Elision* (Entfernen von Klammern)

```cpp
struct Inner {
    int m_array[2];
};

void main()
{
    Inner inner1;                // uninitialized
    Inner inner2{ };             // m_array[0] => 0 & m_array[1] => 0
    Inner inner3{ { 1, 2 } };    // Direct initialization
    Inner inner4{ 1, 2 };        // Uses Brace Elision (!) of m_array
}
```

---

## Literaturhinweise:

Die Anregungen zu den Beispielen stammen teilweise aus

[Bitesize Modern C++: std::initializer_list](https://blog.feabhas.com/2015/08/bitesize-modern-c-stdinitializer_list) (abgerufen am 03.12.2022)

und

[Brace initialization of user-defined types](https://blog.feabhas.com/2019/04/brace-initialization-of-user-defined-types) (abgerufen am 03.12.2022).

---

[Zurück](../../Readme.md)

---
