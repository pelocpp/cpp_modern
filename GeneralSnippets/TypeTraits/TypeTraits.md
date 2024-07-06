# C++ TypeTraits

[Zurück](../../Readme.md)

---

[Quellcode](TypeTraits.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Erstes Beispiel: &bdquo;is_this_a_floating_point&rdquo;](#link2)
  * [Zweites Beispiel: Fallunterscheidung zur Übersetzungszeit](#link3)
  * [Weitere Beispiele: `std::bidirectional_iterator_tag` und `std::random_access_iterator_tag`](#link4)

---

## Allgemeines <a name="link1"></a>

C++ *TypeTraits*, zu deutsch etwa *Typmerkmale*, sind eine Sammlung von *Metafunktionen*.
Sie stammen aus dem Umfeld der so genannten *Metaprogrammierung*.

---

## Erstes Beispiel: &bdquo;is_this_a_floating_point&rdquo; <a name="link2"></a>

Die so genannte *Template Spezialisierung* stellt das Fundament der *Typmerkmale* dar:

```cpp
01: // primary template
02: template <typename T>
03: struct is_this_a_floating_point
04: {
05:     static constexpr bool value = false;
06: };
07: 
08: // explicit (full) specialization
09: template <>
10: struct is_this_a_floating_point<float>
11: {
12:     static constexpr bool value = true;
13: };
14: 
15: template <>
16: struct is_this_a_floating_point<double>
17: {
18:     static constexpr bool value = true;
19: };
20: 
21: template <typename T>
22: void process_a_floating_point(T value)
23: {
24:     static_assert(is_this_a_floating_point<T>::value);
25:     std::cout << "processing a real number: " << value << std::endl;
26: }
27: 
28: void test()
29: {
30:     process_a_floating_point(42.0);
31:     // process_a_floating_point(42);  // does'n t compile: static assertion fails
32: }
```

---

## Zweites Beispiel: Fallunterscheidung zur Übersetzungszeit <a name="link3"></a>

Angenommen, wir haben mehrere Klassen, die Operationen zum Schreiben
in einen Ausgabestrom definieren (Serialisierung).
Einige unterstützen dies mit einem überladenen Operator `<<`,
andere mit Hilfe einer Member-Funktion namens `write`.
Das folgende Code-Fragment zeigt zwei Beispiele derartiger Klassen:

```cpp
01: class Widget
02: {
03: private:
04:     int m_id;
05:     std::string m_name;
06: 
07: public:
08:     Widget() : Widget { 0, ""} {}
09:     Widget (int id, std::string name) : m_id{ id}, m_name{ name } {}
10: 
11:     std::ostream& write(std::ostream& os) const
12:     {
13:         os << m_id << ", " << m_name << '\n';
14:         return os;
15:     }
16: };
17: 
18: class Gadget
19: {
20: private:
21:     int m_id;
22:     std::string m_name;
23: 
24: public:
25:     Gadget() : Gadget{ 0, "" } {}
26:     Gadget(int id, std::string name) : m_id{ id }, m_name{ name } {}
27: 
28:     int getId() const { return m_id; }
29:     std::string getName() const { return m_name; }
30: };
31: 
32: std::ostream& operator <<(std::ostream& os, const Gadget& gadget)
33: {
34:     os << gadget.getId() << ", " << gadget.getName() << '\n';
35:     return os;
36: }
```

Mit diesem Code-Fragment könnten wir folgenden Quellcode schreiben:

```cpp
Widget widget{ 1, "I'm a Widget" };
Gadget gadget{ 2, "I'm a Gadget" };

widget.write(std::cout);
std::cout << gadget;
```

Unser Ziel ist es jedoch, ein Funktionstemplate zu definieren,
das es uns ermöglicht, beide Ausgaben in der gleichen Weise zu behandeln.
Mit anderen Worten, anstatt entweder die `write`-Methode
oder den `<<`-Operator zu bedienen, sollte folgende Schreibweise möglich sein:

```cpp
serialize(std::cout, widget);
serialize(std::cout, gadget);
```

Dieses Ziel erreichen wir nun mit Hilfe von *Type Traits*:


```cpp
01: template <typename T>
02: struct uses_write
03: {
04:     static constexpr bool value = false;
05: };
06: 
07: template <>
08: struct uses_write<Widget>
09: {
10:     static constexpr bool value = true;
11: };
12: 
13: // primary (class) template
14: template <bool>
15: struct Serializer
16: {
17:     template <typename T>
18:     static void serialize(std::ostream& os, T const& value)
19:     {
20:         os << value;
21:     }
22: };
23: 
24: template<>
25: struct Serializer<true>
26: {
27:     template <typename T>
28:     static void serialize(std::ostream& os, T const& value)
29:     {
30:         value.write(os);
31:     }
32: };
33: 
34: // free function template - based on class Serializer<T>
35: template <typename T>
36: void serialize(std::ostream& os, T const& obj)
37: {
38:     Serializer<uses_write<T>::value>::serialize(os, obj);
39: }
```

Damit können wir nun die folgenden beiden `serialize`-Funktionsaufrufe schreiben:

```cpp
Widget widget{ 1, "I'm a Widget" };
Gadget gadget{ 2, "I'm a Gadget" };

serialize(std::cout, widget);
serialize(std::cout, gadget);
```

---

## Weitere Beispiele: `std::bidirectional_iterator_tag` und `std::random_access_iterator_tag` <a name="link4"></a>


Im korrespondierenden Quellcode finden Sie in Bezug auf Iterator-Kategorien
wie `std::bidirectional_iterator_tag` und `std::random_access_iterator_tag`
ein weiteres Beispiel vor.

---

*Hinweis*:

Im Beispiel zum Sortieren eines STL-Containers
finden Sie eine Anwendung von `std::remove_reference` vor.

Welcher Unterschied liegt in den Beispielen mit und ohne Verwendung von `std::remove_reference`?
Warum sind alle Beispiele übersetzungsfähig?

---

[Zurück](../../Readme.md)

---
