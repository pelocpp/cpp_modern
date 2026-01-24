# Aufgaben zu `constexpr`

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Maximum dreier Werte<br/>(Voraussetzungen: `constexpr`, Lambdas und teilweise Templates) |
| *Aufgabe* 2 | Maximum beliebig vieler Werte<br/>(Voraussetzungen: `constexpr`, Lambdas, variadische Templates und Folding) |
| *Aufgabe* 3 | RGB Farben<br/>(Voraussetzungen: `constexpr`) |
| *Aufgabe* 4 | Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit<br/>(Voraussetzungen: `decltype`, `std::is_same`) |

*Tabelle* 1: Aufgaben zu `constexpr`.

---

## Aufgabe 1: Maximum dreier Zahlen

#### Voraussetzungen: `constexpr`, Lambdas und teilweise Templates

Schreiben Sie eine Funktion `maximum`, die zu drei vorgegebenen Zahlen die größte Zahl ermittelt und als Rückgabewert zurückliefert.
Natürlich kommen hier `if`-Anweisungen ins Spiel, es gibt aber durchaus mehrere Möglichkeiten, das Ziel zu erreichen.

Die `maximum`-Funktion soll für alle elementaren Datentypen, die man vergleichen kann, aufrufbar sein.
Inwieweit beim Aufruf der `maximum`-Funktion alle drei Parameter denselben Datentyp haben müssen
oder &bdquo;geringfügige&rdquo; Unterschiede erlaubt sind,
ist Ihrer Entscheidung überlassen.

Die Funktion soll den Qualifizierer `constexpr` besitzen.
Überprüfen Sie Ihre Realisierung darauf hin, dass `maximum` bei konstanten Argumenten oder bei mit `constexpr` deklarierten Variablen
das Ergebnis bereits zur Übersetzungszeit berechnet.

*Beispiel*:

```cpp
constexpr auto result = maximum(1, 2, 3);
```

Aus dem Maschinencode des Programms können wir ablesen,
dass der Übersetzer den Wert 3 bereits berechnet hat:

```
constexpr auto result = maximum(1, 2, 3);
00007FF6CEF273CC  mov dword ptr [result1], 3   // <= value 3 resides in machine code  
```

##### Zusatzfrage:

Welche unterschiedlichen Möglichkeiten gibt es in der Deklaration der Schnittstelle der `maximum`-Funktion?
Diskutieren bzw. erläutern Sie die Unterschiede der jeweiligen Deklaration.

---

## Aufgabe 2: Maximum beliebig vieler Werte

#### Voraussetzungen: `constexpr`, Lambdas, variadische Templates und Folding

Als Ergänzung der letzten Aufgabe wollen wir nicht die Fragestellung außer Acht lassen,
ob sich die Realisierung der `maximum`-Funktion nicht auch auf beliebig viele Parameter erweitern lässt?

Natürlich geht das, nur ist in diesem Fall das Repertoire der einzusetzenden Modern C++ Sprachmittel größer.

Schreiben Sie eine Funktion `maximum`, die den maximalen Wert aller übergebenen Parameter berechnet
und als Ergebnis zurückliefert:

```cpp
constexpr int m{ maximum(1, 5, 3, 9, 2) };
```

Für die Übergabe beliebig vieler Argumente an die `maximum`-Funktion verwenden Sie eine Parameterdeklaration
mit variadischen Templates. Alternativ können Sie auch mit `auto` arbeiten.

Die explizite Berechnung des größten Werts auf der Grundlage eines Parameter Packs kann mit *Folding* erfolgen.
Es bietet sich ein Spezialfall dieser Technik an, das so genannte &bdquo;*Folding over a Comma*&rdquo;.

---

## Aufgabe 3: RGB Farben

#### Voraussetzungen: `constexpr`

Im Windows SDK (*System Development Kit* von Windows) gibt es die folgende Definition eines `RGB`-Makros (Datei *wingdi.h*):

```cpp
#define RGB(r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
```

Mit diesem Makro kann man mit drei primären Farben &ndash; Rot, Grün und Blau &ndash; beliebige Farben erzeugen.
Da die maximale Intensität jeder der drei Grundfarben 255 ist, genügt ein Doppelwort zum Abspeichern einer Farbe.
Hier wäre sogar noch Platz für einen vierten Kanal, den Alpha-Kanal, den wir der Einfachheit halber
in unsere Betrachtungen nicht mit einbeziehen.

Für den Datentyp einer Farbe gibt es in Windows die folgende Typdefinition:

```cpp
typedef DWORD COLORREF;
```

Jetzt fehlen noch die Definitionen für die verwendeten Datentypen wie z. B. `BYTE` oder `DWORD `,
die wir in der Datei *windef.h* vorfinden.
Ein (kleiner) Ausschnitt aus dieser Datei sieht so aus:


```cpp
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
...
```

Damit lassen sich nun in nativen Windows Anwendungen Farben auf folgende Weise definieren:

```cpp
COLORREF red       = RGB(255, 0, 0);
COLORREF lightBlue = RGB(173, 216, 230);
COLORREF aqua      = RGB(0, 255, 255);
COLORREF darkGreen = RGB(1, 50, 32);
```

*Teilaufgabe* 1:

Auch wenn es Microsoft (vor vielen Jahren) in seinen Implementierungen so gemacht hat,
muss das nicht heißen, dass dies eine gute Idee war.
Testen Sie folgende, leicht alternativ, formulierten Farbdefinitionen in einem kleinen Programm:

```cpp
COLORREF red       = RGB(255.0, 0.0, 0.0);
COLORREF lightBlue = RGB('173', '216', '230');
COLORREF aqua      = RGB("0", "255", "255");
COLORREF darkGreen = RGB(1000, 5000, 32000);
```

Kopieren Sie zu diesem Zweck einfach die Makro-Definitionen `COLORREF` und `RGB` aus der Einleitung in ihr Programm um.

Bei genauem Hinsehen erkennen Sie mal kleinere, mal größere Abweichungen im Vergleich zum Originalbeispiel.

  * Welche Fehlermeldungen erzeugt ein C/C++-Compiler bei den gezeigten Variablen?
  * Welche Werte erhalten Sie bei der Ausgabe der Farben in einer Konsole?

*Teilaufgabe* 2:

In einer Modern C++ Anwendung sind `#define`-Makros nicht mehr das Mittel der Wahl.
Schreiben Sie eine `constexpr`-Funktion `Rgb` mit derselben Funktionalität, wie sie das `RGB`-Makro besitzt.

Verwenden Sie dazu die `#include`-Datei `<cstdint>`, um Datentypen wie `std::uint8_t` oder `std::uint32_t` zur Verfügung zu haben.
Testen Sie nun erneut die Beispiele aus dem letzten Abschnitt.

Wir beginnen zunächst mit den &bdquo;korrekten&rdquo; Anweisungen:

```cpp
constexpr std::uint32_t red       = Rgb(255, 0, 0);
constexpr std::uint32_t lightBlue = Rgb(173, 216, 230);
constexpr std::uint32_t aqua      = Rgb(0, 255, 255);
constexpr std::uint32_t darkGreen = Rgb(1, 50, 32);
```

Nun wiederholen wir das Beispiel mit fehlerhaften Parametern:

```cpp
constexpr std::uint32_t red       = Rgb(255.0, 0.0, 0.0);
constexpr std::uint32_t lightBlue = Rgb('173', '216', '230');
constexpr std::uint32_t aqua      = Rgb("0", "255", "255");
constexpr std::uint32_t darkGreen = Rgb(1000, 5000, 32000);
```

Welche Beobachtungen machen Sie beim Übersetzen des Beispiels?

Vergleichen Sie die  `constexpr`-Realisierung mit der Realisierung auf Basis des `RGB` C-Makros.

*Teilaufgabe* 3:

Sollten Sie mit `constexpr` auf den Geschmack gekommen sein, dann gehen wir nun den nächsten Schritt
und erweitern die Funktionalität der `Rgb`-Funktion.
Zu diesem Zweck entwickeln wir eine Klasse `Color` mit folgender öffentlicher Schnittstelle:

| Methode | Schnittstelle und Beschreibung |
|:-|:-|
| Konstruktor | `constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b);`<br/>Benutzerdefinierter Konstruktor, die drei Kanäle `r`, `g` und `b` werden in das Objekt aufgenommen. |
| Konstruktor | `constexpr Color(const std::string_view s);`<br/>Benutzerdefinierter Konstruktor, die Farbe wird durch eine Zeichenkette in hexadezimaler Form beschrieben, z. B. `"#00FFFF"`  |
| Hilfsmethode | `static constexpr Color parse(std::string_view str);`<br/>Rechnet einen Farbwert in Zeichenkettendarstellung in einen numerischen Wert um. Das Ergebnis ist ein Objekt des Typs `Color`. |
| Hilfsmethode | `static constexpr std::optional<std::uint8_t> nibble(char n);`<br/>Dekodiert den Wert eines Nibbles in Zeichendarstellung (Zeichen `0` bis `9`, `a` bis `f` oder `A` bis `F`). Das Ergebnis ist ein numerischer Wert im Bereich von 0 bis 15. |
| Hilfsmethode | `static constexpr std::optional<std::uint8_t> byte(std::string_view sv);`<br/>Dekodiert den Wert eines Bytes in Zeichendarstellung (z. B. `"FF"` oder `"00"`). Das Ergebnis ist ein numerischer Wert im Bereich von 0 bis 255. |
| *getter*-Methode | `constexpr std::uint8_t GetRValue() const;`<br/>Liefert den R-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint8_t GetGValue() const;`<br/>Liefert den G-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint8_t GetBValue() const;`<br/>Liefert den B-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint32_t value() const;`<br/>Liefert den Farbwert in einer Variablen des Typs `std::uint32_t` zurück. |

*Tabelle* 1: Öffentliche und private Methoden der Klasse `Color`.

Verifizieren Sie Ihre Realisierung an folgenden Beispielen:

```cpp
constexpr Color cyan{ "#00FFFF" };

constexpr auto r{ cyan.GetRValue()};
constexpr auto g{ cyan.GetGValue() };
constexpr auto b{ cyan.GetBValue() };
std::cout << std::format("{:#04X}:{:#04X}:{:#04X}", r, g, b) << std::endl;

constexpr auto value{ cyan.value() };
std::cout << std::format("{:#010X}", value) << std::endl;
```

*Ausgabe*:

```
0X00:0XFF:0XFF
0X00FFFF00
```

Oder auch:

```cpp
constexpr Color red{ 255, 0, 0 };
constexpr Color lightBlue{ 173, 216, 230 };
constexpr Color aqua{ 0, 255, 255 };
constexpr Color darkGreen{ 1, 50, 32 };

std::cout << std::format("{:#010X}", red.value()) << std::endl;
std::cout << std::format("{:#010X}", lightBlue.value()) << std::endl;
std::cout << std::format("{:#010X}", aqua.value()) << std::endl;
std::cout << std::format("{:#010X}", darkGreen.value()) << std::endl;
```

*Ausgabe*:

```
0X000000FF
0X00E6D8AD
0X00FFFF00
0X00203201
```

---

## Aufgabe 4: Auswertung von variadischen Templates, `decltype` und Type-Traits am Beispiel von `sameType` zur Übersetzungszeit

#### Voraussetzungen: `std::is_same`

Schreiben Sie eine Funktionsschablone `sameType`, die eine beliebige Anzahl von Argumenten
beliebigen Typs akzeptiert. Der Rückgabewert vom Typ `bool` ist `true`, wenn alle Argumente vom selben Typ
sind, andernfalls `false` *und* ist zur Übersetzungszeit zu berechnen.

*Beispiel*:

```cpp
#include <iostream>

int main() 
{
    constexpr bool result1{ sameType(43, false, "hello") };
    std::cout << std::boolalpha << result1 << std::endl;

    constexpr bool result2{ sameType(1, 2, 3, 4, 5, 6, 7, 8, 9) };
    std::cout << std::boolalpha << result2 << std::endl;
}
```

*Ausgabe*:

```cpp
false
true
```

---

[Lösungen](Exercises_14_ConstExpr.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
