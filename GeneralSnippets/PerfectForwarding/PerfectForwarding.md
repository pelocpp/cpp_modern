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

Man beachte, dass es bei genauerer Betrachtung hier die sogenannte Tabelle der *collapsing rules* 
(zu deutsch etwa: *Zusammenfassungsregeln*) gibt:

| Formaler Typ | Beschreibung | Resultattyp | Beschreibung|
|:------ |:----------|:----------|:----------|
| T& &   | LValue-Referenz auf eine LValue-Referenz | T&  | LValue-Referenz |
| T&& &  | LValue-Referenz auf eine RValue-Referenz | T&  | LValue-Referenz |
| T& &&  | RValue-Referenz auf eine LValue-Referenz | T&  | LValue-Referenz |
| T&& && | RValue-Referenz auf eine RValue-Referenz | T&& | RValue-Referenz |

Tabelle 1. *Zusammenfassungsregeln*/*Collapsing Rules* für das *Perfect Forwarding*.

Von *Scott Meyers* in Worte gefasst lauten diese Regeln, wenn gleich auch nicht einfach verständlich formuliert:

"[given] a type TR that is a reference to a type T, an attempt to create the type “lvalue reference to cv TR”
creates the type “lvalue reference to T”,
while an attempt to create the type “rvalue reference to cv TR” creates the type TR."

Ein zweiter Versuch von *Scott Meyers* bietet eine möglicherweise leichter verständlichere Darstellung
des Sachverhalts an:

![](ScottMeyers_Forward.png)

Abbildung 1. `std::forward`.

---

[Zurück](../../Readme.md)

---

