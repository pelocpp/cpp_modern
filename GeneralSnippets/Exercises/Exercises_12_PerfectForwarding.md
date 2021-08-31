# Aufgaben zum *Perfect Forwarding*

[Zurück](Exercises.md)

---

[Lösungen](Exercises_12_PerfectForwarding.cpp)

---

## Aufgabe 1: Einfaches Beispiel zu variadischen Templates und *Perfect Forwarding*

Schreiben Sie eine Funktion `list`, die eine variable Anzahl Parameter unterschiedlichen Typs besitzt.
Ein Aufruf der `list`-Funktion gibt jeden Parameter auf der Konsole mit einem anschließenden Zeilenumbruch aus.

*Beispiel*:

```cpp
int n = 123;
const double pi = 3.14;

list(10, "abc", n, pi, 2.4, std::string("ABC"), 99.99f);
```

*Ausgabe*:

```cpp
10
abc
123
3.14
2.4
ABC
99.99
```

*Ergänzung*:

Wie müssen Sie Ihre Realisierung ändern, so dass die Ausgabe von `list` im letzten Beispiel so aussieht:


```cpp
1: 10
2: abc
3: 123
4: 3.14
5: 2.4
6: ABC
7: 99.99
```

---

[An den Anfang](#Aufgaben-zum-Perfect-Forwarding)

---

## Aufgabe 2: Ausführungszeit einer Funktion

#### Voraussetzungen: `std::invoke`, variadische Templates

Schreiben Sie eine Funktion, die die Ausführungszeit einer weiteren Funktion messen kann.
Diese Funktion soll dabei eine beliebige Anzahl von Formalparametern haben können.

Die Zeitdauer messen wir im einfachsten Fall in Millisekunden.
In einer etwas anspruchsvolleren Lösung ist es auch denkbar, die Zeitmessung in unterschiedlichen Zeitformaten
durchführen zu können (z.B. Sekunden, Millisekunden, Mikrosekunden usw.).

*Hinweise*:

Um die Ausführungszeit einer Funktion zu messen, benötigen wir zunächst die aktuelle Zeit vor dem Aufruf der
Funktion. Führen Sie nach dieser ersten Zeitmessung die eigentliche Funktion aus,
rufen Sie dann die aktuelle Uhrzeit erneut ab und bestimmen Sie die Differenz von den beiden Zeitpunkten.

Einen aktuellen Zeitpunkt können Sie mit der Klasse `std::chrono::system_clock` ermitteln:

```cpp
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
```

Die Differenzbildung zweier Zeitwerte kann man mit `std::chrono::time_point_cast`-Objekten durchführen,
zum Beispiel:

```cpp
std::chrono::milliseconds diff = tpEnd - tpStart;
```

wenn `tpStart` und `tpEnd` als

```cpp
auto tpStart = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
auto tpEnd = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
```

definiert sind. Das Hauptprogramm für diese Übung könnte so aussehen:

```cpp
void g(int a, double b)
{
    // simulate some work (function with parameters)
    std::cout << "calling g with parameters " << a << " and " << b << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void main() 
{
    std::chrono::milliseconds time = ExecutionTimer::duration(g, 10, 20.0);
    std::cout << time.count() << " msecs." << std::endl;
}
```

Die Klasse `ExecutionTimer` mit einer statischen Methode `duration` führt in diesem Beispiel die Funktion `g` aus
und misst ihre Ausführungszeit.

---

[Lösungen](Exercises_12_PerfectForwarding.cpp)

---

[An den Anfang](#Aufgaben-zum-Perfect-Forwarding)

---
