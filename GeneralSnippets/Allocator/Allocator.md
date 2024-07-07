# Container und Speicher-Allokatoren

[Zur�ck](../../Readme.md)

---

[Quellcode](Allocator.cpp)

---

## Allgemeines

Es wird zum einen auf die Klasse `std::allocator<T>` eingegangen. Sie stellt den Zugang zur
den Speicherverwaltungsfunktionen im C++-Laufzeitsystem zur Verf�gung.

Danach wird am Beispiel des STL-Containers `std::vector` gezeigt, wie sich ein selbstgeschriebener 
in einen STL-Container injizieren l�sst.

Sehr gut lassen sich damit die beiden Methoden `push_back` und `emplace_back` in ihrer Arbeitsweise beobachten.
Diese steht nat�rlich im Zusammenhang mit der `reverse`-Methode eines Containers.

---

[Zur�ck](../../Readme.md)

---
