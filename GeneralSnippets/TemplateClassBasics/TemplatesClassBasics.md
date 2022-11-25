# Klassentemplates: Grundlagen

[Zurück](../../Readme.md)

---

[Quellcode](TemplatesClassBasics01.cpp)

---

Es werden grundlegende Aspekte von Klassentemplates aufgezeigt:

  * Erstellung eines einfachen Klassentemplates
  * Explizite und partielle Spezialisierung
  * Template Member Functions
  * Methoden eines Klassentemplates überschreiben (spezialisieren)

---

## Ein erstes Klassen-Template


```cpp
01: template <typename T>
02: class MyContainer 
03: {
04: private:
05:     T m_data;
06: 
07: public:
08:     MyContainer() : m_data{} {}
09:     void setData(const T& data) { m_data = data; }
10:     T getData() const { return m_data; }
11: };
```

*Beispiel*:

```cpp
01: void main()
02: {
03:     MyContainer<double> container;
04:     container.setData(123.456);
05:     double value = container.getData();
06:     std::cout << value << std::endl;
07: }
```

*Bemerkung*:
Die Methode (*setter*) wurde bewusst mit der Schnittstelle

<pre>const T& data</pre>

als Referenz (oder als Zeiger) realisiert.


#### Hinweis:
Klassen-Templates eigen sich vor allem gut zur Erstellung von Container-Klassen,
siehe deshalb auf den Entwurf und die Konzeption der *Standard Template Library* (STL).

---

## Objekte aus Klassen-Templates erzeugen

Bei der ersten Festlegung eines konkreten Typs für den Platzhalter `T` wird ein
Klassentemplate *instanziiert*:

```cpp
MyContainer<double> container;
container.setData(123.456);
...
```

Im Prinzip haben wir es hier &ndash; oder
allgemeiner formuliert: in der generischen Programmierung  &ndash; mit 3 Ebenen zu tun
(siehe Abbildung 1):

<img src="cpp_template_instantiation.svg" width="400">

*Abbildung* 1: 3-Ebenenmodell der Template-Instanzierung.

Die Instanziierung eines Templates kann dabei *explitit* und *implizit* erfolgen:

*Explitite* Instanziierung:

```cpp
// explicit class template instantiation
template class MyContainer<float>;
```

*Implizite* Instanziierung:

```cpp
void main()
{
    // implicit instantiation of MyContainer<double>
    MyContainer<double> container;
}
```

---

## Klassen-Templates mit mehreren formalen Datentypen


Offensichtlich ist die Definition eines Klassen-Templates nicht
auf einen formalen Datentyp beschränkt:

*Beispiel*:

```cpp
01: template <typename T, typename U>
02: class MyPair
03: {
04: public:
05:     T m_data_01;
06:     U m_data_02;
07: 
08: public:
09:     MyPair(const T& data_01, const U& data_02) 
10:         : m_data_01{ data_01 }, m_data_02{ data_02 } { }
11: 
12:     void print(std::ostream& os) {
13:         os << m_data_01 << " : " << m_data_02 << std::endl;
14:     }
15: };
16: 
17: void main() {
18:     MyPair<std::string, double> averageTemperature{ "March", 5.5 };
19:     averageTemperature.print(std::cout);
20: }
```

*Ausgabe*:

```
March : 5.5
```

---

## Definition von Methoden von Klassen-Templates

Wenn Methoden von Klassen-Templates nicht im
Klassenrumpf definiert werden, müssen sie ähnlich wie ein
Funktions-Template formuliert werden:

```cpp
01: template <typename T>
02: class MyContainer
03: {
04: private:
05:     T m_data;
06: 
07: public:
08:     MyContainer();
09:     T getData() const;
10:     void setData(const T& data);
11: };
12: 
13: ...
14: 
15: template <typename T>
16: MyContainer<T>::MyContainer() : m_data{} {}
17: 
18: template <typename T>
19: T MyContainer<T>::getData() const {
20:     return m_data;
21: }
22: 
23: template <typename T>
24: void MyContainer<T>::setData(const T& data) {
25:     m_data = data;
26: }
```

##### Vorläufige Definition:

Man beachte, dass die Definition von Methoden eines Klassen-Templates
nur eine &ldquo;vorläufige Definition&rdquo; darstellt, weil der Klassentyp immer noch
unvollständig ist, da hier ja nur ein formaler Datentyp enthalten ist.

Die eigentlichen Methoden werden erst dann erzeugt, wenn zu einem Klassentyp ein bestimmtes
Objekt instanziiert wird. Das heißt, dass für den Template Parameter `T`
ein konkreter Typ benannt wird.

---

## Methoden eines Klassen-Templates überschreiben (spezialisieren)

Von einem Klassentemplate lassen sich einzelne Methoden überschreiben (spezialisieren).
Wir betrachten dies an einem Beispiel der Methode  `setData`:

```cpp
01: template <typename T>
02: class MyContainer
03: {
04: private:
05:     T m_data;
06: 
07: public:
08:     MyContainer() : m_data{} {}
09:     T getData() const { return m_data; }
10:     void setData(const T& data) { m_data = data; }
11: };
12: 
13: template <>
14: void MyContainer<std::string>::setData(const std::string& data) {
15:     m_data = "[" + data + "]";
16: }
```

Im vorliegenden Beispiel finden wir eine Spezialisierung der Methode `setData` für die
Klasse `MyContainer<std::string>` vor. Dies beeinträchtigt in keiner Weise
den allgemeinen Fall, der für alle Datentypen in Kraft tritt, für die
keine Spezialisierung vorhanden ist:

*Beispiel*:

```cpp
void main()
{
    MyContainer<std::string> container;
    container.setData("I love C++ Templates :)");
    std::string data = container.getData();
    std::cout << data << std::endl;

    MyContainer<int> anotherContainer;
    anotherContainer.setData(123);
    int value = anotherContainer.getData();
    std::cout << value << std::endl;
}
```

*Ausgabe*:

```
[I love C++ Templates :)]
123
```

---

## Klassen-Templates mit Non-Type Parametern

Neben Datentypen können auch konstante Ausdrücke als Template-Parameter benutzt werden.


---


[Zurück](../../Readme.md)

---


