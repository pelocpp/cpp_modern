# Verschiebe-Semantik / *Move Semantics*

[Zurück](../../Readme.md)

---

[Quellcode / Klasse `BigData`](MoveSemantics.cpp)

---

## Allgemeines

Die Erweiterung einer Klasse von der Kopier-Konstruktion (dies schließt den Kopier-Konstruktor und
den Wertzuweisungsoperator ein) hin zur Verschiebe-Konstruktion (dies wiederum 
schließt den Verschiebe-Konstruktor und
die Verschiebe-Wertzuweisung ein) kann dem dazugehörigen Quellcode entnommen werden.

Prinzipiell kann die Move-Semantik auf dreierlei Weisen realisiert werden:

  * *straight*-*forward*, also Realisierung ohne direktes Entwurfsmuster
  * mit zwei Hilfsmethoden `cleanup` und `moveFrom` - so genannte *Primitive* / minimalistisches Entwurfsmuster
  * auf Basis des *Swap*-Idioms

## Rule of Three (Four), Rule of Five (Six), Rule of Zero

*Allgemeines*:

  * Default constructor: `X()`
  * Copy constructor: `X(const X&)`
  * Copy assignment: `operator=(const X&)`
  * Move constructor: `X(X&&) noexcept`
  * Move assignment: `operator=(X&&) noexcept`
  * Destructor: `~X()`

*Rule of Three*:

  * Copy constructor: `X(const X&)`
  * Copy assignment: `operator=(const X&)`
  * Destructor: `~X()`

*Rule of Five*:

  * Copy constructor: `X(const X&)`
  * Copy assignment: `operator=(const X&)`
  * Move constructor: `X(X&&) noexcept`
  * Move assignment: `operator=(X&&) noexcept`
  * Destructor: `~X()`

*Rule of Zero*:

  * Es dürfen keine Zeiger vorhanden sein, die mit `new` allokiert wurden.
  * Verwenden Sie Container der STL.
  * Verwenden Sie *Smart Pointer*.

In diesen Fällen benötigt man keine Realisierung der *Rule of Three* oder *Rule of Five*,
da der Compiler an Hand der Standardklassen die für diese Klassen passenden Kopier- und Verschiebeoperationen
generiert. Deklarieren oder defineren Sie dann keine Operationen der *Rule of Three* oder *Rule of Five* für Ihre Klasse.

---

[Zurück](../../Readme.md)

---
