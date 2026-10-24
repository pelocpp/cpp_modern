# Legacy

[Zurück](../../Readme.md)

---

WEITER: Hier die Inhaltsangabe .................

---


## Zuerst die Grundregeln

  * Modernisiere schrittweise:<br />
   Aber nur dort, wo es sich auszahlt &ndash; und niemals auf einen Schlag im Rahmen einer kompletten Neuentwicklung
(sogenanntes &bdquo;*Big-Bang Rewrite*&rdquo;).

  * Erstelle Tests für den betroffenen Code, bevor irgendetwas geändert wird:<br />
Sogenannte &bdquo;Characterization Tests&rdquo; (die das aktuelle Verhalten erfassen und festschreiben)
sind wichtiger als jedes spezifische Sprachfeature.

  * Hebe den Standard schrittweise an:<br />
Kompilieren Sie den Code zunächst mit C++11, dann mit C++14, C++17 usw.
Beheben Sie bei jedem Schritt die auftretenden Warnungen.
Ein direkter Sprung auf C++20 oder höhrt macht es schwieriger, Fehler ihren jeweiligen Ursachen zuzuordnen.

  * Nutze Werkzeuge:<br />
`clang-tidy` bietet eine Reihe von &bdquo;modernize-*&rdquo;-Prüfungen
(z. B. `modernize-use-override`, `modernize-use-nullptr`, `modernize-loop-convert`, `modernize-use-auto`, `modernize-make-unique` usw.),
die den Großteil der mechanischen Arbeit sicher erledigen.

  * *Sanitizer* (ASan/UBSan):<br />
Setze Sanitizer (ASan/UBSan) ein und verwende die Compiler-Flags `-Wall` sowie `-Wextra`,
um Probleme aufzudecken, die im alten Code bisher unbemerkt blieben.

  * Ändere nur Code, an dem ohnehin gerade gearbeitet wird:<br />
Modernisiere keine stabilen, unangetasteten Module allein aus stilistischen Gründen.

## Hoher Nutzen, geringes Risiko (C++11-Grundlagen)

#### 1. Versehentliches Kopieren statt Gebrauch einer Referenz

```cpp
01: class Person
02: {
03: private:
04:     std::string m_name;
05: 
06: public:
07:     // c'tor
08:     Person(const std::string& name) : m_name(name) {}
09: 
10:     // setter
11:     void setName(std::string name) { m_name = name; }
15: };
```

Der *setter* kann besser geschrieben werden:

```cpp
void setName(const std::string& name) { m_name = name; }
```

#### 2. Versehentliches Kopieren statt Gebrauch einer Referenz - bei Rückgabe von Werten

```cpp
01: class Person
02: {
03: private:
04:     std::string m_name;
05: 
06: public:
07:     // c'tor
08:     Person(const std::string& name) : m_name(name) {}
12: 
13:     // getter
14:     std::string getName() { return m_name; }
15: };
```

Der *getter* kann besser geschrieben werden:

```cpp
const std::string& getName() { return m_name; }
```

#### 3. `nullptr` statt `NULL` / `0`.

Das Kernproblem: `NULL` ist eine ganzzahlige Konstante.

In C++98 ist `NULL` als `0` (bzw. `0L` oder &ndash; bei GCC &ndash; als `__null`) definiert;
es handelt sich also um eine Ganzzahlkonstante, nicht um einen Zeiger. Dies führt zu mehreren konkreten Problemen.

1. Bei der &bdquo;*Overload Resolution*&rdquo; wird die falsche Funktion gewählt.

```cpp
01: void log(int code) {}
02: void log(const char* msg) {}
03: 
04: log(NULL);     // calls log(int)! (or is ambiguous, depending on the compiler)
05: log(nullptr);  // calls log(const char*), as intended
```

Bei `NULL` erhält man &ndash; ohne dass dies explizit gemeldet wird &ndash; entweder die Überladung für Ganzzahlen oder einen Fehler
wegen eines &bdquo;mehrdeutigen Aufrufs&rdquo; (&bdquo;*ambiguous call*&rdquo;).

`nullptr` hingegen besitzt einen eigenen Typ,
`std::nullptr_t`, der zwar in jeden Zeigertyp konvertiert werden kann, niemals jedoch in eine Ganzzahl.

2. *Template Forwarding* schlägt fehlt

```cpp
01: void takesPointer(int* ptr) {}
02: 
03: template <typename T>
04: void wrap(T arg) { takesPointer(arg); }
05: 
08: wrap(0);           // T = int; int does NOT convert to a pointer, compile error
09: wrap(NULL);        // same problem, compile error
10: wrap(nullptr);     // T = nullptr_t; converts to any pointer, works
```


#### 4. Schlüsselwörter `override` / `final` für virtuelle Funktionen.<br />

Diese Schlüsselwörter erkennen stillschweigende Signaturkonflikte und sind nahezu kostenlos.
Deklariert man eine Methode mit dem Schlüsselwort `override`, drückt man die Absicht aus,
sie zu überschreiben. 
Daher ist es sinnvoll, `override` an der Stelle anzugeben,
an der man diese Absicht hat.
Dies kann und sollte man dann den Übersetzer auch überprüfen lassen,
nämlich die Absicht, diese Methode zu überschreiben.

Frei nach dem Motto

> **The more things you check at compile time the fewer runtime bugs you have.**

Eine derartige Deklaration reicht dann auch aus, um zu überprüfen,
ob die Methode ursprünglich (in einer der Basisklassen) als `virtual` deklariert wurde
und ob man in der abgeleiteten Klasse die Signatur richtig verwendet hat.

*Beispiel*:

```cpp
01: class Base
02: {
03: public:
04:     virtual void func() { std::println("In base class"); }
05: };
06: 
07: class Derived : public Base
08: {
09: public:
10:     void func(int a)
11:     {
12:         std::println("In derived class");
13:     }
14: };
15: 
16: void test()
17: {
18:     Base base;
19:     Derived derived;
20:     std::println("Compiles successfully");
21: 
22:     Base* bp;
23:     bp = &derived;
24:     bp->func();
25: }
```

*Frage*:<br />
Welche Ausgabe erwarten Sie in der Konsole?

*Ausgabe*:

```
Compiles successfully
In base class
```

#### 5. Bereichsbasierte `for`-Schleife und Verwendung von `auto` für Iteratoren-Boilerplate Code

```cpp
01: // C++98
02: for (std::vector<Order>::const_iterator it = orders.begin(); it != orders.end(); ++it)
03:     total += it->price();
04: 
05: // C++11
06: for (const Order& o : orders)
07:     total += o.price();
```

Die zweite Version lautet &bdquo;für jede Bestellung&rdquo; &ndash; ohne expliziten Gebrauch eines Iteratortyps,
ohne `begin()`/`end()` und ohne `++it`, bei dem man Fehler machen kann.

Herkömmliche Schleifen lassen Fehler zu, die der Compiler nicht erkennt:

  * Vergleiche mit dem `end()` eines anderen Containers (*Copy-and-Paste*-Fehler).
  * `it++` statt `++it` (oder das Vergessen des Inkrements).
  * die Verwendung eines `iterator`-Objekts anstelle eines `const_iterator`-Objekts (oder umgekehrt).
  * &bdquo;Off-by-one&rdquo;-Fehler bei indexbasierten Schleifen (z. B. `i <= v.size()`).

Die &bdquo;Range-based for&rdquo;-Schleife schließt all diese Fehler konstruktionsbedingt aus.

#### 6. Verwendung von `auto`: Refactoring wird einfacher

Wenn jemand `std::vector<Person>` in `std::list<Person>` oder `std::deque<Person>` ändert,
müssen alle explizit ausgeschriebenen Anweisungen mit

`std::vector<Person>::const_iterator`-Variablen

angepasst werden:

```cpp
01: std::vector<Person> persons;   // add comment ...
02: // std::list<Person> persons;  // ... and remove comment
03: 
04: std::vector<Person>::const_iterator it = persons.begin();   // Container-class of iterator must be adjusted
05: 
06: auto it2 = persons.begin();                                 // type of it2 is deducted (at compile time)
```

Bei einer &bdquo;Range-based for&rdquo;-Schleife oder der Verwendung von `auto` spielt das hingegen keine Rolle.

Dasselbe gilt für lange Template-Typen wie `std::map<std::string, std::vector<int>>::const_iterator`:

`auto` übernimmt dies, ohne dass man den Typ selbst ausschreiben muss.

##### Man beachte, was man **nicht** gewinnt

  * Kein Performance-Unterschied. Es wird im Wesentlichen in denselben Code übersetzt wie eine Schleife mit Iteratoren.
  * Keine Verhaltensänderung (sofern die Umstellung korrekt durchgeführt wird).
  * Keine Fehlerbehebungen in bereits funktionierendem Code. Schleifen, die seit Jahren einwandfrei funktionieren, werden nicht plötzlich fehlerhaft.

##### Man beachte, wo Probleme auftreten können

  * Versehentliche Kopien: `for (auto o : orders)` kopiert jedes Element. Verwende stattdessen `const auto&` (oder `auto&`), falls man das Element ändern möchten.
  * Schleifen, die den Iterator selbst verwenden (etwa zum Löschen von Elementen, für `std::distance` oder den Zugriff auf das vorherige bzw. nächste Element), lassen sich nicht einfach umstellen.
  * Wird der Container innerhalb der Schleife verändert, werden &ndash; genau wie zuvor &ndash; die Iteratoren ungültig; eine bereichsbasierte `for`-Schleife (*range-based for loop*) bietet in diesem Fall auch keinen Schutz.


#### 7. Enum-Klassen statt einfacher Enums

Unterschiede im Gültigkeitsbereich, keine implizite `int`-Konvertierung:

```cpp
01: // 1. the problem with classic enums (unscoped enums)
02: enum CarColor { Red, Blue, Green };
03: // enum WineColor { Red, WHITE }; // ERROR: "Red" conflicts with CarColor::Red!
04: 
05: // 2. the solution: Enum classes (scoped enums)
06: enum class TrafficLightPhase { Red, Yellow, Green }; // "Red" and "Green" are safely encapsulated here
07: 
08: enum class SensorStatus { Ok, Error, Red };          // No name conflict with TrafficLightPhase::Red!
09: 
10: static void legacy_enums() {
11: 
12:     // --- DIFFERENCE 1: Scope ---
13:     // with classic enums, the values ??are exported into the surrounding scope:
14:     int myColor = Red;
15: 
16:     // with enum class, the name of the enumeration must be prefixed:
17:     TrafficLightPhase light = TrafficLightPhase::Red;
18: 
19:     SensorStatus sensor = SensorStatus::Red;   // cleanly separated! 
20: 
21:     // --- DIFFERENCE 2: Implicit int conversion ---
22:     // classic enums implicitly convert to int (error-prone!):
23:     if (myColor == 0) {
24:         std::println("This works because Red implicitly becomes 0.");
25:     }
26: 
27:     // enum classes completely prevent this implicit conversion:
28:     // if (light == 0) { } // COMPILER ERROR: No implicit conversion! 
29: 
30:     // if you absolutely need the integer value,
31:     // you must request it explicitly (using static_cast):
32:     if (static_cast<int>(light) == 0) {
33:         std::println("Explicit cast works: TrafficLightPhase::Red is {}", static_cast<int>(light));
34:     }
35: }
```

### 8. `= delete` statt des Tricks mit dem &bdquo;privaten undefinierten Kopierkonstruktor&rdquo;

Gegen private Konstruktoren spricht zunächst einmal nichts, wenn sie ihren eigentlichen Zweck erfüllen &ndash; wie
etwa beim *Singleton*-Pattern oder bei *Factory*-Methoden, wo die Instanziierung bewusst kontrolliert werden soll.

Wenn es aber rein darum geht, das Kopieren oder Verschieben eines Objekts zu verhindern,
ist der alte Trick mit dem privaten, undefinierten Kopierkonstruktor (aus C++ 98&ndash;Zeiten) heute veraltet.
Seit C++ 11 ist `= delete` der Standard.

| Kriterium | Alter C++98 Trick (`private` | Moderner C++11 Weg (`= delete`) | 
|:- |:-|:-|
| Fehlermeldung | Spät und kryptisch. Oft erst beim Linken, falls innerhalb der Klasse kopiert wird. | Sofort und klar verständlich. Fehlermeldung direkt beim Kompilieren mit exakter Zeilenangabe. |
| Lesbarkeit (Intention) | Der Entwickler muss raten, ob das Absicht ist oder noch implementiert wird. | Explizit. Drückt die Design-Entscheidung sofort unmissverständlich aus. |

*Tabelle* 1: Zuordnung der Klassen

### `= default` für triviale spezielle Member


6. Aliase statt typedef verwenden und >> in verschachtelten Templates ohne Leerzeichen.

7. static_assert verwenden, um Annahmen zur Kompilierzeit zu dokumentieren und durchzusetzen.

8. constexpr statt Makros für Konstanten und kleine Funktionen zur Kompilierzeit verwenden; ersetzt auch viele #define-Konstanten.

9. noexcept verwenden, wo angebracht (insbesondere bei Verschiebeoperationen und Destruktoren).


## Der größte Gewinn: Ownership und Ressourcenmanagement

C++ 98&ndash;Code enthält typischerweise direkte `new`/`delete`-Aufrufe, manuelle Ressourcenbereinigung sowie `std::auto_ptr`.

Hier verbergen sich die meisten echten Fehler (Leaks, Double-Frees, Lücken in der Exception-Sicherheit).
Daher ist dies die lohnendste Änderung, erfordert aber auch die größte Sorgfalt.
Gehen Sie dabei modulweise vor und setzen Sie Tests ein.

### 1. Ersetze `std::auto_ptr` durch `std::unique_ptr`

Da `std::auto_ptr` in C++17 entfernt wurde, ist dieser Schritt langfristig zwingend erforderlich.

### 2. Klassen `std::unique_ptr` und `std::shared_ptr`

Für besitzende (&bdquo;owning&rdquo;) Rohzeiger gilt: Verwende `std::unique_ptr` (bei exklusivem Besitz) oder
`std::shared_ptr` (nur wenn der Besitz tatsächlich geteilt wird).

Erstelle diese Objekte mittels `std::make_unique` (ab C++14) oder `std::make_shared`.

### 3. Nicht-besitzende (&bdquo;non-owning&rdquo;) Rohzeiger können beibehalten werden

Es ist nicht erforderlich, jeden Zeiger in einen Smart Pointer umzuwandeln &ndash; dies wäre eine unnötige Überkorrektur.

### 4. Nutze RAII-Wrapper für Ressourcen wie Dateien, Locks oder Handles

Nutze RAII-Wrapper Klassen wie z. B. `std::lock_guard` / `std::scoped_lock`, `std::fstream` oder `std::unique_ptr` mit benutzerdefinierten &bdquo;Deletern&rdquo;.

### 5. Verwenden Sie Container bzw. die STL anstelle von manuell verwalteten Arrays

Setze auf `std::vector` oder `std::array` statt auf `new[]`/`delete[]` oder C-Arrays.



## Performanz and API Cleanliness

### 1. Move-Semantik (Rvalue-Referenzen)

Die Rückgabe großer Objekte per Wert wird effizienter. Füge Move-Konstruktoren/Zuweisungen hinzu, wenn Klassen Ressourcen besitzen (folge nach Möglichkeit der Nullregel: Wenn Member sich selbst verwalten, benötigst du keine speziellen Member).

### 2. `emplace_back` / `emplace`

Verwende `emplace_back` / `emplace` anstelle der Erstellung eines temporären Objekts und dessen Zuweisung

### 3. `std::unordered_map` / `unordered_set`

Verwende `std::unordered_map` / `unordered_set`, wenn keine Reihenfolge (Sortierung) erforderlich ist.

### 4. Einheitliche Initialisierung

Einheitliche Initialisierung `{}` und Initialisierungslisten für eine übersichtlichere Konstruktion.

Beachte auf den Fehler `std::vector<int>{3, 4}` vs. `std::vector<int>(3, 4)` und verringere Konvertierungen, die nun Fehler verursachen.

### 5. Vererbung von Konstruktoren

Delegiere und vererbe Konstruktoren, um doppelten Initialisierungscode zu vermeiden.

### 6. Standard-Member-Initialisierer

Verwende Standard-Member-Initialisierer (`int count = 0;`), um Konstruktoren zu vereinfachen.


## Ersetzen von Eigenentwicklungen durch die Standardbibliothek

1. Lambdas anstelle von Funktor-Klassen oder `bind1st`/`bind2nd`. Sie sind im Zusammenhang mit `std::sort`, `std::find_if` usw. deutlich besser lesbar.

2. `std::function` anstelle von rohen Funktionszeigern in Kombination mit `void*`-Benutzerdaten.

3. `<chrono>`, `<thread>`, `<mutex>`, `<atomic>`, `<future>` anstelle von plattformspezifischem Code (wie `pthread` oder Win32-APIs). Dies bedeutet oft einen erheblichen Gewinn an Portabilität.
`<random>` anstelle von `rand()`.

4. `std::string_view` (C++17) für schreibgeschützte String-Parameter

5. `std::optional`, `std::variant` und `std::any` als Ersatz für Sentinel-Werte, getaggte Unions sowie `void*`.

6. `std::filesystem` (C++17) anstelle von selbst implementierter Pfadbehandlung.

7. Strukturierte Bindungen (*Structured Binding*) (C++17) für Paare, Tupel oder die Iteration über Maps.

8. `[[nodiscard]]`, `[[maybe_unused]]` und `[[fallthrough]]` zur selbsterklärenden Kennzeichnung der Absicht.

9. `std::expected` (C++23) zur Fehlerbehandlung ohne Exceptions.

---

## Worauf Sie achten sollten:

Verhaltensänderungen: Der Umstieg auf C++11+ verändert einige Semantiken, z. B.

Details zur Auswertungsreihenfolge,
implizite Verschiebung,
Typverengung in geschweiften Klammern {},
unerwartete automatische Typableitung,
entfernte Funktionen wie `auto_ptr` und `std::random_shuffle`,
dynamische Ausnahmebehandlungen mit `throw(X)`

Modernisieren Sie nicht um seiner selbst willen. Die Umstellung jeder Schleife auf `auto`/`lambda`-Ausdrücke in Code,
der nicht bearbeitet wird, verursacht unnötigen Aufwand bei Code-Reviews und erhöht das Risiko von Regressionen.

### Verkettung von Methodenaufrufen (geändert in C++17)

Wir betrachten ein Beispiel:

```cpp
std::string s = "I have even sold some";
s.replace(0, 6, "").replace(s.find("even"), 4, "only");
```

Es ist kaum zu glauben, aber: Je nach benutzter C++ Version gibt es  hier unterschiedliche Ergebnisse:

n C++ ist die Reihenfolge, in der Teilausdrücke innerhalb einer Zeile ausgewertet werden,
nicht immer strikt von links nach rechts vorgegeben. Das führt in deinem Beispiel dazu, dass je nach Compiler oder C++-Standard unterschiedliche Ergebnisse herauskommen können.
Das Problem liegt hier konkret beim Aufruf von `s.find("even")`.


#### Warum gibt es mehrere Möglichkeiten?

Schauen wir uns die zweite Zeile genau an. Sie besteht aus zwei verketteten `.replace()`-Aufrufen:

```cpp
s.replace(0, 6, "").replace(s.find("even"), 4, "only");
// \_____________/         \_____________/
//    Aufruf 1                Aufruf 2
```

Damit Aufruf 2 ausgeführt werden kann, muss der Compiler zuerst seine Argumente auswerten. Eines dieser Argumente ist `s.find("even")`.
Die Kernfrage ist: Wann wird `s.find("even")` ausgeführt? Vor oder nach dem ersten `.replace()`?


#### Möglichkeit A: find läuft ZUERST (alte C++ Standards / manche Compiler)

1. Der Compiler wertet `s.find("even")` im ursprünglichen String `"I have even sold some"` aus. Das Wort `"even"` startet hier bei Index 7.
2. Jetzt wird der erste Tausch ausgeführt: `s.replace(0, 6, "")`. Dadurch werden die ersten 6 Zeichen (`"I have"`) gelöscht. Der String ist nun: `" even sold some"`.
3. Nun wird der zweite Tausch mit dem vorher gemerkten Index (7) ausgeführt. Im neuen, kürzeren String ist Index 7 aber die Stelle hinter `"even"`.
   Das Ergebnis wird fehlerhaft oder führt zu einem Absturz.

#### Möglichkeit B: Von links nach rechts (C++17 und neuer)

Seit dem Standard C++17 wurde die Reihenfolge für verkettete Funktionsaufrufe (sogenanntes *Method Chaining*) strikt geregelt.
Es gilt: Alles auf der linken Seite einer Kette wird garantiert vor der rechten Seite ausgewertet.

1. Zuerst wird der erste Tausch ausgeführt: `s.replace(0, 6, "")`. Der String wird zu `" even sold some"`.
2. Erst danach wird das Argument für den zweiten Tausch ausgewertet: `s.find("even")`. Im neuen String `" even sold some"` liegt `"even"` nun bei Index 1.
3. Der zweite Tausch nutzt Index 1 und ersetzt `"even"` durch `"only"`.



Method Chaining_01.png

Method Chaining_02.png


#### Fazit

Vor C++ 17 konnte `s.find("even")` bereits ausgewertet werden, bevor der erste `replace`-Aufruf ausgeführt wurde,
was dazu führte, dass eine veraltete Position ermittelt wurde.

In C++ 17 ist festgelegt, dass der Objektausdruck (`s.replace(...)`) vor den Argumenten des nachfolgenden Aufrufs ausgewertet wird;
dadurch sieht `find` den bereits modifizierten String.


## Ist Move-Semantik mein neuer Freund?

Ich möchte, um Laufzeit einzusparen, die eine oder andere überflüssige Kopier-Operation in meinem Programm zu Gunsten einer Verschiebe-Operation 
austauschen. Gibt es hier etwas zu beachten?

### Nebenwirkungen / Seiteneffekte in Kopier-Konstruktoren treten nicht mehr auf

Wenn ein Kopierkonstruktor mehr tut als nur kopiert (Instanzen zählen, protokollieren, das Objekt registrieren, eine Versionsnummer erhöhen),
wird dieser Code nicht ausgeführt, sobald stattdessen eine Verschiebung ausgewählt wird:

```cpp
01: struct Handle {
02:     static int copies;
03:     Handle(const Handle&) { ++copies; }   // legacy: used as a statistic
04:     // ...
05: };
```

*Bemerkung*:<br />
Beachten Sie, dass in C++98 Code mit einem vom Benutzer deklarierten Kopierkonstruktor
keine implizite Verschiebung generiert wird.
Dies funktioniert nur dann, wenn Sie `= default` hinzufügen.

### Standardmäßig generierte (&bdquo;defaulted&rdquo;) Move-Operationen arbeiten elementweise mit flacher Kopie

Bei Verwendung der standardmäßig generierten (&bdquo;defaulted&rdquo;) Move-Operation
werden rohe Zeiger einfach kopiert:

```cpp
01: class Buffer {
02: public:
03:     Buffer() { m_data = new char [5] {}; }
04:     Buffer(Buffer&&) = default;              // looks harmless
05:     ~Buffer() { delete[] m_data; }
06: private:
07:     char* m_data;
08: };
```

Die standardmäßig generierte Move-Operation kopiert den Zeiger,
ohne den Zeiger im Quellobjekt auf `nullptr` zu setzen.
Beide Objekte besitzen nun denselben Speicherbereich, was zu einem &bdquo;Double Free&rdquo;-Fehler führt.

Ein manuell implementierter Move-Konstruktor muss den Zeiger des Quellobjekts zurücksetzen.
Dies ist eine typische Falle, wenn für Klassen, die Ressourcen manuell verwalten, die Move-Operationen mittels `= default` definiert werden.

### Das umgekehrte Problem: Objekte, die nicht verschoben, sondern kopiert werden

In manchen Situationen kommen stillschweigend Kopien zum Einsatz, obwohl man ein
Verschieben erwarten würde.

Es geht hier aber weniger um Fehler als vielmehr um Beeinträchtigungen bzfl. der Performance.

#### `std::move` auf einem `const`-Objekt

Es bindet an den Kopierkonstruktor, sodass eine Kopie erstellt wird und ein trügerisches Gefühl von Effizienz entsteht. 

#### `std::move` im Zusammenspiel mit `return`

Eine Anweisung der Gestalt

```cpp
return std::move(local);
```

verhindert das Feature von RVO (*Return Value Optimization*) und erzwingt eine Verschiebung.




---



x. Benutze const soviel wie möglich


---

TBD: Was fehlt

const
std::initializer_list

std::string_view

is_transparent



---

Sehe CLaude UND Chat GPT

---

[Zurück](../../Readme.md)

---
