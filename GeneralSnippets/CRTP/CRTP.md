# Curiously Recurring Template Pattern (CRTP)

[Quellcode](CRTP.cpp)

---

## Überblick

C ++ bietet eine sehr gute Unterstützung für Polymorphismus mit Hilfe virtueller Funktionen.
Diese Form des Polymorphismus wird auch *dynamischer* Polymorphismus (*Late-Binding* - Laufzeitpunkt
im Gegensatz zum *Early-Binding* - Übersetzungszeitpunkt) genannt,
da die tatsächlich aufzurufende Funktion zur Laufzeit ermittelt wird.
Implementiert ist dieser Mechanismus in der Regel dadurch, indem jedem Objekt einer Klasse mit virtuellen Funktionen
ein versteckter Zeiger hinzugefügt wird (so genannter *vtptr* - *vtable pointer*).
Dieser Zeiger zeigt für ein bestimmtes Objekt auf eine Tabelle mit Funktionszeigern (pro Klasse eine Tabelle),
um diese bei Bedarf (indirekt (!)) aufzurufen.

Das Problem des dynamischen Polymorphismus kann höhere Laufzeit bedeuten:

  * Zusätzliche Indirektionsstrufe (Zeiger-Dereferenzierung) für jeden Aufruf einer virtuellen Methode.
  * Virtuelle Methoden können normalerweise nicht als `inline` aufgerufen werden, was für Methoden mit wenigen Anweisungen
    ein erhebliches Laufzeitproblem darstellen kann.
  * Zusätzlicher Zeiger pro Objekt: Auf 64-Bit-Systemen, die heutzutage vorherrschen, sind dies 8 Bytes pro Objekt.
    Bei kleinen Objekten mit wenigen Daten kann dies wiederum problematisch sein.

Es stellt sich heraus, dass C ++ mithilfe von Templates eine alternative Möglichkeit bietet,
Polymorphismus ohne zusätzliche Kosten zu implementieren. Es gibt natürlich einen Haken:
Die Datentypen dieser Objekte müssen vom Compiler zum Übersetzungszeitpunkt aufgelöst werden.
Dies wird als *statischer Polymorphismus* (oder auch als "simuliertes dynamisches Binden") bezeichnet.

## Beispiel

Hier ein einfaches Codebeispiel, um diese Technik zu demonstrieren:

```cpp
template <typename Child>
struct Base
{
    void interface() {
        static_cast<Child*>(this)->implementation();
    }
};

struct Derived : Base<Derived>
{
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

void test() {

    Derived d;
    d.interface();  // -> "Derived implementation"
}
```

Der Schlüssel zu dieser Technik ist der seltsame Trick mit Templates,
der verwendet wird: Beachten Sie, dass die Klasse `Derived` von `Base<Derived>` erbt.
Was bedeutet das? Die Idee ist, den realen Typ der abgeleiteten Klasse zur Kompilierungszeit in die Basis zu "injizieren".
Der `static_cast` in Methode `interface` erzeugt dann das gewünschte Ergebnis.

Diese Technik hat einen Namen - sie heißt *Curiously Recurring Template Pattern* oder eben kurz *CRTP*.

## Eine Anwendung: Mixins

Ein Anwendungsfall für das *Curiously Recurring Template Pattern* sind die so genannten *Mixins*.
Da ich diese in der von mir gewählten Umsetzung mit variadischen Templates realisiert habe,
finden wir eine Beschreigung unter

[Variadische Templates: Mixins](../../GeneralSnippets/VariadicTemplates/VariadicTemplates_04_Mixins.md)

vor.

## Literaturhinweise:

Die Anregungen zu den Beispielen auf diesem Abschnitt sind entnommen aus

[The Curiously Recurring Template Pattern in C++](https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c/)<br>(abgerufen am 26.05.2020).

und

[Curiously recurring template pattern (CRTP)](https://www.geeksforgeeks.org/curiously-recurring-template-pattern-crtp-2/)<br>(abgerufen am 26.05.2020).

---

[Zurück](../../Readme.md)

---
