# *Type Erasure* &ndash; statischer versus dynamischer Polymorphismus

[Zurück](../../Readme.md)

---

[Quellcode](TypeErasure.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [Beschreibung](#link2)
  * [*Type Erasure* in der C++ Klassenbibliothek STL](#link3)
  * [Benutzerdefinierte Implementierung des *Type Erasure* Idioms](#link4)
  * [Verbesserung der Implementierung mit Konzepten](#link5)
  * [Beispiel: Eine Buchhandung](#link6)
  * [Fazit](#link7)
  * [Literaturhinweise](#link8)

---

## Einleitung <a name="link1"></a>

Unter *Type Erasure* in C++ verstehen wir eine Technik, 
die eine generische Schnittstelle zu verschiedenen darunterliegenden Typen bereitstellt,
diese Typinformationen vor dem Client-Code aber verborgen werden.

*In anderen Worten*:<br />
Der Client-Code kennt die konkreten Typen nicht:
Er kennt und verwendet nur eine Art abstrakte Schnittstelle.

## Beschreibung  <a name="link2"></a>

Die Einführung einer objektorientierten Typhierarchie mit einer abstrakten Basisklasse als einziger Schnittstelle
zu allen abgeleiteten Klassen ist eine Möglichkeit, *Type Erasure* zu realisieren. 

Bei dieser Vorgehensweise steht der virtuelle Methodenaufrufmechnismus im Mittelpunkt.
Dieser besitzt in Punkto Performanz jedoch Schwächen.

In einer Umgebung mit kritischen Leistungsanforderungen oder begrenztem Speicher (z.B. *Embedded Software Development*),
kann ein objektorientierter Ansatz schnell problematisch werden.

Ein weiterer Nachteil des Ansatzes mit virtuellen Methoden ist, dass wir gezwungen sind,
die Objekte überwiegend über Zeiger oder Referenzen zu verwenden,
und folglich auch die Ressourcenverwaltung (Speicherzuweisung und -freigabe, `new`, `delete`) eine Rolle spielt.

Ein zweiter Ansatz besteht in der Verwendung von Templates.
Wir sind beim *Type Erasure* Idiom angekommen.

## *Type Erasure* in der C++ Klassenbibliothek STL  <a name="link3"></a>

Das *Type Erasure* Idiom ist in der C++ Klassenbibliothek bereits an mehrere Stellen vorhanden,
wenngleich uns dies vermutlich nicht unmittelbar bewusst ist:

  * `std::function<>`<br />
  Das `std::function<>`-Klassentemplate (seit C++11 &ndash; Header `<functional>`) ist eine universelle polymorphe Funktionshüllenklasse (*Function Wrapper Class*),
  d.h. sie bietet eine *einheitliche* Schnittstelle zu einer Funktion, einem aurufbaren Objekt oder einem Lambda-Ausdruck.

  * `std::variant<>`<br />
  Das Klassentemplate `std::variant<>` (seit C++17 &ndash; Header `<variant>`) hat Ähnlichkeiten zu einem typsicheren Datentyp `union`.
  Ein `std::variant`-Objekt kann einen Wert enthalten, dessen Typ sich auf einen der Datentypen bezieht,
  der als Templateparameter für `std::variant<...>` aufzuführen ist.
  Beispielsweise kann eine `std::variant<int, double>`-Variable entweder einen ganzzahligen Wert oder einen `double`-Gleitkommawert enthalten.



## Benutzerdefinierte Implementierung des *Type Erasure* Idioms  <a name="link4"></a>


Zusätzlich zu den Möglichkeiten, die die C++&ndash;Standardbibliothek bietet,
kann man *Type Erasure* natürlich auch selbst realisieren &ndash; am besten unter Verwendung von *Templates*:

Wir beginnen mit einem &bdquo;tierischen&rdquo; Beispiel und betrachten zunächst eine Anwendung von *Type Erasure*
mit objektorientierten Techniken:

```cpp
01: struct IAnimal
02: {
03:     virtual ~IAnimal() = default;
04:     virtual std::string see() const = 0;
05:     virtual std::string say() const = 0;
06: };
07: 
08: class Dog : public IAnimal
09: {
10: public:
11:     virtual std::string see() const override { return "dog"; }
12:     virtual std::string say() const override { return "woof"; }
13: };
14: 
15: class Cat : public IAnimal
16: {
17: public:
18:     virtual std::string see() const override { return "cat"; }
19:     virtual std::string say() const override { return "meow"; }
20: };
```

In diesem Listing werden konkrete Objekte der Klassen `Dog` und `Cat` mit einer gemeinsamen Basisklasse `IAnimal` (Schnittstelle, *interface*) definiert.
Wollen wir mehrere dieser Objekte in einem gemeinsamen Container ablegen,
kommt uns diese gemeinsame Schnittstelle zur Hilfe:

```cpp
01: using AnimalPointer = std::shared_ptr<IAnimal>;
02: 
03: using Animals = std::vector<AnimalPointer>;
04: 
05: static void test_type_erasure_using_dynamic_polymorphism()
06: {
07:     AnimalPointer animal1{ std::make_shared<Cat>() };
08:     AnimalPointer animal2{ std::make_shared<Dog>() };
09: 
10:     Animals animals{ animal1, animal2 };
11: 
12:     for (const auto& animal : animals) {
13:         std::cout << animal->see() << ": " << animal->say() << std::endl;
14:     }
15:     std::cout << std::endl;
16: }
```

*Ausgabe*:

```
cat: meow
dog: woof
```

Diese objektorientierte Variante des *Type Erasure* Idioms ist typsicher, einfach und unkompliziert,
hat aber den bekannten kleinen Nachteil des dynamischen Methodenaufrufs mit `virtual`:

Jede Suche einer Methodenadresse in der *virtuellen Funktionstabelle* (*vtable*) kostet mehr Laufzeitleistung als ein
korrespondierender statischer Methodenaufruf.

Diese Beobachtung kann für die meisten Anwendungen irrelevant sein,
aber in einigen zeitkritischen Umgebungen könnte sie ein Problem darstellen.

Darüber kommt durch die Vererbung eine enge Kopplung ins Spiel:
Die abgeleiteten Klassen kennen ihre Basisklasse und deren Implementierung!

Wir betrachten nun eine alternative Implementierung mit C++&ndash;Templates: Das *Type Erasure* Idiom,
auch bekannt als &bdquo;*Duck-Typing*&rdquo;:

&bdquo;*Duck-Typing*&rdquo;:<br />
Der amerikanische Schriftsteller und Dichter James Whitcomb Riley (1849 – 1916) soll den Satz geprägt haben:

> &bdquo;Wenn ich einen Vogel sehe, der wie eine Ente läuft, wie eine Ente schwimmt und wie eine Ente quakt, nenne ich diesen Vogel eine Ente.&rdquo;

Der Test besagt, dass Menschen ein unbekanntes Objekt identifizieren können, indem sie lediglich das Verhalten oder die Gewohnheiten dieses Objekts studieren.

In der objektorientierten Programmierung wird dieses Prinzip verwendet,
um den Typ eines Objekts anhand seiner Verhaltensmerkmale zu bestimmen, d. h.
der Funktionalität, die das Objekt besitzt.

Wir betrachten nun wieder Hunde und Katzen, aber bitte betrachten Sie die Unterschiede in der Realisierung:

```cpp
01: class Dog
02: {
03: public:
04:     std::string see() const { return "dog"; }
05:     std::string say() const { return "woof"; }
06: };
07: 
08: class Cat
09: {
10: public:
11:     std::string see() const { return "cat"; }
12:     std::string say() const { return "meow"; }
13: };
```

Die beiden Klassen leiten sich dieses Mal *nicht* von einer Basisklasse ab!

Nun kommt das Kernstück des *Type Erasure* Idioms in Gestalt einer Klasse `PolymorphicObjectWrapper`:

```cpp
01: class PolymorphicObjectWrapper
02: {
03: public:
04:     template<typename T>
05:     PolymorphicObjectWrapper(const T& obj) :
06:         m_wrappedObject{ std::make_shared<ObjectModel<T>>(obj) }
07:     {}
08: 
09:     std::string see() const
10:     {
11:         return m_wrappedObject->see();
12:     }
13: 
14:     std::string say() const
15:     {
16:         return m_wrappedObject->say();
17:     }
18: 
19: private:
20:     struct ObjectConcept
21:     {
22:         virtual ~ObjectConcept() = default;
23:         virtual std::string see() const = 0;
24:         virtual std::string say() const = 0;
25:     };
26: 
27:     template<typename T>
28:     struct ObjectModel final : public ObjectConcept
29:     {
30:         ObjectModel(const T& object) : m_object{ object } {}
31: 
32:         std::string see() const override
33:         {
34:             return m_object.see();
35:         }
36: 
37:         std::string say() const override
38:         {
39:             return m_object.say();
40:         }
41: 
42:     private:
43:         T m_object;
44:     };
45: 
46:     std::shared_ptr<ObjectConcept> m_wrappedObject;
47: };
```

Zur Klasse `PolymorphicObjectWrapper` bedarf es einiger Anmerkungen:

  * Die Klasse `PolymorphicObjectWrapper` besitzt eine Instanzvariable `m_wrappedObject` (Smart Pointer),
  deren Typ von der inneren Schnittstelle `ObjectConcept` bzw. der abstrakten Klasse `ObjectConcept` definiert wird.
  * Das innere Klassentemplate `ObjectModel<T>` implementiert diese Schnittstelle.
  * Auf konkrete Implementierungen von `ObjectModel<T>` (wie `ObjectModel<Dog>` oder `ObjectModel<Cat>`)
  wird über die Schnittstelle (abstrakte Klasse) `ObjectConcept` zugegriffen.
  * Die Klasse `PolymorphicObjectWrapper` leitet Aufrufe der Methoden `see()` und `say()`
  an ihre Schnittstelle `ObjectConcept` weiter, die wiederum von der konkreten Unterklasse `ObjectModel<T>` implementiert wird.
  * Diese Unterklasse ruft letztendlich `see()` und `say()` für den zugrunde liegenden Typ auf.


Damit kommen wir zu einem Beispiel:


```cpp
01: using Animals = std::vector<PolymorphicObjectWrapper>;
02: 
03: static void test_type_erasure_using_template_techniques()
04: {
05:     Animals animals{ Cat(), Dog() };
06: 
07:     for (const auto& animal : animals) {
08:         std::cout << animal.see() << ": " << animal.say() << std::endl;
09:     }
10:     std::cout << std::endl;
11: }
```

*Ausgabe*:

```
cat: meow
dog: woof
```

Zur *Type Erasure* Nomenklatur:

Im letzten Abschnitt haben wir in der Namensgebung der Klassen ein *Konzept* und ein *Modell* vorgefunden:

  * `ObjectConcept` ist ein Beispiel eines *Type Erasure* **Konzepts**.
  * `ObjectModel` ist ein Beispiel eines *Type Erasure* **Modells**.

Ein **Konzept** beschreibt die Schnittstelle, gegen die wir in der Hüllenklasse programmieren müssen.

Ein **Modell** ist ein auf Templates basierendes Wrapper-Objekt, das die **Konzept**-Schnittstelle implementiert
und alle Konzept-Methoden an den zugrunde liegenden, konkreten Typ weiterleitet.


## Verbesserung der Implementierung mit Konzepten <a name="link5"></a>

Die Klasse `PolymorphicObjectWrapper` und die in ihr enthaltene Klasse `ObjectModel` setzen ein bestimmtes
Verhalten der verwendeten Klassen `T` voraus (*Duck Typing*).

Dieses Verhalten wird zwar durch die (innere) Schnittstelle `ObjectConcept` beschrieben als auch definiert,
der Templateparamter `T` steht prinzipiell für beliebige Datentypen.

Mit Hilfe von *Konzepten* (`concept`) kann man die Eigenschaften des Datentyps `T` exakter fassen.

Hierzu müssen alle konkreten Typen, die für den Templateparamter `T` verwendet werden,
einen Schnittstellenvertrag erfüllen, d.h.
sie müssen öffentliche Methoden haben, die zu denen passen,
die von der inneren Schnittstelle `ObjectConcept` deklariert werden.

Wir stellen sicher, dass diese Anforderung erfüllt wird,
indem wir ein C++-Konzept namens `ClassActingLikeAnAnimal` definieren:

```cpp
01: template<typename T>
02: concept ClassActingLikeAnAnimal = requires (const T& o)
03: {
04:     { o.see() } -> std::same_as<std::string>;
05:     { o.say() } -> std::same_as<std::string>;
06: };
```

Nun ist die Klasse `PolymorphicObjectWrapper` entsprechend anzupassen:


```cpp
01: class PolymorphicObjectWrapper
02: {
03: public:
04:     template<typename T>
05:         requires ClassActingLikeAnAnimal<T>
06:     PolymorphicObjectWrapper(const T& obj) :
07:         m_wrappedObject{ std::make_shared<ObjectModel<T>>(obj) }
08:     {}
09: 
10:     std::string see() const
11:     {
12:         return m_wrappedObject->see();
13:     }
14: 
15:     std::string say() const
16:     {
17:         return m_wrappedObject->say();
18:     }
19: 
20: private:
21:     struct ObjectConcept
22:     {
23:         virtual ~ObjectConcept() = default;
24:         virtual std::string see() const = 0;
25:         virtual std::string say() const = 0;
26:     };
27: 
28:     template<typename T>
29:         requires ClassActingLikeAnAnimal<T>
30:     struct ObjectModel final : public ObjectConcept
31:     {
32:         ObjectModel(const T& object) : m_object{ object } {}
33: 
34:         std::string see() const override
35:         {
36:             return m_object.see();
37:         }
38: 
39:         std::string say() const override
40:         {
41:             return m_object.say();
42:         }
43: 
44:     private:
45:         T m_object;
46:     };
47: 
48:     std::shared_ptr<ObjectConcept> m_wrappedObject;
49: };
```
---

## Beispiel: Eine Buchhandung <a name="link6"></a>

Wir vertiefen die Betrachtungen zu *Type Erasure* an einem praxisnahen Beispiel: einer Buchhandung.
Das *Type Erasure* Idiom kommt hier indirekt zum Zuge, indem wir die Klasse `std::variant` verwenden.

Als Voraussetzungen für dieses Beispiel benötigen wir Kenntnisse bzgl.
der Klassen bzw. Funktionen `std::variant`, `std::visit`, `std::vector` und variadischer Templates.

Worum geht es?

Ein Entwurfsmuster aus der Gruppe der Verhaltensmuster (*Behavioral Design Patterns*),
das so genannt *Visitor*-Entwurfsmuster,
lässt sich mit `std::variant` und `std::visit` sehr einfach umsetzen.

Wir betrachten zu diesem Zweck eine Buchhandlung (Klasse `Bookstore`),
die Bücher und DVDs (Klassen `Book` und `Movie`) verkauft. 

```cpp
class Book
{
  ...
};

class Movie
{
  ...
};
```

1. *Frage*:
Wie ist die Schnittstelle eines Konstruktors für die `Bookstore`-Klasse zu definieren,
wenn dieser `Book`- und `Movie`-Objekte gemischt in einem `std::vector`-Objekt aufnehmen kann?

```cpp
Book cBook { "C", "Dennis Ritchie", 11.99, 12 };
Book javaBook{"Java", "James Gosling", 17.99, 21 };
Book cppBook{"C++", "Bjarne Stroustrup", 16.99, 4 };
Book csharpBook{"C#", "Anders Hejlsberg", 21.99, 8 };

Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

using MyBookstore = Bookstore<Book, Movie>;

MyBookstore bookstore {
    cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
};
```

Entwerfen Sie drei rudimentäre Klassen `Book`, `Movie` und `Bookstore`,
um das gezeigte Code-Fragment übersetzen zu können.


2. *Frage*:
Wie ist in der Klasse `Bookstore` eine Methode `totalBalance` zu implementieren, um den Gesamtwert des Warenbestands in
der Buchhandlung zu berechnen? Hier könnten `std::variant` und `std::visit` zum Einsatz gelangen.

```cpp
double balance = bookstore.totalBalance();
std::cout << "Total value of Bookstore: " << balance << std::endl;
```

Noch ein Hinweis:

Die `std::visit`-Funktion hat als ersten Parameter ein *Callable* (aufrufbares Objekt, generisches Lambda),
um auf das `std::variant`-Objekt zugreifen zu können. Im `std::variant`-Objekt wiederum kann &ndash; in unserer Betrachtung &ndash;
ein `Book`- oder ein `Movie`-Objekt enthalten sein.
Wenn diese Klassen eine Methode desselben Namens (derselben Schnittstelle) enthalten,
wie zum Beispiel `getPrice` oder `getCount`, dann haben Sie das Ziel fast schon erreicht.

*Zusatzaufgabe*:
Realisieren Sie eine Methode `addMedia`, die ein beliebiges &bdquo;Media&rdquo;-Objekt einem `Bookstore`-Objekt hinzufügen kann.
Natürlich muss der Datentyp des &bdquo;Media&rdquo;-Objekts (also z.B. `Book` oder `Movie`) für das `Bookstore`-Objekt
bereits bekannt sein:

```cpp
Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 1 };
bookstore.addMedia(csharpBook);
```

Im Quellcode finden Sie zwei Realisierungen vor:

  * Realisierung mit einer abstrakten Basisklasse (Schnittstelle `IMedia`) und davon abgeleiteten Klassen.
  * Realisierung auf Basis des *Type Erasure* Idioms unter Verwendung von Templates.

---

## Fazit  <a name="link7"></a>

  * Der Vorteil des *Type Erasure* Idioms besteht darin,
  dass die Typen keine gemeinsame Basisklasse benötigen und sie dennoch typsicher ist.

  * Die `PolymorphicObjectWrapper`-Klasse funktioniert mit allen Datentypen, die eine öffentliche Schnittstelle besitzen,
  die von der Klasse erwartet wird (*Duck Typing*).

  * Der Nachteil des Idioms besteht darin, dass es im Vergleich zur viel einfacheren Implementierung
  mit objektorientierten Techniken einen deutlich höheren Komplexitätsgrad aufweist.

  * Ein weiterer Nachteil besteht darin, dass es während der Objekterzeugung ein Performanzproblem gibt,
  da die erstellten Objekte in das `ObjectModel`-Objekt kopiert werden müssen,
  was zu zusätzlichen Aufrufen des Kopierkonstruktors führt.


---

## Literaturhinweise  <a name="link8"></a>


Die Anregungen zu den Beispielen aus diesem Abschnitt sind aus dem Buch

[Clean C++ 20](https://www.clean-cpp.com/) (abgerufen am 19.05.2024)

von Stephan Roth entnommen, siehe dazu auch das [Literaturverzeichnis](../Literatur/Literature.md).

---

[Zurück](../../Readme.md)

---
