# Generierung von Zufallszahlen

[Zurück](../../Readme.md)

---

[Quellcode](Random.cpp)

---

*Allgemeines*:

Das Erzeugen von Zufallszahlen setzt sich in *Modern C++* aus zwei Schritten zusammen:

**Generator**<br/>Die Generatoren - oder auch als *Engines* bezeichnet - sind für das eigentliche
Geniereren von zufälligen Zahlen (Bitmustern) in Software zuständig. Es gibt hierzu mehrere Ansätze.
Einer von ihnen besteht darin, diese Zahlen mittels einer Rechenvorschrift (Algorithmus) zu
berechnen. Diese Zahlen sind dann so gesehen überhaupt nicht zufällig, da sie mit einer 
determistischen Rechenvorschrift berechnet wurden, nur: Man sieht es ihnen nicht an!
Solche Zahlen nennt man deshalb auch *Pseudo*-Zufallszahlen. Sie sind für viele Anwendungen völlig
ausreichend, außerdem lassen sie sich performant erzeugen.
 
**Verteilung**<br/>
Generatoren erzeugen zufälligen Zahlen innerhalb eines minimales und maximalen Grenzwerts.
Dies ist nicht immer das, was man benötigt. Die Verteilung (*Distribution*) kann beispielsweise
auch gehäuft sein, wenn man an eine Normalverteilung denkt. 
Verteilungsobjekte rechnen die vom Generator zurückgelieferten Werte so um, dass
sie der gewünschten Verteilung entsprechen.

Ein bekannter Pseudo-Zufallszahlengenerator trägt den Namen *Mersenne Twister*.
Die dazu gehörige C++-Klasse lautet `std::mt19937`, sie basiert auf der 
Mersenneschen Primzahl 2<sup>19937</sup> - 1. Mit diesem Generator lassen sich
Sequenzen von 32-Bit-Ganzzahlen mit einer sehr langen Periode von 2<sup>19937</sup> - 1 generieren,
d.h. die Sequenz wiederholt sich erst, nachdem 2<sup>19937</sup> - 1 Zahlen erzeugt worden
sind - eine in der Tat sehr große Zahl!

Siehe dazu die Beispiele im korrespondierenden Quellcode.

---

[Zurück](../../Readme.md)

---

