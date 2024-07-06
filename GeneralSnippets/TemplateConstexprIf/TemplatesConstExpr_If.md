# `if constexpr`

[Zur�ck](../../Readme.md)

---

[Quellcode](Template_ConstExpr_If.cpp)

---

## Allgemeines

Die `if constexpr` Anweisung kann als *statisches if* f�r C++ angesehen werden!

Mit dieser Anweisung lassen sich Code-Abschnitte innerhalb einer `if`-Anweisung
zur �bersetzungszeit basierend auf einer Bedingung f�r konstante Ausdr�cke
aktivieren oder verwerfen.

Im Beispiel zu diesem Snippet finden Sie eine Klasse `Adder<T>` mit drei
Methoden vor:

  * `addSingle`
  * `addToVector`
  * `add`

Die ersten beiden Methoden betrachten die unterschiedliche Situation,
dass die `Adder<T>`-Klasse im Templateparameter elementare Datentypen oder `std::vector`
als Templateargument �bergeben bekommt.

Die dritte Realisierung verdeckt diesen Aspekt und unterscheidet die unterschiedlichen 
M�glichkeiten mit `if constexpr()`.


Siehe das Beispiel im korrespondierenden Quellcode.

---

[Zur�ck](../../Readme.md)

---
