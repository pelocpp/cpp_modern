# Funktionale Programmierung

[Zurück](../../Readme.md)

---

[Quellcode](FunctionalProgramming.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [*Pure* Funktionen](#link2)
  * [Funktionen höherer Ordnung](#link3)
  * [Umsetzung in C++ und STL](#link4)
  * [*Filter-Map-Reduce* Pattern](#link5)
  * [Umsetzung in C++ und *Ranges*](#link6)

---

## Allgemeines <a name="link1"></a>

C++ ist eine &bdquo;prozedurale, objektorientierte und generische Programmiersprache&rdquo; und keine rein &bdquo;funktionale Programmiersprache&rdquo;.
Mit den Neuerungen des so genannten &bdquo;Modern C++&rdquo; lassen sich aber auch
einige Aspekte der &bdquo;funktionalen Programmierung&rdquo; in C++ darstellen.

&bdquo;Funktionen&rdquo; ähneln Methoden. Aber anders als Methoden werden Funktionen bei der &bdquo;funktionalen Programmierung&rdquo; weitergereicht, beispielsweise als Argumente an Methoden oder als Return-Wert einer Methode.
Dies ist in C++ spätestens seit Einführung der Lambda-Funktionen elegant darstellbar.

&bdquo;Rein funktionale Sprachen&rdquo; (&bdquo;*Pure functional languages*&rdquo;) wie beispielsweise *Haskell* sind zustandslos und Funktionen haben keinerlei Seiteneffekte. Sie ändern keine Daten, sondern können höchstens neue Daten als Resultat einer Funktion zurückliefern.
Das ist natürlich bei C++ anders. Hier können Funktionen durchaus Daten ändern, sei es wir betrachten
den Zustand eines Objekts oder mögen es Seiteneffekte anderen Ursprungs sein.

&bdquo;Rein funktionale Programmierung&rdquo; eignet sich ideal zur Parallelverarbeitung sowie für mathematische Aufgaben und steht in dem Ruf,
dass auf diese Weise erstellte Programme weniger fehleranfällig sind.
Nachteilig ist, dass sich reale Objekte und Zustandsänderungen nur schwierig abbilden lassen, was die Programmierung realer Vorgänge und Geschäftsprozesse erschwert.
Dies ist eben das Terrain der objektorientierten zustandsbehafteten Programmierung.

## *Pure* Funktionen <a name="link2"></a>

In der objektorientierten Programmierung zerlegen wir typischerweise ein Programm in Objekte,
von denen jedes eine bestimmte Menge an Methoden besitzt.
Eines der grundlegenden Merkmale eines Objekts ist sein Zustand.

Das Ändern des Zustands eines Objekts durch das Senden von Nachrichten an das Objekt (mit anderen Worten: durch das Aufrufen seiner Methoden)
ist in der objektorientierten Programmierung von entscheidender Bedeutung.
Im Regelfall führt der Aufruf einer Methode zur Änderung des Objektzustands.

Bei der funktionalen Programmierung organisieren wir Code in einer Sammlung von &bdquo;pure&rdquo;&ndash;Funktionen,
von denen jede ihren eigenen Zweck hat und unabhängig von den anderen ist.

Heißt: Unter einer *pure* Funktion verstehen wir eine Funktion, die keinen Zugriff auf etwaige Objekte und
deren Objektzustand hat und infolgedessen mögliche Objekte (also deren Objektzustand), die sie benutzt, *nicht* verändert!

Schauen wir uns ein einfaches Beispiel an, um dieses Konzept zu verdeutlichen.
Nehmen wir an, wir haben es mit `User`-Objekten in einem Programm zu tun und
jedes `User`-Objekt enthält das mit dem Benutzer verknüpfte Alter.

```cpp
01: class User
02: {
03: public:
04:     std::string m_name;
05:     int m_age;
06:     std::string m_phone_number;
07:     std::string m_email;
08: };
```

Eine Funktion `updateAge()` übernimmt die Eingabe als Referenz entgegen und aktualisiert das Originalobjekt:

```cpp
01: void updateAge(User& user)
02: {
03:     user.m_age = user.m_age + 1;
04: }
```

Diese Funktion `updateAge()` ist *keine* reine Funktion, sie passt nicht in das Schema der funktionalen Programmierung!

Anstatt das ursprüngliche Objekt als Referenz entgegen zu nehmen und seinen Wert zu ändern,
gibt die folgende reine Funktion `pureUpdateAge` ein zweites Benutzerobjekt mit denselben Eigenschaften zurück,
mit Ausnahme der aktualisierten Alterseigenschaft:

```cpp
01: User pureUpdateAge(const User& user) // cannot modify the input argument
02: {
03:     User tmp{ user };
04:     tmp.m_age = tmp.m_age + 1;
05:     return tmp;
06: }
```

Obwohl es im Vergleich zu `updateAge()` ineffizient erscheint, besteht einer der Vorteile dieses Ansatzes darin,
dass die Abläufe jetzt klarer sind und vor allem keine Nebenwirkungen, sprich Seiteneffekte, vorhanden sind.
Es ist jetzt garantiert, dass `pureUpdateAge()` das Originalobjekt nicht verändert!

Das Erzeugen einer Kopie ließe sich auch anders gestalten.
Wir ändern den vorherigen Code so ab, dass er das Objekt beim Aufruf bereits in Gestalt einer Kopie annimmt.
Auf diese Weise benötigen wir die Erstellung des `tmp`-Objekts nicht, da das Argument selbst bereits eine Kopie darstellt:


```cpp
01: User pureUpdateAge2(User user)       // user is the copy of the passed object
02: {
03:     user.m_age = user.m_age + 1;
04:     return user;
05: }
```

Wenn eine reine Funktion mehrmals mit denselben Argumenten aufgerufen wird, muss sie jedes Mal das gleiche Ergebnis zurückgeben.

Der folgende Code zeigt, dass unsere Funktion `pureUpdateAge()` denselben Wert zurückgibt, wenn sie mit demselben Objekt aufgerufen wird:

```cpp
01: void test()
02: {
03:     User john
04:     {
05:         .m_name{ "John" },
06:         .m_age{ 25 }
07:     };
08: 
09:     auto updated{ pureUpdateAge(john) };
10:     std::println("Age: {}", updated.m_age);
11: 
12:     updated = pureUpdateAge(john);
13:     std::println("Age: {}", updated.m_age);
14: }
```

*Ausgabe*:

```
Age: 26
Age: 26
```

Es wird in der funktionalen Programmierung als großer Vorteil angesehen,
wenn sich eine Funktion bei jedem Aufruf für dieselben Eingabedaten gleich verhält.

Das bedeutet, dass wir die Logik einer Anwendung entwerfen können,
indem wir sie in kleinere Funktionen zerlegen, von denen jede einen genauen und klaren Zweck hat.

Für reine Funktionen entsteht jedoch ein Mehraufwand hinsichtlich zusätzlicher temporärer Objekte.

Ein reguläres Design beinhaltet einen zentralen Speicher, der den Programmstatus enthält,
der indirekt durch reine Funktionen aktualisiert werden kann.

Nach jedem reinen Funktionsaufruf gibt die Funktion das geänderte Objekt als neues Objekt zurück,
das eben bei Bedarf gespeichert werden kann.


## Funktionen höherer Ordnung <a name="link3"></a>

Funktionen, die entweder Funktionen als Argument annehmen oder als Ergebnis zurückgeben, werden als
*Funktionen höherer Ordnung* bezeichnet.

Das bedeutet, dass wir Funktionen als Objekte und nicht als eine Reihe von Anweisungen betrachten sollten.

Welchen Unterschied macht das für uns?
Nun, das Einzige, was an dieser Stelle wichtig ist, damit eine Funktion als Objekt behandelt wird,
ist die Fähigkeit, sie an andere Funktionen übergeben zu können.

Es folgt ein Beispiel, wie eine Funktion an eine andere Funktion übergeben werden kann:

```cpp
01: class Function
02: {
03: private:
04:     int m_state;
05: 
06: public:
07:     Function () : Function{ 0 } {}
08:     Function(int state) : m_state{ state } {}
09: 
10:     void modify_state(int state) {
11:         m_state = state;
12:     }
13: 
14:     int get_state() {
15:         return m_state;
16:     }
17: 
18:     void operator()() {
19:         // do something that a function would do
20:         std::println("Do something using state {}", m_state);
21:     }
22: };
```

Klasse `Function` ist eine Klasse mit einem überladenen Operator `operator()`.

Immer, wenn wir den `operator()` einer Klasse überladen, machen wir Objekte dieser Klasse &rdquo;aufrufbar&rdquo;.
Alles, was aufrufbar ist, wird als Funktion behandelt.

Ein Objekt einer Klasse, das über einen überladenen `operator()` verfügt, kann also als Funktion betrachtet werden.
Das ist in gewisser Weise wie ein Trick, denn anstatt eine Funktion zu einem Objekt zu machen,
haben wir ein Objekt aufrufbar gemacht.


```cpp
01: void doSomething(Function f)
02: {
03:     f();
04: }
05: 
06: static void test_functional_programming_03()
07: {
08:     Function func{ 123 };
09:     doSomething(func);
10: }
```


*Ausgabe*:

```
Do something using state 123
```


Die Klassiker aus der funktionalen Programmierung sind die drei
Funktionen `map`, `filter` und `fold`. Diese drei Funktionen höherer Ordnung werden über eine weitere 
Funktion parametrisiert und wenden diese sukzessive auf die Elemente eines Containers an. In C++ bieten sich an dieser Stelle
speziell Lambda-Funktionen an.

  * `map` - Transformation der Elemente. Dabei entsteht eine neue Menge von Elementen (derselben Anzahl), die typischerweise
    einen anderen Datentyp haben. So können zum Beispiel Umrechnungen oder Umwandlungen durchgeführt werden.
  * `filter` - Filterung gewünschter Elemente aus einer Menge von Elementen (Container).
    Der Datentyp der Elemente bleibt derselbe, aber die Menge der Elemente des Ursprungscontainers wird reduziert.
  * `fold` - Reduktion der Elemente eines Containers auf ein Endergebnis (Resultat). Typischerweise wird eine Lambda-Funktion
    mit zwei Argumenten auf ein Element des Containers und das vorangehende Zwischenergebnis angewendet.


## Umsetzung in C++ und STL <a name="link4"></a>

In einer ersten Näherung finden wir die drei Funktionen höherer Ordnung auch in C++
bei genauem Hinsehen in den STL-Algorithmen vor:

  * `map` - ähnlich zu `std::transform`.
  * `filter` - ähnlich zu `std::copy_if`.
  * `fold` - ähnlich zu `std::accumulate`.


## *Filter-Map-Reduce* Pattern <a name="link5"></a>

&bdquo;Filter-Map-Reduce&rdquo; beschreibt ein Pattern, bei dem eine Menge von Daten in einer Abfolge
von bestimmten Schritten verarbeitet wird. Dabei ist `reduce` eine andere Bezeichnung für `fold`.

Offensichtlich ist die Reihenfolge dabei wichtig:

  * *Filter*: Zunächst findet eine Filterung der Elemente aus einer bestimmten Menge von Elementen statt.
  * *Map*: Danach erfolgt eine Transformation der noch vorhandenen Elemente in einen neuen Datentyp.
  * *Reduce*: Schließlich wird das Zwischenergebnis, eine modifizierte Teilmenge der Ausgangsmenge, auf ein Endergebnis reduziert.

Im Quellcode zu diesem Snippet gibt es Beispiel zum *Filter-Map-Reduce* Pattern:

```cpp
01: // testing 'Filter-Map-Reduce' Pattern
02: class Book 
03: {
04: public:
05:     std::string m_title;
06:     std::string m_author;
07:     int m_year;
08:     double m_price;
09: };
10: 
11: static void test_functional_programming_04() {
12: 
13:     std::list<Book> booksList
14:     {
15:         { "C", "Dennis Ritchie", 1972, 11.99 },
16:         { "Java", "James Gosling", 1995, 19.99 },
17:         { "C++", "Bjarne Stroustrup", 1985, 20.00 },
18:         { "C#", "Anders Hejlsberg", 2000, 29.99 }
19:     };
20: 
21:     // filter books which appeared past 1990
22:     std::vector<Book> booksAfter1990{};
23: 
24:     std::copy_if (
25:         std::begin(booksList),
26:         std::end(booksList),
27:         std::back_inserter(booksAfter1990),
28:         [] (const Book& book) { return book.m_year >= 1990; }
29:     );
30: 
31:     // extract book title
32:     std::vector<std::string> bookTitles{};
33: 
34:     std::transform(
35:         std::begin(booksAfter1990),
36:         std::end(booksAfter1990),
37:         std::back_inserter(bookTitles),
38:         [] (const Book& book) { return book.m_title; }  // convert Book to std::string
39:     );
40: 
41:     // reduce to result string, e.g. comma separated list
42:     std::string titles = std::accumulate(
43:         std::begin(bookTitles),
44:         std::end(bookTitles),
45:         std::string{},
46:         [](std::string a, std::string b) {
47:             std::stringstream ss;
48:             if (a.empty()) {
49:                 ss << b;
50:             }
51:             else {
52:                 ss << a << ", " << b;
53:             }
54:             return ss.str();
55:         }
56:     );
57: 
58:     std::println("Titles: {}", titles);
59: }
```

*Ausgabe*:

```
Titles: Java, C#
```

## Umsetzung in C++ und *Ranges* <a name="link6"></a>


```cpp
01: class Book 
02: {
03: public:
04:     std::string m_title;
05:     std::string m_author;
06:     int m_year;
07:     double m_price;
08: };
09: 
10: static void test_functional_programming_05() {
11: 
12:     std::list<Book> booksList
13:     {
14:         { "C", "Dennis Ritchie", 1972, 11.99 } ,
15:         { "Java", "James Gosling", 1995, 19.99 },
16:         { "C++", "Bjarne Stroustrup", 1985, 20.00 },
17:         { "C#", "Anders Hejlsberg", 2000, 29.99 }
18:     };
19: 
20:     auto results = booksList
21:         | std::ranges::views::filter ([](const Book& book) { return book.m_year < 1990; })
22:         | std::ranges::views::transform([](const Book& book) { return book.m_title; }) 
23:         | std::ranges::views::common;
24: 
25:     // reduce to result string, e.g. comma separated list
26:     std::string titles = std::accumulate(
27:         std::begin(results),
28:         std::end(results),
29:         std::string{},
30:         [](std::string a, std::string b) {
31:             std::stringstream ss;
32:             if (a.empty()) {
33:                 ss << b;
34:             }
35:             else {
36:                 ss << a << ", " << b;
37:             }
38:             return ss.str();
39:         }
40:     );
41: 
42:     std::println("Titles: {}", titles);
43: }
```

*Ausgabe*:

```
Titles: C, C++
```




<!-- 

## Beispiele

Siehe den dazugehörigen [Quellcode zu Variante 1](FunctionalProgramming01.cpp) und [Quellcode zu Variante 2](FunctionalProgramming02.cpp).

## Literaturhinweise

Die Anregungen zu den Beispielen aus diesem Code-Snippet stammen teilweise aus

[Implementing filter and map with C++11](https://bastian.rieck.me/blog/posts/2016/filter_map_cxx11/)<br>(abgerufen am 24.05.2020).

und 

[Funktionale Programmierung](https://www.torsten-horn.de/techdocs/java-lambdas.htm)<br>(abgerufen am 24.05.2020).

Prinzipiell ist diese Materie nicht ganz einfach zu durchdringen.
Zwei Artikel im Netz beschäftigen sich sehr intensiv mit diesem Themenkreis:

[How to Use Class Template Argument Deduction](https://devblogs.microsoft.com/cppblog/how-to-use-class-template-argument-deduction/)

und

[Effective Modern C++ by Scott Meyers: Chapter 1. Deducing Types](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/ch01.html)

-->

---

[Zurück](../../Readme.md)

---
