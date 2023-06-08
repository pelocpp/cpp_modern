# Klasse `std::array`

[Zurück](../../Readme.md)

---

[Quellcode](Array.cpp)

---

*Allgemeines*:

Die Klasse `std::array` stellt im Prinzip eine dünne Hülle um ein Array im C-Stil dar.

Die Verwendung der Klasse `std::array` anstelle eines Arrays im C-Stil bietet eine Reihe von Vorteilen:

  * Sie kennen immer die Größe (Länge) des zugrunde liegenden Datenbereichs.
  * Ein `std::array`-Objekt wird nicht automatisch in einen Zeiger umgewandelt (z.B. bei einem Funktionsaufruf, so genannte &ldquo;*Array Decay*&rdquo; Thematik).
  * `std::array`-Objekte verfügen über Iteratoren-Objekte, mit deren Hilfe man die Elemente des Arrays einfach durchlaufen kann.

Sowohl Arrays im C-Stil als auch `std::array`-Objekte haben eine feste Größe!
Sie muss zur Kompilierzeit bekannt sein, `std::array`-Objekte können zur Laufzeit weder wachsen noch schrumpfen.

Weitere Vorteile der Klasse `std::array`:

  * Kopieren mit `operator=` funktioniert.
  * Vergleichsoperator `operator==` funktioniert.
  * Rückgabe eines `std::array`-Objekts als Ergebnis eines Funktionsaufrufs funktioniert.

---

C++20 führt eine neue Funktion namens `std::to_array` ein (definiert in `<array>`).
Sie konvertiert ein bestimmtes Array im C-Stil in ein `std::array`-Objekt.
Die Funktion funktioniert nur für eindimensionale Arrays. 

Im Zusammenspiel mit *CTAD* (*Class Template Argument Deduction*) kann man bei
der Definition des `std::array`-Objekts die Template Parameter weglassen, vor allem die
bisweilen lästige Angabe der Feldlänge.

---

Die Klasse `std::span` löst das Problem, wenn man `std::array`-Objekte an Funktionen übergeben möchte.

Für ein `std::array`-Objekt muss man den Typ und die Anzahl der Elemente im Array als Template-Parameter angeben.
Der Typ der Elemente ist eher nicht das Problem, aber die Länge: Theoretisch müsste man pro Anzahl der Elemente im Array
eine separate Funktion definieren:

```cpp
void print(const std::array<int, 1>& myArray);
void print(const std::array<int, 2>& myArray);
void print(const std::array<int, 3>& myArray);
```

Das wird kompliziert!
Die Hilfsklasse `std::span` (eingeführt in C++20) stellt hier eine Abhilfe dar, da sie es ermöglicht,
eine einzige Funktion zu schreiben, die mit Vektoren, Arrays im C-Stil
und `std::array`-Objekten beliebiger Größe funktioniert.

Ein `std::span`-Objekt besitzt nur einen Zeiger auf den Datenbereich:

```cpp
template<typename T>
class span {
    T* m_data;
    size_t m_count;
public:
    ...
};
```

Ein `std::span`-Objekt besitzt nur einen Zeiger auf das erste Element und eine Information über die Anzahl der Elemente.

Der Trick bzgl. der Länge des Datenbereichs besteht darin, dass die `std::span`-Klasse
zahlreiche Konstruktoren besitzt, die die Länge des Datenbereichs jeweils zur Laufzeit ermitteln
und in einer Instanzvariablen (hier: `m_count`) ablegen.

Die Zeigervariable `m_data` ist folglich nur solange gültig, wie der Datenbereich existiert.
Lebt das `std::span`-Objekt länger als der Datenbereich, stoßen wir auf UB (*undefined behaviour*).

Man spricht in Bezug auf das `std::span`-Objekt auch von einem
so genannten &ldquo;*Non-Owning*&rdquo; Container.

*Beachte*:
Im Gegensatz zur Klasse `std::string_view`, die eine schreibgeschützte Ansicht
einer Zeichenfolge bereitstellt,
kann ein `std::span`-Objekt Lese- und Schreibzugriff auf die zugrunde liegenden Elemente ermöglichen.

Wenn also ein Element in einem `std::span`-Objekt geändert wird,
wird tatsächlich das Element im zugrunde liegenden Datenbereich geändert.

Wenn Änderungen im Datenbereich nicht gewünscht sind, kann man ein `std::span`-Objekt mit `const`-Elementen erstellen.
Beispielsweise besteht für die Funktion `print` keine Möglichkeit zur Änderung
eines ihrer Elemente im Datenbereich.

```cpp
void print(std::span<const int> values)
{
    std::cout << std::format("Number of elements: {}\n", values.size());
    std::cout << std::format("Size of span: {}\n", values.size_bytes());

    for (const auto elem : values) {
        std::cout << std::format("{} ", elem);
    }
    std::cout << std::endl;
}
```

---


[Zurück](../../Readme.md)

---
