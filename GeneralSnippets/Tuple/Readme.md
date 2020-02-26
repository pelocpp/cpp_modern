# std::tuple

Eine Beispiel-Implementierung für die Klasse `std::tuple`
findet sich unter <https://eli.thegreenplace.net/2014/variadic-templates-in-c/>.

Das nachfolgende Code-Snippet ist übersetzungsfähig:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <optional>

template <class... Ts>
struct MyTuple {};

template <class T, class... Ts>
struct MyTuple<T, Ts...> : MyTuple<Ts...> {
    MyTuple(T t, Ts... ts) : MyTuple<Ts...>(ts...), tail(t) {}

    T tail;
};

int main()
{
    MyTuple<double, uint64_t, const char*> t1(12.2, 42, "big");

    //  MyTuple<double, uint64_t, const char*> : MyTuple<uint64_t, const char*> {
    //      double tail;
    //  }

    //  MyTuple<uint64_t, const char*> : MyTuple<const char*> {
    //      uint64_t tail;
    //  }

    //  MyTuple<const char*> : MyTuple {
    //      const char* tail;
    //  }

    //  MyTuple {
    //  }

    return 1;
}
```
