# Lambda-Funktionen

*Allgemeines*:

Es werden folgende Überlegungen der Reihe nach betrachtet:

  * Betrachtung 1:</br>Sortieren eines Vektors mit einem Funktionsobjekt (also ohne Lambda-Methode):</br>
    Man erkennt, dass es im Prinzip einer zusätzlichen Klasse (Struktur) bedarf, um
    den std::sort-Methodenaufruf mit einer Vergleichsmethode aufrufen zu können.

  * Betrachtung 2:</br>Sortieren eines Vektors mit Lambda-Methode:</br>
    Er werden die Vereinfachungen bzgl. der ersten Variante vorgestellt.

  * Betrachtung 3:</br>Blick auf die *Capture Clause* / Zugriffsklausel</br>
    Es wird auf die Lambda-Zugriffsklausel (engl.: *Capture Clause*) eingegangen.

* Betrachtung 4:</br>`std::function`<> Methode</br>
    Der generische Wrapper `std::function` wird eingeführt.


Teilweise werden Beispiele (mit gutem und schlechtem Vorbildcharakter) entworfen,
um auf die Problematik von Lambda-Zugriffsklausel näher einzugehen.


Die Ausgabe von Betrachtung 3 sieht auf meinem Rechner wie folgt aus:

```cpp
Copy:      1 2
Reference: -858993460 -858993460
```

In der vierten Betrachtung ist es mit Hilfe des Standard-Wrappers `std::function` möglich, Lambda-Funktionen
auch als (Aktual-)Parameter an andere Methoden/Funktionen übergeben zu können.

Die Vielfältigkeiten im Umgang mit Lamda-Funktionen werden damit noch größer - es ändert sich aber nichts an dem Umstand,
dass Zugriffsklausel mit Referenzen nicht zum erwünschten Resultat führen:

Die Ausgabe von Betrachtung 4 sieht auf meinem Rechner wie folgt aus:

```cpp
in test_05     Copy:      1 2
in test_helper Copy:      1 2
in test_05     Reference: -858993460 -858993460
in test_helper Reference: 15725908 15726376
```

Aus dem engl. C++-Manual habe ich einen Überblick bzgl. der Gestaltungsmöglichkeiten der übernommen:

| Capture Clause Example | Explanation |
|:-------------- |-----------------------------------------|
| []	    | Capture nothing (or, a scorched earth strategy?) |
| [&]	    | Capture any referenced variable by reference |
| [=]	    | Capture any referenced variable by making a copy |
| [=, &foo]	| Capture any referenced variable by making a copy, but capture variable foo by reference |
| [bar]	    | Capture bar by making a copy; don't copy anything else |
| [this]	| Capture the this pointer of the enclosing class |

Tabelle: Liste aller Optionen für die Lambda-Zugriffsklausel.
