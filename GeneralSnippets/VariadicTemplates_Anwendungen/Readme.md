# Variadische Templates und ihre Anwendungsbeispiele

## Pack expansion: Types and Values

Umwandlung Parameter Pack in ein `std::tuple`

<https://arne-mertz.de/2016/11/modern-c-features-variadic-templates/>

```cpp
#include <iostream>
#include <memory>
#include <array>
#include <string>
#include <iostream>
#include <functional>
#include <tuple>

// =============================================================
// Pack expansion: Types and Values
// =============================================================

// =============================================================
// templates
//

template <class... Args>
auto f2(Args... args) {
    // expand template parameter pack Args first, 
    // then function parameter pack args
    return std::tuple<Args...> { args... };
}

// =============================================================
// samples

void h1() {

    auto tuple =  f2(123, 'A', 33.33, std::string("ABC"));
}

// =============================================================

int main()
{
    h1();
    return 0;
}

// =============================================================

```
---

## "Unpacking" a tuple to call a matching function pointer

Es wird demonstriert, wie ein Parameter Pack auf einen Methodenaufruf
(hier: Konstruktor) abgebildet werden kann.

Es kommt die zentrale `forwarding`-Anweisung zum Zuge:

```cpp
T(std::forward<Args>(args)...);
```

Siehe eine detailliertere Beschreibung unter *Arne Mertz*:

<https://arne-mertz.de/2016/11/modern-c-features-variadic-templates/>

und

<https://arne-mertz.de/2015/10/new-c-features-templated-rvalue-references-and-stdforward/>

```cpp
#include <iostream>
#include <memory>
#include <array>
#include <iostream>
#include <functional>

// =============================================================
// "Unpacking" a tuple to call a matching function pointer
// =============================================================

//// Test Class - only c'tors are interesting ..
//

class Unknown {
private:
    int m_var1;
    int m_var2;
    int m_var3;

public:
    Unknown() : m_var1(0), m_var2(0), m_var3(0) {
        std::cout << "c'tor()" << std::endl;
    }

    Unknown(int n) : m_var1(n), m_var2(0), m_var3(0) {
        std::cout << "c'tor(int)" << std::endl;
    }

    Unknown(int n, int m) : m_var1(n), m_var2(m), m_var3(0)  {
        std::cout << "c'tor(int, int)" << std::endl;
    }

    Unknown(int n, int m, int k) : m_var1(n), m_var2(m), m_var3(k) {
        std::cout << "c'tor(int, int, int)" << std::endl;
    }

    friend std::ostream& operator<< (std::ostream&, const Unknown&);
};

std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
    os << "var1: " << obj.m_var1 
       << ", var2: " << obj.m_var2 
       << ", var3: " << obj.m_var3 << std::endl;
    return os;
}

// =============================================================
// templates
//

template<typename T, typename... Args>
T make_me_an_object(Args&&... args)
{
    return T(std::forward<Args>(args)...);
}

// =============================================================
// samples

void h1() {
    Unknown u1 = make_me_an_object<Unknown>(1, 2, 3);
    std::cout << u1 << std::endl;

    const int k = 10;
    Unknown u2 = make_me_an_object<Unknown>(k, k+1, k+2);
    std::cout << u2 << std::endl;

    int par = 123;
    Unknown u3 = make_me_an_object<Unknown>(par, par + 1, par + 2);
    std::cout << u3 << std::endl;
}

// =============================================================

int main()
{
    h1();
    return 0;
}

// =============================================================

```

---

## Verwendung eines Parameter Packs bei Unique Pointern (allg.: Smart Pointern)


```cpp
// =============================================================
// Anwendungsfall bei std::unique_ptr
// =============================================================

#include <iostream>
#include <memory>
#include <array>
#include <iostream>
#include <functional>

// =============================================================
// templates

// Test Class - only c'tors are interesting ..

class Unknown {

public:
    Unknown() {
        std::cout << "c'tor()" << std::endl;
    }

    Unknown(int n) {
        std::cout << "c'tor(int)" << std::endl;
    }

    Unknown(int n, int m) {
        std::cout << "c'tor(int, int)" << std::endl;
    }

    Unknown(int n, int m, int k) {
        std::cout << "c'tor(int, int, int)" << std::endl;
    }
};

// =============================================================
// templates

template<typename T, typename... Args>
std::unique_ptr<T> my_make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// =============================================================
// samples

void h1() {

    std::unique_ptr<Unknown> f = my_make_unique<Unknown>(1, 2, 3);
}

// =============================================================

int main()
{
    h1();
    return 0;
}

// =============================================================

```

---

## Eine Instanz der Klasse `std::array` dynamisch anlegen

Bei diesem Beispiel ist die Vorbelegung eines Objekts vom Typ `std::array`
interessant. Das Array selbst kann der Einfachheit nur `int`-Elemente
aufnehmen, diese können dafür in einer beliebig langen Liste übertragen
werden:

Der Original-Quellcode des Beispiels (hier mit beliebigen Elementtypen)
befindet sich unter

<https://en.cppreference.com/w/cpp/language/sizeof...>

```cpp
// =============================================================
// Eine Instanz der Klasse std::array dynamisch anlegen
// =============================================================

#include <iostream>
#include <memory>
#include <array>
#include <iostream>
#include <functional>

// =============================================================
// templates
//

template<typename... Ts>
auto my_make_array(Ts&&... ts) -> std::array<int, sizeof...(Ts)> 
{
    return { std::forward<Ts>(ts)... };
}

// =============================================================
// samples

void h1() {
    auto b = my_make_array(1, 2, 3);
    std::cout << b.size() << '\n';
    for (auto i : b)
        std::cout << i << ' ';
}


// =============================================================

int main()
{
    h1();

    return 0;
}

// =============================================================

```

---

## Beliebige Schachtelung von Methodenaufrufen

In funktionalen Programmiersprachen werden Funktionen verkettet oder
auch geschachtelt aufgerufen:

In Haskell werden mit der Anweisung (schematisch dargestellt)

```haskell
unique_words = length.sort.sort.words.toLower
```

die Anzahl der unterschiedlichen Wörter in einem Text bestimmen:

```haskell
unique_words A B c d a b c d e
```

It first maps all the characters from the input to lowercase with map toLower.
This way, words like FOO and foo can be regarded as the same word.Then, the words function
splits a sentence into individual words, as from "foo bar baz" to ["foo", "bar",
"baz"]. Next step is sorting the new list of words. This way, a word sequence such as
["a", "b", "a"] becomes ["a", "a", "b"]. Now, the group function takes over. It
groups consecutive equal words into grouped lists, so ["a", "a", "b"] becomes [
["a", "a"], ["b"] ]. The job is now nearly done, as we now only need to count how
many groups of equal words we got, which is exactly what the length function does.

Im folgenden Stellen wir eine Schablone vor, die zwar nicht das zuvor 
diskutierte Problem löst, aber die Verkettung (Schachtelung)
einer beliebigen Anzahl von Methoden demonstriert:



```cpp
#include <iostream>
#include <memory>
#include <iostream>
#include <functional>

// =============================================================
// templates

template <typename F>
auto concat1(F f)
{
    return [=](auto ... params) {

        std::cout << "sizeof... " << sizeof...(params) << "." << std::endl;
        return f(params...);
    };
}

template <typename F, typename G>
auto concat2(F f, G g)
{
    return [=](auto ... params) {
        return f(g(params...));
    };
}

template <typename F, typename G, typename H>
auto concat3(F f, G g, H h)
{
    return [=](auto ... params) {
        return f(g(h(params...)));
    };
}

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto ...parameters) {
            return t(concat(ts...)(parameters...));
        };
    }
    else {
        return [=](auto ...parameters) {
            return t(parameters...);
        };
    }
}

// =============================================================
// functions (lambdas)

auto times = [](int i, int j) { return i * j; };

auto ntimes = [](int i, int j, int k) { return i * j * k; };

auto twice = [](int i) {
    std::cout << "twice(" << i << ")" << std::endl;
    return i * 2;
};

auto thrice = [](int i) {
    std::cout << "thrice(" << i << ")" << std::endl;
    return i * 3;
};

auto fource = [](int i) {
    std::cout << "fource(" << i << ")" << std::endl;
    return i * 4;
};

// =============================================================
// samples

void h0() {
    auto l1 = concat1(twice);
    int result = l1(123);
    std::cout << result << std::endl;
}

void h1() {
    auto l1 = concat1(times);
    int result = l1(8, 9);
    std::cout << result << std::endl;
}

void h2() {
    auto l1 = concat1(ntimes);
    int result = l1(8, 9, 10);
    std::cout << result << std::endl;
}

void h3() {
    auto l2 = concat2(twice, thrice);
    int result = l2(123);
    std::cout << result << std::endl;
}

void h4() {
    auto l2 = concat2(twice, times);
    int result = l2(12, 13);
    std::cout << result << std::endl;
}

void h5() {
    auto l2 = concat2(twice, ntimes);
    int result = l2(12, 13, 14);
    std::cout << result << std::endl;
}

void h6() {
    auto l2 = concat3(twice, thrice, ntimes);
    int result = l2(12, 13, 14);
    std::cout << result << std::endl;
}

void h10() {
    auto l2 = concat(twice, thrice, fource, ntimes);
    int result = l2(12, 13, 14);
    std::cout << result << std::endl;
}

// =============================================================

int main()
{
    h1();
    h2();
    h3();
    h4();
    h5();
    h6();
    h10();
    return 0;
}

// =============================================================

```

---

## Standard-Klasse std::visit und eine Funktion make_visitor

Siehe <https://pabloariasal.github.io/2018/06/26/std-variant/>

Neben der Beschreibung gibt es eine weitere C++-Definition zu beachten:

### *Why doesn't overloading work for derived classes*

Oder an folgendem Beispiel betrachtet:

```cpp
 using namespace std;
    class B {
    public:
        int f(int i) { cout << "f(int): "; return i+1; }
        // ...
    };
    class D : public B {
    public:
        double f(double d) { cout << "f(double): "; return d+1.3; }
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


```cpp
// =====================================================================================
// Variadic Templates - Overload Pattern
// =====================================================================================

#include<iostream>
#include <variant>
#include <string>

namespace VariadicTemplatesOverloadPattern {

    // https://pabloariasal.github.io/2018/06/26/std-variant/
    // or
    // https://www.bfilipek.com/2018/09/visit-variants.html

    template <class... Ts>
    struct Visitor;

    template <class T, class... Ts>
    struct Visitor<T, Ts...> : T, Visitor<Ts...>
    {
        Visitor(T t, Ts... rest) : T(t), Visitor<Ts...>(rest...) {}

        using T::operator();
        using Visitor<Ts...>::operator();
    };

    template <class T>
    struct Visitor<T> : T
    {
        Visitor(T t) : T(t) {}

        using T::operator();
    };

    template<typename ...Ts>
    auto make_visitor(Ts... lamdbas)
    {
        return Visitor<Ts...>(lamdbas...);
    }

    auto myVisitor = make_visitor(
        [](int n)
        {
            // called if variant holds an int
            std::cout << "Variant holds an int right now: " << n << std::endl;
        },
        [](float f)
        {
            // called if variant holds a float
            std::cout << "Variant holds a float right now: " << f << std::endl;
        },
        [](char ch)
        {
            // called if variant holds a char
            std::cout << "Variant holds a char right now: " << ch << std::endl;
        }
    );

    void test_01() {

        std::variant<int, float, char> var = 42;
        std::visit(myVisitor, var);
        var = 3.141f;
        std::visit(myVisitor, var);
        var = 'c';
        std::visit(myVisitor, var);
    }
}

int main()
// int main_overload_pattern()
{
    using namespace VariadicTemplatesOverloadPattern;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
```

---
