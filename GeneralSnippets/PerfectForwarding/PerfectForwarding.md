# PerfectForwarding

[Quellcode 1](PerfectForwarding01.cpp): Elementarer Datentyp (`int`)

[Quellcode 2](PerfectForwarding02.cpp): Benutzerdefinierter Datentyp (`class`)

---

Ein einfaches Beispiel findet sich unter

https://isocpp.org/blog/2018/02/quick-q-whats-the-difference-between-stdmove-and-stdforward

## What’s the difference between `std::move` and `std::forward`?

Eine Antwort in SO (*Stackoverflow*) lautet:

`std::move` takes an object and allows you to treat it as a temporary (an *rvalue*). Although it isn’t a semantic requirement,
typically a function accepting a reference to an *rvalue* will invalidate it.
When you see `std::move`, it indicates that the value of the object should not be used afterwards.

`std::forward` has a single use case: to cast a templated function parameter (inside the function)
to the value category (*lvalue* or *rvalue*) the caller used to pass it.
This allows *rvalue* arguments to be passed on as *rvalues*, and *lvalues* to be passed on as *lvalues*,
a scheme called “perfect forwarding.”

Zu deutsch etwa:

`std :: move` nimmt ein Objekt und ermöglicht es, diese als Temporärobjekt (als *rvalue*) zu behandeln.
Obwohl dies keine semantische Anforderung ist, macht in der Regel eine Funktion,
die einen Verweis auf einen *rvalue* akzeptiert, diesen ungültig.
Wenn Sie `std::move` sehen, bedeutet dies, dass der Wert des Objekts danach nicht mehr verwendet werden sollte.

`std :: forward` hat einen einzigen Anwendungsfall: 
einen Parameter einer Templatefunktion (innerhalb der Funktion) in die *Value* Kategorie
(*lvalue* oder *rvalue*) umzuwandeln, mit der der Aufrufer sie übergeben hat.
Auf diese Weise können *rvalue*-Argumente als *rvalues* und *lvalue*-Argumente als *lvalues* weitergegeben werden,
ein Schema, das als “perfekte Weiterleitung” (“perfect forwarding”) bezeichnet wird.


## Reference Collapsing Rules

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


## Literaturhinweise:

Eine sehr gute Beschreibung zu diesem Thema befindet sich unter

[Arne Mertz Blog](https://arne-mertz.de/2015/10/new-c-features-templated-rvalue-references-and-stdforward//)<br>(abgerufen am 31.05.2020).

---

[Zurück](../../Readme.md)

---
