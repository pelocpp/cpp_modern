# Default-Initialisierung für Member-Variablen

[Zurück](../../Readme.md)

---

*Hinweis*:

Siehe dazu auch die Spracherweiterung [*Uniform Initialization*](../../GeneralSnippets/UniformInitialization/UniformInitialization.md).

---

# Default-Initialisierung für Member-Variablen

Eines der weniger bekannten, aber dennoch nützlichen Features
ab C++ 11 ist die Möglichkeit, Initialisierungen für Instanzvariablen
direkt in der Klassendefinition (und damit typischerweise im Header-File) bereitzustellen.

## Wie funktioniert es 

Man kann einfach einen Vorbelegungswert angeben,
indem man diesen Wert nach seiner Deklaration in der Klassendefinition
hinzufügt. Sowohl Initialisierungen mit geschweiften Klammern (siehe "*Uniform Initialization*")
als auch in Gestalt 
einer Wertzuweisung sind zulässig - sie werden daher im C++-Standard als
"*Brace-or-Equal-Initializer*" bezeichnet:

```cpp
class X 
{
private:
  int m_i = 1;
  int m_j {2};

public:
  X(int);
};
```

Diese Initialisierungswerte werden dann implizit in jedem Konstruktor verwendet,
es sei denn, Sie initialisieren die Instanzvariablen **explizit** in der
"*Member Initialization List*" eines Konstruktors, wie zum Beispiel:

```cpp
X::X(int value) : m_i{ value }
{
  ...
}
```

In diesem Fall wird `m_i` mit dem Wert von `value` initialisiert,
während `m_j` mit 2 initialisiert wird, da diese Variable
in dieser "*Member Initialization List*" nicht explizit erwähnt wurde.

Die "*Brace-or-Equal*"-Initialisierung für Instanzvariablen ist nicht auf Literale beschränkt.
Sie können auch Funktionen aufrufen oder andere Ausdrücke verwenden.

# Default-Wert für Instanzvariablen bereitstellen

Offensichtlich funktioniert diese Feature am besten für Instanzvariablen,
die meistens mit demselben Wert oder einem Wert vorbelegt werden,
der durch den Aufruf einer statischen Funktion ermittelt werden kann.
Wenn Sie Klassen haben, deren Konstruktoren keine komplizierte Logik benötigen,
kann der Einsatz der Default-Initialisierung für Instanzvariablen das Erstellen von Konstruktoren für diese Klasse
sogar in Gänze unnötig machen.

Im folgenden Beispiel initialisiert der vom Compiler generierte Standardkonstruktor
`m_i` mit 4 und `m_j` mit 5. Wenn Sie zusätzliche Konstruktoren haben
und dennoch einen Standardkonstruktor möchten,
deklarieren Sie ihn als `default` und Sie sind fertig:

```cpp
class X 
{
private:
  int m_i = 4;
  int m_j {5};

public:
  X(int a) : m_i{ a } {}  // initializes m_i with a and m_j with 5
  X() = default;          // initializes m_i with 4 and m_j with 5
};
```

Insbesondere wenn Sie mehrere Konstruktoren haben und alle oder die meisten von ihnen
ihre Membervariablen mit demselben Wert initialisieren,
kann der "*Brace-or-Equal*"-Initialisierer für Membervariablen
nicht nur das Hinzufügen dieser Variablen in die *Member Initialization List*
des Konstruktors ersparen, sondern es versieht jedes Element dieser Liste mit einem expliziten Hinweis darauf,
dass dieses Element eine Initialisierung besitzt,
die nicht dem Standardwert entspricht.

*Fazit*:

Betrachten Sie die Verwendung von "*Brace-or-Equal*"-Initialisierungen als Mittel,
um Standardwerte für Membervariablen bereitzustellen und um
*Member Initialization* Listen in Konstruktoren weniger länglich und dafür
umso aussagekräftiger zu gestalten.

---

[Zurück](../../Readme.md)

---
