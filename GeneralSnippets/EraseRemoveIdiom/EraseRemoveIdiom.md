# Erase Remove Idiom

[Quellcode](EraseRemoveIdiom.cpp)

---

*Allgemeines*:

Das Idiom *Erase-Remove* ist eine C++-Technik, um Elemente aus einem Container zu entfernen, die ein bestimmtes Kriterium erfüllen.
Natürlich wäre es möglich, Elemente eines STL-Containers mit traditionellen, herkömmlichen Techniken zu eliminieren,
aber das *Erase-Remove* Idiom hat mehrere Vorteile.

STL-Algorithmus `std::remove`, `std::remove_if`:

Das Entfernen der betroffenen Elemente erfolgt durch Verschieben der Elemente im Container so,
dass die Elemente, die nicht entfernt werden sollen, am Anfang erscheinen.

Dies hat zur Folge, dass in hinteren Teil des Containers sich diejenigen Elemente ansammeln,
die eigentlich nicht mehr zum Container gehören. Die physische Größe des Containers bleibt bei dieser Methoden jedoch unverändert,
es werden faktisch nur Elemente im Container verschoben.

Welche Elemente eigentlich nicht mehr zum Conainer gehören, wird durch den Rückgabewert der Methode zum 
Ausdruck gebracht: Dies ist ein Iterator-Objekt, das auf das erste nicht mehr dazugehörige Element zeigt.

STL-Algorithmus `std::erase`:

Mit dieser Methoden lassen sich Elemente eines STL-Containers entfernen (ein einzelnes Element oder aber ein Bereich von Elementen).
Die Methode verringert die Größe des Containers entsprechend.

Mit einer Kombination von `std::remove` / `std::remove_if` und `std::erase` ist Code zum Löschen und Entfernen von Elementen nicht nur ausdrucksvoller, sondern auch effizienter.

Zuerst verwendet man `std::remove` / `std::remove_if`, um alle Elemente, die *nicht* dem Kriterien für das Entfernen entsprechen,
an den Anfang des Bereichs zu verschieben, wobei die relative Reihenfolge der Elemente beibehalten wird.
Danach löscht ein einziger Aufruf von `std::erase` alle verbleibenden, aber nicht mehr zum Container gehörenden Elemente,
am Ende des Bereichs.

Siehe das Beispiel im korrespondierenden Quellcode. Man betrachte die Ausgaben des Beispiels genau:

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

[Zurück](../../Readme.md)

---

