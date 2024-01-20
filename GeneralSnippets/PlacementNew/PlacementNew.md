# *Placement New*: Trennung von Speicherallokation und Objektkonstruktion

[Zur�ck](../../Readme.md)

---

[Quellcode](PlacementNew.cpp)

---

# Allgemeines

Es ist &ndash; wenngleich auch eher selten benutzt &ndash; in C++ m�glich,
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

hei�t *Placement new*.

Dieser Aufruf des new-Operators reserviert keinen Speicher, sondern konstruiert auf bereits vorhandenem Speicher ein neues Objekt.

Der Doppelpunkt (::) vor new stellt sicher, dass die Suche nach `new` aus dem globalen Namensraum erfolgt,
um zu vermeiden, dass eine �berladene Version des `new`-Operators erfasst wird.

Im vorherigen Beispiel wird ein `User`-Objekt an einem vorgegebenen Speicherort konstruiert.

Es gibt kein *Placement delete*. Um das Objekt zu zerst�ren und den von ihm benutzten Speicher freizugeben,
Wir m�ssen den Destruktor explizit aufrufen und dann den Speicher freigeben.

```cpp
user->~User();
std::free(memory);
```

---



// ALTES ZEUGS ..................

# Allgemeines

Wenn der Compiler ein `std::initializer_list`-Objekt erstellt,
werden die Elemente der Liste auf dem Stapel konstruiert (als konstante Objekte).

Danach erstellt der Compiler das `std::initializer_list`-Objekt selbst,
das die Adresse des ersten und letzten Elements enth�lt
(genauer in Bezug auf das letzte Element: die Adresse des ersten Elements *nach* dem letzten Element).

Folglich besteht ein `std::initializer_list`-Objekt nur aus zwei Zeigervariablen,
es handelt sich also um ein recht kleines Objekt.
Damit ist es nicht wirklich notwendig, bei der Parameter�bergabe 
eine Referenz zu verwenden &ndash; die Parameter�bergabe *Call-by-Value* ist v�llig ausreichend.

<img src="cpp_initializer_list.svg" width="300">

*Abbildung* 1: Konstruktion des Inhalts eines `std::initializer_list`-Objekts auf dem Stack.

*Hinweis*:
Ein `std::initializer_list`-Objekt ist immer *per-Value* zu �bergeben.
Eine m�gliche *per-Reference*-�bergabe k�nnte m�glichen Optimierungen des Compilers im Wege stehen. 

---

## Zusammenspiel der Klassen `std::initializer_list` und `std::vector`

Die Klasse `std::vector` ist daf�r ausgelegt,
mit einem `std::initializer_list`-Objekt initialisiert zu werden:

```cpp
std::initializer_list<int> list{ 1, 2, 3, 4, 5 };
std::vector<int> vec{ list };
```

---

## Konstruktoren mit einem `std::initializer_list<T>`-Parameter

Um f�r Konstruktoren eine variable Anzahl von Parametern (desselben Typs) zu erm�glichen,
wurde in C++ das Konzept von *Initialisierungs-Listen* eingef�hrt.

Eine Klasse muss dann einen entsprechenden Konstruktor zur Verf�gung stellen,
der das Klassentemplate `std::initializer_list<>` verwendet.

*Beispiel*:

```cpp
std::map (std::initializer_list<T> init);
std::vector (std::initializer_list<T> init);
```

Die Anweisung

```cpp
std::vector<int> vec = { 1, 2, 3 };
```

erzeugt *zun�chst* ein `std::initializer_list<int>`-Objekt mit den Werten 1, 2 und 3
und benutzt dieses dann anschlie�end, um den entsprechenden Konstruktor des Vektors aufzurufen.

  * Ein Konstruktor mit `std::initializer_list<T>`-Parameter wird auch *Sequenzkonstruktor* genannt.
  * Bei der Suche nach einem passenden Konstruktor f�r einen bestimmten Aufruf wird im
    Regelfall der Sequenzkonstruktor bevorzugt ausgew�hlt.


Sequenzkonstruktoren lassen sich auch in benutzer-definierten Klassen &ndash; oder auch 
Funktionen/Methoden &ndash; einsetzen:

```cpp
class Polygon {
public:
    Polygon(std::initializer_list<Point> elements)
        : m_elements{ elements } {};
    ...

private:
    std::vector<Point> m_elements;
};
```

Bei Funktionen, die eine Initialisierungs-Liste als Parameter haben,
sind die geschweiften Klammern direkt als Argument anzugeben:

```cpp
int sum = adder( { 1, 3, 5, 7, 9 } );
```

## Regeln f�r Klassen mit Konstruktoren mit `std::initializer_list`-Parameter

Unterschiedliche Deklarationen von Konstruktoren in einer Klasse
im Zusammenspiel mit `std::initializer_list<T>`-Parametern
f�hren zu unterschiedlichen (und m�glicherweise unerwarteten!) Ergebnissen:

```cpp
class TinyContainer {
public:
    TinyContainer() {}
    TinyContainer(int value) {}
    TinyContainer(std::initializer_list<int>) {};
    TinyContainer(const std::vector<int>&) {};
};

void test_03() {
    TinyContainer tc0;                                 // TinyContainer::TinyContainer ()
    TinyContainer tc1{ 1, 2, 3, 4 };                   // TinyContainer::TinyContainer (std::initializer_list<int>)
    TinyContainer tc2{ 1 };                            // TinyContainer::TinyContainer (std::initializer_list<int>)
    TinyContainer tc3(1);                              // TinyContainer::TinyContainer (int)
    TinyContainer tc4{ };                              // TinyContainer::TinyContainer ()
    TinyContainer tc5{ std::vector<int> { 1, 2, 3} };  // TinyContainer::TinyContainer (const std::vector<int>&)
}
```

---

[Zur�ck](../../Readme.md)

---
