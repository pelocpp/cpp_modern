# Variadische Templates und ihre Anwendungsbeispiele

[Zurück](../../Readme.md)

---

## Template Parameter Pack Expansion: Typen und Werte

Umwandlung eines *parameter packs* in ein `std::tuple`

```cpp
// =============================================================
// Variadic Templates
// Template parameter pack args vs Function parameter pack args
// =============================================================

#include <iostream>
#include <string>
#include <tuple>

// Es wird demonstriert, wie ein variadisches Funktionstemplate
// (hier: my_make_tuple) auf die Erzeugung eines std::tuple abgebildet
// werden kann.

template <class... Args>
auto my_make_tuple(Args... args) {
    // expand template parameter pack Args first, 
    // then function parameter pack args
    return std::tuple<Args...> { args... };
}

// =============================================================

int main()
{
    auto tuple = my_make_tuple(123, 'A', 33.33, std::string("ABC"));

    // same as

    std::tuple<int, char, double, std::string> tuple2 = 
        my_make_tuple(123, 'A', 33.33, std::string("ABC"));

    return -1;
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
#include <array>

// =============================================================
// templates
//

template<typename... Ts>
auto my_make_array(Ts&&... ts) -> std::array<int, sizeof...(Ts)>  
{
    return { std::forward<Ts>(ts)... };
}

// =============================================================

int main()
{
    auto a = my_make_array(1, 2, 3);
    std::cout << "Array Size: " << a.size() << std::endl;
    for (auto i : a)
        std::cout << i << ' ';
    std::cout << std::endl;

    auto b = my_make_array();
    std::cout << "Array Size: " << b.size() << std::endl;

    std::array<int, 1> c = my_make_array(999);
    std::cout << "Array Size: " << c.size() << std::endl;
    for (auto i : c)
        std::cout << i << ' ';

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


[Zurück](../../Readme.md)

---
