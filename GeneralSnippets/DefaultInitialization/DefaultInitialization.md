# Default-Initialisierung f�r Member-Variablen

[Zur�ck](../../Readme.md)

---

*Hinweis*:

Siehe dazu auch die Spracherweiterung [*Uniform Initialization*](../../GeneralSnippets/BraceInitialization/BraceInitialization.md).

---

# Default-Initialisierung f�r Member-Variablen

Eines der weniger bekannten, aber dennoch n�tzlichen Features
ab C++ 11 ist die M�glichkeit, Initialisierungen f�r Instanzvariablen
direkt in der Klassendefinition (und damit typischerweise im Header-File) bereitzustellen.

## Wie funktioniert es 

Man kann einfach einen Vorbelegungswert angeben,
indem man diesen Wert nach seiner Deklaration in der Klassendefinition
hinzuf�gt. Sowohl Initialisierungen mit geschweiften Klammern (siehe "*Brace Initialization*")
als auch in Gestalt 
einer Wertzuweisung sind zul�ssig - sie werden daher im C++-Standard als
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
w�hrend `m_j` mit 2 initialisiert wird, da diese Variable
in dieser "*Member Initialization List*" nicht explizit erw�hnt wurde.

Die "*Brace-or-Equal*"-Initialisierung f�r Instanzvariablen ist nicht auf Literale beschr�nkt.
Sie k�nnen auch Funktionen aufrufen oder andere Ausdr�cke verwenden.

# Default-Wert f�r Instanzvariablen bereitstellen

Offensichtlich funktioniert diese Feature am besten f�r Instanzvariablen,
die meistens mit demselben Wert oder einem Wert vorbelegt werden,
der durch den Aufruf einer statischen Funktion ermittelt werden kann.
Wenn Sie Klassen haben, deren Konstruktoren keine komplizierte Logik ben�tigen,
kann der Einsatz der Default-Initialisierung f�r Instanzvariablen das Erstellen von Konstruktoren f�r diese Klasse
sogar in G�nze unn�tig machen.

Im folgenden Beispiel initialisiert der vom Compiler generierte Standardkonstruktor
`m_i` mit 4 und `m_j` mit 5. Wenn Sie zus�tzliche Konstruktoren haben
und dennoch einen Standardkonstruktor m�chten,
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
kann der "*Brace-or-Equal*"-Initialisierer f�r Membervariablen
nicht nur das Hinzuf�gen dieser Variablen in die *Member Initialization List*
des Konstruktors ersparen, sondern es versieht jedes Element dieser Liste mit einem expliziten Hinweis darauf,
dass dieses Element eine Initialisierung besitzt,
die nicht dem Standardwert entspricht.

*Fazit*:

Betrachten Sie die Verwendung von "*Brace-or-Equal*"-Initialisierungen als Mittel,
um Standardwerte f�r Membervariablen bereitzustellen und um
*Member Initialization* Listen in Konstruktoren weniger l�nglich und daf�r
umso aussagekr�ftiger zu gestalten.

---

[Zur�ck](../../Readme.md)

---
