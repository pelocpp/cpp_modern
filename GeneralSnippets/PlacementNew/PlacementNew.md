# *Placement New*:<br />Trennung von Speicherallokation und Objektkonstruktion

[Zurück](../../Readme.md)

---

[Quellcode](PlacementNew.cpp)

---

## Allgemeines

Es ist &ndash; wenngleich auch eher selten benutzt &ndash; in C++ möglich,
die Speicherallokation von der Objektkonstruktion zu trennen.

Man kann zum Beispiel mit `std::malloc()` ein Byte-Array reservieren
und in diesem Speicherbereich ein neues Objekt erstellen.

Betrachte den folgenden Codeausschnitt:

```cpp
auto* memory = std::malloc(sizeof(User));
auto* user = ::new (memory) User("John");
```

Die vielleicht ungewohnte Syntax

```cpp
::new (memory)
```

heißt *Placement new*.

Dieser Aufruf des `new`-Operators reserviert keinen Speicher,
sondern konstruiert auf bereits vorhandenem Speicher ein neues Objekt.

Der Doppelpunkt (`::`) vor `new` stellt sicher, dass die Suche nach `new` aus dem globalen Namensraum erfolgt,
um zu vermeiden, dass eine überladene Version des `new`-Operators erfasst wird.

Im Beispiel wird ein `User`-Objekt an einem vorgegebenen Speicherort konstruiert.

Es gibt kein *Placement delete*. Um das Objekt zu zerstören und den von ihm benutzten Speicher freizugeben,
müssen wir den Destruktor explizit aufrufen und danach den Speicher explizit freigeben.

```cpp
user->~User();
std::free(memory);
```
---

## Ein Anwendungsfall

Wir betrachten Klassen, die keinen Standard-Konstruktor besitzen.
Für manche Container kann dies zu Problemen führen:

```cpp
01: template <class T>
02: class Vector
03: {
04: private:
05:     T* m_data;
06: 
07: public:
08:     Vector() : m_data{ new T[10] } {}
09:     ~Vector() { delete[] m_data; }
10: };
11: 
12: static void test_05()
13: {
14:     Vector<int> a;      // compiles
15:     // Vector<User> b;  // Error: User type doesn't have a default c'tor
16: }
```

Wir legen dabei zu Grunde, dass die Klasse `User` keinen Standard-Konstruktor besitzt.

Das Problem finden wir in Zeile 8 vor. Die Anweisung `new T[10]` bewirkt zwei Dinge:

  * Reserviere Speicher mit einer Länge von `sizeof(T) * 10`.
  * Konstruiere alle Objekt mit einem Aufruf von `T{}`, dem Standardkonstruktor.

Da `T` keinen Standardkonstruktor hat und `m_data` beim Erstellen lediglich einen zusammenhängenden Speicherbereich benötigt,
warum trennen wir dann nicht die Speicherzuweisung vom Konstruieren der Objekte?

Damit betrachten wir folgenden Ansatz, um Speicher zu reservieren:

```cpp
T *data = reinterpret_cast<T*>(std::malloc(sizeof(T) * 10));
```

Was machen wir nun, wenn der Benutzer `push_back(value);` aufruft?
Mit der Syntax des *Placement New* kann man bei vorhandenem Zeiger
den Konstruktor eines Typs an der Position des Zeigers aufrufen:

```cpp
T* node = new (static_cast<void*>(&data[size])) T{ value };
```

`&data[size]` wäre in diesem Beispiel ein verfügbarer Platz eines zusammenhängenden Speicherbereichs,
in dem wir das Element `T{ value }` platzieren könnten.

Der Wert wird durch Kopieren eines neuen `T`-Objekts erstellt.
Da der Kopierkonstruktor verwendet wird, wird das Problem des fehlenden Standardkonstruktors umgangen.

Eine Klasse `Vector`, die mit dem Hilfsmittel des *Placement New* arbeitet,
könnte so aussehen:

```cpp
01: template <class T>
02: class VectorEx
03: {
04: private:
05:     size_t m_capacity;
06:     size_t m_size;
07:     T* m_data;
08: 
09: public:
10:     VectorEx() :
11:         m_capacity{ 10 },
12:         m_size{},
13:         m_data{ reinterpret_cast<T*>(std::malloc(sizeof(T) * m_capacity)) }
14:     {}
15: 
16:     ~VectorEx()
17:     {
18:         while (m_size) {
19:             pop_back();
20:         }
21: 
22:         std::free(m_data);
23:     }
24: 
25:     void push_back(const T& value)
26:     {
27:         T* ptr{ m_data + m_size };
28:         new (ptr) T{ value };
29:         ++m_size;
30:     }
31: 
32:     void push_back(T&& value)
33:     {
34:         T* ptr{ m_data + m_size };
35:         new (ptr) T{ std::move(value) };
36:         ++m_size;
37:     }
38: 
39:     void pop_back() {
40: 
41:         --m_size;
42:         m_data[m_size].~T();
43:     }
44: };
```

---

## Literaturhinweise

Ideen und Anregungen zu den Beispielen aus diesem Abschnitt stammen aus

[C++ Placement New](https://medium.com/@dgodfrey206/c-placement-new-1298ccbb076e) (abgerufen am 21.01.2024).

von David Godfrey.

---

[Zurück](../../Readme.md)

---
