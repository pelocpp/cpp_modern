# Why is "using namespace std;" considered bad practice?

[Zurück](../../Readme.md)

---

Siehe

https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice

Der wichtige Ausschnitt:

This is not related to performance at all. But consider this: you are using two libraries called `Foo` and `Bar`:

```cpp
using namespace foo;
using namespace bar;
```

Everything works fine, and you can call `Blah()` from `Foo` and `Quux()` from Bar without problems. But one day you upgrade to a new version of **Foo 2.0**,
which now offers a function called `Quux()`. Now you've got a conflict: Both Foo 2.0 and Bar import `Quux()` into your global namespace.
This is going to take some effort to fix, especially if the function parameters happen to match.

If you had used `foo::Blah()` and `bar::Quux()`, then the introduction of `foo::Quux()` would have been a non-event.

---

[Zurück](../../Readme.md)

---

