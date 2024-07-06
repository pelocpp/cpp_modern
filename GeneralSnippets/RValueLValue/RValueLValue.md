# *RValues* und *LValues*

[Zurück](../../Readme.md)

---

[Quellcode](RValueLValue.cpp)

---

## Inhalt

  * [Wertekategorien](#link1)
  * [Funktionsüberladungen mit *RValue* und *LValue* Referenzen als Parametertyp](#link2)
  * [`std::move`](#link3)
  * [Zusammenfassung:*RValue* Referenzen als Parametertyp](#link4)

---

## Wertekategorien <a name="link1"></a>

*RValues* und *LValues* zahlen in C++ zu so genannten *Wertekategorien*.
Auf Basis dieser Wertekategorien gibt es für den C++&ndash;Übersetzer Regeln,
die dieser beim Erstellen, Kopieren und Verschieben temporärer Objekte
während der Auswertung eines Ausdrucks befolgen muss.

Unter einem *RValue* verstehen wir

  * Konstante
  * temporäre Objekte
  * Objekte ohne Namen

```cpp
// 123 ist ein RValue
int n = 123;

// std::string{ "ABC"} ist ein Objekt ohne Namen:
std::string s = std::string{ "ABC"};

// std::string{ "ABC"} + std::string{ "DEF"} ist ein temporäres Objekt:
std::string a = std::string{ "ABC"} + std::string{ "DEF"};
```

Unter einem *LValue* verstehen wir

  * einen Ausdruck, der eine Referenz eines Objekts beschreibt.
    Zum Beispiel Objekte mit Namen oder auch Objekte,
    die in einem Array über einen Index erreichbar sind.

---

## Funktionsüberladungen mit *RValue* und *LValue* Referenzen als Parametertyp <a name="link2"></a>

Wenn `X` ein Typ ist, wird `X&&` als *RValue* Referenz auf `X` bezeichnet.
Zur besseren Unterscheidung wird die gewöhnliche Referenz `X&` jetzt auch als *LValue* Referenz bezeichnet.
Eine *RValue* Referenz ist ein Typ, der sich - von einigen Ausnahmen abgesehen - ähnlich
wie die normale *LValue* Referenz `X&` verhält.

Das Wichtigste ist, dass *LValue*s bei der Auflösung von Funktionsüberladungen die
herkömmlichen *LValue*-Referenzen bevorzugen, während *RValue*s
die neuen *RValue*-Referenzen bevorzugen:

```cpp
01: void foo(X& x);   // lvalue reference overload
02: void foo(X&& x);  // rvalue reference overload
03: 
04: X x;
05: X foobar();
06: 
07: foo(x);         // argument is lvalue: calls foo(X&)
08: foo(foobar());  // argument is rvalue: calls foo(X&&)
```

Eine der Kernaussagen bei *RValue* / *LValue* Referenzen lautet also:
 
Mit *Rvalue*-Referenzen kann eine Funktion zur Übersetzungszeit (mittels Überladung)
unter der Bedingung "*Werde ich für einen L-Wert oder einen R-Wert aufgerufen?*" verzweigen.

Siehe weiteres dazu im korrespondieren [Quellcode](RValueLValue.cpp).

---

## `std::move` <a name="link3"></a>

Man kann eine *LValue*-Referenz in eine *RValue*-Referenz umwandeln,
indem man die Funktion `std::move` einsetzt 
(Headerdatei `<utility>`):


```cpp
01: void sayHello(std::string& message) {
02:     std::cout << "sayHello [std::string&]:  " << message << std::endl;
03: }
04: 
05: void sayHello(std::string&& message) {
06:     std::cout << "sayHello [std::string&&]: " << message << std::endl;
07: }
08: 
09: void test() {
10: 
11:     std::string s = "Hello";
12: 
13:     sayHello(s);             // sayHello with lvalue reference called
14:     // versus
15:     sayHello(std::move(s));  // casts an lvalue to an rvalue: sayHello with rvalue reference called
16: }
17: 
```

---

## Zusammenfassung: *RValue* Referenzen als Parametertyp <a name="link4"></a>

Mit der Einführung von *RValue* Referenzen können diese natürlich auch als Parameter
in Funktionen oder Methoden erscheinen:

| Funktions-/Methodensignatur | Zulässige Parametertypen |
|:-|:-|
| `void function(Type param)`<br />`void X::method(Type param)` | Sowohl *LValue* Referenzen als auch *RValue* Referenzen können als Parameter übergeben werden. |
| `void function(Type& param)`<br />`void X::method(Type& param)` | Als Parameter können nur *LValue* Referenzen übergeben werden. |
| `void function(const Type& param)`<br />`void X::method(const Type& param)` | Sowohl *LValue* Referenzen als auch *RValue* Referenzen können als Parameter übergeben werden. |
| `void function(Type&& param)`<br />`void X::method(Type&& param)` | Als Parameter können nur *RValue* Referenzen übergeben werden. |

*Tabelle* 1: Unterschiedliche Funktions- und Methodensignaturen und ihre zulässigen Parametertypen..

Obwohl *RValue*-Referenzen natürlich für Parameter in jeder Funktion oder Methode verwendet werden können,
ist ihr prädestiniertes Anwendungsgebiet die [*Verschiebe-Semantik*](../../GeneralSnippets/MoveSemantics/MoveSemantics.md).

---

[Zurück](../../Readme.md)

---
