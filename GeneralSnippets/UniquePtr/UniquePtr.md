# Unique Pointer: Klasse `std::unique_ptr`

[Zurück](../../Readme.md)

---

[Quellcode](UniquePtr.cpp)

---

## &ldquo;It's about ownership&rdquo;

#### Exklusiver Besitz: `std::unique_ptr<T>`

###### Geteilter Besitz: `std::shared_ptr<T>`

###### Temporärer Besitz: `std::weak_ptr<T>`

---

#### Das *Source*-*Sink*-Pattern mit `std::unique_ptr<T>`-Objekten

`std::unique_ptr<T>`-Objekte sind weder kopierbar (Kopier-Konstruktor)
noch ist eine Wertzuweisung (`operator=`) möglich.

Dies schließt interessanterweise nicht aus, dass man Funktionen/Methoden schreiben kann,
die einen Parameter des Typs `std::unique_ptr<T>` (*by-value*) haben,
also nicht vom Typ `std::unique_ptr<T>&` (*by-reference*)!

Wir zeigen die Vorgehensweise an einem Beispiel auf &ndash;
in der Praxis sprechen wir vom *Source*-*Sink*-Pattern:

> Eine Funktion kreiert (`new`) eine Ressource, eine andere gibt sie wieder frei (`delete`).
Natürlich kommt in diesem Pattern bzgl. des `std::unique_ptr<T>`-Objekts die Move-Semantik zum Tragen.
Sie muss in diesem Beispiel nur nicht explizit formuliert werden,
da der Rückgabewert des Erzeugers ein temporäres Objekt ist und infolgedessen der
Verschiebe-Konstruktor automatisch aufgerufen wird.

Im [Quellcode](StdUniquePtr.cpp) finden Sie hierzu ein Beispiel vor.

---

## Literaturhinweise:

Auch in das C++&ndash;Umfeld dringen bisweilen *Fake*-*News* ein:

[No New New: Das Ende von Zeigern in C++](https://www.heise.de/blog/No-New-New-4009347.html) (abgerufen am 13.06.2022).

&ldquo;*Vor zwei Wochen fand das ISO-C++-Standardisierungsmeeting in Jacksonville statt.*
*Das Standardisierungskomitee entschied, dass Zeiger mit C++ 20 deprecated und mit C++23 mit hoher Wahrscheinlichkeit entfernt werden.*&rdquo;
Alles weitere hierzu können Sie dem zitierten Artikel entnehmen :)

Ein interessanter &ndash; und inhaltlich zutreffenderer &ndash; Artikel zum Thema &ldquo;Smart Pointer&rdquo; findet sich unter

[unique_ptr, shared_ptr, weak_ptr, or reference_wrapper for class relationships](https://www.nextptr.com/tutorial/ta1450413058/unique_ptr-shared_ptr-weak_ptr-or-reference_wrapper-for-class-relationships)<br>(abgerufen am 20.12.2021).

---

[Zurück](../../Readme.md)

---





