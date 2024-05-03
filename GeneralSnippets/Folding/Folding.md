# Folding-Ausdrücke

[Zurück](../../Readme.md)

---

[Quellcode](Folding.cpp)

---

Wenn es um die Handhabung variadischer Funktionen geht, können wir nicht im klassischen
"iterativen" C++ - Stil denken. Wir müssen solche Funktionen rekursiv schreiben - mit
einem so genannten "Normal"-Fall und einem "rekursiven" Fall, der sich nach endlich vielen Schritten
auf einen "Normal"-Fall reduzieren lässt. 

Variadische Templates bestehen deshalb aus zwei Template-Überladungen:

  * Einem *normalen* Template
  * Einem *rekursiven* Template, das neben einem normalen Parameter ein so genanntes *Parameter Pack* besitzt (Notation mit "..."). 
    Diese drei Punkte können sowohl links vom Argument (Parameter-Pack-Deklaration) als auch rechts stehen (Entpacken des Parameter Packs).

Ab C++ 17 kann man die zwei Templates eines variadischen Templates auch auf Eines reduzieren. 
Dies erfolgt mit Hilfe eines sogenannten "*Folding-Ausdrucks*".

*Folding-Expressions* lassen sich in 4 Kategorien einteilen, wie folgende Tabelle 
darstellt:

| Name | Ausdruck | Wird erweitert zu |
|:-|:-|:-|
| Unary Left Fold | (... *op* pack) | ((pack<sub>1</sub> *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Binary Left Fold | (init *op* ... *op* pack) | (((init *op* pack<sub>1</sub>) *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Unary Right Fold | (pack *op* ...) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* pack<sub>N</sub>)) |
| Binary Right Fold | (pack *op* ... *op* init) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* (pack<sub>N</sub> *op* init))) |

*Tabelle* 1: *"Folding-Expressions"*.

Der Addierer und ein einfacher Printer demonstrieren in den Code-Snippets *fold expressions*.

Theoretisch stehen für *Folding-Expressions* 32 Operatoren zur Verfügung.
Diese wären `+`, `-`, `*`, `/`, `%`, `^`, `&`, `|`, `=`, `<`, `>`, `<<`, `>>`, `+=`, `-=`, `*=`, `/=`, `%=`, `^=`, `&=`, `|=`, `<<=`, `>>=`, `==`, `!=`, `<=`, `>=`, `&&`, `||`, `,`, `.*` und `->*`.

Ein Sonderfall des Foldings ist das sogenannte *"Folding über einem Komma"*.
Dieses wird ebenfalls an mehreren Beispielen veranschaulicht.

Ausgabe der Code-Snippets zu *fold expressions*:

```cpp
Sum from 1 up to 10: 55
123ABCDEFGHI
BRF: 1 - (2 - (3 - (4 - ( 5 - 0)))): 3
BLF: ((((0 - 1) - 2) - 3) - 4) - 5: -15
URF: 1 - (2 - (3 - (4 - 5))): 3
URF: ((((1 - 2) - 3) - 4) - 5: -13
1 2 3 ABC DEF GHI
1 2 3 ABC DEF GHI
1-2-3-ABC-DEF-GHI-
```

---

[Zurück](../../Readme.md)

---
