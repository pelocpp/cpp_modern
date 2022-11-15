# Generische Lambdas

[Zurück](../../Readme.md)

---

[Quellcode](GenericLambdas.cpp)

---

## Generische Lambda Ausdrücke (*Generic Lambda Expressions*)

Ein Lambda-Ausdruck, der mindestens einen Parameter vom Typ `auto` hat,
wird als generischer Lambda-Ausdruck bezeichnet:

```cpp
auto lambda = [](auto x, int y) {
    std::cout << "x=" << x << ", y=" << y << std::endl;
};
```

Man beachte, dass der Lambda Ausdruck einen Parameter vom Typ `auto` hat.

Intern &ndash; also aus Sicht des Compilers &ndash; wird ein derartiger Lambda Ausdruck
auf ein &ldquo;aufrufbares Objekt&rdquo; (*Funktor*) abgebildet.
Der Aufruf-Operator `operator()` wird dabei im Sinne der Template Technik als so genannte
*Template Member Function* realisiert:

```cpp
struct Lambda
{
    template <typename T>
    void operator() (T x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
};
```

Besitzt ein Lambda Ausdruck mehrere `auto` Parameter, dann werden bei der Umsetzung
auf eine adäquate *Template Member Function* mehrere Template Parameter eingesetzt:

```cpp
auto lambdaTwice = [](auto x, auto y) {
    std::cout << "x=" << x << ", y=" << y << std::endl;
};

struct LambdaTwice
{
    template <typename T, typename U>
    void operator() (T x, U y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
};
```

---

## *Automatic Type Deduction* bei generischen Lambda Ausdrücken

Das Feature der *Automatic Type Deduction* wird bei Lambda-Ausdrücken angewendet,
und zwar sowohl beim Rückgabetyp als auch bei den Parametern der Lambda-Funktion.
Um *Automatic Type Deduction* für Parameter anwenden zu können,
müssen diese als `auto` deklariert werden:

```cpp
// define a generic lambda
auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

std::vector<int> intValues { 44, 65, 22, 77, 2 };

// use generic lambda with a vector of integers
auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFifty);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

// use exactly the *same* generic lambda with a vector of doubles
auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFifty);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

*Ausgabe*:

```
Found a value: 65
Found a value: 75
```

**Bemerkung**:
Zwischen Funktionstemplates und generischen Lambda Ausdrücken lassen sich wiederum Gemeinsamkeiten erkennen.
Das letzte Beispiel hätte man auch mit einem Funktionstemplate realisieren können:

```cpp
template <typename T>
bool isGreaterThanFiftyEx (const T& n) 
{
    return n > 50;
};
```

Damit sehen die Aufrufe von `std::find_if` so aus:

```cpp
std::vector<int> intValues{ 44, 65, 22, 77, 2 };

// use function template with a vector of integers
auto it1 = std::find_if(std::begin(intValues), std::end(intValues), isGreaterThanFiftyEx<int>);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.0, 75.0, 12.0, 87.0, 12.0 };

// use exactly the *same* function template with another specialization with a vector of doubles
auto it2 = std::find_if(std::begin(doubleValues), std::end(doubleValues), isGreaterThanFiftyEx<double>);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

---

## Lambda Ausdrücke mit `template`-Header


Lambda Ausdrücke mit `template`-Header, die in C++ 20 eingeführt wurden,
ermöglichen es, die Template Syntax zu verwenden, um explizit
auf die Gestaltung des Template-basierten Funktionsaufrufoperators `operator()`
Einfluss zu nehmen:

```cpp
auto l1 = [](int a) { return a + a; };             // C++ 11, regular lambda

auto l2 = [](auto a) { return a + a; };            // C++ 14, generic lambda

auto l3 = []<typename T>(T a) { return a + a; };   // C++ 20, template lambda
```


Hier haben wir drei verschiedene Lambda Ausdrücke:
`l1` ist ein regulärer Lambda Ausdruck, `l2` ist ein generischer Lambda Ausdruck,
da mindestens einer der Parameter vom Typ `auto` definiert ist 
und `l3` ist ein Lambda Ausdruck mit `template`-Header.

Wir können `l1` mit einer `int`-Zahl aufrufen; wir können es auch mit einem `double`-Wert aufrufen,
aber dieses Mal gibt der Compiler eine Warnung über einen möglichen Datenverlust aus.
Der Versuch, `l1` mit einem `std::string`-Argument aufzurufen,
erzeugt einen Kompilierungsfehler, da `std::string` nicht in einen `int`-Wert umgewandelt werden kann.

`l2` hingegen ist ein generischer Lambda Ausdruck. Der Compiler erzuegt in diesem Fall
Spezialisierungen für alle Arten von Argumenten, mit denen der Ausdruck aufgerufen wird,
in unserem Beispiel sind dies `int`, `double` und `std::string`. 

Es überrascht nicht, dass der Compiler für den dritten Lambda-Ausdruck `l3` denselben Code generiert.
Welchen Vorteil besitzen nun Lambda Ausdrücke mit `template`-Header?
Um diese Frage zu beantworten, modifizieren wir das vorherige Beispiel ein wenig:




---

[Zurück](../../Readme.md)

---
