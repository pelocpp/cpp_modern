# Klasse `std::array`, Hilfsfunktion `std::to_array` und Hilfsklasse `std::span`

[Zur�ck](../../Readme.md)

---

[Quellcode](Array.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [`std::to_array`](#link2)
  * [`std::span`](#link3)
  * [&bdquo;*Non-Owning*&rdquo; Objekte](#link4)

---

## Allgemeines <a name="link1"></a>

Die Klasse `std::array` stellt im Prinzip eine d�nne H�lle um ein Array im C-Stil dar.

Die Verwendung der Klasse `std::array` anstelle eines C-Stil Arrays bietet eine Reihe von Vorteilen:

  * Die Gr��e (L�nge) des zugrunde liegenden Datenbereichs ist immer bekannt.
  * Ein `std::array`-Objekt wird nicht automatisch in einen Zeiger umgewandelt (z.B. bei einem Funktionsaufruf, so genannte &bdquo;*Array Decay*&rdquo; Thematik),
    wenn das Objekt �ber Funktionsgrenzen weitergereicht wird.
  * `std::array`-Objekte verf�gen �ber Iteratoren-Objekte, mit deren Hilfe man die Elemente des Arrays einfach durchlaufen kann.

Sowohl Arrays im C-Stil als auch `std::array`-Objekte haben eine feste Gr��e!
Sie muss zur Kompilierzeit bekannt sein, `std::array`-Objekte k�nnen zur Laufzeit weder wachsen noch schrumpfen.

Weitere Vorteile der Klasse `std::array`:

  * Kopieren mit `operator=` funktioniert.
  * Vergleichsoperator `operator==` funktioniert.
  * R�ckgabe eines `std::array`-Objekts als Ergebnis eines Funktionsaufrufs funktioniert.

---

## `std::to_array` <a name="link2"></a>

C++20 f�hrt eine neue Funktion namens `std::to_array` ein (definiert in der Include-Datei `<array>`).
Sie konvertiert ein bestimmtes Array im C-Stil in ein `std::array`-Objekt.
Die Funktion funktioniert nur f�r eindimensionale Arrays. 

Im Zusammenspiel mit *CTAD* (*Class Template Argument Deduction*) kann man bei
der Definition des `std::array`-Objekts die Template Parameter weglassen, vor allem die
bisweilen l�stige Angabe der Feldl�nge.

---

## `std::span` <a name="link3"></a>

Die Klasse `std::span` stellt eine Hilfestellung dar, wenn man `std::array`-Objekte an Funktionen �bergeben m�chte.
F�r ein `std::array`-Objekt muss man den Typ und die Anzahl der Elemente im Array als Template-Parameter angeben.
Der Typ der Elemente ist eher nicht das Problem, aber die L�nge: Theoretisch m�sste man pro Anzahl der Elemente im Array
eine separate Funktion definieren:

```cpp
void print(const std::array<int, 1>& myArray);
void print(const std::array<int, 2>& myArray);
void print(const std::array<int, 3>& myArray);
...
```

Das wird kompliziert!
Die Hilfsklasse `std::span` (eingef�hrt in C++20) stellt hier eine Abhilfe dar, da sie es erm�glicht,
eine einzige Funktion zu schreiben, die sogar mit Vektoren, Arrays im C-Stil
und eben `std::array`-Objekten beliebiger Gr��e funktioniert.

Ein `std::span`-Objekt besitzt nur einen Zeiger auf das erste Element des Datenbereichs
und eine Information �ber die Anzahl der Elemente:

```cpp
template<typename T>
class span {
    T*   m_data;
    size_t m_count;
public:
    ...
};
```

Der Trick bzgl. der L�nge des Datenbereichs besteht darin, dass die `std::span`-Klasse
zahlreiche Konstruktoren besitzt, die die L�nge des Datenbereichs jeweils zur Laufzeit ermitteln
und in einer Instanzvariablen (hier: `m_count`) ablegen.

---

## &bdquo;*Non-Owning*&rdquo; Objekte <a name="link4"></a>

Die Zeigervariable `m_data` ist nur solange g�ltig, wie der Datenbereich existiert.
Lebt das `std::span`-Objekt l�nger als der Datenbereich, sto�en wir auf *UB* (*Undefined Behaviour*).

Man spricht in Bezug auf das `std::span`-Objekt von einem
so genannten &bdquo;*Non-Owning*&rdquo; Container.

*Beachte*:
Im Gegensatz zur Klasse `std::string_view` (ebenfalls eine &bdquo;*Non-Owning*&rdquo; Klasse), die eine schreibgesch�tzte Ansicht
einer Zeichenfolge bereitstellt,
kann ein `std::span`-Objekt Lese- und Schreibzugriff auf die zugrunde liegenden Elemente erm�glichen.

Wenn also ein Element in einem `std::span`-Objekt ge�ndert wird,
wird tats�chlich das Element im zugrunde liegenden Datenbereich ge�ndert.

Wenn �nderungen im Datenbereich nicht gew�nscht sind, kann man ein `std::span`-Objekt mit `const`-Elementen erstellen.
Beispielsweise besteht f�r die nachfolgende Funktion `print` keine M�glichkeit zur �nderung
eines ihrer Elemente im Datenbereich.

```cpp
01: void printArray(std::span<const int> values) {
02: 
03:     std::println("Number of elements: {}", values.size());
04:     std::println("Size of span:       {}", values.size_bytes());
05: 
06:     for (const auto elem : values) {
07:         std::println("{}", elem);
08:     }
09:     std::println();
10: }
```

---

[Zur�ck](../../Readme.md)

---
