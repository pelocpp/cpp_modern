# Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich

[Zur�ck](../../Readme.md)

---

In diesem Unterverzeichnis gibt es keine Quellcode-Datei, also kein Code-Snippet.
Dieses Snippet stellt viel mehr eine Merkhilfe dar, wie man die unterschiedlichen M�glichkeiten
in der Deklaration eines Formalparameters mit den erg�nzenden Kennzeichnungen `const` und `&` gestalten kann
bzw. welche Bedeutung diese haben.

---

*Fragestellung*:<br &/>
Welches sind die Unterschiede zwischen `int& const`, `int const&`, `const& int` und `const int&` in C++?

Um diese Deklarationen verstehen zu k�nnen, liest man sie immer am besten von *rechts* nach *links*:

  * `int& const`:</br>
  Eine konstante (`const`) Referenz (`&`) auf einen `int`-Wert. Da Referenzen prinzipell nach ihrer Definition immer auf dasselbe Objekt verweisen, sind sie immer konstant.
  Das `const`-Schl�sseltwort ist in diesem Fall daher �berfl�ssig. Manche Compiler quittieren dies mit einer Warning, anderen �bersehen diese Deklaration geflissentlich.

  * `int const&`:</br>
  Eine Referenz (`&`) zu einen unver�nderbaren (`const`) `int`-Wert. Der Wert kann durch diese Referenz nicht ver�ndert werden.

  * `const& int`:</br>
  Ein `int`-Wert, der sich auf eine `const`-Referenz bezieht. Weder dieser Satz geschweige denn diese Deklaration ergeben Sinn.
  Diese Deklaration ist nicht �bersetzungsf�hig.

  * `const int&`:</br>
  Eine Referenz f�r einen `int`-Wert, der als konstant (`const`) deklariert wird. Dieser Fall ist identisch zu `int const&`.


---

*Fragestellung*:<br />
Welches sind die Unterschiede zwischen `const int*`, `int* const` und `const int* const`?

Es gibt 2 M�glichkeiten, um das `const`-Schl�sselwort in einer Variablendeklaration mit einem Zeiger zu verwenden.
Der Grund liegt darin, dass es zwei Variablen gibt, deren Werte man bzgl. �nderung sch�tzen m�chte:
Den Zeiger selbst und die Variable, auf die der Zeiger zeigt.

  * `const int * ptr`:</br>
Deklariert einen ver�nderbaren Zeiger, der auf einen unver�nderbaren Wert zeigt.
Der `int`-Wert kann durch den Zeiger nicht ge�ndert werden, aber der Zeiger kann ver�ndert werden,
um auf einen anderen, unver�nderbaren `int`-Wert zu zeigen.

  * `int * const ptr`:</br>  
Deklariert einen unver�nderbaren Zeiger, der auf einen ver�nderbaren Wert zeigt.
Der `int`-Wert kann durch den Zeiger ge�ndert werden, aber der Zeiger kann nicht ver�ndert werden.

  * `const int * const ptr`:</br>
Mit dieser Deklaration kann weder der Inhalt der Zeigervariablen `ptr` ver�ndert werden noch der Inhalt der Variablen,
auf die `ptr` zeigt.

---

[Zur�ck](../../Readme.md)

---
