# STL Algorithmen `std::all_of`, `std::any_of` und `std::none_of`

[Zurück](../../Readme.md)

---

[Quellcode](AllOfAnyOfNoneOf.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [`std::all_of`](#link2)
  * [`std::any`](#link3)
  * [`std::none_of`](#link4)
  * [*Short Circuit Evaluation*](#link5)
  * [Drei weitere Beispiele](#link6)

---

## Allgemeines <a name="link1"></a>

Am einfachsten lassen sie sich diese drei Hilfsalgorithmen anhand einer Frage unterscheiden, die sie beantworten:

  * `std::all_of` &RightArrow; Erfüllen alle Elemente eine bestimmte Bedingung?
  * `std::any_of` &RightArrow; Erfüllt mindestens ein Element eine bestimmte Bedingung?
  * `std::none_of` &RightArrow; Erfüllt kein Element eine bestimmte Bedingung?

---

## `std::all_of` <a name="link2"></a>

*Beispiel*:

```cpp
01: void std_all_of()
02: {
03:     std::vector<int> numbers{ 2, 4, 6, 8 };
04: 
05:     bool result = std::all_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) { return n % 2 == 0; }
09:     );
10: 
11:     std::println("Result: {}", result); // result == true
12: }
```

Hier lautet die Fragestellung: &bdquo;Sind alle Zahlen gerade?&rdquo;

Ja, das Ergebnis ist in diesem Beispiel wahr.

---

## `std::any_of` <a name="link3"></a>

*Beispiel*:

```cpp
01: void std_any_of()
02: {
03:     std::vector<int> numbers{ 1, 3, 4, 7 };
04: 
05:     bool result = std::any_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) { return n % 2 == 0; }
09:     );
10: 
11:     std::println("Result: {}", result); // result == true
12: }
```

Hier fragen wir: &bdquo;Gibt es mindestens eine gerade Zahl?&rdquo;

Ja, 4 ist gerade, also ist das Ergebnis wahr.

Wichtig ist: Es spielt keine Rolle, dass die anderen Zahlen ungerade sind.

---

## `std::none_of` <a name="link4"></a>

*Beispiel*:

```cpp
01: void std_none_of()
02: {
03:     std::vector<int> numbers{ 1, 3, 5, 7 };
04: 
05:     bool result = std::none_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) { return n % 2 == 0; }
09:     );
10: 
11:     std::println("Result: {}", result); // result == true
12: }
```

Wir fragen: Gibt es keine geraden Zahlen?

Ja, keine der Zahlen ist gerade, daher ist das Ergebnis wahr.

Eine gute Eselsbrücke ist:

`std::all_of` &RightArrow; Bedingung für alle Elemente erfüllt.<br />
`std::any_of` &RightArrow; Bedingung für mindestens ein Element erfüllt.<br />
`std::none_of` &RightArrow; Bedingung für kein Element erfüllt.

---

## *Short Circuit Evaluation* <a name="link5"></a>

Unterstützen diese drei Algorithmen eine Art &bdquo;*Short Circuit Evaluation*&rdquo;?

Ja &ndash; alle drei weisen dieses optimierende Verhalten auf, sprich sie beenden die Ausführung,
wenn das Endergebnis bereits vorzeitig bekannt ist.

Man kann sie sich also fast wie die logischen Operatoren `&&` und `||` vorstellen:

| Algorithmus | *Short Circuit Evaluation* |
|:-|:-|
| `std::all_of`  | &#x2258; `condition1` && `condition2` && `condition3` ... | 
| `std::any_of`  | &#x2258; `condition1` &#124;&#124; `condition2` &#124;&#124; `condition3` ... |
| `std::none_of` | &#x2258; `!condition1` && `!condition2` && `!condition3` ... | 

*Tabelle* 1: *Short Circuit Evaluation* von `std::all_of`, `std::any_of` und `std::none_of`.

#### `std::all_of`

Hält bei dem ersten Element an, das die Bedingung nicht erfüllt.

*Beispiel*:

```cpp
01: void std_all_of_short_circuit()
02: {
03:     std::vector<int> numbers{ 2, 4, 5, 8, 10 };
04: 
05:     bool result = std::all_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) {
09:             return n % 2 == 0;
10:         }
11:     );
12: }
```

Es gibt keinen Grund, 8 oder 10 zu untersuchen, da wir bereits mit Wert 5 wissen, dass nicht alle Elemente die Bedingung erfüllen.

---

#### `std::any_of`

Hält bei dem ersten Element an, das die Bedingung erfüllt.

*Beispiel*:

```cpp
01: void std_any_of_short_circuit()
02: {
03:     std::vector<int> numbers{ 1, 3, 4, 7, 9 };
04: 
05:     bool result = std::any_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) {
09:             return n % 2 == 0;
10:         }
11:     );
12: }
```

Auch hier wissen wir bereits, dass mindestens ein Element (hier: Element 4) die Bedingung erfüllt.

---

#### `std::none_of`

Hält bei dem ersten Element an, das die Bedingung erfüllt.

*Beispiel*:

```cpp
01: void std_none_of_short_circuit()
02: {
03:     std::vector<int> numbers{ 1, 3, 4, 7, 9 };
04: 
05:     bool result = std::none_of(
06:         numbers.begin(),
07:         numbers.end(),
08:         [](int n) {
09:             return n % 2 == 0;
10:         }
11:     );
12: }
```

Da `std::none_of` prüft, ob kein Element die Bedingung erfüllt, genügt es, ein einziges solches Element zu finden, um `false` zurückzugeben.
Dies ist in diesem Beispiel beim Wert 4 der Fall.

---

## Drei weitere Beispiele <a name="link6"></a>

  * `std::all_of` &ndash; Wir validieren Benutzerkonten, bevor wir einen Batch-Vorgang zulassen. Die Frage lautet: Sind alle Nutzer volljährige Personen mit verifizierten E-Mail-Adressen?
	Dies ist eine sehr natürliche Verwendung von `std::all_of`: &bdquo;Erfüllt der gesamte STL Container eine bestimmte Anforderung&rdquo;?
  * `std::any_of` &ndash; Erkennen, ob etwas Aufmerksamkeit erfordert. In Bezug auf das Beispiel von unten: &bdquo;Gibt es mindestens einen Auftrag, der Aufmerksamkeit erfordert&rdquo;?
  * `std::none_of` &ndash; Sicherstellen, dass eine Sammlung keine ungültigen Elemente enthält. In Bezug auf das Beispiel von unten: &bdquo;Gibt es keine .exe-Dateien&rdquo;?


*Beispiel*:

```cpp
01: void std_all_of_example()
02: {
03:     struct User {
04:         std::string name;
05:         int age;
06:         bool emailVerified;
07:     };
08: 
09:     std::vector<User> users {
10:         { "Alice", 32, true },
11:         { "Bob", 25, true },
12:         { "Charlie", 17, true },
13:         { "Diana", 41, true }
14:     };
15: 
16:     bool allValid = std::all_of(
17:         users.begin(),
18:         users.end(),
19:         [](const User& user) {
20:             return user.age >= 18 && user.emailVerified;
21:         }
22:     );
23: 
24:     std::println("Are all users adults with verified email addresses? {}", allValid);
25: }
```

*Ausgabe*:

```
Are all users adults with verified email addresses? false
```

*Beispiel*:

```cpp
01: void std_any_of_example()
02: {
03:     struct Job {
04:         int id;
05:         int priority;
06:         bool failed;
07:     };
08: 
09:     std::vector<Job> jobs{
10:         { 101, 1, false },
11:         { 102, 2, false },
12:         { 103, 5, true },
13:         { 104, 3, false }
14:     };
15: 
16:     bool needsAttention = std::any_of(
17:         jobs.begin(),
18:         jobs.end(),
19:         [](const Job& job) {
20:             return job.failed || job.priority >= 5;
21:         }
22:     );
23: 
24:     std::println("Is there at least one job that needs attention? {}", needsAttention);
25: }
```

*Ausgabe*:

```
Is there at least one job that needs attention? true
```

*Beispiel*:

```cpp
01: void std_none_of_example()
02: {
03:     std::vector<std::string> filenames{
04:         "report.pdf",
05:         "photo.jpg",
06:         "data.csv",
07:         "virus.exe"
08:     };
09: 
10:     bool safe = std::none_of(
11:         filenames.begin(),
12:         filenames.end(),
13:         [](const std::string& filename) {
14:             return filename.ends_with(".exe");
15:         }
16:     );
17: 
18:     std::println("Are there no .exe files? {}", safe);
19: }
```

*Ausgabe*:

```
Are there no .exe files? false
```

---

[Zurück](../../Readme.md)

---
