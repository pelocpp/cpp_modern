# PerfectForwarding

Ein einfaches Beispiel findet sich unter

https://isocpp.org/blog/2018/02/quick-q-whats-the-difference-between-stdmove-and-stdforward

## What’s the difference between std::move and std::forward?

Eine Antwort in SO (*Stackoverflow*) lautet:

`std::move` takes an object and allows you to treat it as a temporary (an rvalue). Although it isn’t a semantic requirement,
typically a function accepting a reference to an rvalue will invalidate it.
When you see `std::move`, it indicates that the value of the object should not be used afterwards,
but you can still assign a new value and continue using it.

`std::forward` has a single use case: to cast a templated function parameter (inside the function)
to the value category (lvalue or rvalue) the caller used to pass it.
This allows rvalue arguments to be passed on as rvalues, and lvalues to be passed on as lvalues, a scheme called “perfect forwarding.”

*Ausgabe des Code-Snippets*:

```cpp
initial caller passes rvalue:
via std::forward: by rvalue
via std::move: by rvalue
by simple passing: by lvalue
initial caller passes lvalue:
via std::forward: by lvalue
via std::move: by rvalue
by simple passing: by lvalue
```
