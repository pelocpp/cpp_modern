# Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich

[Zurück](../../Readme.md)

---

In diesem Unterverzeichnis gibt es keine Quellcode-Datei, also kein Code-Snippet.
Dieses Snippet stellt viel mehr eine Merkhilfe dar, wie man die unterschiedlichen Möglichkeiten
in der Deklaration eines Formalparameters mit den ergänzenden Kennzeichnungen `const` und `&` gestalten kann
bzw. welche Bedeutung diese haben.

---

*Fragestellung*:<br &/>
Welches sind die Unterschiede zwischen `int& const`, `int const&`, `const& int` und `const int&` in C++?

Um diese Deklarationen verstehen zu können, liest man sie immer am besten von *rechts* nach *links*:

  * `int& const`:</br>
  Eine konstante (`const`) Referenz (`&`) auf einen `int`-Wert. Da Referenzen prinzipell nach ihrer Definition immer auf dasselbe Objekt verweisen, sind sie immer konstant.
  Das `const`-Schlüsseltwort ist in diesem Fall daher überflüssig. Manche Compiler quittieren dies mit einer Warning, anderen übersehen diese Deklaration geflissentlich.

  * `int const&`:</br>
  Eine Referenz (`&`) zu einen unveränderbaren (`const`) `int`-Wert. Der Wert kann durch diese Referenz nicht verändert werden.

  * `const& int`:</br>
  Ein `int`-Wert, der sich auf eine `const`-Referenz bezieht. Weder dieser Satz geschweige denn diese Deklaration ergeben Sinn.
  Diese Deklaration ist nicht übersetzungsfähig.

  * `const int&`:</br>
  Eine Referenz für einen `int`-Wert, der als konstant (`const`) deklariert wird. Dieser Fall ist identisch zu `int const&`.


---

*Fragestellung*:<br />
Welches sind die Unterschiede zwischen `const int*`, `int* const` und `const int* const`?

Es gibt 2 Möglichkeiten, um das `const`-Schlüsselwort in einer Variablendeklaration mit einem Zeiger zu verwenden.
Der Grund liegt darin, dass es zwei Variablen gibt, deren Werte man bzgl. Änderung schützen möchte:
Den Zeiger selbst und die Variable, auf die der Zeiger zeigt.

  * `const int * ptr`:</br>
Deklariert einen veränderbaren Zeiger, der auf einen unveränderbaren Wert zeigt.
Der `int`-Wert kann durch den Zeiger nicht geändert werden, aber der Zeiger kann verändert werden,
um auf einen anderen, unveränderbaren `int`-Wert zu zeigen.

  * `int * const ptr`:</br>  
Deklariert einen unveränderbaren Zeiger, der auf einen veränderbaren Wert zeigt.
Der `int`-Wert kann durch den Zeiger geändert werden, aber der Zeiger kann nicht verändert werden.

  * `const int * const ptr`:</br>
Mit dieser Deklaration kann weder der Inhalt der Zeigervariablen `ptr` verändert werden noch der Inhalt der Variablen,
auf die `ptr` zeigt.

---

[Zurück](../../Readme.md)

---
