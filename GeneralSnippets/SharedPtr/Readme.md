# Shared Pointer

Es erfolgt eine Gegenüberstellung:

  * Dynamisches Allokieren eines Objekts - klassisch mit new und delete
  * Dynamisches Allokieren eines Objekts mit der Wrapper-Klasse `std::shared_ptr`


Ausgabe des Code-Snippets - klassisch:

```cpp
Begin-of-program
c'tor Dummy
Hello World
d'tor Dummy
End-of-program
```

Ausgabe des Code-Snippets - mit Wrapper-Klasse:

```cpp
Begin-of-program
c'tor Dummy
outer use_count: 1
Hello World
inner use_count: 2
outer use_count: 1
End-of-program
d'tor Dummy
```

In beiden Fällen wird der Destruktor einer Testklasse `Dummy` aufgerufen, soweit passt alles.

Wenn man die beiden Ausgaben genau vergleicht, erkennt man, dass die letzten beiden Zeilen vertauscht sind.
Das hat sehr wohl seine Richtigkeit: In der klassischen Variante wird der `delete`-Operator explizit aufgerufen,
damit kommt es zum Destruktor-Aufruf, bevor die `main`-Funktion verlassen wird.

In der zweiten Variante wird der Destruktor des Testobjekts implizit im Destruktor der `std::shared_ptr`-Wrapperklasse aufgerufen.
Damit erfolgen etwaige Testausgaben nach dem eigentlichen Verlassen der `main`-Funktion.

Ein weiteres Snippet demonstriert, wie sich ein Shared-Pointer "sharen" lässt:

Ausgabe des Code-Snippets:

```cpp
Begin-of-program
c'tor Dummy
use_count: 3
use_count: 3
use_count: 3
End-of-program
d'tor Dummy
```