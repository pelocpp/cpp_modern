# Verschiedene Varianten mit `const`

[Zur�ck](../../Readme.md)

---

[Quellcode](Const.cpp)

---

## Allgemeines

Mit C++20 haben wir vier Schl�sselw�rter, die alle mit `const` beginnen:

<p>
<img src="cpp_const.svg" width="250">
</p>

*Abbildung* 1: Verschiedene Varianten mit `const`.


## `const` 

  * `const` deklariert ein Objekt als konstant. Das hei�t,
dass sich der Wert dieses Objekts nach der Initialisierung nicht mehr �ndert.
Der Compiler kann diese Tatsache f�r Optimierungen nutzen.

  * Es verhindert au�erdem, dass der Programmierer Code schreibt, der Objekte �ndert,
die nach der Initialisierung nicht mehr ge�ndert werden sollten.

  * `const` impliziert keine Auswertung zur &bdquo;�bersetzungszeit&rdquo;.
Der Compiler kann den Code optimieren und dies tun,
aber im Allgemeinen werden `const`-Objekte zur Laufzeit initialisiert:


## `constexpr` 


  * `constexpr` teilt dem Compiler mit, dass dieser Ausdruck zu einem berechenbaren konstanten Wert zur *�bersetzungszeit* f�hrt,
sodass er an Stellen wie Array-L�ngen und Zuweisungen zu konstanten Variablen etc. verwendet werden kann.

  * `constexpr` erlaubt es explizit zur �bersetzungszeit zu programmieren und dies in der vertrauten C++&ndash;Syntax.

  * Mit dem Schl�sselwort `constexpr` l�sst sich ein Ausdruck definieren,
der zur �bersetzungszeit evaluiert werden kann.

  * `constexpr` l�sst sich f�r Variablen, Funktionen, aber auch f�r benutzerdefinierte Typen (Klassen, Strukturen) verwenden.

  * Ein zur �bersetzungszeit evaluierter Ausdruck besitzt viele Vorteile.
So sind `constexpr` Variablen und auch Instanzen von benutzerdefinierten Typen automatisch thread-sicher
und k�nnen im ROM gespeichert werden.

  * `constexpr` Funktionen werden zur �bersetzungszeit ausgef�hrt,
so dass deren Ergebnisse direkt zur Laufzeit zur Verf�gung stehen


## `consteval` 

  * `consteval` kann nur auf Funktionen angewendet werden und erzwingt,
dass alle Aufrufe zur �bersetzungszeit erfolgen.


  * Mit `consteval` werden sogenannte *Immediate-Functions* erzeugt.
Jeder Aufruf einer solchen Funktion erzeugt eine �bersetzungszeit-Konstante.
Oder einfacher ausgedr�ckt:
Eine `consteval`&ndash;Funktion / *Immediate-Function* wird zur �bersetzungszeit ausgef�hrt.

  * *Immediate-Functions* k�nnen als Alternative zu Makros angesehen werden.

  * Man kann Variablen als `constexpr` deklarieren,
es gibt jedoch keine M�glichkeit zum Deklarieren von `consteval`-Variablen.


## `constinit` 

  * Das Schl�sselwort `constinit` garantiert,
dass eine Variable w�hrend der �bersetzungszeit initialisiert wird,
wodurch die Leistung verbessert wird,
da keine dynamische Initialisierung erforderlich ist.

  * `constinit` erzwingt die Initialisierung statischer oder threadlokaler Variablen
zur �bersetzungszeit mit einem konstanten Wert.

  * Mit `constinit` ist man in der Lage, das so genannte &bdquo;*Static Order Initialization Fiasco*&rdquo;
zu begrenzen,
indem vorkompilierte Werte in einer genau definierten Reihenfolge verwendet werden
im Gegensatz zu einer dynamischen Initialisierung, die vom Linker abh�ngig ist.

  * Im Gegensatz zu `const` oder `constexpr` bedeutet `constinit` nicht, dass das Objekt unver�nderlich ist.

  * Im Gegenteil: `constinit` kann nicht in konstanten Ausdr�cken verwendet werden!

---

[Zur�ck](../../Readme.md)

---
