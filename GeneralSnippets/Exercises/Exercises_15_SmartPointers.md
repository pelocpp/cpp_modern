# Aufgaben zu Smart Pointers

[Zurück](Exercises.md)

---

[Lösungen](Exercises_15_SmartPointers.cpp)

---

## Aufgabe 1: Quiz zu Smart Pointers

#### Vorausetzungen: `std::shared_ptr`

Studieren Sie das folgende Code-Fragement.
Welchen Wert hat der Referenzzähler des Objekts `pC` in Zeile 13?

```cpp
01: class X {};
02: 
03: std::shared_ptr<X> pA;
04: std::shared_ptr<X> pB;
05: std::shared_ptr<X> pC;
06: 
07: pA = std::make_shared<X>(); 
08: 
09: pB = pA;
10: 
11: pC = std::move(pA); 
12: 
13: pB = nullptr; // (1)
```

## Aufgabe 2: Noch ein Quiz zu Smart Pointers

#### Vorausetzungen: `std::shared_ptr`

Studieren Sie das folgende Code-Fragement.

  * Welchen Wert erwarten Sie in der Ausgabe von Zeile 23?
  * Wie erklären Sie sich das Laufzeitverhalten des Programms?
  * Welcher prinzipielle Programmierfehler liegt in diesem Code-Fragment vor?

```cpp
01: class X
02: {
03: public:
04:     X() : m_value{ 123 } {}
05:     int getValue() const { return m_value; }
06: 
07: private:
08:     int m_value;
09: };
10: 
11: std::shared_ptr<X> pA{ new X{} };
12: std::shared_ptr<X> pB;
13: std::shared_ptr<X> pC;
14: 
15: pB = pA;
16: 
17: pC = std::shared_ptr<X>(pB.get());
18: 
19: pC = nullptr;  // or pC.reset();
20: 
21: int value = (*pB).getValue();
22: 
23: std::cout << "Value: " << value << std::endl; 
```

---

[An den Anfang](#aufgaben-zu-smart-pointers)

---

## Aufgabe 3: Betrachtung eines &ldquo;nicht besitzenden&rdquo; Zeigers

#### Voraussetzungen: `std::shared_ptr` und `std::weak_ptr`

Wir betrachten in dieser Übungsaufgabe die Situation, dass wir zu einem Objekt
eine Zeigervariable haben möchten, aber nicht um den Preis, dass wir damit
einen Anspruch auf Eigentum erheben.
Natürlich könnten wir einen klassischen &ldquo;raw&rdquo; Zeiger verwenden,
um die Idee eines &ldquo;nicht besitzenden&rdquo; Zeigers auszudrücken,
aber in Zeiten von *Modern C++* ist das keine opportune Lösung.
Außerdem bestünde dann die Gefahr, dass der tatsächliche Eigentümer des referenzierten Objekts beschließen könnten, dieses freizugeben.
Wenn wir dann den &ldquo;nicht besitzenden&rdquo; Zeiger dereferenzieren, käme es zu einem Absturz.

Ein entsprechendes Szenario könnte so aussehen:

```cpp
01: class UnsafeWatcher {
02: private:
03:     int* m_ptr;
04: 
05: public:
06:     UnsafeWatcher() : m_ptr{ nullptr } {}
07: 
08:     void watch(const std::shared_ptr<int>& sp)
09:     {
10:         m_ptr = sp.get();
11:     }
12: 
13:     int currentValue() const
14:     {
15:         return *m_ptr;  // m_ptr might have been released !
16:     }
17: };
18: 
19: void test_01() {
20: 
21:     UnsafeWatcher watcher;
22: 
23:     {
24:         std::shared_ptr<int> sp = std::make_shared<int>(123);
25:         watcher.watch(sp);
26:         std::cout << "Value: " << watcher.currentValue() << std::endl;
27:     }
28: 
29:     std::cout << "Value: " << watcher.currentValue() << std::endl;
30: }
```

Alternativ zum letzten Beispiel könnten wir in der Klasse `UnsafeWatcher` eine `std::shared_ptr`-Variable verwenden.
Damit werden wir aber zu einem Besitzer des Zeigers und verlassen den Ansatz eines &ldquo;nicht besitzenden&rdquo; Zeigers
Auch dies wollen wir mit einem Beispiel untermauern:

```cpp
01: class HeavyAndSafeWatcher {
02: private:
03:     std::shared_ptr<int> m_ptr;
04: 
05: public:
06:     HeavyAndSafeWatcher() {}
07: 
08:     void watch(const std::shared_ptr<int>& sp)
09:     {
10:         m_ptr = sp;
11:     }
12: 
13:     int currentValue() const
14:     {
15:         return *m_ptr;  // m_ptr is always alive!
16:     }
17: };
18: 
19: void test_02() {
20:     HeavyAndSafeWatcher watcher;
21: 
22:     {
23:         std::shared_ptr<int> sp = std::make_shared<int>(123);
24:         watcher.watch(sp);
25:         std::cout << "Value: " << watcher.currentValue() << std::endl;
26:     }
27: 
28:     std::cout << "Value: " << watcher.currentValue() << std::endl;
29: }
```

*Aufgabe*: 

Schreiben Sie das letzte Code-Fragment so um, dass die `HeavyAndSafeWatcher`-Klasse einen nicht-besitzenden Zeiger besitzt,
der Zugang zu einem korrespondierenden `std::shared_ptr`-Objekt hat und in der Lage ist, 
dessen Kontrollblock abzufragen und zu entscheiden, ob das referenzierte Objekt noch existiert oder nicht.

Die gesuchte primitive Operation ist *atomar* (&ldquo;multithreading sicher&rdquo;) in dem Sinne,
dass sie eine besitzende Referenz (`std::shared_ptr`-Objekt) auf das
referenzierte Objekt zurückliefert, wenn dieses noch existiert, oder andernfalls einen Fehler anzeigt.

Man könnte auch die Formulierung wählen, dass wir auf der Suche nach einer &ldquo;Fahrkarte&rdquo;
für ein `std::shared_ptr`-Objekt sind.
Das Ticket selbst steht für einen nicht-besitzenden Zeiger,
man kann es zu einem späteren Zeitpunkt gegen ein `std::shared_ptr`-Objekt eintauschen &ndash; sofern
das referenzierte Objekt noch existiert.

---

[Lösungen](Exercises_15_SmartPointers.cpp)

---

[An den Anfang](#aufgaben-zu-smart-pointers)

---
