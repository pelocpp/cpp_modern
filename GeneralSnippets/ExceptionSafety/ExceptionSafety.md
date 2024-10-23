# Ausnahmesicherheit / *Exception Safety*

[Zurück](../../Readme.md)

---

[Quellcode](ExceptionSafety.cpp)

---

## Inhalt

  * [Überblick](#link1)
  * [*No Exception* Garantie](#link2)
  * [*Basic Exception Safety*](#link3)
  * [*Strong Exception Safety*](#link4)
  * [*No-throw* Garantie](#link5)
  * [RAII-Idiom zur Verwaltung von Ressourcen](#link6)
  * [Literaturhinweise](#link7)


---

## Überblick <a name="link1"></a>


Die C++-Standardbibliothek bietet mehrere Ebenen der Ausnahmesicherheit (in aufsteigender Reihenfolge):


  * **Keine Ausnahmesicherheit** (*No Exception Safety*):<br />
  Es werden keine Garantien gegeben.

  * **Elementare Ausnahmesicherheit** (*Basic Exception Safety*):<br />
  Die teilweise Ausführung fehlgeschlagener Operationen kann zu Nebenwirkungen führen,
  aber alle Invarianten bleiben erhalten.<br />
  Alle gespeicherten Daten enthalten gültige Werte, die von den ursprünglichen Werten abweichen können.
  Ressourcenleaks (einschließlich Speicherleaks) werden üblicherweise durch eine Invariante ausgeschlossen,
  die besagt, dass alle Ressourcen berücksichtigt und verwaltet werden.

  * **Starke Ausnahmesicherheit** (*Strong Exception Safety*):<br />
  Wird auch als *Commit*- oder *Rollback*-Semantik bezeichnet:
  Operationen können fehlschlagen, aber fehlgeschlagene Operationen haben garantiert keine Nebenwirkungen
  und die ursprünglichen Werte bleiben erhalten.

  * **No-throw-Garantie** (*No-throw guarantee*):<br />
  Operationen sind garantiert erfolgreich und erfüllen alle Anforderungen auch in Ausnahmesituationen.
  Tritt eine Ausnahme auf, wird sie intern behandelt und von Clients nicht wahrgenommen.


---

## *No Exception* Garantie <a name="link2"></a>

Was bedeutet es, wenn Code keine Garantien bezüglich Ausnahmen gibt?

Diese Ebene der Ausnahmesicherheit bedeutet, dass &bdquo;alles&rdquo; passieren kann,
wenn während der Ausführung des Programms eine Ausnahme eintritt.

Zum Beispiel das Vorhandensein nicht freigegebener Ressourcen, Zeiger oder Referenzen, deren Ziel nicht mehr vorhanden ist
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
13: static void test_exception_safety()
14: {
15:     TwoPointers tp { new int(123), new double(123.456) };
16: }
```

Auf den ersten Blick mag diese Beispiel gut aussehen,
da das Objekt beide Zeiger direkt an die beiden `std::unique_ptr`-Objekte weitergibt,
die sich um die Speicherfreigabe kümmern.

Aber dieser Code kann ein Speicher-Leak produzieren,
da beim Versagen des zweiten der beiden `new`-Aufrufe eine `std::bad_alloc`&ndash;Ausnahme geworfen wird.

Diese Ausnahme wird beim Aufruf des Konstruktors der `TwoPointers`-Klasse geworfen!
Dies bedeutet, dass der vom ersten `new`-Aufruf zugewiesene Speicher keinem der beiden `std::unique_ptr`-Objekte zugewiesen wurde
und daher nie freigegeben wird.

**Fazit**:<br />**&bdquo;Schreiben Sie keinen Code, der die *No Exception* Garantie besitzt!&rdquo;**

---

## *Basic Exception Safety* <a name="link3"></a>

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


**Fazit**:<br />**&bdquo;Entwerfen Sie Ihre Klassen so, dass sie über geeignete Klasseninvarianten verfügen, die immer eingehalten werden, auch bei Eintreten von Ausnahmen!&rdquo;**


---

## *Strong Exception Safety* <a name="link4"></a>

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
  und weder mit `*this` noch mit dem anderen Objekt `other` ist etwas passiert!

  * Nun werden die Instanzvariablen der beiden Objekte `*this` und `temp` ausgetauscht.
  Um die *Strong Exception Safety* zu garantieren, darf dieser Vorgang keine Ausnahmen auslösen!

  * Der *Swap*-Vorgang stellt die *Commit*-Aktion dar, danach ist die Zuweisung abgeschlossen.
  Wenn die Funktion mit der `return`-Anweisung verlassen wird,
  wird das temporäre Objekt zerstört und der Status, der zuvor `*this` gehörte, ist aktualisiert.


Man erkennt, dass die Umsetzung der *Strong Exception Safety* Garantie kostspielig sein kann &ndash; 
wir reden von Laufzeit oder zusätzlichem Speicherbedarf.


**Fazit**:<br />**&bdquo;Realisieren Sie die *Strong Exception Safety* Garantie nur dann, wenn sie benötigt wird!&rdquo;**

---

## *No-throw* Garantie <a name="link5"></a>

Die letzte Ebene in der *Exception Safety*&ndash;Hierarchie ist die *no-throw* Garantie.

Sie bedeutet einfach, dass eine Operation *keine* Ausnahme auslöst.

Wir haben am letzen Beispiel gesehen, dass *no-throw* Operationen erforderlich sind,
um die starke und elementare Garantie bereitzustellen.

Es gibt einige Operationen, die niemals eine Ausnahme auslösen sollten, egal was passiert:

  * Destruktoren:<br />
  Destruktoren dürfen grundsätzlich keine Ausnahme werfen,
  da sie während des Entfernen des aktuellen *Stackframes* aufgerufen werden.<br />
  Wenn eine Ausnahme aktiv ist und während der Entfernung des *Stackframes* eine zweite Ausnahme eintritt, wird das Programm beendet.
  * Aufräumarbeiten:<br />
  Alle Aufräumarbeiten wie das Schließen von Dateien, das Freigeben von Speicher und alles andere, was von einem Destruktor aufgerufen werden kann, sollten keine Ausnahme auslösen.
  * *Swap*-Funktionen:<br />
  Von *Swap*-Funktionen wird erwartet, dass sie keine Ausnahme auslösen.


**Fazit**:<br />**&bdquo;Verwenden Sie das Schlüsselwort `noexcept`, um Funktionen/Methoden kennzuzeichnen, die die *No-throw* Garantie gewähren!&rdquo;**

---

## RAII-Idiom zur Verwaltung von Ressourcen <a name="link6"></a>

Um gegen Exceptions gerüstet zu sein, muss eine Funktion sicherstellen,
dass Objekte, die sie mithilfe von `new` (`malloc`) zugewiesen hat, zerstört werden
und alle Ressourcen wie Datei-Handles geschlossen oder freigegeben werden,
selbst wenn eine Ausnahme ausgelöst wird.

Das *Resource Acquisition Is Initialization* (*RAII*)-Idiom verknüpft die Verwaltung solcher Ressourcen
mit der Lebensdauer von Hüllen-Objekten, die am Stack liegen.

Wenn eine Funktion/Methode ihren Gültigkeitsbereich verlässt,
entweder durch normale Beendigung oder auf Grund einer eingetretenen Ausnahme,
werden die Destruktoren für alle am Stack liegenden Hüllen-Objekte aufgerufen.

Ein RAII-Hüllenobjekt (z.B. ein Smart Pointer Objekt) ruft in seinem Destruktor
die entsprechende `delete`- oder `free`-Funktion auf.

In Exception-sicherem Code ist es folglich von entscheidender Bedeutung,
den Besitz jeder Ressource sofort an eine Art RAII-Hüllenobjekt zu binden.

---

## Literaturhinweise <a name="link7"></a>

Die Anregungen zu den Beispielen aus diesem Abschnitt sind aus dem Artikel

[Levels of Exception Safety](https://arne-mertz.de/2015/12/levels-of-exception-safety/)<br>(abgerufen am 23.09.2020).

von Arne Mertz entnommen.

Ebenfalls interessant zum Lesen sind die beiden Artikel

[How to: Design for exception safety](https://learn.microsoft.com/en-us/cpp/cpp/how-to-design-for-exception-safety)<br>(abgerufen am 08.03.2024).

und

[The Deep Dive into Advanced Exception Safety in Embedded C++](https://www.codewithc.com/the-deep-dive-into-advanced-exception-safety-in-embedded-c)<br>(abgerufen am 08.03.2024).

---

[Zurück](../../Readme.md)

---
