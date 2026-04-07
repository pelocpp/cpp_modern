# Funktionale Programmierung

[Zurück](../../Readme.md)

---

[Quellcode](FunctionalProgramming.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [*Pure* Funktionen](#link2)
  * [*Partial Application* und *Currying*](#link3)
    * [*Partial Application*](#link4)
    * [*Currying*](#link5)
  * [Funktionen höherer Ordnung](#link6)
  * [*Filter-Map-Reduce* Pattern](#link7)
    * [Umsetzung in C++ und STL](#link8)
    * [Umsetzung in C++ und *Ranges*](#link9)

---

## Allgemeines <a name="link1"></a>

C++ ist eine &bdquo;prozedurale, objektorientierte und generische Programmiersprache&rdquo; und keine &bdquo;funktionale Programmiersprache&rdquo;.
Mit den Neuerungen des so genannten &bdquo;Modern C++&rdquo; lassen sich aber auch
Aspekte der &bdquo;funktionalen Programmierung&rdquo; in C++ darstellen.

&bdquo;Funktionen&rdquo; ähneln Methoden. Aber anders als Methoden werden Funktionen bei der &bdquo;funktionalen Programmierung&rdquo; weitergereicht, beispielsweise als Argumente an Methoden oder als Return-Wert einer Methode.
Dies ist in C++ spätestens seit Einführung der Lambda-Funktionen auch möglich.

&bdquo;Rein funktionale Sprachen&rdquo; (&bdquo;*Pure functional languages*&rdquo;) wie beispielsweise *Haskell* sind zustandslos und Funktionen haben keine Seiteneffekte.
Sie ändern keine Daten, sondern können höchstens neue Daten als Resultat einer Funktion zurückliefern.
Das ist natürlich bei C++ anders. Hier können Funktionen durchaus Daten ändern.

&bdquo;Rein funktionale Programmierung&rdquo; eignet sich ideal zur Parallelverarbeitung sowie für mathematische Aufgaben und steht in dem Ruf,
dass auf diese Weise erstellte Programme weniger fehleranfällig sind.
Nachteilig ist, dass sich reale Objekte und Zustandsänderungen nur schwierig abbilden lassen, was die Programmierung realer Vorgänge und Geschäftsprozesse erschwert.
Dies ist eben das Terrain der objektorientierten zustandsbehafteten Programmierung.


## *Pure* Funktionen <a name="link2"></a>

Eine &bdquo;Pure Function&rdquo; (&bdquo;reine Funktion&rdquo;) ist im Grunde eine Funktion,
die sich wie eine mathematische Formel verhält. Sie zeichnet sich durch zwei Hauptmerkmale aus: 

  * Determinismus:<br />Bei gleichen Eingabewerten liefert sie immer das gleiche Ergebnis.
  * Keine Nebenwirkungen (*Side Effects*):<br />Sie verändert keine globalen Variablen, schreibt nicht in Dateien
    und manipuliert keine Daten durch übergebene Referenzen oder Zeiger.

Schauen wir uns ein einfaches Beispiel an, um dieses Konzept zu verdeutlichen.
Nehmen wir an, wir haben es mit `User`-Objekten in einem Programm zu tun und
jedes `User`-Objekt enthält das mit dem Benutzer verknüpfte Alter.

```cpp
01: class User
02: {
03: public:
04:     std::string m_name;
05:     std::string m_phone;
06:     std::size_t m_age;
07: };
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
06:         .m_phone{ "12345678" },
07:         .m_age{ 25 }
08:     };
09: 
10:     auto updated{ pureUpdateAge(john) };
11:     std::println("Age: {}", updated.m_age);
12: 
13:     updated = pureUpdateAge(john);
14:     std::println("Age: {}", updated.m_age);
15: }
```

*Ausgabe*:

```
Age: 26
Age: 26
```

Es wird in der funktionalen Programmierung als großer Vorteil angesehen,
wenn sich eine Funktion bei jedem Aufruf für dieselben Eingabedaten gleich verhält.


## *Partial Application* und *Currying* <a name="link3"></a>

### *Partial Application* <a name="link4"></a>

In C++ bedeutet *Partial Application*, einige Argumente einer Funktion festzulegen
und eine neue Funktion zu erzeugen, die die verbleibenden Argumente entgegennimmt.
Lambdas ermöglichen dies auf eine sehr natürliche und einfache Weise.

*Beispiel*:

```cpp
01: int add(int a, int b) {
02:     return a + b;
03: }
04: 
05: void test()
06: {
07:     auto addFive = [](int b) {
08:         return add(5, b);  // partially applied: a = 5
09:     };
10: 
11:     auto result{ addFive(3) };
12:     std::print("{} ", result);
13: }
```

*Ausgabe*:

```
8
```

Der Wert 5 war im letzten Beispiel im Aufruf der freien Funktion `addFive` gewissermaßen einprogrammiert.
Das kann man flexibler mit Lambdas und deren Erfassungsklausel gestalten:

*Beispiel*:

```cpp
01: auto partialAdd(int a) {
02:     return [a](int b) {
03:         return a + b;
04:     };
05: }
06: 
07: void test()
08: {
09:     auto addTen = partialAdd(10);
10:     auto result{ addTen(5) };
11:     std::print("{} ", result);
12: }
```

*Ausgabe*:

```
15
```

Noch immer haben wir eine freie Funktion beteiligt (`partialAdd`). Es geht aber auch ganz ohne freie Funktionen:


*Beispiel*:

```cpp
01: void test()
02: {
03:     auto partialAdd = [](int a) {
04:         return [a](int b) {
05:             return a + b;
06:         };
07:     };
08: 
09:     auto addTwenty = partialAdd(20);
10:     auto result{ addTwenty(10) };
11:     std::print("{} ", result);
12: }
```

*Ausgabe*:

```
30
```

Die Idee hinter *Partial Application*, einige Parameter in einer neuen Funktion (ggf. Lambda) zu fixieren
und die anderen später beim Aufruf bereitzustellen, lässt sich verallgemeinern.
Im folgenden werden mehrere neue &bdquo;partielle&rdquo; Funktionen auf Basis der vorhandenen Funktion `partialAdd` gebildet:

```cpp
01: void test()
02: {
03:     auto partialAdd = [](int a) {
04:         return [a](int b) {
05:             return a + b;
06:             };
07:         };
08: 
09:     auto addTen = partialAdd(10);
10:     auto addTwenty = partialAdd(20);
11:     auto addThirty = partialAdd(30);
12: 
13:     auto result{ 0 };
14: 
15:     result= addTen(10);
16:     std::println("{} ", result);
17: 
18:     result = addTwenty(10);
19:     std::println("{} ", result);
20: 
21:     result = addThirty(10);
22:     std::println("{} ", result);
23: }
```

*Ausgabe*:

```
20
30
40
```

Das Thema der *Partial Application* wird mit mehreren Argumenten interessanter:

```cpp
01: auto multiply(auto a, auto b, auto c) {
02:     return a * b * c;
03: }
04: 
05: void test()
06: {
07:     auto multiply_By_5_and_10 = [](int c) {
08:         return multiply(5, 10, c);  // partially applied: a=5, b=10
09:     };
10: 
11:     auto result{ multiply_By_5_and_10(15) };
12: 
13:     std::println("5*10*15={} ", result);    // output: 750
14: }
```

*Ausgabe*:

```
5*10*15=750
```

*Bemerkung*: Kernidee der *Partial Application*<br />
  * Die Kernidee der *Partial Application* besteht darin, einige Argumente einer Funktion vorab festzulegen, die restlichen Argumente später beim Aufruf hinzuzufügen.
  * Mit Lambdas kann dies sehr elegant umgesetzt werden: Die festgelegten Argumente werden auf die Erfassungsklausel abgebildet, die restlichen auf die Parameter des Aufrufs.


### *Currying* <a name="link5"></a>

Die Hauptunterschiede zwischen *Partial Application* und *Currying* sind:

  * *Partial Application*:<br />
  Man nimmt eine Funktion mit mehreren Argumenten und legt einige von ihnen vorab fest &RightArrow; man erhält eine neue Funktion mit weniger Argumenten.
  * *Currying*:<br />
  Man transformiert eine Funktion so, dass sie immer nur ein Argument entgegennimmt und jedes Mal eine neue Funktion zurückgibt.

Zum *Currying* betrachten wir nun einige Beispiele:


```cpp
01: auto addRegular(auto a, auto b) {
02:     return a + b;
03: }
04: 
05: auto addCurried = [](auto a) {
06:     return [a](auto b) {
07:         return a + b;
08:     };
09: };
10: 
11: void test_01()
12: {
13:     auto result{ addCurried(5)(5) };
14: 
15:     std::println("{} ", result);
16: }
17: 
18: void test_02()
19: {
20:     auto addFive{ addCurried(5) };
21: 
22:     auto result{ addFive(10) };
23: 
24:     std::println("{} ", result);
25: }
```

*Ausgabe*:

```
10
15
```

Was kann man beobachten?

Eine &bdquo;reguläre&rdquo; Addition zweier ganzer Zahlen würde so aussehen:

```cpp
auto result{ addRegular(5, 10) };
```

In der Variante mit *Currying*:

```cpp
auto result{ addCurried(5)(5) };
```

Die Funktion wird in eine Kette von Funktionen und Funktionsaufrufen mit jeweils einem Argument umgewandelt.

In einer Art intuitiven Betrachtung könnte man auch sagen:

  * *Partial Application*: &bdquo;Ich kenne bereits einige Eingaben &ndash; fixiere sie.&rdquo;
  * *Currying*: &bdquo;Lass uns die Funktion so umgestalten, dass die Eingaben nacheinander erfolgen.&rdquo;

Wir betrachten auch beim *Currying* ein Beispiel mit mehreren Parametern:

```cpp
01: auto addMoreCurried(int a) {
02:     return [a] (int b) {
03:         return [a, b](int c) { 
04:             return a + b + c;
05:         };
06:     };
07: }
08: 
09: void test()
10: {
11:     auto result{ addMoreCurried(1)(2)(3) };
12:     std::println("{} ", result);
13: }
```

*Ausgabe*:

```
6
```

Von Interesse ist die Funktion `addMoreCurried`: Sie besitzt einen Parameter `a`,
dessen Wert von einem Lambda erfasst wird. Dieser Lambda ist das Ergebnis der `addMoreCurried`-Funktion.

Das zurückgelieferte Lambdaobjekt besitzt ebenfalls einen Parameter (hier: `b`),
der ebenfalls von einem unterlagerten Lambda erfasst wird. Dieses nochmals unterlagerte Lambdaobjekt 
hat über die Erfassungsklausel Zugriff auf die beiden Parameter `a` und `b` und besitzt selbst einen Parameter `c`.

Dieses Spiel könnte man natürlich beliebig weit treiben. Wir demonstrieren den Zugriff auf die vorhandenen Lambdas
in einer alternativen Formulierung der letzten `test`-Funktion:

```cpp
01: void test()
02: {
03:     auto addToOne{ addMoreCurried(1) };
04: 
05:     auto addToThree{ addToOne(2) };
06: 
07:     auto result{ 0 };
08:     result = addToThree(3);
09:     std::println("{} ", result);
10: 
11:     result = addToThree(4);
12:     std::println("{} ", result);
13: }
```


*Ausgabe*:

```
6
7
```

In dieser Funktion extrahieren wir die zwei Lamba-Objekte zunächst manuell.
`addToOne` ist das erste Lambdaobjekt, in seiner Erfassungsklausel wird der Wert `1` abgespeichert.
`addToThree` ist das zweite Lambdaobjekt, in seiner Erfassungsklausel wird der Wert `2` abgespeichert.

Da nun immer die zwei Werte `1` und `2` als Summe (`3`) im Endergebnis berücksichtigt werden,
habe ich die beiden Lambdas mit den entsprechenden Namen `addToOne` und `addToThree` versehen.

Das zweite Lambdaobjekt können wir nun mit unterschiedlichen Parametern aufrufen,
in unserem Beispiel mit den Werten `3` und `4`. Damit erhalten wir die erwarteten Summenwerte `6` und `7` als Endergebnis.

Das letzte Beispiel mit den geschachtelten Lambdaobjekten wollen wir zum Abschluss noch auf 
eine andere Weise analysieren. &bdquo;Lambdas&rdquo; werden auf aufrufbare Objekte vom Compiler abgebildet.
Wie würde dies am Beispiel der Funktion `addMoreCurried` aussehen?


```cpp
01: void test()
02: {
03:     class OuterLambda
04:     {
05:     private:
06:         class MiddleLambda
07:         {
08:         private:
09:             class InnerLambda
10:             {
11:             public:
12:                 inline int operator()(int c) const
13:                 {
14:                     return (m_a + m_b) + c;
15:                 }
16: 
17:             private:
18:                 int m_a;
19:                 int m_b;
20: 
21:             public:
22:                 InnerLambda(int a, int b) : m_a{ a }, m_b{ b } {}
23:             };
24: 
25:         public:
26:             inline InnerLambda operator()(int b) const
27:             {
28:                 InnerLambda tmp{ m_a, b };
29:                 return tmp;
30:             }
31: 
32:         private:
33:             int m_a;
34: 
35:         public:
36:             MiddleLambda(int a) : m_a{ a } {}
37:         };
38: 
39:     public:
40:         inline MiddleLambda operator()(int a) const
41:         {
42:             MiddleLambda tmp{ a };
43:             return tmp;
44:         }
45:     };
46: 
47:     // longer, explanatory syntax
48:     auto firstLambda{ OuterLambda{} };
49:     auto secondLambda{ firstLambda(21) };
50:     auto thirdLambda{ secondLambda(22) };
51:     auto result1{ thirdLambda(23) };
52:     std::println("{} ", result1);
53: 
54:     // short syntax
55:     OuterLambda lambda = OuterLambda{};
56:     auto result2{ lambda(10)(11)(12) };
57:     std::println("{} ", result2);
58: }
```


*Ausgabe*:

```
66
33
```

## Funktionen höherer Ordnung <a name="link6"></a>

Funktionen, die entweder Funktionen als Argument annehmen oder als Ergebnis zurückgeben, werden als
*Funktionen höherer Ordnung* bezeichnet.

Das bedeutet, dass wir Funktionen als Objekte und nicht als eine Reihe von Anweisungen betrachten.

Welchen Unterschied macht das für uns?
Nun, das Einzige, was an dieser Stelle wichtig ist, damit eine Funktion als Objekt behandelt wird,
ist die Fähigkeit, sie an andere Funktionen übergeben zu können.

Es folgt ein Beispiel, wie eine Funktion an eine andere Funktion übergeben werden kann:

```cpp
01: class Function
02: {
03: private:
04:     std::size_t m_state;
05: 
06: public:
07:     Function () : Function{ 0 } {}
08:     Function(std::size_t state) : m_state{ state } {}
09: 
10:     void modify_state(std::size_t state) { m_state = state; }
11:     std::size_t get_state() const { return m_state; }
12: 
13:     void operator()() const {
14:         // do something that a function would do
15:         std::println("Do something using state {}", m_state);
16:     }
17: };
```

Klasse `Function` ist eine Klasse mit einem überladenen Operator `operator()`.

Immer, wenn wir den `operator()` einer Klasse überladen, machen wir Objekte dieser Klasse &bdquo;aufrufbar&rdquo;.
Alles, was aufrufbar ist, wird als Funktion behandelt.

Ein Objekt einer Klasse, das über einen überladenen `operator()` verfügt, kann also als Funktion betrachtet werden.
Das ist in gewisser Weise wie ein Trick, denn anstatt eine Funktion zu einem Objekt zu machen,
haben wir ein Objekt aufrufbar gemacht.


```cpp
01: void doSomething (const Function& f) {
02:     f();
03: }
04: 
05: void test () {
06:     Function func{ 123 };
07:     doSomething(func);
08: }
```

*Ausgabe*:

```
Do something using state 123
```

*Bemerkung*:<br />
Aufrufbare Objekte (*Callables*, Objekte, die den Operator `operator()` überladen) sind nicht die einzige Möglichkeit,
Funktionen als Parameter zu übergeben. Die Hüllenklasse `std::function` und Lambda-Objekte sind weitere Kandidaten in C++,
um diese Wirkung zu erzielen.


## *Filter-Map-Reduce* Pattern <a name="link7"></a>

Die Klassiker aus der funktionalen Programmierung sind die drei
Funktionen `map`, `filter` und `reduce`. Diese drei Funktionen höherer Ordnung werden über eine weitere 
Funktion parametrisiert und wenden diese sukzessive auf die Elemente eines Containers an. In C++ bieten sich an dieser Stelle
speziell Lambda-Funktionen an.

  * `map` &ndash; Transformation der Elemente. Dabei entsteht eine neue Menge von Elementen (derselben Anzahl), die typischerweise
    einen anderen Datentyp haben. So können zum Beispiel Umrechnungen oder Umwandlungen durchgeführt werden.
  * `filter` &ndash; Filterung gewünschter Elemente aus einer Menge von Elementen (Container).
    Der Datentyp der Elemente bleibt derselbe, aber die Menge der Elemente des Ursprungscontainers wird reduziert.
  * `reduce` &ndash; Reduktion der Elemente eines Containers auf ein Endergebnis (Resultat). Typischerweise wird eine Lambda-Funktion
    mit zwei Argumenten auf ein Element des Containers und das vorangehende Zwischenergebnis angewendet.

### Umsetzung in C++ und STL <a name="link8"></a>

In einer ersten Näherung finden wir die drei Funktionen höherer Ordnung auch in C++
bei genauem Hinsehen in den STL-Algorithmen vor:

  * `map` &ndash; ähnlich zu `std::transform`.
  * `filter` &ndash; ähnlich zu `std::copy_if`.
  * `reduce` &ndash; ähnlich zu `std::accumulate`.


*Ein Beispiel*:

```cpp
01: class Book 
02: {
03: public:
04:     std::string m_title;
05:     std::string m_author;
06:     std::size_t m_year;
07:     double      m_price;
08: };
09: 
10: void test () {
11: 
12:     std::list<Book> booksList
13:     {
14:         { "C", "Dennis Ritchie", 1972, 11.99 },
15:         { "Java", "James Gosling", 1995, 19.99 },
16:         { "C++", "Bjarne Stroustrup", 1985, 20.00 },
17:         { "C#", "Anders Hejlsberg", 2000, 29.99 }
18:     };
19: 
20:     // filter books which appeared past 1990
21:     std::vector<Book> booksAfter1990{};
22: 
23:     std::copy_if (
24:         std::begin(booksList),
25:         std::end(booksList),
26:         std::back_inserter(booksAfter1990),
27:         [] (const Book& book) { return book.m_year >= 1990; }
28:     );
29: 
30:     // extract book title
31:     std::vector<std::string> bookTitles{};
32: 
33:     std::transform(
34:         std::begin(booksAfter1990),
35:         std::end(booksAfter1990),
36:         std::back_inserter(bookTitles),
37:         [] (const Book& book) { return book.m_title; }  // convert Book to std::string
38:     );
39: 
40:     // reduce to result string, e.g. comma separated list
41:     std::string titles{
42:         std::accumulate(
43:             std::begin(bookTitles),
44:             std::end(bookTitles),
45:             std::string{},
46:             [](const std::string& a, const std::string& b) {
47:                 return a.empty() ? b : std::format("{}, {}", a, b);
48:             }
49:         ) 
50:     };
51: 
52:     std::println("Titles: {}", titles);
53: }
```

*Ausgabe*:

```
Titles: Java, C#
```

### Umsetzung in C++ und *Ranges* <a name="link9"></a>

*Ein Beispiel*:


```cpp
01: class Book 
02: {
03: public:
04:     std::string m_title;
05:     std::string m_author;
06:     std::size_t m_year;
07:     double      m_price;
08: };
09: 
10: void test() {
11: 
12:     std::list<Book> booksList
13:     {
14:         { "C", "Dennis Ritchie", 1972, 11.99 } ,
15:         { "Java", "James Gosling", 1995, 19.99 },
16:         { "C++", "Bjarne Stroustrup", 1985, 20.00 },
17:         { "C#", "Anders Hejlsberg", 2000, 29.99 }
18:     };
19: 
20:     auto results {
21:         booksList
22:         | std::ranges::views::filter([](const Book& book) { return book.m_year >= 1990; })
23:         | std::ranges::views::transform([](const Book& book) { return book.m_title; })
24:         | std::ranges::views::common 
25:     };
26: 
27:     // reduce to result string, e.g. comma separated list
28:     std::string titles{
29:         std::accumulate(
30:             std::begin(results),
31:             std::end(results),
32:             std::string{},
33:             [](const std::string& a, const std::string& b) {
34:                 return a.empty() ? b : std::format("{}, {}", a, b);
35:             }
36:         ) 
37:     };
38: 
39:     std::println("Titles: {}", titles);
40: }
```

*Ausgabe*:

```
Titles: Java, C#
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
