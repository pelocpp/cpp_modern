# Aufgaben zu CRTP

[Zurück](Exercises.md)

---

[Lösungen](Exercises_10_CRTP.cpp)

---

## Aufgabe 1: Der *kuriose* Polymorphismus (CRTP) an einem Beispiel betrachtet

#### Voraussetzungen: Polymorphismus, Templates

Polymorphismus ist die Fähigkeit, mehrere Implementierungen für dieselbe Schnittstelle zu unterstützen.
Virtuelle Methoden ermöglichen es abgeleiteten Klassen, Implementierungen aus einer Basisklasse überschreiben.
Wir sprechen hier von der klassischen Form des Polymorphismus, auch als *Late-Bindung* bezeichnet,
weil die Entscheidung, eine bestimmte Methode aufzurufen, zur Laufzeit erfolgt.
Das Gegenteil dazu ist die so genannte "frühe Bindung" (*Early-Bindung*),
die zur Übersetzungszeit stattfindet.

Ein großer Unterschied zwischen beiden Techniken besteht in der Laufzeit des Programms.
Das frühe Binden, das zur Übersetzungszeit stattfindet, ermöglicht es dem Übersetzer,
die Adressen der Methoden direkt im Compilat zu generieren (es eigentlich der *Linker*, auf den wir hier nicht näher eingehen wollen).
Das späte Binden erzwingt den Aufruf einer Methode indirekt über eine Tabelle mit Methodenadressen (*vtable*, *virtual function pointer table*),
die zur Laufzeit adressiert wird. Je nachdem, wie häufig virtuelle Methoden aufgerufen werden,
können die Auswirkungen auf die Laufzeit erheblich sein.

In dieser Übung wollen wir einen Laufzeitvergleich zwischen dem klassischen Polymorphismus
und einer Variation davon, dem "*Curiously Recurring Template Pattern (CRTP)*" anstellen.

Betrachten Sie hierzu das folgende Code-Fragment. Es besteht aus der einfachsten Form einer Hierarchie
von zwei Klassen. Die Methoden besitzen eine triviale Implementierung mit dem Ziel, den C++-Optimizer davon abzuhalten,
die Methodenrümpfe gänzlich wegzuoptimieren. Bei zu trivialen Beispielen erzielen vergleichende Benchmark-Tests
keine seriösen Aussagen.

Stellen Sie das Beispiel-Programm auf CRTP-konforme Klassen um.
Analysieren Sie mit entsprechenden Wiederholungsanweisungen, welchen Unterschied Sie in der Laufzeit der beiden
Testprogramme feststellen können.

*Hinweis*:
Damit Sie die erwünschten Ergebnisse beobachten können, müssen Sie in Ihren Programmeinstellungen
zwingend den "Release"-Modus und die "x64"-Konfiguration eingestellt haben.

Damit zum Beispiel: Sie finden eine Basisklasse `Image` und eine davon abgeleitete Klasse `PngImage` vor.
Die Basisklasse `Image` definiert drei abstrakte Methoden `draw`, `drawPixel` und `getNumPixels`.
Diese werden in der abgeleiteten Klasse mit einiger "Fantasie" der Gestalt überschrieben,
dass sie der C++-Optimierer nicht gänzlich wegoptimieren kann.
Kopieren Sie das Code-Fragment in ihre Entwicklungsumgebung und führen Sie es aus.
Gegebenenfalls müssen Sie die Konstante `MaxIterations` anpassen, damit Sie auf Ihrem Rechner
eine adäquate Laufzeit erzielen.

Realisieren Sie anschließend zwei Klassen `ImageCRTP` und `PngImageCRTP` unter Beachtung
des CRTP-Patterns. Vergleichen Sie die Laufzeiten der beiden Programme. Welche Beobachtung machen Sie?


```cpp
using Clock = std::chrono::high_resolution_clock;
constexpr long MaxIterations = 10000;
constexpr bool Verbose = false;
constexpr int Width = 400;
constexpr int Height = 400;

// classical approach: base class for image types
class Image {
protected:
    long m_width;
    long m_height;

public:
    // c'tor
    Image(int width, int height) : m_width{ width }, m_height{ height } {}

public:
    // public interface
    virtual void draw() = 0;
    virtual void drawPixel(int position) = 0;
    virtual long getNumPixels() = 0;
};

class PngImage : public Image {
private:
    long m_numPixels;
    long m_currPixel;

public:
    PngImage() : Image{ 0, 0 }, m_currPixel(0) { setNumPixels(); }
    PngImage(int width, int height) : Image{ width, height } { setNumPixels(); }

    virtual void draw() override {
        // just to prevent optimizer to optimize "too much" some sloppy stuff
        m_currPixel = 0;
        int numPixels = getNumPixels();
        int currPosition = getCurrPixel();
        while (currPosition != numPixels) {
            drawPixel(currPosition);
            incCurrPixel();
            currPosition = getCurrPixel();
        }
    }

    virtual void drawPixel(int position) override {
        if (Verbose) {
            std::cout << "draw pixel at position " << position << std::endl;
        }
    }

    virtual long getNumPixels() override {
        return m_numPixels;
    }

private:
    // private helper methods
    void setNumPixels() {
        m_numPixels = m_width * m_height;
    }

    long getCurrPixel() {
        return m_currPixel;
    }

    void incCurrPixel() {
        m_currPixel++;
    }
};

// driver code for classical polymorphism benchmark
void test_classic_benchmark()
{
    std::cout << "Classical Polymorphism Benchmark: " << std::endl;

    Image* pImage = new PngImage(Width, Height);

    auto start = Clock::now();

    // call draw several times to make sure performance is visible 
    for (int i = 0; i < MaxIterations; ++i) {
        pImage->draw();
    }

    long pixels = pImage->getNumPixels();
    std::cout << "Pixels: " << pixels << std::endl;

    auto end = Clock::now();
    std::cout << "Time taken: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " microseconds" << std::endl;
}
```

Da es gerade bei dieser Übung immer wieder zu überraschenden Ergebnissen kommt, hier die Resultate
meines Rechners:

```
Classical Polymorphism Benchmark:
Pixels: 160000
Time taken: 2014668 microseconds
CRTP Benchmark:
Pixels: 160000
Time taken: 402634 microseconds
```

---

[Lösungen](Exercises_10_CRTP.cpp)

---

[An den Anfang](#Aufgaben-zu-CRTP)

---
