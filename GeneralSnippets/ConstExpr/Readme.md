# constexpr - Ausdrücke, die der Compiler zur Übersetzungszeit auswertet.

*Allgemeines*:

Im ersten, einfachen Beispiel zum Thema "constexpr" wird das klassische Thema von Log- bzw. Debug-Methoden betrachtet.
Diese sind einerseits eminent wichtig, aber man möchte ihnen zur Laufzeit nicht zuviel unnütze Rechenzeit zukommen lassen.
"Unnütze" aus dem Blickwinkel des eigentlichen Programms, nicht aus dem des Entwicklers, der ohne derartige Hilfsmittel
nicht auskommt!

Ein sehr exzessives Beispiel zum Thema "Compile Time Expressions" ist aus dem Netz entnommen:

https://codereview.stackexchange.com/questions/102495/compile-time-list-in-c

Mit meinem Compiler bzw. mit den Voreinstellungen des Übersetzers bin ich nicht in der Lage,
den Quellcode zu übersetzen:

"Warning	C6262	Function uses '18446744071562067976' bytes of stack:  exceeds /analyze:stacksize '16384'.  Consider moving some data to heap."

Sollte ich einmal mehr Zeit zur Verfügung haben - oder Sie mir einen Hinweis zukommen lassen - würde ich versuche,
das Beispiel zum Laufen zu bekommen.
