# Klasse `std::initializer_list<T>`

[Zurück](../../Readme.md)

---

[Quellcode](InitializerList.cpp)

---

Um für Konstruktoren eine variable Anzahl von Parametern (desselben Typs) zu ermöglichen,
wurde in C++ das Konzept von *Initialisierungslisten* eingeführt.

Eine Klasse muss dann einen entsprechenden Konstruktor zur Verfügung stellen, der das Klassentemplate `std::initializer_list<>`
verwendet.

---

Wenn der Compiler eine `std::initializer_list`-Objekt erstellt,
werden die Elemente der Liste auf dem Stapel konstruiert (als konstante Objekte).

Danach erstellt der Compiler das `std::initializer_list`-Objekt selbst,
das die Adresse des ersten und letzten Elements enthält
(genauer in Bezug auf das letzte Element: die Adresse des ersten Elements *nach* dem letzten Element).

Folglich besteht ein `std::initializer_list`-Objekt nur aus zwei Zeigervariablen,
es handelt sich also um ein recht kleines Objekt.
Damit ist es nicht wirklich notwendig, bei der Parameterübergabe 
eine Referenz zu verwenden &ndash; die Parameterübergabe *Call-by-Value* ist völlig ausreichend.

<img src="cpp_initializer_list.svg" width="300">

*Abbildung* 1: Konstruktion des Inhalts eines `std::initializer_list`-Objekts auf dem Stack.

---

[Zurück](../../Readme.md)

---
