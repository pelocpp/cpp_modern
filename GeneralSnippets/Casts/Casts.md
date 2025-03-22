# Typumwandlungen

[Zur�ck](../../Readme.md)

---

[Quellcode](Casts.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [Implizite Konvertierungen](#link2)
  * [Explizite C-Style Konvertierungen](#link3)
  * [Explizite C++ Konvertierungen](#link4)

---

## Einleitung <a name="link1"></a>

<img src="cpp_casts.svg" width="500">

*Abbildung* 1: �berblick �bert die unterschiedlichen Typkonvertierungsm�glichkeiten in C/C++

---

WEITER:

https://web.archive.org/web/20160316114647/http://pvtuts.com/cpp/cpp-type-conversions

https://stackoverflow.com/questions/1609163/what-is-the-difference-between-static-cast-and-c-style-casting#:~:text=In%20short%3A,much%20better%20using%20C%2B%2B%20casts.


https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/

https://stackoverflow.com/questions/103512/why-use-static-casttx-instead-of-tx


---

ALTES ZEUGS

Es wird an mehreren Beispielen die Funktionsweise folgender C++-Typumwandlungen gezeigt:

  * `static_cast`
  * `dynamic_cast`
  * `const_cast`
  * `reinterpret_cast`

Der `static_cast`-Operator ist dazu gedacht, implizit erlaubte Typumwandlungen durchzuf�hren,
die zur �bersetzungszeit stattfinden.

Interessanter ist der `dynamic_cast`-Operator. Er wird zur Laufzeit ausgef�hrt
(von trivialen �berpr�fungen zur �bersetzungszeit einmal abgesehen).

Seine St�rke sind *downcast*-Typwandlungen (*upcast*-Typwandlungen sind trivial).
Kann zur Laufzeit die Typwandlung *nicht* durchgef�hrt werden, liefert der Operator
einen `nullptr` zur�ck. Dies kann man zur Laufzeit abfragen.

Der `const_cast`-Operator wird verwendet,
um die `const`-Eigenschaft von Variablen zu entfernen.

Dies sollte man eigentlich nur im Ausnahmefall machen, denn die urspr�ngliche Vergabe des `const`-Attributs
sollte ja einen Sinn gehabt haben.

Der `reinterpret_cast`-Cast ist der freiz�gigste Cast-Operator von allen: Er *re-interpretiert* eine Variable / ein Objekt
im Sinne des gew�nschten Datentyps. Diese Operation betrifft die Interpretation von Bits (also der Repr�sentation einer Variablen / eines Objekts im Speicher),
ist folglich extrem maschinenabh�ngig und sollte nur selten bzw. sehr bewusst eingesetzt werden.

**Ausgabe** zu `static_cast`-Beispiel:

```cpp
2
This is Base!
This is Derived!
This is Derived!
This is Derived!
This is Derived!
```

**Ausgabe** zu `dynamic_cast`-Beispiel:

```cpp
1
2
3
4
```

**Ausgabe** zu `const_cast`-Beispiel:

```cpp
This is Derived!
This is Derived!
dynamic_cast failed!
This is Base!
```

**Ausgabe** zu `reinterpret_cast`-Beispiel:

```cpp
65
A
ABC
```

---

[Zur�ck](../../Readme.md)

---
