# Move Semantics

[Quellcode](MoveSemantics.cpp)

---

*Allgemeines*:

Die Erweiterung einer Klasse von der Copy-Konstruktion (dies schließt den Kopier-Konstruktor und
den Wertzuweisungsoperator ein) hin zur Verschiebe-Konstruktion (dies wiederum 
schließt den Verschiebe-Konstruktor und
die Verschiebe-Wertzuweisung ein) kann dem dazugehörigen Quellcode entnommen werden.

Prinzipiell kann die Move-Semantik auf dreierlei Weisen realisiert werden:

  * manuell
  * mit zwei Hilfsmethoden `cleanup` und `moveFrom` (*Primitiven*) 
  * auf Basis des *Swap*-Idioms

 

---

[Zurück](../../Readme.md)

---
