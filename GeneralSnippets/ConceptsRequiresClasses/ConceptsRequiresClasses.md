# Moderne Stilistik für die Schreibweise von Klassen

[Zurück](../../Readme.md)

---

[Quellcode](ConceptsRequiresClasses.cpp)

---

# Allgemeines

Es gibt zwei Möglichkeiten, um Konzepte (`concept`) mit Klassen zu verwenden.

Sowohl mit der `requires`-Klausel als auch mit `den so genannten &ldquo;Constrained Template Parametern&rdquo;
haben wir eine einfache und lesbare Möglichkeit, Konzepte zu verwenden, um die Menge aller möglichen Datentypen einzuschränken,
die für eine Template-Klasse Anwendung finden sollen.


## Variante 1: `requires`-Klausel nach der Template-Parameterliste

Wir können eine `requires`-Klausel verwenden, um Einschränkungen (*Constraints*) für ein
Klassentemplate zu definieren.

Ein Klassentemplate wird in gewohnter Manier definiert,
nach der Template-Parameterliste ergänzen wir eine `requires`-Klausel mit allen Einschränkungen einfügen,
die wir festlegen wollen.


Beispiel:

```cpp
01: template <typename T>
02: concept Number = std::integral<T> || std::floating_point<T>;
03: 
04: template <typename T>
05: requires Number<T>
06: class WrappedNumber
07: {
08: private:
09:     T  m_number;
10: 
11: public:
12:     WrappedNumber(T number) : m_number{ number } {}
13: 
14:     T getNumber() const { return m_number; }
15: };
```

Wie wir an dem Beispiel erkennen können, ist die Syntax
&ndash; abgesehen von der zusätzlichen Zeile mit der `requires`-Klausel &ndash;
dieselbe wie die eines Klassentemplate.

Wir wollen noch ein Beispiel mit mehreren Template Parametern betrachten.

In diesem Fall müssen wir die `requires`-Klausel entsprechend für alle Template Parameter erweitern:

```cpp
01: template <typename T, typename U>
02: requires Number<T> && Number<U>
03: class WrappedPair
04: {
05: private:
06:     T  m_firstNumber;
07:     U  m_secondNumber;
08: 
09: public:
10:     WrappedPair(T firstNumber, U secondNumber)
11:         : m_firstNumber{ firstNumber }, m_secondNumber{ secondNumber }
12:     {}
13: 
14:     T getFirstNumber() const { return m_firstNumber; }
15:     U getSecondNumber() const { return m_secondNumber; }
16: };
```

Das obige Beispiel zeigt, dass wir zusammengesetzte Ausdrücke als Einschränkungen verwenden können.
Mit der nun folgenden Art, eingeschränkte Klassentemplates zu schreiben, ist dies nicht mehr möglich.


## Variante 2: Eingeschränkte Template Parameter

Mit &ldquo;Constrained Template Parametern&rdquo; ist es noch einfacher,
das Sprachmittel `concept` zu verwenden.

In der Liste der Template Parameter wird anstelle des Schlüsselworts `typename`
einfach das Konzept angeben, das man verwenden möchte:


```cpp
01: template <Number T>
02: class WrappedNumber
03: {
04: private:
05:     T  m_number;
06: 
07: public:
08:     WrappedNumber(T number) : m_number{ number } {}
09: 
10:     T getNumber() const { return m_number; }
11: };
```

In diesem Beispiel können wir sehen, wie wir den Template Parameter `T` eingeschränkt haben,
um das `Number`-Konzept zu erfüllen.

Wir wollen zum Abschluss auch für diese Variante ein Beispiel mit mehreren Template Parametern betrachten:

```cpp
01: template <Number T, Number U>
02: class WrappedPair
03: {
04: private:
05:     T  m_firstNumber;
06:     U  m_secondNumber;
07: 
08: public:
09:     WrappedPair(T firstNumber, U secondNumber)
10:         : m_firstNumber{ firstNumber }, m_secondNumber{ secondNumber }
11:     {}
12: 
13:     T getFirstNumber() const { return m_firstNumber; }
14:     U getSecondNumber() const { return m_secondNumber; }
15: };
```

---

## Literaturhinweise:

Ideen und Anregungen zu den Beispielen aus diesem Abschnitt stammen aus

[C++ concepts with classes](https://www.sandordargo.com/blog/2021/02/24/cpp-concepts-with-classes) (abgerufen am 01.05.2023).

von Sandor Dargo.

---

[Zurück](../../Readme.md)

---

