# Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich

[Zurück](../../Readme.md)

---

In diesem Unterverzeichnis gibt es keine Quellcode-Datei, also kein Code-Snippet.
Dieses Snippet stellt viel mehr eine Merkhilfe dar, wie man die unterschiedlichen Möglichkeiten
in der Deklaration eines Formalparameters mit den ergänzenden Kennzeichnungen const und & gestalten kann
bzw. welche Bedeutung diese haben.

*Fragestellung*:
Welches sind die Unterschiede zwischen `int& const`, `int const&`, `const& int` und `const int&` in C++?

Um diese Deklarationen verstehen zu können, liest man sie immer am besten von *rechts* nach *links*:

  * `int& const`:</br>
  Eine konstante (`const`) Referenz (`&`) auf einen `int`-Wert. Da Referenzen prinzipell nach ihrer Definition immer auf dasselbe Objekt verweisen, sind sie immer konstant.
  Das `const`-Schlüssertwort ist in diesem Fall daher überflüssig. Manche Compiler quittieren dies mit einer Warning, anderen übersehen diese Deklaration geflissentlich.

  * `int const&`:</br>
  Eine Referenz (`&`) zu einen unveränderbaren (`const`) `int`-Wert. Der Wert kann durch diese Referenz nicht verändert werden.

  * `const& int`:</br>
  Ein `int`-Wert, der sich auf eine `const`-Referenz bezieht. Weder dieser Satz geschweige denn diese Deklaration ergeben Sinn.
  Diese Deklaration ist nicht übersetzungsfähig.

  * `const int&`:</br>
  Eine Referenz für einen `int`-Wert, der als konstant (`const`) deklariert wird. Dieser Fall ist identisch zu `int const&`.


---

[Zurück](../../Readme.md)

---
