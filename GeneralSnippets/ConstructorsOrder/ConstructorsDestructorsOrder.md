# Reihenfolge der Aufrufe von Konstruktoren und Destruktoren

[Zurück](../../Readme.md)

---

[Quellcode](ConstructorsDestructorsOrder.cpp)

---

Im Umfeld der Vererbung sollte man sich im Klaren sein, in welcher Reihenfolge die Konstruktoren und Destruktoren
aller beteiligten Objekte aufgerufen werden. Um das Szenario vollständig zu betrachten, bringen wir auch
noch die Komposition bzw. Aggregation ins Spiel: Eine Klasse (besser: ein Objekt) kann auch aus Unterobjekten bestehen.

Damit stellt sich wiederum die Frage, in welcher Reihenfolge jetzt die Konstruktoren (und Destruktoren) aufgerufen werden?

Prinzipiell gilt:

  1. Hat eine Klasse eine Basisklasse, wird zuerst deren (Default-)Konstruktor aufgerufen. Alternativ ist es auch möglich,
     dass ein benutzerdefinierter Konstruktor der Basisklasse explizit aufgerufen wird. Syntaktisch erfolgt dies in der
     Initialisierungsliste.

  2. Hat die Klasse (genauer: das Objekt) Unterobjekte, so werden als Zweites die Konstruktoren der Unterobjekte aufgerufen.
     Die Reihenfolge ergibt sich dabei aus der textuellen Reihenfolge, in der die Unterobjekte in der umgebenden Klasse definiert sind.

  3. Der Konstruktor des aktuellen Objekts (genauer: der Rumpf dieses Konstruktors) gelangt nun zur Ausführung.

  Bzgl. der Aufrufe der Destruktoren kann man sagen, dass diese in der genau umgekehrten Reihenfolge aufgerufen werden.

Ausgabe des Code-Snippets:

```cpp
c'tor Base
c'tor Something
c'tor Derived
Hello!
d'tor Derived
d'tor Something
d'tor Base
```

---

[Zurück](../../Readme.md)

---
