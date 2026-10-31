# Wertsemantik versus Referenzsemantik in Bildern

[Zurück](Architecture.md)

---

## Allgemeines

  * Wertsemantik in C++
    * Objekte erzeugen
    * Objekte kopieren
  * Referenzsemantik in C++
    * Mit Referenzen
    * Mit Adressen (Pointer)

Es werden Vergleiche mit C# und Python betrachtet.

---

## Objekte erzeugen

### Wertsemantik in C++

Objekte können in C++ global oder lokal angelegt werden:

<img src="cpp_architecture_01_value_vs_reference_semantics.svg" width="600">

*Abbildung* 1: Wertsemantik in C++.


### Referenzsemantik in C#

Objekte in C# liegen generall am Heap:

<img src="cpp_architecture_02_value_vs_reference_semantics.svg" width="600">

*Abbildung* 2: Referenzsemantik in C#.

### Referenzsemantik in Python

Objekte in Python liegen ausnahmslos am Heap:

<img src="cpp_architecture_10_value_vs_reference_semantics_python.svg" width="800">

*Abbildung* 3: Referenzsemantik in Python.

Zwischen C# und Python gibt es kleine Unterschiede. So kennt Python keine *Null*-Referenzen wie im Sinne von C#.
Wenn in Python eine Variable auf &bdquo;nichts&rdquo; zeigen soll, weist man ihr das eingebaute Schlüsselwort `None` zu.
`None` ist ein vollwertiges Objekt vom Datentyp `NoneType` und liegt am Heap (*Singleton*).

---

## Objekte kopieren

### Kopieren eines Objekts bei Wertsemantik

Beim Kopieren eines C++&ndash;Objekts entsteht eine echte Kopie.
Je nach Struktur des Objekts kann hierzu ein Kopierkonstruktor notwendig sein,
ein entsprechender Aufruf erfolgt implizit:

<img src="cpp_architecture_03_value_vs_reference_semantics.svg" width="600">

*Abbildung* 4: Kopieren eines Objekts bei Wertsemantik in C++.



### Kopieren eines Objekts bei Referenzsemantik

Beim Kopieren eines C#&ndash; oder Python&ndash;Objekts wird die Referenz kopiert &ndash; das Objekt selbst bleibt davon unberührt:

<img src="cpp_architecture_04_value_vs_reference_semantics.svg" width="600">

*Abbildung* 5: Kopieren eines C#&ndash;Objekts bei Referenzsemantik in C#.

<img src="cpp_architecture_11_value_vs_reference_semantics_python.svg" width="800">

*Abbildung* 6: Kopieren eines Python&ndash;Objekts bei Referenzsemantik in Python.














### Erstellen einer echten Kopie bei Referenzsemantik

Um in C# eine echte (tiefe) Kopie eines Objekts zu erstellen, muss dies mit einem expliziten Methodenaufruf erfolgen.

<img src="cpp_architecture_05_value_vs_reference_semantics.svg" width="600">

*Abbildung* 7: Erstellen einer echten Kopie bei Referenzsemantik in C#.


---

## Referenzsemantik in C++

### Referenzsemantik mit Referenzen

In C++ kann man zu existierenden Objekten eine Referenz definieren.
Die Referenz ist ein Alias &ndash; hinter dem Alias verbirgt sich eine Adresse und damit keine Kopie:

<img src="cpp_architecture_06_value_vs_reference_semantics.svg" width="600">

*Abbildung* 8: Referenzsemantik mit Referenzen.



### Referenzsemantik mit Zeigern

Objekte in C++ können dynamisch sein:
Dazu sind in &bdquo;*Classic C++*&rdquo; die Operatoren `new` und `delete` zu verwenden,
in *Modern C++* die Smart Pointer Klassen `std::unique_ptr`, `std::shared_ptr` oder `std::weak_ptr`:

<img src="cpp_architecture_07_value_vs_reference_semantics.svg" width="800">

*Abbildung* 9: Referenzsemantik mit Zeigern.

Theoretisch ließen sich Objekte am Heap auch über Referenzen ansprechen, dies ist aber mehr als unüblich
und führt auf Grund der Lebensdauereinschränkungen von dynamischen Objekten vermutlich eher zu Fehlern:

```cpp
01: std::unique_ptr<Person> hansPtr{
02:     std::make_unique<Person>("Hans", "Meier", 30)
03: };
04: 
05: Person& personRef = *hansPtr;
06: 
07: hansPtr->m_age++;
08: 
09: personRef.m_age++;
```

Die allgemeine Regel für Zeiger (Pointer) und Referenzen in C++ lautet:

  * Referenzen: Sie werden für lokale und globale Objekte verwendet.<br />
    Zum Beispiel bei der Parameterübergabe, um bei diesem Vorgang Kopien zu vermeiden.
    Globale Objekte existieren für die gesamte Laufzeit des Programms, lokale Objekte hingegen eignen sich nur für die Betrachtung von Zwischenergebnissen,
    da diese nach dem Verlassen des Unterprogramms (Methode, freie Funktion, Block) wieder zerstört werden.
  * Zeiger: Sie werden für dynamische Objekte verwendet.<br />Ihr Speicherbedarf wird bei Bedarf reserviert und danach wieder freigegeben. 
    Dies ist der Hauptunterschied zu globalen oder lokalen Objekten.

---

[Zurück](Architecture.md)

---
