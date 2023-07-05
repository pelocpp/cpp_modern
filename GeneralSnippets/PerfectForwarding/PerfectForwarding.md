# Perfect Forwarding

[Zurück](../../Readme.md)

---

[Quellcode](PerfectForwarding.cpp)

---

## Zusammenfassung

Voraussetzung für das &ldquo;Perfect Forwarding&rdquo; ist das Vorhandensein eines
Funktionstemplates, das im Rumpf weitere unterlagerte Funktionen aufruft:

 > Werden die Argumente des Funktionstemplate &ldquo;identisch&ldquo;
   &ndash;
   darunter verstehen wir in diesem Kontext: die *LValue*- oder *RValue*-Eigenschaft bleibt erhalten 
   &ndash;
   weitergereicht, so sprechen wir von  &ldquo;Perfect Forwarding&rdquo;.

Zu den Begriffen *LValue* oder *RValue* siehe auch
[RValue Referenzen / LValue Referenzen](../RValueLValue/RValueLValue.md).

---

*Scott Meyers* bietet eine möglicherweise leichter verständlichere Darstellung
des Sachverhalts an:

<img src="ScottMeyers_Forward.png" width="600">

*Abbildung* 1: `std::forward`.

---

## Literaturhinweise:

Gute Beschreibungen zu diesem Thema befinden sich in

> Peter Pohmann, "C++ 17: Praxiswissen zum neuen Standard. Von C++11 bis 17" (siehe das [Literaturverzeichnis](../Literatur/Literature.md)).

oder
 
[Arne Mertz Blog](https://arne-mertz.de/2015/10/new-c-features-templated-rvalue-references-and-stdforward//)<br>(abgerufen am 31.05.2020).

oder

[Eli Bendersky's website: Perfect forwarding and universal references in C++](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c//)<br>(abgerufen am 15.01.2021).

oder auch

[C++11: Perfect forwarding](https://oopscenities.net/2014/02/01/c11-perfect-forwarding//)<br>(abgerufen am 14.03.2021).

---

[Zurück](../../Readme.md)

---
