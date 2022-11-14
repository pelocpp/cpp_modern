# Typumwandlungen

[Zurück](../../Readme.md)

---

[Quellcode](Casts.cpp)

---

Es wird an mehreren Beispielen die Funktionsweise folgender C++-Typumwandlungen gezeigt:

  * `static_cast`
  * `dynamic_cast`
  * `const_cast`
  * `reinterpret_cast`

Der `static_cast`-Operator ist dazu gedacht, implizit erlaubte Typumwandlungen durchzuführen,
die zur Übersetzungszeit stattfinden.

Interessanter ist der `dynamic_cast`-Operator. Er wird zur Laufzeit ausgeführt
(von trivialen Überprüfungen zur Übersetzungszeit einmal abgesehen).

Seine Stärke sind *downcast*-Typwandlungen (*upcast*-Typwandlungen sind trivial).
Kann zur Laufzeit die Typwandlung *nicht* durchgeführt werden, liefert der Operator
einen `nullptr` zurück. Dies kann man zur Laufzeit abfragen.

Der `const_cast`-Operator wird verwendet,
um die `const`-Eigenschaft von Variablen zu entfernen.

Dies sollte man eigentlich nur im Ausnahmefall machen, den die ursprüngliche Vergabe des `const`-Attributs
sollte ja einen Sinn gehabt haben.

Der `reinterpret_cast`-Cast ist der freizügigste Cast-Operator von allen: Er *re-interpretiert* eine Variable / ein Objekt
im Sinne des gewünschten Datentyps. Diese Operation betrifft die Interpretation von Bits (also der Repräsentation einer Variablen / eines Objekts im Speicher),
ist folglich extrem maschinenabhängig und sollte nur selten bzw. sehr bewusst eingesetzt werden.

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

[Zurück](../../Readme.md)

---
