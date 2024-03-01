# Konzepte (*Concepts*) und Einschr�nkungen (*Requirements*) f�r Klassen

[Zur�ck](../../Readme.md)

---

[Quellcode](ConceptsRequiresClasses.cpp)

---

## Allgemeines

Es gibt zwei M�glichkeiten, um Konzepte (`concept`) mit Klassen zu verwenden.

Sowohl mit der `requires`-Klausel als auch mit `den so genannten &bdquo;Constrained Template Parametern&rdquo;
haben wir eine einfache und lesbare M�glichkeit, Konzepte zu verwenden, um die Menge aller m�glichen Datentypen einzuschr�nken,
die f�r eine Template-Klasse Anwendung finden sollen.


## Variante 1: `requires`-Klausel nach der Template-Parameterliste

Wir k�nnen eine `requires`-Klausel verwenden, um Einschr�nkungen (*Constraints*) f�r ein
Klassentemplate zu definieren.

Ein Klassentemplate wird in gewohnter Manier definiert,
nach der Template-Parameterliste erg�nzen wir eine `requires`-Klausel mit allen Einschr�nkungen einf�gen,
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

Wie wir an dem Beispiel erkennen k�nnen, ist die Syntax
&ndash; abgesehen von der zus�tzlichen Zeile mit der `requires`-Klausel &ndash;
dieselbe wie die eines Klassentemplate.

Wir wollen noch ein Beispiel mit mehreren Template Parametern betrachten.

In diesem Fall m�ssen wir die `requires`-Klausel entsprechend f�r alle Template Parameter erweitern:

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

Das obige Beispiel zeigt, dass wir zusammengesetzte Ausdr�cke als Einschr�nkungen verwenden k�nnen.
Mit der nun folgenden Art, eingeschr�nkte Klassentemplates zu schreiben, ist dies nicht mehr m�glich.


## Variante 2: Eingeschr�nkte Template Parameter

Mit &bdquo;Constrained Template Parametern&rdquo; ist es noch einfacher,
das Sprachmittel `concept` zu verwenden.

In der Liste der Template Parameter wird anstelle des Schl�sselworts `typename`
einfach das Konzept angeben, das man verwenden m�chte:


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

In diesem Beispiel k�nnen wir sehen, wie wir den Template Parameter `T` eingeschr�nkt haben,
um das `Number`-Konzept zu erf�llen.

Wir wollen zum Abschluss auch f�r diese Variante ein Beispiel mit mehreren Template Parametern betrachten:

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

[Zur�ck](../../Readme.md)

---

