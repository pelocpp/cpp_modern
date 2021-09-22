# Leerzeichen am Anfang und Ende einer Zeichenkette entfernen

## `std::find_if`, `erase` und `base`

[Zurück](../../Readme.md)

---

[Quellcode](Trim.cpp)

---

Im Quellcode wird gezeigt, wie sich der STL-Algorithmus `std::find_if` einsetzen lässt, um eine `trim`-Funktion für Zeichenketten zu realisieren.
`std::find_if` wird sowohl mit einem Vorwärts- als auch einem Rückwärts-Iterator angewendet,
um jeweils das erste &ldquo;non-space&rdquo;-Zeichen zu finden.
Das so gefundene Iterator-Objekt kann nun an die `erase`-Methode der Klasse `std::string` übergeben werden.

*Hinweis*: Bei Rückwärts-Iteratoren gilt es eine Eigenheit zu beachten:
Ist `rit` ein Rückwärts-Iterator, so kann mit `base()` der korrespondierende Vorwärts-Iterator `it` bestimmt werden.
Dabei gilt zwischen `rit` und `it` die folgende &ndash; auf den ersten Blick nicht ganz einleuchtende &ndash; Beziehung:

```cpp
*rit == *(it - 1)
```

Siehe dazu auch die folgenden Abbildung:

<img src="cpp_snippet_base_02.svg" width="350">

*Abbildung* 1: Vorwärts- und Rückwärts-Iteratoren im Vergleich.

Bei der Realisierung der entsprechenden `trim`-Funktionen ist zu beachten,
dass diese prinzipiell auf dem Original-Objekt agieren oder aber das Ergebnis in Form einer Kopie zurückliefern können.
Im [Quellcode](Trim.cpp) finden Sie beide Realisierungen vor.

---

## `base`-Methode

Die `base`-Methode wandelt einen Rückwärts-Iterator in den entsprechenden Vorwärts-Iterator um.
Trotz dieser einfachen Funktionalität ist diese Zuordnung nicht ganz so trivial, wie man meinen könnte.
Wenn ein Rückwärts-Iterator auf ein Element zeigt, wird beim Dereferenzieren das &ldquo;vorherige&rdquo; Element zurückgeliefert!
Dies bedeutet, dass das Element, auf das er physisch zeigt, und das Element, auf das er logisch verweist, unterschiedlich sind!

Im folgenden Diagramm ist `it` ein Vorwärts-Iterator und `rit` ein Rückwärts-Iterator, der sich auf `it` bezieht:

<img src="cpp_snippet_base_01.svg" width="350">

*Abbildung* 2: Zusammenhang von Vorwärts- und Rückwärts-Iterator.

Wenn `rit` also logisch auf Element 2 zeigt, zeigt es physisch auf Element 3.
Der Vorwärts-Iterator hingegen zeigt sowohl physisch als auch logisch auf das Element 3.
Das folgende kleine Programm demonstriert diesen Sachverhalt:

```cpp
std::vector<int> vec{ 1, 2, 3, 4, 5 };

std::vector<int>::iterator it = std::find(
    std::begin(vec),
    std::end(vec),
    3
);

std::cout << *it << std::endl;  // prints '3'

std::reverse_iterator<std::vector<int>::iterator> rit{ it };
std::cout << *rit << std::endl; // prints '2'

std::vector<int>::iterator i2 = rit.base();
std::cout << *i2 << std::endl;  // prints '3'
```

*Ausgabe*:

```
3
2
3
```

---

## Literaturhinweise:

Die Anregungen zu den Beispielen dieses Code-Snippets finden sich unter

[Trim a string in C++ – Remove leading and trailing spaces](https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/)<br>(abgerufen am 21.09.2021).

Die Besonderheit der `base`-Methode ist beschrieben unter

[How to call erase with a reverse iterator](https://stackoverflow.com/questions/1830158/how-to-call-erase-with-a-reverse-iterator/)<br>(abgerufen am 21.09.2021).

oder

[C++ STL what does base() do](https://stackoverflow.com/questions/16609041/c-stl-what-does-base-do/)<br>(abgerufen am 21.09.2021).

---

[Zurück](../../Readme.md)

---
