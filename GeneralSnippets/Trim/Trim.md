# Leerzeichen am Anfang und Ende einer Zeichenkette entfernen

## `std::find_if`, `erase` und `base`

[Zur�ck](../../Readme.md)

---

[Quellcode](Trim.cpp)

---

Im Quellcode wird gezeigt, wie sich der STL-Algorithmus `std::find_if` einsetzen l�sst, um eine `trim`-Funktion f�r Zeichenketten zu realisieren.
`std::find_if` wird sowohl mit einem Vorw�rts- als auch einem R�ckw�rts-Iterator angewendet,
um jeweils das erste &bdquo;non-space&rdquo;-Zeichen zu finden.
Das so gefundene Iterator-Objekt kann nun an die `erase`-Methode der Klasse `std::string` �bergeben werden.

*Hinweis*: Bei R�ckw�rts-Iteratoren gilt es eine Eigenheit zu beachten:
Ist `rit` ein R�ckw�rts-Iterator, so kann mit `base()` der korrespondierende Vorw�rts-Iterator `it` bestimmt werden.
Dabei gilt zwischen `rit` und `it` die folgende &ndash; auf den ersten Blick nicht ganz einleuchtende &ndash; Beziehung:

```cpp
*rit == *(it - 1)
```

Siehe dazu auch die folgenden Abbildung:

<img src="cpp_snippet_base_02.svg" width="350">

*Abbildung* 1: Vorw�rts- und R�ckw�rts-Iteratoren im Vergleich.

Bei der Realisierung der entsprechenden `trim`-Funktionen ist zu beachten,
dass diese prinzipiell auf dem Original-Objekt agieren oder aber das Ergebnis in Form einer Kopie zur�ckliefern k�nnen.
Im [Quellcode](Trim.cpp) finden Sie beide Realisierungen vor.

---

## `base`-Methode

Die `base`-Methode wandelt einen R�ckw�rts-Iterator in den entsprechenden Vorw�rts-Iterator um.
Trotz dieser einfachen Funktionalit�t ist diese Zuordnung nicht ganz so trivial, wie man meinen k�nnte.
Wenn ein R�ckw�rts-Iterator auf ein Element zeigt, wird beim Dereferenzieren das &bdquo;vorherige&rdquo; Element zur�ckgeliefert!
Dies bedeutet, dass das Element, auf das er physisch zeigt, und das Element, auf das er logisch verweist, unterschiedlich sind!

Im folgenden Diagramm ist `it` ein Vorw�rts-Iterator und `rit` ein R�ckw�rts-Iterator, der sich auf `it` bezieht:

<img src="cpp_snippet_base_01.svg" width="350">

*Abbildung* 2: Zusammenhang von Vorw�rts- und R�ckw�rts-Iterator.

Wenn `rit` also logisch auf Element 2 zeigt, zeigt es physisch auf Element 3.
Der Vorw�rts-Iterator hingegen zeigt sowohl physisch als auch logisch auf das Element 3.
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

[Trim a string in C++ � Remove leading and trailing spaces](https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/)<br>(abgerufen am 21.09.2021).

Die Besonderheit der `base`-Methode ist beschrieben unter

[How to call erase with a reverse iterator](https://stackoverflow.com/questions/1830158/how-to-call-erase-with-a-reverse-iterator/)<br>(abgerufen am 21.09.2021).

oder

[C++ STL what does base() do](https://stackoverflow.com/questions/16609041/c-stl-what-does-base-do/)<br>(abgerufen am 21.09.2021).

---

[Zur�ck](../../Readme.md)

---
