# Variadische Templates: Mixins

[Zurück](../../Readme.md)

---

&#x21D0; [Teil III: Variadische Templates: Anwendungsfall &ldquo;Summe von Summen&rdquo;](VariadicTemplates_03_SumOfSums.md)

---

[Quellcode](VariadicTemplate_04_Mixins.cpp)

---

## Einleitung

Parameter Packs können auch bei der Vererbung eingesetzt werden,
um die Menge der Basisklassen zu definieren,
von denen eine Unterklasse abgeleitet werden soll. Neben dem Begriff *Mixin*
spricht man hier auch von der so genannten *variadischen Vererbung* (*&ldquo;Variadic&rdquo; Inheritance*).

## Mixins

Wir betrachten das Ganze am besten an einem Beispiel:

```cpp
01: // need some classes with default constructors
02: class A { public: A() = default; };
03: class B { public: B() = default; };
04: class C { public: C() = default; };
05: 
06: template<typename ... TS>
07: class X : public TS...
08: {
09: public:
10:     X(const TS&... mixins) : TS{ mixins } ... {}
11: };
12: 
13: void test_00() 
14: {
15:     A a{};
16:     B b{};
17:     C c{};
18:     X<A, B> xAB{ a, b };
19:     // X<B, A> xBA{};   // Error, needs arguments
20:     X<C> xC{ c };
21:     X<> xNoBases{};
22: 
23:     X<A, B, C>  xabc{ a, b, c };
24: }
```

Das Parameter Pack `TS` wird so erweitert, dass jeder darin enthaltene Typ zu einer Basisklasse von `X` wird.
Beachte jedoch, dass die Reihenfolge, in der sie angegeben werden, von Bedeutung ist,
da das Ändern der Reihenfolge zu einem anderen Typ führt - wie unterschiedlich dieser auch sein mag.

---

*Hinweis*:

Bei Mehrfachvererbung gilt:
&ldquo;Die Reihenfolge der Ableitung ist relevant, um die Reihenfolge der Standardinitialisierung
durch Konstruktoren und die Bereinigung durch den Destruktor zu bestimmen&rdquo;.

---

Aus diesem Grund ist die hier vorgestellte Technik eine ziemlich fragile Methode
zum Spezifizieren von Basisklassen. Sie kann jedoch nützlich sein,
wenn sie als Teil einer Template-Implementierung verwendet wird,
die derlei Abhängigkeiten ausschließen kann.

Betrachten wir den Konstruktor der Klasse X noch einmal detaillierter.
Es sind **zwei** Parameter Pack Expansionen vorhanden:

```cpp
X(const TS&... mixins) : TS{ mixins } ... {}
```

Das Muster wird für jedes Argument im Parameter Pack einmal instanziiert, also:
Bei beiden oben genannten Erweiterungen wird `TS` durch jeden Typ aus dem Parameter Pack ersetzt,
und `mixins` fungiert als Platzhalter für den jeweiligen Parameternamen.

*Beispiel*:

Der Konstruktor einer Klasse

```cpp
X<A,B,C>
```

wird effektiv erweitert zu


```cpp
X(const A& a, const B& b, const C& c) : A(a), B(b), C(c) {}
```

Wir können uns davon auch mit dem Tool *CppInsight.io* überzeugen:

```cpp
#ifdef INSIGHTS_USE_TEMPLATE
template<>
class X<A, B, C> : public A, public B, public C
{
    public: 
    inline X(const A & __mixins0, const B & __mixins1, const C & __mixins2) :
        A(__mixins0) , B(__mixins1), C(__mixins2) {}
};
#endif
```

Wir können also in C++ eine Klasse erstellen, die von einer beliebigen Anzahl von Basisklassen erbt.
Eine **class X: public T...** wird folglich in eine Klasse `X` wie folgt &ldquo;transformiert&rdquo;:
**class X: public A, public B, public C, ...**.

## Eine Anwendung zu Mixins

Als Beispiel betrachten wir eine *Repository*-Klasse im Sinne eines Assoziativ-Speichers. 
Das Repository-Objekt soll über ein oder mehrere so genannte *Slots* verfügen,
auf die mit einem Schlüssel (*Key*) zugegriffen werden kann. Ferner enthält ein Slot einen Wert.
Die genaue Intention des Aussehens eines `Repository`-Objekts entnehmen Sie bitte *Abbildung* 1:

<img src="cpp_snippets_mixins_01.svg" width="600">

*Abbildung* 1: `Repository`-Klasse mit Schlüssel-Wert-Paaren, die via Vererbung verfügbar gemacht werden.

Wir stellen im Folgenden zwei Implementierungen gegenüber:

  * klassischer Ansatz
  * Ansatz mit Mixins

### Klassische Realisierung

###### Realisierung:

```cpp
01: class SlotA
02: {
03: public:
04:     int m_value{};
05: };
06: 
07: class SlotB
08: {
09: public:
10:     std::string m_value{};
11: };
12: 
13: // Note:
14: // private inheritance, no one can access directly 
15: // to the slots other than Repository itself
16: class MyRepository : private SlotA, private SlotB
17: {
18: public:
19:     void setSlotA(const int& value)
20:     {
21:         // access the base-class's value: since we have multiple bases
22:         // with a 'value' field, we need to "force" the access to SlotA.
23:         SlotA::m_value = value;
24:     }
25: 
26:     int getSlotA() 
27:     {
28:         return SlotA::m_value;
29:     }
30: 
31:     void setSlotB(const std::string& value)
32:     {
33:         SlotB::m_value = value;
34:     }
35: 
36:     std::string getSlotB()
37:     {
38:         return SlotB::m_value;
39:     }
40: };
```

###### Testrahmen:

```cpp
01: void main() 
02: {
03:     MyRepository repo{};
04: 
05:     repo.setSlotA(123);
06:     std::cout << repo.getSlotA() << std::endl; // printing 123
07: 
08:     repo.setSlotB(std::string{ "ABC" });
09:     std::cout << repo.getSlotB() << std::endl; // printing "ABC"
10: }

```

Man kann unschwer die Nachteile dieser Realisierung erkennen: Für jeden Slot muss man eine eigene *Slot*-Klasse
definieren. Und zum Zweiten muss man für jeden dieser Slots eine separate *getter*- und *setter*-Methode implementieren. 
Dies kann man nur als &ldquo;Copy-Paste&rdquo;-Programmierung bezeichnen, es muss andere Lösungsmöglichkeiten geben.

### Ansatz mit Mixins

###### Realisierung:

```cpp
01: template <typename T>
02: class Slot
03: {
04: protected:
05:     T& get()
06:     {
07:         return m_value;
08:     }
09: 
10:     void set(const T& value)
11:     {
12:         m_value = value;
13:     }
14: 
15: private:
16:     T m_value{};
17: };
18: 
19: template <typename... Slots>
20: class Repository : private Slots...  // inherit private from our slots...
21: {
22: public:
23:     template <typename T> // select type
24:     T& get()
25:     {
26:         return Slot<T>::get(); // select base class
27:     }
28: 
29:     template <typename T>
30:     void set(const T& value)
31:     {
32:         Slot<T>::set(value);
33:     }
34: };
```

###### Testrahmen:

```cpp
01: void main() 
02: {
03:     using MyRepo = Repository<Slot<int>, Slot<std::string>>;
04: 
05:     MyRepo repo{};
06: 
07:     repo.set<std::string>(std::string{ "XYZ" });
08:     repo.set(987); // note type deduction: we pass an int, so it writes to the int slot
09: 
10:     std::cout << repo.get<int>() << std::endl; // printing 987
11:     std::cout << repo.get<std::string>() << std::endl; // printing "XYZ"
12: }
```

Dieser zweite Ansatz in der Implementierung einer Klasse `Repository` nimmt Gestalt an, aber wir sind noch nicht fertig!
Wenn Sie versuchen, zwei `int`-Slots anzulegen, wird ein Kompilierungsfehler ausgegeben:
&ldquo;*Basisklasse 'Slot' wurde mehrmals als direkte Basisklasse angegeben*&rdquo;.

### Verbesserung des Mixins-Ansatzes

Wir müssen unsere `Slot`-Klasse um einen zusätzlichen Template Parameter erweitern (Typ für Schlüssel mit Standardwert).
In *Abbildung* 2 können wir die Modifikationen erkennen. Wollten wir zwei Slot-Einträge
desselben Typs haben (siehe Typ `std::string` in *Abbildung* 2), dann sind diese beiden
Einträge durch einen zusätzlichen Schlüsseltyp zu unterscheiden.

<img src="cpp_snippets_mixins_02.svg" width="700">

*Abbildung* 2: Modifikationen am Konzept der Klasse `Slot`.

Dies zieht allerdings Änderungen an den Repository-Methoden nach sich:

###### Realisierung:

```cpp
01: struct DefaultSlotKey; // forward definition sufficient
02: 
03: template <typename T, typename Key = DefaultSlotKey>
04: class SlotEx
05: {
06: protected:
07:     T& get()
08:     {
09:         return m_value;
10:     }
11: 
12:     void set(const T& value)
13:     {
14:         m_value = value;
15:     }
16: 
17: private:
18:     T m_value;
19: };
20: 
21: template <typename... Slots>
22: class RepositoryEx : private Slots...  // inherit private from our slots...
23: {
24: public:
25:     template <typename T, typename Key = DefaultSlotKey>
26:     T& get()
27:     {
28:         return SlotEx<T, Key>::get(); // select base class
29:     }
30: 
31:     template <typename T, typename Key = DefaultSlotKey>
32:     void set(const T& value)
33:     {
34:         SlotEx<T, Key>::set(value);
35:     }
36: };
```

###### Testrahmen:

```cpp
01: void main()
02: {
03:     // again forward definition sufficient, definitions not needed
04:     struct Key1;
05:     struct Key2;
06: 
07:     // repository definition with keys
08:     using MyRepoEx =
09:         RepositoryEx<SlotEx<int>, SlotEx<std::string, Key1>, SlotEx<std::string, Key2>>;
10: 
11:     MyRepoEx repo{};
12: 
13:     repo.set(12345); // note type deduction: we pass an int, so it writes to the int slot
14:     repo.set<std::string, Key1>("ABC");
15:     repo.set<std::string, Key2>("123");
16: 
17:     std::cout << repo.get<int>() << std::endl; // printing 12345
18:     std::cout << repo.get<std::string, Key1>() << std::endl; // printing "ABC"
19:     std::cout << repo.get<std::string, Key2>() << std::endl; // printing "123"
20: }
```

### Realisierung einer `emplace`-Methode

Das vorliegende Beispiel eignet sich sehr gut, um eine `emplace`-Methode zu ergänzen.
Die `emplace`-Methode kennen wir bereits von der Container-Klasse `std::vector`:

`emplace` erstellt ein Objekt an Ort und Stelle, so dass im `std::vector`-Objekt kein temporäres Hilfsobjekt
angelegt werden muss. `emplace` wird direkt mit Argumenten für einen geeigneten Konstruktor
des gewünschten Objekts aufgerufen. In diesem Fall vermeiden wir es, ein unnötiges
temporäres Objekt zu erstellen und wieder zu zerstören.

Um den geeigneten Konstruktor des Zielobjekts zu &ldquo;finden&rdquo;, verwendet `emplace`
eine variable Anzahl von Argumenten unterschiedlichen Typs und leitet diese
an den korrespondierenden Konstruktor weiter.
Eine variable Anzahl von Argumenten und Typen muss Sie an etwas erinnern ... variadische Templates!
Damit stellen wir nun unsere Realisierung einer variadischen `emplace`-Methode
sowie ihre Entsprechung in der `Slot`-Klasse vor.
Es genügt die beiden `emplace`-Methoden zu betrachten, der Rest der Implementierung
ändert sich nicht:

###### Realisierung (Klasse `SlotEx`):

```cpp
01: template <typename... Args>
02: void emplace(const Args&... args)
03: {
04:     m_value = T{ args... }; // copy-operator (might use move semantics)
05: }
```

oder noch besser mit *Perfect Forwarding*:

```cpp
01: template <typename... Args>
02: void emplace(Args&& ... args)
03: {
04:     m_value = T{ std::forward<Args>(args) ... }; // copy-operator (might use move semantics)
05: }
```

###### Realisierung (Klasse `RepositoryEx`):

```cpp
01: template <typename T, typename Key = DefaultSlotKey, typename... Args>
02: void emplace(const Args&... args)
03: {
04:     SlotEx<T, Key>::emplace(args...);
05: }
```

oder noch besser mit *Perfect Forwarding*:

```cpp
01: template <typename T, typename Key = DefaultSlotKey, typename... Args>
02: void emplace(Args&& ... args)
03: {
04:     SlotEx<T, Key>::emplace(std::forward<Args>(args)...);
05: }
```

###### Testrahmen:

> Klasse `Person`:

```cpp
01: class Person {
02: private:
03:     std::string m_name;
04:     int m_age;
05: public:
06:     Person() : m_name{}, m_age{} {}
07: 
08:     Person(const std::string& name, const int age)
09:     : m_name{ name }, m_age{age } {}
10: 
11:     // just for testing: if move-assignment is available, copy-assignment is ignored !!!
12:     Person& operator= (const Person& person) {
13:         // prevent self-assignment
14:         if (this == &person)
15:             return *this;
16: 
17:         // assign right side
18:         m_name = person.m_name;
19:         m_age = person.m_age;
20: 
21:         return *this;
22:     }
23: 
24:     Person& operator= (Person&& person) noexcept  { 
25:         // prevent self-assignment
26:         if (this == &person)
27:             return *this;
28: 
29:         // assign right side
30:         m_name = person.m_name;
31:         m_age = person.m_age;
32: 
33:         // reset source  object, ownership has been moved
34:         person.m_name.clear();
35:         person.m_age = 0;
36: 
37:         return *this;
38:     }
39: 
40:     std::string operator()() { 
41:         std::ostringstream oss; 
42:         oss << m_name << " [" << m_age << "]";
43:         return  oss.str();
44:     }
45: };
```

> Beispielprogramm:

```cpp
01: void test_04() 
02: {
03:     using MyRepo = RepositoryEx<SlotEx<Person>, SlotEx<std::string>>;
04: 
05:     MyRepo repo{};
06: 
07:     repo.emplace<std::string>(std::string{ "ABCDEFGHIJK" });
08:     std::cout << repo.get<std::string>() << std::endl; // printing "ABCDEFGHIJK"
09: 
10:     repo.emplace<Person>(std::string{ "Hans" }, 21);
11:     std::cout << repo.get<Person>()() << std::endl; // printing "Hans [21]"
12: }
```

## Literaturhinweise:

Die Anregungen zu den Beispielen aus diesem Abschnitt sind entnommen aus

[Practical uses for variadic templates](https://crascit.com/2015/03/21/practical-uses-for-variadic-templates/)<br>(abgerufen am 12.05.2020).

und

[Jean Guegant' Blog](https://jguegant.github.io/blogs/tech/thread-safe-multi-type-map.html)<br>(abgerufen am 12.05.2020).

---

[Zurück](../../Readme.md)

---

