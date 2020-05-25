# Curiously Recurring Template Pattern (CRTP)

[Quellcode](CRTP.cpp)

---

## Überblick

C ++ bietet eine sehr gute Unterstützung für Polymorphismus mit Hilfe virtueller Funktionen.
Diese Form des Polymorphismus wird auch *dynamischer* Polymorphismus (*Late-Binding* - Laufzeit im Gegensatz zum *Early-Binding* - Übersetzungszeit) genannt,
da die tatsächlich aufzurufende Funktion zur Laufzeit ermittelt wird.
Implementiert ist dieser Mechanismus in der Regel dadurch, indem jedem Objekt einer Klasse mit virtuellen Funktionen
ein versteckter Zeiger hinzugefügt wird (*vtptr* - *vtable pointer*).
Dieser Zeiger zeigt für ein bestimmtes Objekt auf eine Tabelle mit Funktionszeigern, um diese bei Bedarf (indirekt (!)) aufzurufen.

Das Problem des dynamischen Polymorphismus kann höhere Laufzeit bedeuten:

  * Zusätzliche Indirektion (Zeiger-Dereferenzierung) für jeden Aufruf einer virtuellen Methode.
  * Virtuelle Methoden können normalerweise nicht via `inline` aufgerufen werden, was für Methoden mit wenig Anweisungen
    ein erhebliches Laufzeitproblem darstellen kann.
  * Zusätzlicher Zeiger pro Objekt: Auf 64-Bit-Systemen, die heutzutage vorherrschen, sind dies 8 Bytes pro Objekt.
    Bei kleinen Objekten mit wenig Daten kann dies wiederum problematisch sein.

Es stellt sich heraus, dass C ++ mithilfe von Templates eine alternative Möglichkeit bietet,
Polymorphismus ohne zusätzliche Kosten zu implementieren. Es gibt natürlich einen Haken:
Die Datentypen dieser Objekte müssen vom Compiler zur Kompilierungszeit aufgelöst werden.
Dies wird als *statischer Polymorphismus* (oder auch "simuliertes dynamisches Binden") bezeichnet.

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
Was bedeutet das? Die Idee ist, den realen Typ der abgeleiteten Klasse zur Kompilierungszeit in die Basis zu "injizieren",
damit der `static_cast` davon in der Schnittstelle das gewünschte Ergebnis erzeugt.

Diese Technik hat einen Namen - sie heißt *Curiously Recurring Template Pattern* oder eben kurz *CRTP*.


## Eine Anwendung: Mixins

HIer weiter !!!

Und im Readme.md ergänzen !!!

---

[Zurück](../../Readme.md)

---
