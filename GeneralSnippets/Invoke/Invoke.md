# Funktion `std::invoke`: "*Uniformly invoking anything callable*"

[Zur�ck](../../Readme.md)

---

[Quellcode](Invoke.cpp)

---

Der Begriff des *Callables* tritt in C++ an vielen Stellen in Erscheinung.
Man z�hlt dazu

  * eine (regul�re) Funktion,
  * einen Zeiger auf eine (regul�re) Funktion,
  * einen Zeiger auf eine Methode (*member function pointer*),
  * ein Funktionsobjekt,
  * ein aufrufbares Objekt,
  * eine Lambda-Funktion

Mit C++ 17 hat man nun eine Standardfunktion `std::invoke` erg�nzt, 
die jedes *Callable* mit einer entsprechenden Liste von Parametern aufrufen kann.

`std::invoke` ist eine variadische Funktionsschablone, die
das aufrufbare Objekt als erstes Argument entgegennimmt und anschlie�end eine variable
Anzahl von Argumenten, die an den Aufruf �bergeben werden.

Der Sinn und Zweck von `std::invoke` ist es nicht,
den direkten Aufrufe zu ersetzen,
aber `std::invoke` kann n�tzlich sein bei der Programmierung von
Templates und allgemein gehaltenen Bibliotheksfunktionen.

Ausgabe des Code-Snippets:

```cpp
result: 3
result: 7
result: 11
m_x: 5
result: 5
result: 13
result: 15
a: 23
```

---

[Zur�ck](../../Readme.md)

---
