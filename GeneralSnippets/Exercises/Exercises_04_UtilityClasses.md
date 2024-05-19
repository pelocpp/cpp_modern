# Aufgaben zu Utility Klassen

[Zurück](Exercises.md)

---

[Lösungen](Exercises_04_UtilityClasses.cpp)

---

## Aufgabe 1: `std::visit` und generische Lambdas

#### Vorausetzungen: `if constexpr`, `decltype`, `std::variant`, `std::visit`, Type Traits, `std::remove_reference`,<br/>`std::is_scalar`, `std::is_same` und `std::remove_cvref`

Für `std::variant`-Objekte gibt es eine *Visitor*-Unterstützung in Gestalt der Funktion `std::visit`.
Diese benötigt neben einem `std::variant`-Objekt ein so genanntes *Callable*-Objekt,
das jede mögliche Alternative im `std::variant`-Objekt besuchen kann.
Eine sehr elegante wie auch kurze Lösung ist ein *Callable* in Gestalt eines generischen Lambdas,
siehe dazu folgendes Beispiel:

```cpp
// generic visitor (matching all types in the variant)
auto visitor = [](auto const& elem) {
    std::cout << elem << std::endl;
};

void test() {

    std::variant<int, double, std::string> var{ 123.456 };
    std::visit(visitor, var);

    var = 10;
    std::visit(visitor, var);

    var = std::string{ "ABCDE" };
    std::visit(visitor, var);
}
```

Einziger Wermutstropfen bei dieser Realisierung ist der Umstand,
dass es in dieser kurzen Fassung des Lambdas nicht möglich ist,
auf unterschiedliche Parametertypen zu reagieren.
Anders formuliert: Es ist per Quellcode nicht möglich, an Hand unterschiedlicher Parametertypen
unterschiedliche Aktionen auszuführen.

Wie könnte eine erweiterte Realisierung aussehen,
die &ndash; an dem gezeigten Beispiel &ndash; eine Unterscheidung der drei Datentypen `int`, `double` und `std::string` vornimmt?

*Hinweis*: Funktionen aus dem *Type Traits* Umfeld stellen eine große Hilfe dar.

*Zusatzaufgabe*:
Im vorliegenden Beispiel &ndash; `std::variant`-Objekt, unter anderem mit Werten des Typs `std::string` &ndash; ist
im Falle von Zeichenketten in der Lambda-Funktion die Länge der Zeichenkette auszugeben.
Welche Beobachtung machen Sie?

---

## Aufgabe 2: `std::optional`: Umwandlung von Zeichenketten in ganze Zahlen

#### Vorausetzungen: Templates Grundlagen, `std::optional`, `if constexpr`

Schreiben Sie eine Funktion `std::optional<int> toInt(std::string)`.
Der Rückgabewert vom Typ `std::optional<int>` darf nur dann einen gültigen `int`-Wert enthalten,
wenn sich die Zeichenkette `s` komplett in eine ganze Zahl umwandeln lässt.

Schreiben Sie eine zweite Funktion `toNumber`:

```cpp
template <typename T>
std::optional<T> toNumber(std::string s);
```

Realisieren Sie die Funktion analog zur Funktion `toInt`. Für `T` sollen die integralen Datentypen
`short`, `int`, `long` und `long long` als Template Argumente möglich sein.

---

[An den Anfang](#Aufgaben-zu-Utility-Klassen)

---

## Aufgabe 3: `std::variant`: Ein heterogener Container

#### Vorausetzungen: `std::variant`, `std::visit`, `std::vector`

Für STL-Container in C++ gilt prinzipiell die Anwort auf die Frage "Kann ich einen `std::vector` so verwenden,
dass er Variablen mehr als einen Typs enthält?": Nein!
Diese Aussage ist mit Erscheinen der Klasse `std::variant` etwas in Wanken geraten.
Ein Variant ist in C++ eine Datenstruktur, die zur Laufzeit Variablen unterschiedlichen Typs aufnehmen kann:

```cpp
std::variant<int, double, std::string> myVariant;
```

Also zum Beispiel

```cpp
myVariant = 1; // initially it's an integer
```

Um wiederum zur Laufzeit ermitteln zu können, welche Variable welchen Typs sich in einem Variant befindet,
gibt es die so genannten *Besucher*- / *Visitor*-Objekte:

Ein generischer, nicht-modifizierender Besucher, der das Variant-Objekt nicht verändert, könnte so definiert werden:

```cpp
struct MyPrintVisitor
{
    void operator()(const int& value) { 
        std::cout << "int: " << value << std::endl;
    }

    void operator()(const std::string& value) { 
        std::cout << "std::string: " << value << std::endl; 
    }
};
```

Um nun ein Variant-Objekt besuchen zu können, gibt es die Standard-Methode `std::visit`:

```cpp
std::variant<int, std::string> myVariant;
myVariant = 123;
std::visit(MyPrintVisitor{}, myVariant);
```

Mit diesem Code-Fragment erhalten wir die Ausgabe `123`.

Versuchen Sie, mit diesen Vorüberlegungen das Code-Fragment

```cpp
std::vector<std::variant<int, std::string>> heterogeneousVec;

heterogeneousVec.emplace_back(12);
heterogeneousVec.emplace_back(std::string("34"));
heterogeneousVec.emplace_back(56);
heterogeneousVec.emplace_back(std::string("78"));

// print them
for (const auto& var : heterogeneousVec) {
    std::visit(MyPrintVisitor{}, var);
}
```

zum Laufen zu bringen.

In einem weiteren Schritt wollen wir diesen Vektor in einer Klasse als Member-Variable ablegen.
Erstellen Sie eine Klasse `HeterogeneousContainer`.

```cpp
HeterogeneousContainer<int, std::string> heterogeneousCont;

heterogeneousCont.Values().emplace_back(12);
heterogeneousCont.Values().emplace_back(std::string("34"));
heterogeneousCont.Values().emplace_back(56);
heterogeneousCont.Values().emplace_back(std::string("78"));

// print them
heterogeneousCont.visit(lambdaAllInOneVisitor);
std::cout << std::endl;
```

Versuchen nun wiederum, dieses Code-Fragment zum Laufen zu bekommen.
Die Methode `Values` (*getter*) liefert eine Referenz des in der Klasse `HeterogeneousContainer`
gekapselten `std::vector<std::variant<...>`-Objekts zurück.

---

[Lösungen](Exercises_04_UtilityClasses.cpp)

---

[An den Anfang](#Aufgaben-zu-Utility-Klassen)

---
