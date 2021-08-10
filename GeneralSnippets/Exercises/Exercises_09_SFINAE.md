# Aufgaben

[Zurück](Exercises_Ex.md)

---

## Aufgabe 1: Eine Methode, mehrere Implementierungen

#### Vorausetzungen: `std::array`

Arrays treten in C++ - unter anderem aus historischen Gründen - mehrfach in Erscheinung:
Als klassisches Array im Stile von C oder als Objekte der Klasse `std::array`.

Schreiben Sie eine Funktion `first`, die eine Referenz des ersten Arrayelements zurückliefert.
Bei klassischen C-Arrays sollte dies die Anfangsadresse des Arrays sein, bei `std::array`
das Iterator-Objekt `begin`.

---

[An den Anfang](#aufgaben)

---

## Aufgabe 2: Detektion von Methoden in einer Klasse

#### Vorausetzungen: Templates, `decltype` und `std::declval`

Das *Detection Idiom* (zu deutsch etwa &ldquo;Erkennungsidiom&rdquo;)
ermöglicht die Introspektion eines C++-Klassentyps zur Übersetzungszeit.
Einfacher ausgedrückt: Mithilfe dieses Idioms können wir überprüfen, ob eine Klasse eine bestimmte Methode
oder ein Element eines bestimmten Namens enthält &ndash; und das zur Übersetzungszeit.

Studieren Sie hierzu das folgende Klassentemplate `MethodDetector`:
Welchen Namen hat die Methode, die hier offensichtlich gesucht wird?
Welche Rolle spielen `decltype` und `std::declval` bei der Suche?

```cpp
01: template <typename T>
02: struct MethodDetector {
03: 
04:     template <typename U, typename TEST = decltype(std::declval<U>().get())>
05:     static constexpr bool detect(int) {
06:         return true;
07:     }
08: 
09:     template <typename U>
10:     static constexpr bool detect(...) {
11:         return false;
12:     }
13: 
14:     static constexpr bool value = MethodDetector::detect<T>(int{});
15: };
```

Es folgen einige Hinweise:<br/>

  * Im Klassentemplate gibt es zwei Methoden namens `detect`:
    Der Rückgabewert ist in beiden Fällen `bool`! 
    Die zweite Überladung akzeptiert bzgl. der aktuellen Parameter &ldquo;alles&rdquo;,
    was durch das Symbol der Ellipses `'...'` zum Ausdruck gebracht wird.

  * Die erste `detect`-Methode besitzt einen `int`-Parameter.
    Dies führt dazu, dass die erste `detect`-Methode gegenüber der zweiten `detect`-Methode, bevorzugt wird,
    wenn sie mit einem `int`-Wert aufgerufen wird.
    Diese Überladung kommt aber nur dann in die engere Auswahl,
    wenn der Ausdruck innerhalb von `decltype`, also die Berechnung des zweiten Template-Parameters `TEST`,
    fehlerfrei aufgelöst werden kann.

  * Je nachdem, für welche Überladung der Übersetzer sich entscheidet, liefert `detect` den Wert `true` oder `false` zurück.
    Die Klassenvariable `value` in Zeile 14 nimmt diesen Wert an.

**Aufgabe**:

Im folgenden sind zwei Klassen `FirstStruct` und `SecondStruct` definiert,
die unterschiedliche Methoden haben (`get` bzw. `getter`):

```cpp
struct FirstStruct {
    int get() { return 123; };
};

struct SecondStruct {
    int getter() { return 456; };
};
```

  * Welche Ausgabe erwarten Sie bei der Ausführung der folgenden beiden Anweisungen?
  * Erklären Sie detailliert, warum sich das Programm so verhält?
  * Welche Regel gilt bei der Auflösung von Funktionsschablonen im Falle von Mehrdeutigkeiten?

```cpp
std::cout
    << "FirstStruct:  "
    << std::boolalpha
    << MethodDetector<FirstStruct>::value
    << std::endl;

std::cout
    << "SecondStruct: "
    << std::boolalpha
    << MethodDetector<SecondStruct>::value
    << std::endl;
```

*Ausgabe*:

```cpp
FirstStruct:  true
SecondStruct: false
```

**Zusatzaufgabe 1**:

Im Lösungsteil finden Sie eine Variation in der Definition der ersten `detect`-Methode vor.
Beschreiben Sie ihre Funktionsweise!

*Antwort*:<br/>
In der ersten Überladung der Variation beachte man,
dass der Ausdruck innerhalb von `decltype` eine Sequenz ist (siehe den Komma-Operator `','`)!
Der Typ des Ausdrucks ist damit gleich dem des letzten Elements in der Sequenz und damit ebenfalls gleich `bool`.

**Zusatzaufgabe 2**:

Wie müsste eine Klasse `MethodDetectorEx` implementiert werden,
die eine Klasse überprüfen kann, ob sie  eine Methode namens `get` mit zwei Parametern des Typs `int` besitzt?
Realisieren und testen Sie eine entsprechende Klasse `MethodDetectorEx`.

*Abschließender Hinweis*: Die Anregungen zu dieser Aufgabe stammen teilweise aus
[C++ Detection Idiom Through the Years](https://people.eecs.berkeley.edu/~brock/blog/detection_idiom.php).

---

[Lösungen](Exercises.cpp)

---

[An den Anfang](#Aufgaben-zu-Lambda-Funktionen)

---

[Zurück](Exercises_Ex.md)

---
