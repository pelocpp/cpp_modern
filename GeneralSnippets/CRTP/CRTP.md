# Curiously Recurring Template Pattern (CRTP)

[Zurück](../../Readme.md)

---

[Quellcode](CRTP.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [*Curiously Recurring Template Pattern* (CRTP)](#link2)
  * [Funktionsweise von CRTP](#link3)
  * [Einschränkungen von CRTP](#link4)
  * [Ein zweites Beispiel](#link5)
  * [Literaturhinweise](#link6)

---

## Allgemeines <a name="link1"></a>

C ++ bietet eine sehr gute Unterstützung für Polymorphismus mit Hilfe virtueller Funktionen.
Diese Form des Polymorphismus wird auch *dynamischer* Polymorphismus (*Late-Binding* - Laufzeitpunkt
im Gegensatz zum *Early-Binding* - Übersetzungszeitpunkt) genannt,
da die tatsächlich aufzurufende Funktion zur Laufzeit ermittelt wird.
Implementiert ist dieser Mechanismus in der Regel dadurch, indem jedem Objekt einer Klasse mit virtuellen Funktionen
ein versteckter Zeiger hinzugefügt wird (so genannter *vtptr* - *vtable pointer*).
Dieser Zeiger zeigt für ein bestimmtes Objekt auf eine Tabelle mit Funktionszeigern (pro Klasse eine Tabelle),
um diese bei Bedarf (indirekt (!)) aufzurufen.

Das Problem des dynamischen Polymorphismus kann höhere Laufzeit bedeuten:

  * Zusätzliche Indirektionsstufe (Zeiger-Dereferenzierung) für jeden Aufruf einer virtuellen Methode.
  * Virtuelle Methoden können normalerweise nicht als `inline` aufgerufen werden, was für Methoden mit wenigen Anweisungen
    ein erhebliches Laufzeitproblem darstellen kann.
  * Zusätzlicher Zeiger pro Objekt: Auf 64-Bit-Systemen, die heutzutage vorherrschen, sind dies 8 Bytes pro Objekt.
    Bei kleinen Objekten mit wenigen Daten kann dies wiederum problematisch sein.

Es stellt sich heraus, dass C ++ mithilfe von Templates eine alternative Möglichkeit bietet,
Polymorphismus ohne zusätzliche Kosten zu implementieren. Es gibt natürlich einen Haken:
Die Datentypen dieser Objekte müssen vom Compiler zum Übersetzungszeitpunkt aufgelöst werden.
Dies wird als *statischer Polymorphismus* (oder auch als "simuliertes dynamisches Binden") bezeichnet.

## *Curiously Recurring Template Pattern* (CRTP) <a name="link2"></a>

Das *Curiously Recurring Template Pattern* genannte Entwurfsmuster ist eine Technik,
die eine Simulation des auf virtuellen Methoden basierenden Polymorphismus zur Kompilierungszeit ermöglicht.
In einem Satz formuliert kann man sagen:
"Das CRTP leitet Klassen aus einer Basisklassenvorlage ab, die mit der abgeleiteten Klasse zu parametrisieren ist".
Diese Technik ist nicht ganz neu, sie wird in einigen Bibliotheken
wie der Microsofts *Active Template Library* (ATL) und *Windows Template Library* (WTL)
intensiv eingesetzt.

Um zu demonstrieren, wie das CRTP funktioniert, betrachten wir ein Beispiel,
das eine Reihe von graphischen 'Control'-Klassen definiert.
Das Zeichnen eines derartigen Steuerelements soll in unserem Beispiel eine Operation sein,
die in zwei Phasen ausgeführt wird:

  * Löschen des Hintergrunds (Methode `eraseBackground`)
  * Anschließendes Malen des Steuerelements (Methode `paint`)

Im Folgenden stellen wir nun eine Art Gebrauchsanweisung vor,
wie Sie das *Curiously Recurring Template Pattern* in der Praxis anwenden können:

1. Definieren Sie eine Klassenschablone, die eine Basisklasse für andere Klassen darstellt,
   die zur Übersetzungszeit polymorph zu behandeln sind.
   Polymorphe Methoden werden von dieser Klasse aufgerufen:

```cpp
template <class T> 
class Control
{
public:
    void draw()
    { 
        static_cast<T*>(this)->eraseBackground();
        static_cast<T*>(this)->paint();
    } 
};
```

2. Abgeleitete Klassen verwenden diese Klassenschablone als Basisklasse.
   Die abgeleitete Klasse ist auch das Template Argument für die Basisklasse.
   Die abgeleitete Klasse implementiert die Funktionen, die von der Basisklasse aufgerufen werden:

```cpp
class Button : public Control<Button>
{
public: 
    void eraseBackground()
    {
        std::cout << "erasing button background ..." << std::endl;
    }

    void paint() 
    { 
        std::cout << "painting button ..." << std::endl; 
    }
};

class Checkbox : public Control<Checkbox>
{
public: 
    void eraseBackground() 
    { 
        std::cout << "erasing checkbox background ..." << std::endl;
    }

    void paint()
    {
        std::cout << "painting checkbox ..." << std::endl;
    }
};
```

3. Funktionsschablonen können nun abgeleitete Klassen polymorph 
   durch einen Zeiger oder Verweis auf die Basisklassenvorlage verarbeiten:

```cpp
template <class T>
void drawControl(Control<T>& c)
{
    c.draw();
}

void test_crtp()
{
    Button b;
    drawControl(b);

    Checkbox c;
    drawControl(c);
}
```

###### *Ausgabe*:

```
erasing button background ...
painting button ...
erasing checkbox background ...
painting checkbox ...
```

## Funktionsweise von CRTP <a name="link3"></a>

Virtuelle Methoden können ein Performanceproblem aufweisen,
wenn sie wenige Anweisungen enthalten und häufig in einer Wiederholungsschleife aufgerufen werden.
Moderne Hardware verdeckt viele dieser Situationen,
aber es gibt dennoch einige Kategorien von Anwendungen,
für die Performance kritisch ist und die Leistungssteigerungen zu schätzen wissen.
Das CRTP Muster ermöglicht die Simulation von virtuellen Aufrufen zur Kompilierungszeit mit Mechanismen der Metaprogrammierung,
die letzten Endes in der Überladung (Overloading) von Methoden resultieren.

Das Muster mag auf den ersten Blick ziemlich seltsam aussehen, daher auch der Name,
aber es ist in seinem Aufbau vollkommen korrektes C++. 
Die Idee besteht darin, eine Klasse von einer Basisklasse abzuleiten,
die eine Templateklasse ist und die abgeleitete Klasse selbst
als Typ Template Argument an die Basisklasse zu übergeben.

Die Basisklasse ihrerseits ruft nun die abgeleiteten Klassenmethoden auf.
In unserem Beispiel wird die Methode `Control<Button>::draw()` deklariert,
bevor dem Übersetzer die `Button`-Klasse bekannt gemacht wird.
Die `Control`-Klasse jedoch ist eine Templateklasse, das heißt,
sie wird erst instanziiert, wenn der Übersetzer Anweisungen übersetzen muss,
die diese Klasse verwenden.
Wenn es dazu kommt, ist in unserem Beispiel die `Button`-Klasse bereits bekannt,
so dass Methodenaufrufe wie `Button::eraseBackground()` und `button::paint()` übersetzbar sind.

Um Methoden aus der abgeleiteten Klasse aufzurufen, müssen wir zuerst
einen Zeiger auf die abgeleitete Klasse haben.
Dies erfolgt mit einer `static_cast`-Konvertierung, wie wir am Beispiel von 
`static_cast<T*>(this)->eraseBackground()` sehen können.
Sollten Sie diese Anweisungen in ihrem Quellcode häufig benötigen,
dann könnten Sie ihren Quellcode auch mit einer privaten Hilfsmethode vereinfachen:

```cpp
template <class T>
class ControlEx : public ControlBase
{
public:
    void draw()
    {
        derived()->erase_background(); 
        derived()->paint();
    }

private:
    T* derived() { return static_cast<T*>(this); }
};
```

## Einschränkungen von CRTP <a name="link4"></a>

Wenn Sie CRTP einsetzen wollen, müssen Sie sich einiger Einschränkungen oder Fallstricke
bei der Verwendung bewusst sein:

1. Alle Methoden in den abgeleiteten Klassen, die aus der Basisklasseschablone aufgerufen werden,
   müssen `public` sein. Eine Umgehung dieses Sachverhalts besteht darin,
   die Spezialisierung der Basisklasse als Freund der abgeleiteten Klasse zu deklarieren:

```cpp
// does NOT compile: 'Button::paint': cannot access private member declared in class 'Button'
class Button : public Control<Button>
{
private: 
    void paint() 
    { 
        std::cout << "painting button ..." << std::endl; 
    }
    ...
};
```

Diese Variante der Klasse `Button` hingegen ist übersetzungsfähig:

```cpp
class ButtonEx : public Control<ButtonEx>
{
friend class Control<ButtonEx>;

private:
    void eraseBackground()
    {
        std::cout << "erasing button background ..." << std::endl;
    }

    void paint()
    {
        std::cout << "painting button ..." << std::endl;
    }
};
```

2. Es ist nicht möglich, Objekte von CRTP-Typen in einem homogenen STL-Container (`std::list`, `std::vector`) zu abzuspeichern.
   Der Grund liegt darin, dass jede Basisklasse eines solchen Typs (wie zum Beispiel `Control<Button>` oder `Control<Checkbox>`) 
   ein separater eindeutiger Typ ist, was gegen die Philosophie des virtuellen Polymorphismus verstößt.
   Mit einem Workaround kann man dieses Problem aber umgehen, siehe dazu den nächsten Punkt.

3. Wenn Sie Objekte von CRTP-Typen in einem homogenen STL-Container ablegen wollen,
   muss die Basisklassenschablone ihrerseits von einer weiteren Klasse abgeleitet sein.
   Diese Klasse wiederum muss entsprechende abstrakte Methoden (*pure virtual*) und einen
   virtuellen Basisklassendestruktor aufweisen.
   Um dies an der `Control`-Klasse zu veranschaulichen, sind folgende Änderungen bzw.
   Erweiterungen erforderlich:

```cpp
class ControlBase 
{ 
public : 
    virtual void draw() = 0; 
    virtual ~ControlBase() {}
};

template <class T> 
class Control : public ControlBase
{
public:
    void draw()
    { 
        static_cast<T*>(this)->eraseBackground();
        static_cast<T*>(this)->paint();
    } 
};
```

An den abgeleiteten Klassen selbst sind keine Änderungen erforderlich,
wie zum Beispiel an den Klassen `Button` und `Checkbox`.
Nun lassen sich Zeiger auf die abstrakte Basisklasse (hier: `ControlBase`) 
wie folgt in einem Container abspeichern:

```cpp
void drawControls(std::vector<std::shared_ptr<ControlBase>>& controls) {

    for (auto& control : controls) { 
        control->draw();
    }
}

void test_crtp_02()
{
    std::vector<std::shared_ptr<ControlBase>> vector;

    vector.emplace_back(std::make_shared<Checkbox>());
    vector.emplace_back(std::make_shared<Button>());

    drawControls(vector);
}
```

###### *Ausgabe*:

```
erasing checkbox background ...
painting checkbox ...
erasing button background ...
painting button ...
```

## Ein zweites Beispiel <a name="link5"></a>

Ein zweites Beispiel zur Technik des CRTP finden Sie im Aufgabenteil vor.
Die Laufzeiten der beiden Varianten (*klassischer* versus *statischer* Polymorphismus) sieht auf meinem Rechner so aus:

```cpp
Time taken: 53401 microseconds
Time taken: 16082 microseconds
```

Man erkennt unschwer, dass die Variante des "*statischen* Polymorphismus" ca. um den Faktor 3 schneller ist.


#### *Hinweis*:

Beim Vergleich der Programmlaufzeiten dieses Beispiels ist strikt darauf zu achten,
dass in den Projekt-Einstellungen der "**Release**"-Modus eingestellt ist!
Die Unterschiede bzgl. der Laufzeiten zwischen "*Debug*"-Modus und "*Release*"-Modus sind exorbitant groß!


## Literaturhinweise <a name="link6"></a>

Die Anregungen zu den Beispielen aus diesem Abschnitt sind aus dem Buch

[Modern C++ Programming Cookbook](https://mariusbancila.ro/blog/2016/11/07/my-book-on-modern-c-programming/)<br>(abgerufen am 23.09.2020).

von Marius Bancila entnommen.

Weitere gute Beispiele und Beschreibungen dieses Themas finden sich in

[The Curiously Recurring Template Pattern in C++](https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c/)<br>(abgerufen am 26.05.2020).

und

[Curiously recurring template pattern (CRTP)](https://www.geeksforgeeks.org/curiously-recurring-template-pattern-crtp-2/)<br>(abgerufen am 26.05.2020).

---

[Zurück](../../Readme.md)

---
