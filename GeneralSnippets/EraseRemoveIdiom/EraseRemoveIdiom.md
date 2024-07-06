# Erase Remove Idiom

[Zur�ck](../../Readme.md)

---

[Quellcode](EraseRemoveIdiom.cpp)

---

## Allgemeines

Das Idiom *Erase-Remove* ist eine C++-Technik, um Elemente aus einem Container zu entfernen, die ein bestimmtes Kriterium erf�llen.
Nat�rlich w�re es m�glich, Elemente eines STL-Containers mit traditionellen, herk�mmlichen Techniken zu eliminieren,
aber das *Erase-Remove* Idiom hat mehrere Vorteile, die sich vor allem auf die Laufzeit des Programms auswirken.

  * STL-Algorithmus `std::remove`, `std::remove_if`:
    Das Entfernen der betroffenen Elemente erfolgt durch Verschieben der Elemente im Container so,
    dass die Elemente, die nicht entfernt werden sollen, am Anfang erscheinen.
    Dies hat zur Folge, dass sich im hinteren Teil des Containers diejenigen Elemente ansammeln,
    die eigentlich nicht mehr zum Container geh�ren.
    Die physische Gr��e des Containers bleibt bei dieser Methode unver�ndert,
    es werden faktisch nur Elemente im Container verschoben.

    Welche Elemente dann nicht mehr zum Container geh�ren, wird durch den R�ckgabewert der Methode zum 
    Ausdruck gebracht: Dies ist ein Iterator-Objekt, das auf das erste, nicht mehr dazugeh�rige Element im Container zeigt.

  * STL-Algorithmus `std::erase`:
    Mit dieser Methode lassen sich Elemente eines STL-Containers entfernen (ein einzelnes Element oder ein Bereich von Elementen).
    Die Methode verringert die Gr��e des Containers entsprechend.

## Das *Erase-Remove* Idiom

Mit einer Kombination von `std::remove` / `std::remove_if` und `std::erase` ist Code zum L�schen und Entfernen von Elementen nicht nur ausdrucksvoller, sondern auch effizienter.

Zuerst verwendet man `std::remove` / `std::remove_if`, um alle Elemente, die *nicht* dem Kriterien f�r das Entfernen entsprechen,
an den Anfang des Bereichs zu verschieben, wobei die relative Reihenfolge der Elemente beibehalten wird.
Danach l�scht ein einziger Aufruf von `std::erase` alle verbleibenden, aber nicht mehr zum Container geh�renden,
Elemente am Ende des Bereichs.

Man kann dies in der Regel in einer einzigen Programmzeile formulieren,
siehe dazu das Beispiel im korrespondierenden Quellcode. Man betrachte die Ausgaben des Beispiels genau:

```
Length:   10
Capacity: 10
0 1 2 5 4 5 6 5 8 9

Position of iterator: 7
Length:   10
Capacity: 10
0 1 2 4 6 8 9 5 8 9

Length:   7
Capacity: 10
0 1 2 4 6 8 9
```

---

[Zur�ck](../../Readme.md)

---

