# Shared Pointer: Klasse `std::shared_ptr`

[Zurück](../../Readme.md)

---

[Quellcode](StdSharedPtr.cpp)

---

## &ldquo;It's about ownership&rdquo;

###### Exklusiver Besitz: `std::unique_ptr<T>`

#### Geteilter Besitz: `std::shared_ptr<T>`

###### Temporärer Besitz: `std::weak_ptr<T>`

---

*Hinweis*:

Die beiden Varianten, ein `std::shared_ptr`-Objekt anzulegen, sind nicht
ganz identisch:

  * `std::shared_ptr` und expliziter `new` Aufruf
  * `std::make_shared` Aufruf

Ein `std::shared_ptr`-Objekt verwaltet zwei Speicherbereiche:

  * einen so genannten `Control-Block` (speichert Metadaten wie Referenz-Zähler, den *Deleter* für das Objekt usw.)
  * das zu allokierende Objekt selbst

Ein Aufruf von `std::make_shared` löst eine einzige Heap-Speicherplatzanforderung aus,
die den `Controlblock` und den für die Daten erforderlichen Speicherplatz umfasst.

Im anderen Fall bewirkt `new Obj ("foo")` eine Heap-Speicherplatzanforderung für die zu verwaltenden Daten,
und der Konstruktor von `std::shared_ptr` führt die zweite Anforderung
für den Kontrollblock aus.

Man kann damit zusammenfassen, dass die Verwendung der `std::make_shared`-Funktion
effizienter ist.

---

## Literaturhinweise:

Auch in das C++&ndash;Umfeld dringen bisweilen *Fake*-*News* ein:

[No New New: Das Ende von Zeigern in C++](https://www.heise.de/blog/No-New-New-4009347.html) (abgerufen am 13.06.2022).

&ldquo;*Vor zwei Wochen fand das ISO-C++-Standardisierungsmeeting in Jacksonville statt.*
*Das Standardisierungskomitee entschied, dass Zeiger mit C++ 20 deprecated und mit C++23 mit hoher Wahrscheinlichkeit entfernt werden.*&rdquo;
Alles weitere hierzu können Sie dem zitierten Artikel entnehmen :)

---

[Zurück](../../Readme.md)

---
