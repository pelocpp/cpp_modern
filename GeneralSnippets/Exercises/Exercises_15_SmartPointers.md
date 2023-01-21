# Aufgaben zu Smart Pointers

[Zurück](Exercises.md)

---

[Lösungen](Exercises_15_SmartPointers.cpp)

---

## Aufgabe 1: Quiz zu Smart Pointer

#### Vorausetzungen: `std::shared_ptr<>`

Studieren Sie das folgende Code-Fragement genau.
Welchen Wert hat der Referenzzähler des Objekts `pC` in der letzten Zeile?

```cpp
01: class X {};
02: 
03: std::shared_ptr<X> pA;
04: std::shared_ptr<X> pB;
05: std::shared_ptr<X> pC;
06: 
07: pA = std::make_shared<X>();
08: pB = pA; 
09: pC = std::move(pA);
10: pB = nullptr;
```

## Aufgabe 2: Noch ein Quiz zu Smart Pointer

#### Vorausetzungen: `std::shared_ptr<>`

Studieren Sie das folgende Code-Fragement genau.

  * Welchen Wert erwarten Sie in der Ausgabe von Zeile 19?
  * Wie erklären Sie sich das vorliegende Laufzeitverhalten des Programms?
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
16: pC = std::shared_ptr<X>(pB.get());
17: pC = nullptr; 
18: int value = (*pB).getValue();
19: std::cout << "Value: " << value << std::endl;
```

---

[An den Anfang](#aufgaben-zu-smart-pointers)

---

## Aufgabe 3: Beobachtungen eines Zyklus von Smart Pointer Objekten

#### Voraussetzungen: `std::shared_ptr<>`, ggf. `std::weak_ptr<>`

Studieren Sie das folgende Code-Fragement genau:

```cpp
01: struct X;
02: struct Y;
03: 
04: struct X
05: {
06:     std::shared_ptr<Y> m_sp_Y{};
07: };
08: 
09: struct Y
10: {
11:     std::shared_ptr<X> m_sp_X{};
12: };
13: 
14: void test()
15: {
16:     {
17:         std::shared_ptr<X> sp_X{ std::make_shared<X>() };
18:         std::shared_ptr<Y> sp_Y{ std::make_shared<Y>() };
19: 
20:         sp_X->m_sp_Y = sp_Y;
21:         sp_Y->m_sp_X = sp_X;
22:     }
23: }
```

  * Bringen Sie das Programm zunächst zum Laufen &ndash; es sind nur fehlende `#include`-Direktiven zu ergänzen.
  * Wie erklären Sie sich das vorliegende Laufzeitverhalten des Programms?
    Möglicherweise müssen Sie dazu die Anweisungen der *Memory Leaks Detection* aktivieren, siehe [hier](https://github.com/pelocpp/cpp_modern_examples/blob/master/GeneralSnippets/MemoryLeaks/MemoryLeaksDetection.md).
  * Welcher prinzipielle Programmierfehler liegt in diesem Code-Fragment vor?
    Wie könnte man diesen beheben?

---

[An den Anfang](#aufgaben-zu-smart-pointers)

---

## Aufgabe 4: Betrachtungen eines &ldquo;nicht besitzenden&rdquo; Zeigers

#### Voraussetzungen: `std::shared_ptr<>` und `std::weak_ptr<>`

Wir betrachten in dieser Übungsaufgabe die Situation, dass wir zu einem Objekt
(hier: dynamisch allokierte Variable vom Typ `int`)
eine Zeigervariable haben möchten, aber nicht um den Preis, dass wir damit
einen Anspruch auf Eigentum erheben.
Natürlich könnten wir einen klassischen &ldquo;raw&rdquo; Zeiger verwenden,
um die Idee eines &ldquo;nicht besitzenden&rdquo; Zeigers auszudrücken,
aber in Zeiten von *Modern C++* ist das keine opportune Lösung.
Außerdem bestünde dann die Gefahr, dass der tatsächliche Eigentümer des referenzierten Objekts beschließen könnte,
dieses freizugeben.
Wenn wir dann den &ldquo;nicht besitzenden&rdquo; Zeiger dereferenzieren, käme es zu einem Absturz.

Studieren Sie vor dem geschilderten Hintergrund das folgende Szenario:

  * Wie erklären Sie sich das vorliegende Laufzeitverhalten dieses Code-Fragments?
  * Welcher prinzipielle Programmierfehler liegt in diesem Code-Fragment vor?

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
15:         return *m_ptr;
16:     }
17: };
18: 
19: void test()
20: {
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

---

Alternativ zum letzten Beispiel könnten wir in der Klasse `UnsafeWatcher` eine `std::shared_ptr`-Variable verwenden.
Damit würden wir aber zu einem Besitzer des Zeigers und verlassen den Ansatz eines &ldquo;nicht besitzenden&rdquo; Zeigers!
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
15:         return *m_ptr;
16:     }
17: };
18: 
19: void test()
20: {
21:     HeavyAndSafeWatcher watcher;
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

*Aufgabe*: 

  * Vergleichen und erklären Sie das Laufzeitverhalten der beiden Code-Fragmente (Klassen `UnsafeWatcher` und `HeavyAndSafeWatcher`)?
  * Schreiben Sie das letzte Code-Fragment so um, dass die `HeavyAndSafeWatcher`-Klasse
    einen nicht-besitzenden Zeiger besitzt, der Zugang zu einem korrespondierenden `std::shared_ptr`-Objekt hat und in der Lage ist, 
    dessen Kontrollblock abzufragen und zu entscheiden, ob das referenzierte Objekt noch existiert oder nicht.

*Hinweis*: 

Die gesuchte primitive Operation ist *multithreading sicher*!
Sie liefert eine besitzende Referenz (`std::shared_ptr`-Variable) auf das
referenzierte Objekt zurück, wenn dieses noch existiert, oder zeigt andernfalls einen Fehler an.

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
