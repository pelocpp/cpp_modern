# Variadische Templates und Fold-Ausdrücke

Variadische Templates bestehen aus zwei Template-Überladungen:

  * Einem *normalen* Template
  * Einem *rekursiven* Template, das neben einem normalen Parameter ein so genannten *Parameter Pack* besitzt (Notation mit "..."). 
    Diese drei Punkte können sowohl links vom Argument (Parameter-Deklaration) als auch rechts stehen (Entpacken des Parameter Packs).

Ab C++ 17 kann man die zwei Templates eines variadischen Templates auch auf eines reduzieren. 
Dies erfolgt mit Hilfe eines sogenannten "*Fold-Ausdrucks*".

*"Folding-Expressions"* lassen sich in 4 Kategorien einteilen, wie folgende Tabelle 
darstellt:

| Name | Ausdruck | Wird erweitert zu |
|:-|:-|:-|
| Unary Left Fold | (... *op* pack) | ((pack<sub>1</sub> *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Binary Left Fold | (init *op* ... *op* pack) | (((init *op* pack<sub>1</sub>) *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Unary Right Fold | (pack *op* ...) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* pack<sub>N</sub>)) |
| Binary Right Fold | (pack *op* ... *op* init) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* (pack<sub>N</sub> *op* init))) |

Tabelle *"Folding-Expressions"*.

Der Addierer und ein einfacher Printer demonstrieren in den Code-Snippets *fold expressions*.

Theoretisch stehen für *"Folding-Expressions"* 32 Operatoren zur Verfügung.
Diese wären `+`, `-`, `*`, `/`, `%`, `^`, `&`, `|`, `=`, `<`, `>`, `<<`, `>>`, `+=`, `-=`, `*=`, `/=`, `%=`, `^=`, `&=`, `|=`, `<<=`, `>>=`, `==`, `!=`, `<=`, `>=`, `&&`, `||`, `,`, `.*` und `->*.

Ausgabe der Code-Snippets zu variadische Templates:

```cpp
Sum from 1 up to 10: 55
String Concatenation: ABCDEFGHIJKLMNO

Value: char
Value: short
Value: int
Value: long
Value: float
Value: double
Value: const char*
Value: bool

double - value: 3.1415
short - value: 123
int - value: 123
long - value: 123
float - value: 3.14
double - value: 3.14
char - value: A
const char* - value: ABC
bool - value: 0
```

Ausgabe der Code-Snippets zu *fold expressions*:

```cpp
123ABCDEFGHI
Sum from 1 up to 10: 55
BRF: 1 - (2 - (3 - (4 - ( 5 - 0)))): 3
BLF: ((((0 - 1) - 2) - 3) - 4) - 5: -15
URF: 1 - (2 - (3 - (4 - 5))): 3
URF: ((((1 - 2) - 3) - 4) - 5: -13
1 2 3 ABC DEF GHI
1-2-3-ABC-DEF-GHI-
```
