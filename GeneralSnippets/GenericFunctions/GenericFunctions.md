# Generische Funktionen (inkl. Lambdas)

[Zurück](../../Readme.md)

---

[Quellcode](GenericLambdas.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [*Automatic Type Deduction* bei generischen Lambda Ausdrücken](#link2)
  * [Lambda Ausdrücke mit `template`-Header](#link3)
  * [*Perfect Forwarding* mit generischen Lambdas](#link4)
  * [Rekursive Lambda Ausdrücke](#link5)
  * [Literaturhinweise](#link6)
    
---

## Einleitung <a name="link1"></a>

Eine Funktion, die mindestens einen Parameter vom Typ `auto` hat,
wird als *generische Funktion* bezeichnet:

```cpp
auto function(auto x, int y) {
    std::cout << "x=" << x << ", y=" << y << std::endl;
};
```

Ebenso:

Ein Lambda-Ausdruck, der mindestens einen Parameter vom Typ `auto` hat,
wird als generischer Lambda-Ausdruck bezeichnet:

```cpp
auto lambda = [](auto x, int y) {
    std::cout << "x=" << x << ", y=" << y << std::endl;
};
```

Man beachte, dass der Lambda Ausdruck einen Parameter vom Typ `auto` hat.

Intern &ndash; also aus Sicht des Compilers &ndash; wird ein derartige Funktion bzw. ein derartiger Lambda Ausdruck
auf ein &bdquo;aufrufbares Objekt&rdquo; abgebildet.
Der Aufruf-Operator `operator()` wird dabei im Sinne der Template Technik als so genannte
*Template Member Function* realisiert:

```cpp
struct Lambda
{
    template <typename T>
    auto operator() (T x, int y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
};
```

Besitzt eine Funktion bzw. ein Lambda Ausdruck mehrere `auto` Parameter, dann werden bei der Umsetzung
auf eine adäquate *Template Member Function* mehrere Template Parameter eingesetzt:

```cpp
auto functionTwice(auto x, auto y) {
    std::cout << "x=" << x << ", y=" << y << std::endl;
};

struct FuncionTwice
{
    template <typename T, typename U>
    auto operator() (T x, U y) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
};
```

---

## *Automatic Type Deduction* bei generischen Lambda Ausdrücken <a name="link2"></a>

Das Feature der *Automatic Type Deduction* wird auch bei Lambda-Ausdrücken angewendet,
und zwar sowohl beim Rückgabetyp als auch bei den Parametern der Lambda-Funktion.
Um *Automatic Type Deduction* für Parameter anwenden zu können,
müssen diese als `auto` deklariert werden:

```cpp
// define a generic lambda
auto isGreaterThanFifty = [](const auto& n) { return n > 50; };

std::vector<int> intValues{ 44, 65, 22, 77, 2 };

// use generic lambda with a vector of integers
auto it1 = std::find_if(
    std::begin(intValues),
    std::end(intValues),
    isGreaterThanFifty
);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

// use exactly the *same* generic lambda with a vector of doubles
auto it2 = std::find_if(
    std::begin(doubleValues),
    std::end(doubleValues),
    isGreaterThanFifty
);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

*Ausgabe*:

```
Found a value: 65
Found a value: 75.5
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

// use template function with a vector of integers
auto it1 = std::find_if(
    std::begin(intValues),
    std::end(intValues),
    isGreaterThanFiftyEx<int>
);
if (it1 != std::end(intValues)) {
    std::cout << "Found a value: " << *it1 << std::endl;
}

std::vector<double> doubleValues{ 24.5, 75.5, 12.5, 87.5, 12.5 };

// use exactly the *same* template function with
// another specialization with a vector of doubles
auto it2 = std::find_if(
    std::begin(doubleValues),
    std::end(doubleValues),
    isGreaterThanFiftyEx<double>
);
if (it2 != std::end(doubleValues)) {
    std::cout << "Found a value: " << *it2 << std::endl;
}
```

---

## Lambda Ausdrücke mit `template`-Header <a name="link3"></a>

Lambda Ausdrücke mit `template`-Header Syntax, die in C++ 20 eingeführt wurde,
ermöglichen es, explizit auf die Gestaltung des Template-basierten Funktionsaufrufoperators `operator()`
Einfluss zu nehmen:

```cpp
auto l1 = [](int a) { return a + a; };             // C++ 11, regular lambda

auto l2 = [](auto a) { return a + a; };            // C++ 14, generic lambda

auto l3 = []<typename T>(T a) { return a + a; };   // C++ 20, template lambda
```

Hier haben wir drei verschiedene Lambda Ausdrücke:
`l1` ist ein regulärer Lambda Ausdruck, `l2` ein generischer Lambda Ausdruck,
da mindestens einer der Parameter vom Typ `auto` definiert ist 
und `l3` ein Lambda Ausdruck mit `template`-Header.

Wir können `l1` mit einer `int`-Zahl aufrufen. Wenn wir einen `double`-Wert übergeben,
gibt der Compiler eine Warnung über einen möglichen Datenverlust aus.
Der Versuch, `l1` mit einem `std::string`-Argument aufzurufen,
erzeugt einen Übersetzungsfehler,
da `std::string` nicht in einen `int`-Wert umgewandelt werden kann.

`l2` hingegen ist ein generischer Lambda Ausdruck. Der Compiler erzeugt in diesem Fall
Spezialisierungen für alle Arten von Argumenten, mit denen der Ausdruck aufgerufen wird.
In unserem Beispiel sind dies `int`, `double` und `std::string`:

```cpp
auto v1 = l1(42);                       // Ok
auto v2 = l1(42.0);                     // Warning
auto v3 = l1(std::string{ "42" });      // Error

auto v5 = l2(42);                       // Ok
auto v6 = l2(42.0);                     // Ok
auto v7 = l2(std::string{ "42" });      // Ok
        
auto v8 = l3(42);                       // Ok
auto v9 = l3(42.0);                     // Ok
auto v10 = l3(std::string{ "42" });     // Ok
```

Es überrascht nicht, dass der Compiler für den dritten Lambda-Ausdruck `l3`
denselben Code generiert.
Welchen Vorteil besitzen nun Lambda Ausdrücke mit `template`-Header?
Um diese Frage zu beantworten, modifizieren wir das vorherige Beispiel ein wenig:

```cpp
auto l1 = [](int a, int b) { return a + b; };          // C++ 11, regular lambda

auto l2 = [](auto a, auto b) { return a + b; };        // C++ 14, generic lambda

auto l3 = []<typename T, typename U>(T a, U b) {       // C++ 20, template lambda
    return a + b; 
};
```

Die neuen Lambda-Ausdrücke besitzen zwei Parameter.
Auch hier können wir `l1` mit zwei ganzen Zahlen aufrufen
oder einem `int`- und einem `double`-Wert, obwohl dies wiederum eine Warnung erzeugt.
Mit einem `std::string`-Objekt und einem `char`-Wert lässt sich `l1` nicht aufrufen.
Mit `l2` und `l3` ist dies möglich, der vom Compiler generierte Code
ist für `l2` und `l3` identisch:

```cpp
auto v1 = l1(42, 1);                                       // Ok
auto v2 = l1(42.0, 1.0);                                   // Warning
auto v3 = l1(std::string{ "42" }, '1');                    // Error

auto v4 = l2(42, 1);                                       // Ok
auto v5 = l2(42.0, 1);                                     // Ok
auto v6 = l2(std::string{ "42" }, '1');                    // Ok
auto v7 = l2(std::string{ "42" }, std::string{ "1" });     // Ok

auto v8 = l3(42, 1);                                       // Ok
auto v9 = l3(42.0, 1);                                     // Ok
auto v10 = l3(std::string{ "42" }, '1');                   // Ok
auto v11 = l3(std::string{ "42" }, std::string{ "42" });   // Ok
```

Wie gehen wir vor, wenn wir die Verwendung des generischen Lambda Ausdrucks einschränken wollen?
Zum Beispiel in Bezug auf Argumente desselben Typs?
Das ist mit `l1` und `l2` nicht möglich.

Für Lambda Ausdrücke mit `template`-Header gibt es einen Weg:

```cpp
auto l5 = []<typename T>(T a, T b) { return a + b; };
```

Jegliche Aufrufe des Lambda Ausdrucks mit zwei Argumenten unterschiedlichen Typs sind nicht möglich. 
Auch für den Fall, dass die Argumente implizit konvertierbar sind,
wie z.B. von `int` nach `double`. Der Compiler erzeugt auch in diesen Fällen einen Fehler.

*Hinweis*:
Mit C++ 14 und `decltype` kann man einen alternativen Lösungsansatz betrachten:

```cpp
auto l6 = [](auto a, decltype(a) b) { return a + b; };
```

Diese Realisierung impliziert jedoch, dass der Typ des zweiten Parameters `b`
in den Typ des ersten Parameters `a` konvertierbar sein muss.

Der erste Aufruf ist problemlos übersetzbar, da `int` implizit in `double` konvertierbar ist.
Der zweite Aufruf wird mit einer Warnung übersetzt, da die Konvertierung von `double`
nach `int` zu einem Datenverlust führen kann.
Der dritte Aufruf generiert einen Fehler, da `char` kann nicht in `std::string` konvertierbar ist.

```cpp
auto v1 = l6(42.0, 1);                        // Ok
auto v2 = l6(42, 1.0);                        // Warning
auto v3 = l6(std::string{ "42" }, '1');       // Error
```

Möchte man einen Aufruf der gezeigten Lambda Ausdrücke für Argumente unterschiedlichen Typs ausschließen,
ist dies nur mit dem gezeigten Lösungswegs eines Lambda Ausdrucks mit `template`-Header möglich.

---

## *Perfect Forwarding* mit generischen Lambdas <a name="link4"></a>

Das Prinzip des &bdquo;perfekteb Weiterleitens&rdquo; gibt es auch für generische Lambdas.
Definiert man einen Parameter eines generischen Lambdas vom Typ `auto&&`, also als so genannte *Universal Reference*,
so lassen sich die Argumente beim Aufruf &bdquo;perfekt&rdquo; Weiterleiten:

```cpp
void foo(const std::string& s) {
    std::cout << "Signature: const&" << std::endl;
}

void foo(std::string&& s) {
    std::cout << "Signature: &&" << std::endl;
}

auto callingFoo = [](auto&& s) {
    std::cout << "Calling foo(): " << s;
    foo(std::forward<decltype(s)>(s));
};
```

Wir rufen die Lambda-Funktion `callingFoo` mit zwei unterschiedlichen Argumenten auf.
Studieren Sie die Ausgabe sorgfältig:

```cpp
const std::string str{ "Hello World with LValue - " };
callingFoo(str);
callingFoo("Hello World with RValue - ");
```

*Ausgabe*:

```
Calling foo(): Hello World with LValue - Signature: const&
Calling foo(): Hello World with RValue - Signature: &&
```

---

## Rekursive Lambda Ausdrücke <a name="link5"></a>


Generische Lambda Ausdrücke eröffnen auch die Möglichkeit, rekursive Lambda-Funktionen zu realisieren,
ohne dabei auf `std::function` zurückgreifen zu müssen.

##### Vorgehensweise ohne generische Lambda Ausdrücke

Lambda Ausdrücke haben keine Namen, sie sind anonym.
Daher lassen sie sich nicht direkt rekursiv aufrufen.

Stattdessen muss man ein `std::function`-Objekt definieren,
ihm als Wert den Lambda-Ausdruck zuweisen und dieses Objekt zusätzlich noch
als Referenz in der *Capture Clause* erfassen:

```cpp
std::function<int(int)> factorial;

factorial = [&] (int n) {
    if (n < 2) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
};

std::cout << factorial(5) << std::endl; // 120
```

##### Vorgehensweise mit generischen Lambda Ausdrücken

Durch die Verwendung von generischen Lambdas kann die gezeigte Funktion `factorial` vereinfacht werden.
Man benötigt kein `std::function`-Objekt und keine Erfassung in der *Capture Clause*.
Ein rekursives generisches Lambda kann folgendermaßen definiert werden:

```cpp
auto factorial = [] (auto f, int const n) {

    if (n < 2) {
        return 1;
    }
    else {
        return n * f(f, n - 1);
    }
};

std::cout << factorial (factorial, 5) << std::endl;
```

Die obige generische Lambda-Version von `factorial` ist
vom Standpunkt der Lesbarkeit aus betrachtet nicht besser.
Sie kann jedoch auf unterschiedliche Basistypen angewendet werden,
siehe dazu das Beispiel von `power` im begleitenden Quelltext:

```cpp
std::cout << power(power, 2, 10) << std::endl;    // 2^10 = 1024

std::cout << power(power, 2.71828, 10);           // e^10 = 22026.3
```

---

## Literaturhinweise <a name="link6"></a>

Die Anregungen zu rekursiven Lambda Ausdrücken stammen aus
[Generic code with generic lambda expression](https://www.nextptr.com/tutorial/ta1224017367/generic-code-with-generic-lambda-expression).

---

[Zurück](../../Readme.md)

---
