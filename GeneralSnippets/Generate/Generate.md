# Algorithmus `std::generate`

[Zurück](../../Readme.md)

---

[Quellcode](Generate.cpp)

---

## Allgemeines

Es werden einfache Anwendungsfälle der STL-Algorithmen

  * `std::for_each`
  * `std::fill`
  * `std::generate`

demonstriert.

---

## `std::generate`

Im Wesentlichen ruft `std::generate` eine &bdquo;Generator Funktion&rdquo; (z.B. Lambda-Funktion)
für jeden existierenden Eintrag eines Bereichs (Container) auf,
um mit den Rückgabewerten dieser Funktion den Container zu befüllen:

<img src="cpp_generate.svg" width="300">

*Abbildung*: Prinzip einer &bdquo;Generator Funktion&rdquo; im Zusammenspiel mit `std::generate`.

---

## Unterschied `std::fill` und `std::generate`

`std::fill` und `std::generate` sind einfache Algorithmen zum Füllen von Containern (Bereichen).

  * Der Algorithmus `std::fill` füllt den angegebenen Bereich mit Kopien eines bereitgestellten Werts.

  * Der Algorithmus `std::generate` füllt den Bereich mit den Ergebnissen der sukzessiven Aufrufe eines bereitgestellten *Callables*.

---

## Unterschied `std::for_each` und `std::generate`

  * Der Algorithmus `std::for_each` hat lesenden und schreibenden Zugriff auf den angegebenen Bereich.
    Änderungen des Containers können folglich an Hand des vorhandenen Inhalts erfolgen.

  * Der Algorithmus `std::generate` kann einen Bereich mit berechneten Ergebnissen eines bereitgestellten *Callables* nur *überschreiben*.
    Das *Callable* hat keine Informationen über den vorhandenen Containerinhalt.

---

[Zurück](../../Readme.md)

---
