# Ausnahmesicherheit / *Exception Safety*

[Zurück](../../Readme.md)

---

[Quellcode](ExceptionSafety.cpp)

---

## Überblick


Die C++-Standardbibliothek bietet mehrere Ebenen der Ausnahmesicherheit (in aufsteigender Reihenfolge):


  * **Keine Ausnahmesicherheit** (*No Exception Safety*):<br />
  Es werden keine Garantien gegeben.

  * **Elementare Ausnahmesicherheit** (*Basic Exception Safety*):<br />
  Die teilweise Ausführung fehlgeschlagener Operationen kann zu Nebenwirkungen führen,
  aber alle Invarianten bleiben erhalten.<br />
  Alle gespeicherten Daten enthalten gültige Werte, die von den ursprünglichen Werten abweichen können.
  Ressourcenlecks (einschließlich Speicherlecks) werden üblicherweise durch eine Invariante ausgeschlossen,
  die besagt, dass alle Ressourcen berücksichtigt und verwaltet werden.

  * **Starke Ausnahmesicherheit** (*Strong Exception Safety*):<br />
  Wird auch als *Commit*- oder *Rollback*-Semantik bezeichnet:
  Operationen können fehlschlagen, aber fehlgeschlagene Operationen haben garantiert keine Nebenwirkungen
  und die ursprünglichen Werte bleiben intakt.

  * **No-throw-Garantie** (*No-throw guarantee*):<br />
  Operationen sind garantiert erfolgreich und erfüllen alle Anforderungen auch in Ausnahmesituationen.
  Tritt eine Ausnahme auf, wird sie intern behandelt und von Clients nicht beobachtet.


---

## *No Exception* Garantie

Was bedeutet es, wenn Code keine Garantien bezüglich Ausnahmen trifft?

Diese Ebene der Ausnahmesicherheit bedeutet, dass &bdquo;alles&rdquo; passieren kann,
wenn während der Ausführung des Programms eine Ausnahme eintritt.

Zum Beispiel nicht freigegebene Ressourcen, Zeiger oder Referenzen, deren Ziel nicht mehr vorhanden ist
bis hin zu verletzten Klasseninvarianten.

*Beispiel*:

```cpp
01: class TwoPointers
02: {
03: private:
04:     std::unique_ptr<int> m_pi;
05:     std::unique_ptr<double> m_pd;
06: 
07: public:
08:     TwoPointers(int* pi, double* pd) 
09:         : m_pi{ pi }, m_pd{ pd }
10:     {}
11: };
12: 
13: static void test_01_exception_safety()
14: {
15:     TwoPointers tp { new int(123), new double(123.456) };
16: }
```

Auf den ersten Blick mag das gut aussehen,
da das Objekt beide Zeiger direkt an die beiden `std::unique_ptr`-Objekte weitergibt,
die sich um die Speicherfreigabe kümmern.

Aber dieser Code kann ein Speicher-Leak produzieren,
da beim Versagen des zweiten der beiden `new`-Aufrufe eine `std::bad_alloc`-Ausnahme geworfen wird.

Die Ausnahme wird beim Aufruf des Konstruktors der `TwoPointers`-Klasse geworfen!
Dies bedeutet, dass der vom ersten `new` zugewiesene Speicher keinem der beiden `std::unique_ptr`-Objekte zugewiesen wurde
und daher nie freigegeben wird.

*Fazit*: **&bdquo;Don’t write code that has no exception guarantee!&rdquo;**

> 

---

## *Basic Exception Safety*

Prinzipiell muss man festhalten, dass die *Basic Exception Safety* in ihrer Berücksichtigung
ziemlich einfach ist.

Sie besagt, dass, wenn während der Ausführung des Programms eine Ausnahme ausgelöst wird,
keine Ressourcen verloren gehen und man sicher sein kann,
dass die Klasseninvarianten der Objekte nicht verletzt sind.

Nicht mehr und nicht weniger.

Es bedeutet insbesondere **nicht**, dass wir den Inhalt,
den Status oder die Werte von Objekten kennen!

Aber wir wissen, dass wir sie verwenden und zerstören können,
weil die Invarianten intakt sind.


*Fazit*: **&bdquo;Entwerfen Sie Ihre Klassen so, dass sie über geeignete Klasseninvarianten verfügen, die immer eingehalten werden, auch bei Eintreten von Ausnahmen.!&rdquo;**


---

## *Strong Exception Safety*


Die *Strong Exception Safety* Garantie ergänzt die *Basic Exception Safety* Garantie um den Umstand,
dass wenn eine Operation mit einer Ausnahme fehlschlägt, das Objekt im gleichen Zustand verbleibt,
in dem es sich vorher befunden hat (*Commit*- oder *Rollback*-Semantik).


*Beispiel*:

```cpp
01: StrongExceptionSafety& operator= (const StrongExceptionSafety& other) {
02:     StrongExceptionSafety temp{ other };
03:     temp.swap(*this);
04:     return *this;
05: }
```

Die Realisierung des Zuweisungsoperators sieht ziemlich einfach, 
aber man muss sie sehr genau betrachten:

  * Zunächst wird eine Kopie des anderen Objekts erstellt.
  Dies kann eine Ausnahme auslösen (!), aber wenn dies der Fall ist, wird die Funktion vorzeitig beendet
  und weder mit `*this` noch mit dem anderen Objekt `other` ist bisher etwas passiert!

  * Nun werden die Instanzvariablen der beiden Objekte `*this` und `temp` ausgetauscht.
  Um die *Strong Exception Safety* zu garantieren, darf dieser Vorgang keine Ausnahmen auslösen!

  * Der *Swap*-Vorgang stellt die *Commit*-Aktion dar, danach ist die Zuweisung abgeschlossen.
  Wenn die Funktion mit der `return`-Anweisung verlassen wird,
  wird das temporäre Objekt zerstört und der Status, der zuvor `*this` gehörte, ist aktualisiert.


Man erkennt, dass die Umsetzung der *Strong Exception Safety* Garantie kostspielig sein kann &ndash; 
wir reden von Laufzeit oder zusätzlichem Speicherbedarf.


*Fazit*: **&bdquo;Realisieren Sie die *Strong Exception Safety* Garantie nur dann, wenn sie benötigt wird!&rdquo;**

---

## *No-throw* Garantie

Die letzte fehlende Ebene ist die *no-throw* Garantie.

Sie bedeutet einfach, dass eine Operation *keine* Ausnahme auslösen kann.

Wir haben am letzen Beispiel gesehen, dass *no-throw* Operationen erforderlich sind,
um die starke und elementare Garantie bereitzustellen.

Es gibt einige Operationen, die niemals eine Ausnahme auslösen sollten, egal was passiert:

  * Destruktoren:<br />
  Destruktoren dürfen grundsätzlich keine Ausnahme werfen,
  da sie während des Entfernen des aktuellen *Stackframes* aufgerufen werden.<br />
  Wenn eine Ausnahme aktiv ist und während der Entfernung des *Stackframes* eine zweite Ausnahme ausgelöst wird, wird das Programm beendet.
  * Aufräumarbeiten:<br />
  Alle Aufräumarbeiten wie das Schließen von Dateien, das Freigeben von Speicher und alles andere, was von einem Destruktor aufgerufen werden kann, sollten keine Ausnahme auslösen.
  * *Swap*-Funktionen:<br />
  Von *Swap*-Funktionen wird erwartet, dass sie keine Ausnahme auslösen.


*Fazit*: **&bdquo;Verwenden Sie das Schlüsselwort `noexcept`, um Funktionen/Methoden kennzuzeichnen, die die *No-throw* Garantie gewähren.!&rdquo;**

---

## Literaturhinweise

Die Anregungen zu den Beispielen aus diesem Abschnitt sind aus dem Artikel

[Levels of Exception Safety](https://arne-mertz.de/2015/12/levels-of-exception-safety/)<br>(abgerufen am 23.09.2020).

von Arne Mertz entnommen.

---

[Zurück](../../Readme.md)

---
