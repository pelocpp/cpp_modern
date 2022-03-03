# Aufgaben zu SFINAE

[Zurück](Exercises.md)

---

[Lösungen](Exercises_09_SFINAE.cpp)

---

## Aufgabe 1: Eine Funktion mit bestimmten Parametertypen

Wir betrachen folgende Funktion `distance`, die den Abstand zweier Punkte in der Ebene berechnet:

```cpp
template <typename T>
T distance(T a1, T a2, T b1, T b2)
{
    T tmp1 = a1 - b1;
    T tmp2 = a2 - b2;
    return std::sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
```

Auf die Schnelle erkennen wir ein Problem:

  * Prinzipiell ist die `distance`-Funktion für Argumente beliebigen Typs definiert, da es sich um eine Template Funktion handelt.
  * Im Rumpf von `distance` wird die Bibliotheksfunktion `std::sqrt` aufgerufen.
    Diese Funktion ist (C++ 17) aber nur für die drei Datentypen `float`, `double` und `long double` definiert.

Wollten wir `distance` mit einem anderen Template Parameter spezialisieren, z.B. `int`,
müssen wir mit Warnungen oder Fehlermeldungen des Übersetzers rechnen.
Für nicht-integrale Datentypen wiederum ergibt eine Spezialisierung von `distance` überhaupt keinen Sinn.

**Aufgabe**: Realisieren Sie eine Funktion `distance`, so dass diese nur mit Argumenten
des Typs `float` oder `double` aufgerufen werden kann.
Verwenden Sie hierzu die SFINAE-Technik!

---

[An den Anfang](#Aufgaben-zu-SFINAE)

---

## Aufgabe 2: Eine Methode, unterschiedliche Implementierungen

In dieser Aufgabe betrachten wir eine Template Funktion `print`:

```cpp
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstring>

template<class T>
void print(const T& arg) {
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
    std::cout << "[" << printTimeStamp(ttp) << "] " << arg << std::endl;
}
```

Die `print`-Funktion besitzt einen Parameter vom Typ des Template-Arguments 
und gibt seinen Wert mit einem Zeitstempel versehen auf der Konsole aus.
Für Argumente des Typs `std::string` bzw. `int` sieht die Ausgabe wie folgt aus:

```cpp
int n{ 123 };
print(n);
std::string s{ "a string" };
print(s);
```

*Ausgabe*:

```
[Mon Oct 18 11:02:55 2021] 123
[Mon Oct 18 11:02:55 2021] a string
```

*Hinweis*: Die `print`-Funktion darf auf die Realisierung
der folgenden Hilfsfunktion `printTimeStamp` zugreifen:

```cpp
char* printTimeStamp(const std::time_t& ttp)
{
    char* cp{ std::ctime(&ttp) };
    size_t len{ std::strlen(cp) };
    cp[len - 1] = '\0';
    return cp;
}
```

Die Datums- und Uhrzeitfunktionen von C sind in der C++-Standardbibliothek
noch nicht richtig angekommen. Aus diesem Grund muss man hier auf entsprechende C-Bibliotheksfunktionen
zurückgreifen. Verwenden Sie die `printTimeStamp`-Funktion &ldquo;*as it is*&rdquo;,
und nicht zu vergessen: Vor der `#include`-Anweisung der Datei `<ctime>` muss die Zeile

```cpp
#define _CRT_SECURE_NO_WARNINGS  
```

stehen!

Die `print`-Funktion lässt sich auch für Klassen spezialisieren &ndash; solange diese offensichtlich
den `<<`-Operator bereitstellen:

```cpp
class AnyClass
{
friend std::ostream& operator << (std::ostream& out, const AnyClass& m); 

public:
    AnyClass() : AnyClass{ 0 } {};
    AnyClass(int n) : m_i{ n } {};

protected:
    int m_i;
};

std::ostream& operator<<(std::ostream& os, const AnyClass& m) {
    return os << m.m_i;
}
```

Eine Anwendung der `print`-Funktion, etwa in der Gestalt

```cpp
AnyClass obj{ 456 };
print(obj);
```

führt zum erwarteten Ergbnis:

```cpp
[Mon Oct 18 11:16:16 2021] 456
```

Nun kommen wir auf das eigentliche Thema dieser Aufgabe zu sprechen: Bei Objekten des Typs `AnyClass` 
soll von der `print`-Funktion nicht der Ausgabe-Operator `<<` angewendet werden,
sondern eine spezifische Methode der Klasse `AnyClass` &ndash; nennen wir sie beispielsweise `log` &ndash; 
aufgerufen werden:

<pre><b>virtual void log() const {
    std::cout << "AnyClass: m_i=";
    std::cout << *this << std::endl;
}</b></pre>

Nun bräuchten wir eigentlich zwei unterschiedliche Implementierungen der `print`-Funktion:
Eine, die bei Template Parametern des Typs `AnyClass` die `log`-Methode aufruft,
und eine zweite, die bei allen anderen Template Parametern auf die ursprüngliche Implementierung von `print` zugreift.
Eine zweite Implementierung der `print`-Funktion &ndash; speziell für Klasse `AnyClass` &ndash; könnte so aussehen:

```cpp
template<typename T>
void print(const T& arg) {
    arg.log();
}
```

*Hinweis*: Sie werden es schon vermutet haben: Dieser Ansatz zweier `print`-Funktionen
führt nicht zum Ziel. Die meisten C++&ndash;Compiler werden diesen Versuch mit einer Fehlermeldung der Art

```
'void print(const T&)': function template has already been defined
```

quittieren!

**Aufgabe**:

Bringen Sie an Hand der vorgestellten Code-Fragmente das Programm prinzipiell zum Laufen.
Wenden Sie auf die beiden Realisierungen der `print`-Funktion das SFINAE-Prinzip an!
Das folgende Code-Fragent sollte nun ausführbar sein:

```cpp
char ch{ '!' };
print(ch);
AnyClass obj{ 123456 };
print(obj);
```

*Ausgabe*:

```
[Mon Oct 18 12:34:17 2021] !
AnyClass: m_i=123456
```

*Zusatzaufgabe*:

Die im Lösungsteil vorgestellte Realisierung löst die Aufgabenstellung,
aber sie lässt sich schwer erweitern. Wie gehen wir vor, wenn wir beispielsweise 
eine weitere Klasse `AnotherClass` haben, die ebenfalls eine `log`-Methode besitzt.
Auf einmal wird der Lösungsansatz unattraktiv,
weil wir die `print`-Funktion für jede weitere Klasse wiederholt implementieren müssten,
die eine `log`-Methode hat.

Versuchen Sie, einen anderen Ansatz zu wählen,
der die gewünschte `print`&ndash;Templatefunktion in Abhängigkeit
von einem Template Argument auswählt.

*Hinweis*: Studieren Sie das folgende Code-Fragment:

```cpp
template <typename, typename = void>
struct hasLogMessage : std::false_type {};

template <typename T>
struct hasLogMessage<T, decltype(std::declval<T>().log())> : std::true_type {};
```

Wir finden ein *primäres* Klassentemplate und eine partielle Templatespezialisierung vor.
Der zweite Template Parameter besitzt einen Voreinstellungswert.
In der partiellen Templatespezialisierung besitzt der zweite Template Parameter den Wert

```cpp
decltype(std::declval<T>().log())
```

`std::declval` legt zur Übersetzungszeit ein Objekt des Typs `T` an.
`decltype` bestimmt einen Datentyp, der sich durch den Rückgabedatentyp 
der Methode `log` ergibt unter der Vorraussetzung, dass der Typ `T` eine
derartíge Methode besitzt.
Besitzt `T` keine `log`&ndash;Methode, schlägt die Substitution fehl!

Die beiden Klassentypen `std::true_type` und `std::false_type` besitzen eine Klassenvariable `value`.

Damit können wir festhalten, dass bei einer Instanziierung von `hasLogMessage` in jedem Fall
durch die Vererbung eine Klassenvariable mit dem Namen `value` zur Verfügung steht!
Mit diesen Hilfestellungen sollten Sie nun in der Lage sein,
den zweiten Lösungsansatz sowohl zu verstehen als auch anwenden zu können.

Weitere Erläuterungen finden Sie unter
[Advanced C++ Templates Tutorial](https://levelup.gitconnected.com/advanced-c-templates-tutorial-7b54259b2671)
vor.

---

[An den Anfang](#Aufgaben-zu-SFINAE)

---


## Aufgabe 3: Detektion von Methoden in einer Klasse

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
    Dies führt dazu, dass die erste `detect`-Methode gegenüber der zweiten `detect`-Methode bevorzugt wird,
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

## Aufgabe 4: Eine Methode, unterschiedliche Implementierungen zum Zweiten

#### Vorausetzungen: `std::array`

Arrays treten in C++ - unter anderem aus historischen Gründen - mehrfach in Erscheinung:
Als klassisches Array im Stile von C oder als Objekte der Klasse `std::array`.

Schreiben Sie eine Funktion `first`, die eine Referenz des ersten Arrayelements zurückliefert.
Bei klassischen C-Arrays sollte dies die Anfangsadresse des Arrays sein, bei `std::array`
das Iterator-Objekt `begin`.

---

[An den Anfang](#Aufgaben-zu-SFINAE)

[Lösungen](Exercises_09_SFINAE.cpp)

---

[An den Anfang](#Aufgaben-zu-SFINAE)

---
