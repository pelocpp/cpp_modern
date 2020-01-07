# Variadic Templates

Variadische Templates bestehen aus zwei Template-Überladungen:

  * Einem *normalen* Template
  * Einem *rekursiven* Template, das neben einem normalen Parameter ein so genannten *Parameter Pack* besitzt (Notation mit "..."). 
    Diese drei Punkte können sowohl links vom Argument (Parameter-Deklaration) als auch rechts stehen (Entpacken des Parameter Packs).

Ausgabe der Code-Snippets:

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