# Reference Wrapper: `std::reference_wrapper` und `std::ref`

[Zurück](../../Readme.md)

---

[Quellcode](ReferenceWrapper.cpp)

---

Die Klasse `std::reference_wrapper<T>` steht für kopierbare (*copyable*)
und zuweisbare (*assignable*) Objekte,
die eine Referenz (*T&*) imitieren.
Sie bietet die *non-nullable*-Garantie einer Referenz und eine *Pointer*-ähnliche Flexibilität,
sich an ein anderes Objekt zu binden.

Die Beispiele zeigen den zulässigen, aber auch unzulässigen Gebrauch vom Einsatz 
eines Reference Wrappers auf.

---

[Zurück](../../Readme.md)

---

// ============================================

# The Return of &bdquo;`printf`&rdquo;: `std::print(ln)` in C++ 23

[Zurück](../../Readme.md)

---

[Quellcode](Formatting.cpp)

---

## Überblick

&bdquo;`printf`&rdquo;: Wer hat sie nicht vermisst? Die C-Bibliotheksfunktion war uns doch &ndash; trotz all ihrer Schwächen &ndash; 
sehr ans Herz gewachsen.

<img src="StdPrintln.png" width="400">

<sup>(Credits: Found in [std::print in C++23](https://vitaut.net/posts/2023/print-in-cpp23/) from *Victor Zverovic*)</sup>

*Abbildung* 1: The Return of &bdquo;`printf`&rdquo;: `std::print` ab C++ 23.

In C++ 23 ist sie zurückgekehrt, und wenn wir so wollen: Stärker denn je zuvor!
Typsicherheit, Erweiterbarkeit, Unterstützung von Unicode und Performanz sind 
einige der Stärken der neuen Funktionen `std::print` und  `std::println`.
Darüber hinaus weisen sie große Ähnlichkeiten zu `printf` auf!

---

## Dokumentation

Eine genaue Beschreibung der Formatzeichenkette findet man in der
&bdquo;[Standard Format Specification](https://en.cppreference.com/w/cpp/utility/format/spec)&rdquo; wieder.

Aus diesem Grund macht es wenig Sinn, hier die Spezifikation zu wiederholen.

Ich versuche, mit einer Reihe möglichst ausdrucksstarker Beispiele die wesentlichen Features der `std::print(ln)`
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

[Zurück](../../Readme.md)

---
