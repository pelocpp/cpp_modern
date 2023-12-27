# Perfect Forwarding

[Zur�ck](../../Readme.md)

---

## Zusammenfassung

Voraussetzung f�r das &bdquo;Perfect Forwarding&rdquo; ist das Vorhandensein eines
Funktionstemplate, das im Rumpf weitere unterlagerte Funktionen aufruft:

 > Werden die Argumente des Funktionstemplate &bdquo;identisch&bdquo;
   &ndash;
   darunter verstehen wir in diesem Kontext: die *LValue*- oder *RValue*-Eigenschaft bleibt erhalten 
   &ndash;
   weitergereicht, so sprechen wir von  &bdquo;Perfect Forwarding&rdquo;.

Zu den Begriffen *LValue* oder *RValue* siehe auch
[RValue Referenzen / LValue Referenzen](../RValueLValue/RValueLValue.md).

---

## Vertiefung zu &bdquo;Perfect Forwarding&rdquo;

&#x21D2; [Teil II: Ein klassischer �bersetzungsfehler](PerfectForwarding_03.md)

---

[Quellcode zur Beschreibung](PerfectForwarding01.cpp)

[Quellcode im Vergleich](PerfectForwarding03.cpp)

---

## Motivation / �berblick

Betrachten Sie das folgende Code-Fragment:

```cpp
template <typename T>
T* Clone(const T& src) {
    return new T{ src };
}
```

In diesem Code-Fragment ist `src` keine *RValue*-Referenz, eben weil die
Referenz einen Namen hat. Um trotzdem die `Clone`-Methode mit der 
Verschiebesemantik verwenden zu k�nnen, gibt es die Funktion `std::forward`:

```cpp
template <typename T>
T* Clone(const T& src) {
    return new T{ std::forward<T>(src) };
}
```

Weitere Details hierzu beschreiben wir nun ausf�hrlicher.

*Anmerkung*: Auch sind &ndash; nebenbei bemerkt &ndash; diese beiden Code-Fragmente nicht �bersetzungsf�hig,
wir betrachten und beheben den vorhandenen Fehler nat�rlich in den nachfolgenden Erl�uterungen.

## Das &bdquo;perfekte Weiterleiten&rdquo; / &bdquo;Perfect Forwarding&rdquo;

### Vorbereitungen: Eine Hilfsklasse `AnyClass`

Hintergrund des &bdquo;perfekten Weiterleitens&rdquo; ist ein Szenario,
in dem eine normale C++-Funktion/Methode im Kontext eines Templates
aufgerufen wird. Dies stellt prinzipiell kein Problem dar, 
aber wenn man nicht aufpasst, kann hier eben Funktionalit�t verloren gehen.
Was ist damit im Detail gemeint? Zun�chst ben�tigen wir zur genaueren Analyse des Sachverhalts
eine Hilfsklasse, nennen wir sie `AnyClass`:

```cpp
class AnyClass
{
public:
    AnyClass() = default;
    ~AnyClass() = default;

    AnyClass(const AnyClass&) {
        std::cout << "copy c'tor" << std::endl;
    }

    AnyClass(AnyClass&&) noexcept {
        std::cout << "move c'tor" << std::endl;
    }
};
```

Wichtig an der Klasse `AnyClass` sind nur die beiden Konstruktoren,
einer mit Kopier-Semantik, ein zweiter mit Verschiebesemantik.

### Objekte vom Typ `AnyClass` erzeugen

Objekte des Typs `AnyClass` lassen sich ohne weitere Probleme erzeugen:

```cpp
// a)
AnyClass obj1;
AnyClass* obj2{ new AnyClass(obj1) };               // copy c'tor invoked
AnyClass* obj3{ new AnyClass(std::move(*obj2)) };   // move c'tor invoked
```

*Ausgabe*:

```
copy c'tor
move c'tor
```

Beachten Sie in dem Beispiel: Es soll zum einen m�glich sein, ein `AnyClass`-Objekt klassisch mit dem Kopierkonstruktor
erzeugen zu k�nnen (Objekt `obj2`). An einer anderen Stelle soll eine Kopie von `obj2` mit der Verschiebesemantik erzeugt werden,
da `obj2` anschlie�end nicht mehr ben�tigt wird. Dies bewerkstelligen wir mit dem Einsatz von `std::move`:
Aus der *LValue*-Referenz `obj2` wird eine *RValue*-Referenz, die Klasse `AnyClass` setzt auf diese Weise 
den effizienteren Verschiebe-Konstruktor ein.

### Objekte vom Typ `AnyClass` in einem Template-Kontext erzeugen

Wir verlagern nun die Funktionalit�t zum Kopieren von Instanzen der Klasse `AnyClass`
&ndash; einer Klasse mit Kopier- und Verschiebekonstruktor &ndash;
in eine separate Template-Funktion:

```cpp
template <typename T>
T* Clone(const T& src) {
    return new T{ src };
}
```

Mit Hilfe der Template-Funktion `Clone` k�nnen wir das letzte Beispiel etwas k�rzer formulieren:

```cpp
AnyClass obj10;
AnyClass* obj11{ Clone(obj10) };                    // copy c'tor invoked
AnyClass* obj12{ Clone(std::move(*obj11)) };        // copy c'tor invoked (???)
```

*Ausgabe*:

```
copy c'tor
copy c'tor
```

Prinzipiell funktioniert das Erzeugen von Objekten, allerdings kann man an der Ausgabe erkennen, dass beim zweiten Aufruf 
der `Clone`-Funktion auch der Kopierkonstruktor zum Einsatz kommt, obwohl wir das Quellobjekt `obj11` doch explizit mit 
mit `std::move` versehen haben, also hierdurch eine *RValue*-Referenz an `Clone` �bergeben.

> Der Grund f�r dieses Verhalten ist naheliegend:
> Innerhalb der `Clone`-Funktion ist `src` eine Variable mit Namen, also eine *LValue*-Referenz und damit keine *RValue*-Referenz.
> Deshalb wird der regul�re Kopierkonstruktor aufgerufen!

Was ist unser Wunsch: Gesucht ist eine Implementierung von `Clone`, die

  * bei einem Aufruf mit einer *LValue*-Referenz diesen Parameter wie einen *LValue* behandelt und infolgedessen den Kopierkonstruktor der Klasse `AnyClass` aufruft,
  * bei einem Aufruf mit einer *RValue*-Referenz diesen Parameter wie einen *RValue* behandelt und infolgedessen den Verschiebekonstruktor der Klasse `AnyClass` aufruft!

### Ein erster L�sungsversuch

Wir unternehmen einen ersten Versuch zur L�sung des Problems und wandeln den *LValue*-Parameter `src` in eine *RValue*-Referenz um:

```cpp
template <typename T>
T* Clone(T&& src) {
    return new T{ src };
}
```

Auf den ersten Blick k�nnte man meinen, dass `src` jetzt immer eine *RValue*-Referenz ist, aber dem ist nicht so!
Es gibt n�mlich spezielle Regeln zum Aufl�sen von Template-Parametertypen, wenn *RValue*-Referenzen beteiligt sind:

  * Wird `Clone` f�r einen *LValue*-Parameter vom Typ `X` aufgerufen, dann wird der Template-Parameter `T` an `X&` gebunden. Folglich ist `src` vom Typ `X& &&`.
  * Wird `Clone` f�r einen *RValue*-Parameter vom Typ `X` aufgerufen, dann wird der Template-Parameter `T` an `X` gebunden. Folglich ist `src` vom Typ `X&&`.

Damit sind wir auf die Frage gesto�en, was im ersten Fall `X& &&` eigentlich bedeuten soll.
Dies ist keine Typdefinition, die in einem regul�ren C++&ndash;Programm erlaubt ist:

```cpp
int& && n;  // Error: reference to reference is not allowed
```

Beim Zuordnen (&bdquo;Binden&rdquo;, &bdquo;Aufl�sen&rdquo;) von aktuellen Parametertypen zu Template-Parametern k�nnen
w�hrend des �bersetzens solche Kombinationen auftreten, wie das Beispiel gezeigt hat.
Aus diesem Grund hat man in der C++&ndash;Sprachdefinition die so genannten *Zusammenfassungsregeln* (engl. *Reference Collapsing Rules*)
definiert:


| Formaler Typ | Beschreibung | Resultat-Typ | Beschreibung|
|:------ |:----------|:----------|:----------|
| T& &   | *LValue*-Referenz auf eine *LValue*-Referenz | T&  | *LValue*-Referenz |
| T&& &  | *LValue*-Referenz auf eine *RValue*-Referenz | T&  | *LValue*-Referenz |
| T& &&  | *RValue*-Referenz auf eine *LValue*-Referenz | T&  | *LValue*-Referenz |
| T&& && | *RValue*-Referenz auf eine *RValue*-Referenz | T&& | *RValue*-Referenz |

Tabelle 1. *Zusammenfassungsregeln*/*Collapsing Rules* f�r das *Perfect Forwarding*.

Nun wenden wir die *Zusammenfassungsregeln* an: Ist `obj` ein Objekt der Klasse `AnyClass`, so f�hrt

```cpp
Clone(obj);
```

zur Aufl�sung

```cpp
AnyClass* Clone(AnyClass& src)
```

Eine Instanziierung von 

```cpp
Clone(std::move(*obj));
```

hingegen f�hrt zu

```cpp
AnyClass* Clone(AnyClass&& src)
```

Wir sind leider noch nicht am Ziel angekommen:

### Ein unerwarteter �bersetzungsfehler

Wenn wir die Erkenntnisse aus dem letzten Abschnitt versuchen, in die Tat umzusetzen,
werden wir mit einem &ndash; aus Sicht vieler C++&ndash;Entwickler &ndash; unerwarteten �bersetzungsfehler konfrontiert:

```cpp
template <typename T>
T* Clone(T&& src) {
    return new T{ src };
}

int main()
{
    AnyClass obj10;
    AnyClass* obj11{ Clone(obj10) };   // error
}
```

Die Fehlermeldung lautet:

```
error: no matching function for call to 'Clone'

    AnyClass* obj21{ Clone(obj20) };
                     ^~~~~~

note: candidate template ignored: substitution failure
[with T = AnyClass &]:
'Clone' declared as a pointer to a reference of type 'AnyClass &'

    T* Clone(T&& src) {
     ~ ^
1 error generated.
```

Erkennen Sie das Problem? Es geht hier um den R�ckgabedatentyp der Funktion `Clone`:
Dieser ist `T*`, aber womit verbindet der �bersetzer den Template-Parameter `T`?
Dies k�nnen mit der Fehlermeldung entnehmen: `[with T = AnyClass &]`.
Damit leitet sich `T*` zu `AnyClass &*` ab!
Oder wie es wiederum im Fehlermeldungstext hei�t: *'Clone' declared as a pointer to a reference of type 'AnyClass &'*. 

Jetzt d�rfte das Problem klar sein: Der Datentyp des Parameters `src` von Clone passt (`AnyClass &`),
aber **nicht** der R�ckgabedatentyp `T*`:

Wir wollten es hier mit `AnyClass*` zu tun haben, aber nicht mir `AnyClass&*`!
Es ist also eine Referenz `&` zu viel!
Dieser Fehler tritt in der Template-Programmierung des �fteren auf, aus diesem Grund
gibt es eine C++&ndash;Template-Funktion namens `std::remove_reference<T>`:

> *If the type T is a reference type, std::remove_reference provides the member typedef type<br/>which is the type referred to by T. Otherwise type is T.*

Jetzt haben wir eine M�glichkeit, den �bersetzungsfehler zu beheben, zum Beispiel auf diese Weise:

```cpp
template <typename T>
auto Clone(T&& src) {
    using TT = typename std::remove_reference<T>::type;
    return new TT{ src };
}
```

Letzen Endes haben wir zwei Werkzeuge aus dem &bdquo;Modern&ndash;C++&rdquo; Baukasten verwendet:

  * R�ckgabewert `auto` &ndash; der Compiler leitet den R�ckgabedatentyp anhand der `return`-Anweisung ab
  * Definition des R�ckgabedatentyps mit `std::remove_reference<T>` und `using` 

Da es in diesem Umfeld der Modern C++&ndash;Programmierung mehrere M�glichkeiten gibt,
die `Clone`-Funktion korrekt zu implementieren,
stellen wir nachfolgend f�nf Variationen des L�sungsansatzes vor:

```cpp
template <typename T>
auto Clone2a(T&& src) {
    using TT = typename std::remove_reference<T>::type;
    return new TT{ src };
}

template <typename T>
auto Clone2b(T&& src) -> typename std::remove_reference<T>::type * {
    using TT = typename std::remove_reference<T>::type;
    return new TT { src };
}

template <typename T>
auto Clone2c(T&& src) -> typename std::remove_reference<T>::type * {
    return new typename std::remove_reference<T>::type{ src };
}

template <typename T>
auto Clone2d(T&& src) {
    return new typename std::remove_reference<T>::type{ src };
}

template <typename T>
typename std::remove_reference<T>::type* Clone2e(T&& src) {
    return new typename std::remove_reference<T>::type{ src };
}
```

Damit sind folgende Aufrufe �bersetzungsf�hig:

```cpp
// d1)
AnyClass obj20;
AnyClass* obj21{ Clone2a(obj20) };
AnyClass* obj22{ Clone2a(std::move(*obj21)) };

// d2)
AnyClass obj30;
AnyClass* obj31{ Clone2b(obj30) };
AnyClass* obj32{ Clone2b(std::move(*obj31)) };

// d3)
AnyClass obj40;
AnyClass* obj41{ Clone2c(obj40) };
AnyClass* obj42{ Clone2c(std::move(*obj41)) };

// d4)
AnyClass obj50;
AnyClass* obj51{ Clone2d(obj50) };
AnyClass* obj52{ Clone2d(std::move(*obj51)) };

// d5)
AnyClass obj60;
AnyClass* obj61{ Clone2e(obj60) };
AnyClass* obj62{ Clone2e(std::move(*obj61)) };
```

Haben wir unser eingangs betrachtetes Problem (*LValue*-Referenz wird auf Kopierkonstruktor,
*RValue*-Referenz wird auf Verschiebekonstruktor abgebildet)
nun gel�st? Die Ausgabe beantwortet die Frage:

```
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
copy c'tor
```

Leider Nein, und diese Antwort war eigentlich zu erwarten: Zwar haben wir es &ndash; je nach Aufruf &ndash; geschafft,
das `src` den Typ *RValue*-Referenz von `AnyClass` annimmt, `src` selbst hat aber einen Namen, ist damit
ein *LValue* und wir landen damit wieder beim Aufruf des klassischen Kopierkonstruktors!

### Die L�sung: Eine Template-Funktion `forward`

Wir bringen nun eine Template-Funktion `forward` ins Spiel, die 

  * eine *LValue*-Referenz in einen *LValue* konvertiert
  * eine *RValue*-Referenz in einen *RValue* konvertiert


Da wird zun�chst auf Hilfestellungen aus der Standardbibliothek verzichten wollen, definieren wir selbst eine Template-Funktion
namens `my_forward`:

```cpp
template <typename F>
F&& my_forward(typename std::remove_reference<F>::type& t) noexcept {
    return static_cast<F&&>(t);
}

template <typename F>
F&& my_forward(typename std::remove_reference<F>::type&& t) noexcept {
    return static_cast<F&&>(t);
}
```

Dazu ben�tigen wir nun noch eine passende Definition der `Clone`-Funktion:

```cpp
template <typename T>
auto Clone(T&& src) {
    return new typename std::remove_reference<T>::type(my_forward<T>(src));
}
```

*Et Voil�*: Wenn wir nun das Fragment

```cpp
AnyClass obj80;
AnyClass* obj81{ Clone(obj80) };              // copy c'tor invoked
AnyClass* obj82{ Clone(std::move(*obj81)) };  // move c'tor invoked (!!!)
```

ausf�hren, erhalten wir die Ausgabe

```cpp
copy c'tor
move c'tor
```

Zu den Details:

  * Wird `Clone` mit einer `AnyClass`-Instanz aufgerufen (erster Aufruf in obigem Beispiel),
   wird `T` an `AnyClass&` gebunden und damit auch `F` an `AnyClass&`. 
   Deshalb wird die erste �berladung von `my_forward` ausgew�hlt, deren Template-Parameter `AnyClass& &`
   auf Grund der *Zusammenfassungsregeln* zu `AnyClass&` verschmilzt, also eine *LValue*-Referenz ist:
   Es wird der regul�re Kopier-Konstruktor von `AnyClass` aufgerufen! 
   Betrachten wir noch den R�ckgabe-Datentyp von `Clone`: `F&&` evaluiert zu `AnyClass& &&`,
   was wiederum auf Grund der *Zusammenfassungsregeln* zu `AnyClass&` verschmilzt, 
   es wird also eine *LValue*-Referenz zur�ckgeliefert.

  * Wird `Clone` jedoch mit einer *RValue*-Referenz aufgerufen, die von `std::move` zur�ckgeliefert wird,
   dann bindet `T` an `AnyClass` &ndash; siehe die Regeln eines `T&&`-Parameters innerhalb eines Templates weiter oben!
   Dann bindet auch `F` an `AnyClass` und die zweite �berladung von `my_forward` kommt zum Zuge.
   Dadurch ist der Parameter von `my_forward` eine *RValue*-Referenz, genauso wie der R�ckgabewert
   dann eine (unbenannte) *RValue*-Referenz ist.

Jetzt leitet `Clone` ein *LValue* Argument als *LValue* weiter und ein *RValue* Argument als *RValue*,
die Weiterleitung ist &bdquo;perfekt&bdquo;.

### `std::forward`:

Nat�rlich m�ssen Sie die vorgestellte Implementierung von `my_forward` in Ihrem Programm nicht abtippen,
sie in Gestalt der Template-Funktion `std::forward` in der C++&ndash;Standardbibliothek enthalten:

```cpp
#include <utility>

template <typename T>
auto Clone99(T&& src) {
    return new typename std::remove_reference<T>::type(std::forward<T>(src));
}

AnyClass obj90;
AnyClass* obj91{ Clone99(obj90) };              // copy c'tor invoked
AnyClass* obj92{ Clone99(std::move(*obj91)) };  // move c'tor invoked (!!!)
```

*Ausgabe*:

```
copy c'tor
move c'tor
```

*Bemerkung*:
Wir sind mit unserer exemplarischen Implementierung der `my_forward`-Funktion nicht weit vom Original (`std::forward`) entfernt:

```
template <class _Ty>
_NODISCARD constexpr _Ty&& forward(
    remove_reference_t<_Ty>& _Arg) noexcept { // forward an lvalue as either an lvalue or an rvalue
    return static_cast<_Ty&&>(_Arg);
}
```

## Zusammenfassung:

`std::move` und `std::forward<T>` weisen Gemeinsamkeiten auf: Beide Male geht es darum,
das Argument in einen *RValue* zu konvertieren:

  * `std::move` konvertiert *LValue* Argumente und auch Konstante (Werte) in *RValue* Referenzen. Es findet folglich eine echte Typ-Konvertierung statt.
  * `std::forward<T>` hingegen verwandelt nur *RValue* Referenzen **mit Namen** in *RValue* Referenzen **ohne Namen**, macht sie infolgedessen zu *RValues*.


## Literaturhinweise:

Das oben verwendete Bespiel stammt im Gro�en und Ganzen aus

> Peter Pohmann, "C++ 17: Praxiswissen zum neuen Standard. Von C++11 bis 17" (siehe das [Literaturverzeichnis](../Literatur/Literature.md)).

Weitere gute Beschreibungen zu diesem Thema befinden sich unter

[Arne Mertz Blog](https://arne-mertz.de/2015/10/new-c-features-templated-rvalue-references-and-stdforward//)<br>(abgerufen am 31.05.2020).

oder

[Eli Bendersky's website: Perfect forwarding and universal references in C++](https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c//)<br>(abgerufen am 15.01.2021).

oder auch

[C++11: Perfect forwarding](https://oopscenities.net/2014/02/01/c11-perfect-forwarding//)<br>(abgerufen am 14.03.2021).

---

[Zur�ck](../../Readme.md)

---
