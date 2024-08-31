# Reference Wrapper: `std::reference_wrapper` und `std::ref`

[Zur�ck](../../Readme.md)

---

[Quellcode](ReferenceWrapper.cpp)

---

Die Klasse `std::reference_wrapper<T>` steht f�r kopierbare (*copyable*)
und zuweisbare (*assignable*) Objekte,
die eine Referenz (*T&*) imitieren.
Sie bietet die *non-nullable*-Garantie einer Referenz und eine *Pointer*-�hnliche Flexibilit�t,
sich an ein anderes Objekt zu binden.

Die Beispiele zeigen den zul�ssigen, aber auch unzul�ssigen Gebrauch vom Einsatz 
eines Reference Wrappers auf.

---

[Zur�ck](../../Readme.md)

---

// ============================================

# The Return of &bdquo;`printf`&rdquo;: `std::print(ln)` in C++ 23

[Zur�ck](../../Readme.md)

---

[Quellcode](Formatting.cpp)

---

## �berblick

&bdquo;`printf`&rdquo;: Wer hat sie nicht vermisst? Die C-Bibliotheksfunktion war uns doch &ndash; trotz all ihrer Schw�chen &ndash; 
sehr ans Herz gewachsen.

<img src="StdPrintln.png" width="400">

<sup>(Credits: Found in [std::print in C++23](https://vitaut.net/posts/2023/print-in-cpp23/) from *Victor Zverovic*)</sup>

*Abbildung* 1: The Return of &bdquo;`printf`&rdquo;: `std::print` ab C++ 23.

In C++ 23 ist sie zur�ckgekehrt, und wenn wir so wollen: St�rker denn je zuvor!
Typsicherheit, Erweiterbarkeit, Unterst�tzung von Unicode und Performanz sind 
einige der St�rken der neuen Funktionen `std::print` und  `std::println`.
Dar�ber hinaus weisen sie gro�e �hnlichkeiten zu `printf` auf!

---

## Dokumentation

Eine genaue Beschreibung der Formatzeichenkette findet man in der
&bdquo;[Standard Format Specification](https://en.cppreference.com/w/cpp/utility/format/spec)&rdquo; wieder.

Aus diesem Grund macht es wenig Sinn, hier die Spezifikation zu wiederholen.

Ich versuche, mit einer Reihe m�glichst ausdrucksstarker Beispiele die wesentlichen Features der `std::print(ln)`
Funktion vorzustellen.

---

## Beispiele


##### Verwendung einfacher Variablenersetzungen


*Beispiel*:

```cpp
XXX
```

*Ausgabe*:

```
AAA
```


---

## Literaturhinweise:

Die Anregungen zu den Beispielen stammen teilweise bzw. in modifizierter Form aus

[`std::format` in C++ 20](https://www.heise.de/developer/artikel/std-format-in-C-20-4919132.html)

von Rainer Grimm und Peter Gottschling.

---

[Zur�ck](../../Readme.md)

---
