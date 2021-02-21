# Funktionstemplates: Grundlagen

[Zurück](../../Readme.md)

---

[Quellcode](FunctionTemplatesBasics.cpp)

---

## Typableitung (Type Deduction) und Templatespezialisierung

Es wird an einem einfachen Beispiel die Syntax zu Funktionstemplates gezeigt.

**Hinweis**:

Es wird auf die beiden Features

  * Typableitung / Type Deduction
  * Templatespezialisierung

  eingegangen.

Den Aspekt der Templatespezialisierung kann man an den beiden unterschiedlichen Ausgaben

<pre>
Value: 10
Value: <b>1</b>
Value: 12.5
</pre>

bzw.

<pre>
Value: 10
Value: <b>true</b>
Value: 12.5
</pre>

erkennen.

---

## Function Template Overloading

Betrachten wir nun das Überladen von Funktionsschablonen.
Es ist nicht dasselbe wie Spezialisierung, aber es hängt mit Spezialisierung zusammen.

In C++ kann man Funktionen überladen, der Compiler stellt sicher, dass die richtige bzw. gewünschte Funktion aufgerufen wird:

```cpp
int  f( int );
long f( double );

int    i;
double d;

f( i );   // calls f(int)
f( d );   // calls f(double)
```

Wir betrachten nun die folgenden Funktionsdeklarationen:

```cpp
template<typename T1, typename T2>
void f( T1, T2 );                       // 1
template<typename T> void f( T );       // 2
template<typename T> void f( T, T );    // 3
template<typename T> void f( T* );      // 4
template<typename T> void f( T*, T );   // 5
template<typename T> void f( T, T* );   // 6
template<typename T> void f( int, T* ); // 7
template<> void f<int>( int );          // 8
void f( int, double );                  // 9
void f( int );                          // 10
```

Den Aspekt des "*Function Template Overloading*" betrachten wir nun nacheinander an einer Reihe von Aufrufen:
Die dabei verwendeten Parameter lauten

```cpp
int             i;
double          d;
float           ff;
complex<double> c;
```

Es folgen nun die Beispiele:

```cpp
    f( i );         // a
```

A. Dies ruft #10 auf, da es genau mit #10 übereinstimmt und Nicht-Template-Aufrufe immer Template-Aufrufen vorgezogen werden.

```cpp
    f<int>( i );    // b
```

B. Dies ruft #8 auf, da `f<int>` explizit aufgerufen wird.

```cpp
    f( i, i );      // c
```

C. Dies ruft #3 auf (`T` ist `int`), da dies die beste Übereinstimmung ist.

```cpp
    f( c );         // d
```

D. Dies ruft #2 auf (`T` ist `std::complex<double>`), da kein anderes `f` übereinstimmen kann.

```cpp
    f( i, ff );     // e
```

E. Dies ruft #1 auf (`T1` ist `int`, `T2` ist `float`). Sie könnten denken, dass #9 sehr nahe ist - und das ist es auch -, aber eine Nicht-Template-Funktion wird nur bevorzugt, wenn sie genau übereinstimmt.

```cpp
    f( i, d );      // f
```

F. Dieser ruft #9 an, weil #9 jetzt genau übereinstimmt und die Nichtvorlage bevorzugt wird.

```cpp
    f( c, &c );     // g
```

G. Dies ruft #6 auf (`T` ist `std::complex<double>`), da #6 die nächste Überladung ist. #6 liefert eine Überladung von `f`, wobei der zweite Parameter ein Zeiger auf denselben Typ wie der erste Parameter ist.

```cpp
    f( i, &d );     // h
```

H.  Dies ruft #7 auf (T ist `double`), da #7 die am besten passende Überladung ist.

```cpp
    f( &d, d );     // i
```

I. Dies ruft #5 auf (`T` ist `double`). #5 liefert eine Überladung von `f`, wobei der erste Parameter ein Zeiger auf denselben Typ wie der zweite Parameter ist.

---

[Zurück](../../Readme.md)

---
