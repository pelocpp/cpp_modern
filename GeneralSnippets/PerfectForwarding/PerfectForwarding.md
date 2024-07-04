# Perfect Forwarding

[Zur�ck](../../Readme.md)

---

[Quellcode](PerfectForwarding.cpp)

---

## Einleitung

Voraussetzung f�r das &bdquo;Perfect Forwarding&rdquo; ist das Vorhandensein eines
Funktionstemplates, das im Rumpf weitere unterlagerte Funktionen aufruft:

 > Werden die Argumente des Funktionstemplate &bdquo;identisch&bdquo;
   &ndash;
   darunter verstehen wir in diesem Kontext: die *LValue*- oder *RValue*-Eigenschaft bleibt erhalten 
   &ndash;
   weitergereicht, so sprechen wir von  &bdquo;Perfect Forwarding&rdquo;.

Zu den Begriffen *LValue* oder *RValue* siehe auch
[RValue Referenzen / LValue Referenzen](../RValueLValue/RValueLValue.md).

---

## Begrifflichkeiten

### `const` Referenzen

Eine konstante Referenz, gekennzeichnet durch `const T&`, kann an alles gebunden werden.

Das Originalobjekt kann durch eine solche Referenz niemals ver�ndert werden.

`const`-Referenzen sollten eigentlich immer dann verwendet werden, 
wenn man das betroffene Objekt nicht kopieren m�chte.
Sei es zum Schutze des Objekts oder aus Gr�nden der Performanz.


### Ver�nderbare (mutable) Referenzen

Im Gegensatz zu einer konstanten Referenz kann eine ver�nderbare Referenz (gekennzeichnet durch `T&`)
nicht an eine tempor�re Variable / tempor�res Objekt gebunden werden.

Verwenden Sie eine ver�nderbare Referenz nur dann, wenn Sie das Objekt �ndern m�chten, auf das die Referenz verweist.

### Universal Referenzen / *Forwarding Referenz*

Die Schreibweise `T&&` wird als *Forwarding Referenz* (auch als *universelle Referenz*) bezeichnet.
Sie kann an alles gebunden werden.

*Achtung*:<br />
Verwenden Sie universelle Referenzen nur dann, wenn Sie Variablen/Objekte an unterlagerte Funktionen/Methoden weiterleiten wollen.

*Bemerkung*:<br />
Man beachte, dass `T&&` nur dann eine universelle Referenz darstellt,
wenn sie in einem Funktionstemplate verwendet wird,
in der `T` ein Templateparameter des umgebenden Funktionstemplates ist.

Die Verwendung der `&&`-Syntax mit einem expliziten Typ,
z.B. `std::string&&`, bezeichnet eine *RValue*-Referenz und ist *keine* universelle Referenz!


---

## Erl�uterung einer *universellen Referenz* nach Scott Meyers


*Scott Meyers* bietet eine m�glicherweise leichter verst�ndlichere Darstellung
des Sachverhalts an:

<img src="ScottMeyers_Forward.png" width="600">

*Abbildung* 1: `std::forward`.

---

## Literaturhinweise

Gute Beschreibungen zu diesem Thema befinden sich in

> Peter Pohmann, "C++ 17: Praxiswissen zum neuen Standard. Von C++11 bis 17" (siehe das [Literaturverzeichnis](../Literatur/Literature.md)).

oder
 
[Arne Mertz Blog](https://arne-mertz.de/2015/10/new-c-features-templated-rvalue-references-and-stdforward//)<br>(abgerufen am 31.05.2020).

oder

[Eli Bendersky's website: Perfect forwarding and universal references in C++](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c//)<br>(abgerufen am 15.01.2021).

oder auch

[C++11: Perfect forwarding](https://oopscenities.net/2014/02/01/c11-perfect-forwarding//)<br>(abgerufen am 14.03.2021).

---

[Zur�ck](../../Readme.md)

---
