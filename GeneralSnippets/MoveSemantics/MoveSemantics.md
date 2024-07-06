# Verschiebe-Semantik / *Move Semantics*

[Zurück](../../Readme.md)

---

[Quellcode](MoveSemantics.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Realisierung](#link2)
  * [Notwendigkeit des Schlüsselworts `noexcept`](#link3)
  * [Rule of Three (Four), Rule of Five (Six), Rule of Zero](#link4)

---

## Allgemeines <a name="link1"></a>

Die Erweiterung einer Klasse von der Kopier-Konstruktion (dies schließt den Kopier-Konstruktor und
den Wertzuweisungsoperator ein) hin zur Verschiebe-Konstruktion (dies wiederum 
schließt den Verschiebe-Konstruktor und
die Verschiebe-Wertzuweisung ein) kann dem dazugehörigen Quellcode entnommen werden.

*Ausschnitt*:

```cpp
01: BigData::BigData(BigData&& data) noexcept {  // move c'tor
02: 
03:     m_data = data.m_data;   // shallow copy
04:     m_size = data.m_size;
05:     data.m_data = nullptr;  // reset source object, ownership has been moved
06:     data.m_size = 0;
07: }
```

Man beachte, dass das Objekt `data` &ndash; also das durch eine Referenz / einen Aliasnamen
an den verschiebenden Konstruktor übergebene Objekt &ndash; sich *nach* nach dem Methodenaufruf
in dem so genannten &bdquo;*Moved-From*&rdquo;-Zustand befindet:

An einem Objekt im &bdquo;*Moved-From*&rdquo;-Zustand lassen sich nur 2 Vorgänge durchführen:

  * Man kann es zerstören
  * Man kann es neu zuweisen

---

## Realisierung <a name="link2"></a>

Prinzipiell kann die Move-Semantik auf dreierlei Weisen realisiert werden:

  * *Straightforward*, also Realisierung ohne direktes Entwurfsmuster,
  * mit zwei Hilfsmethoden `cleanup` und `moveFrom` - so genannte *Primitive* / minimalistisches Entwurfsmuster oder
  * auf Basis des [*Copy-Swap*-Idioms](../../GeneralSnippets/CopySwapIdiom/CopySwapIdiom.md).

---

## Notwendigkeit des Schlüsselworts `noexcept` <a name="link3"></a>


Man beachte die Notwendigkeit des Schlüsselworts `noexcept` bei der Definition
des Move-Konstruktors.

Das folgende Beispiel führt zu unterschiedlichen Ausführungen in Abhängigkeit vom 
Vorhandensein des `noexcept`-Schlüsselworts:

```cpp
01: void test() {
02: 
03:     std::vector<BigData> vec;
04:     vec.push_back(BigData(10, 1));
05:     vec.push_back(BigData(20, 2));
06: }
```

*Ausgabe*:

```
move c'tor
move c'tor
move c'tor
```

oder


```
move c'tor
move c'tor
copy c'tor
```

Fehlt das `noexcept`-Schlüsselwort, verwendet das STL-Containerobjekt vom Typ `std::vector`
den Kopierkonstruktor, wenn intern der Datenpuffer neu auszurichten ist!

---

## Rule of Three (Four), Rule of Five (Six), Rule of Zero <a name="link4"></a>

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
