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


```cpp
```

---
