# Two-Phase Name Lookup

[Zur�ck](../../Readme.md)

---

[Quellcode](TwoPhaseNameLookup.cpp)

---

## Allgemeines

  * [Allgemeines](#link1)
  * [Ein Beispiel](#link2)
  * [Two-Phase Name Lookup](#link3)

---

## Allgemeines <a name="link1"></a>

Klassen- und Funktions-Templates  werden vom C++-Compiler (mindestens) zweimal �bersetzt:

  * Zum Ersten ohne eigentliche Instanziierung des Template Quellcodes. Es wird nur grob die Syntax �berpr�ft,
    also ob zum Beispiel Syntaxfehler wie ein fehlendes `;` etc. vorhanden sind.

  * Zum Zeitpunkt der Instanziierung (also wenn der Template Parametertyp `T` bekannt ist) wird der Template Quellcode erneut �berpr�ft,
    um sicherzustellen, dass alle Aufrufe f�r diesen bestimmten Typ `T` g�ltig sind.

*Beispiel*: Im Quellcode des Templates k�nnen Aufrufe von Funktionen bzw. Zugriffe auf �ffentlich deklarierte Instanzvariablen
vorhanden sein, die f�r einen konkreten Parametertyp `T` m�glicherweise nicht existieren.

*Hinweis*: Einige Compiler unterst�tzen die erste Phase nicht vollst�ndig und verz�gern stattdessen
fast die gesamte Arbeit auf die zweite Phase,
bis eine Instanziierung des Templates stattfindet.


## Ein Beispiel <a name="link2"></a>

Im Umfeld der Vererbung weist das *Two-Phase Name Lookup* ein �berraschendes Verhalten auf,
wie das folgende Beispiel verdeutlicht:

```cpp
template <typename T>
class Base {
public:
    void doSomething() {
        std::cout << "doSomething" << std::endl;
    }
};

template <typename T>
class Derived : public Base<T> {
public:
    void callBase() {
        doSomething();  // doesn't compile !
    }
};
```

Dieser Quellcode zieht folgenden �bersetzungsfehler nach sich:

```
error: function declaration must be available as none of the arguments depend on a template parameter
```

Die Aussage *none of the arguments depend on a template parameter* 
aus der Fehlermeldung gibt einen ersten Hinweis. `doSomething` ist ein so genannter *nicht-abh�ngiger* Name,
da sein Name **nicht** vom Template-Parameter `T` abh�ngt.
*Nicht-abh�ngige* Namen werden zum Zeitpunkt der Template-Definition gesucht und aufgel�st.
Folglich sucht der Compiler *nicht* in der von `T` abh�ngigen Basisklasse `Base<T>`.
Da au�er in der Basisklasse kein weiterer Bezeichner `doSomething` 
verf�gbar ist, kommt es zu einer Fehlermeldung!

*Abh�ngige* Namen werden zum Zeitpunkt der Template-Instanziierung aufgel�st.

## Two-Phase Name Lookup <a name="link3"></a>

Damit w�ren wir wieder beim Thema des *Two-Phase Name Lookups* angekommen:

  * Die erste Phase ist f�r das Aufl�sen *nicht-abh�ngiger* Namen zust�ndig.
  * Die zweite Phase ist f�r das Aufl�sen *abh�ngiger* Namen verantwortlich.

Es gibt drei M�glichkeiten, um im vorliegenden Fall die Suche nach einem Bezeichner
auf die abh�ngige Basisklasse zu erweitern, also um die nicht sinnvolle
Fehlermeldung zu beseitigen:

  1. Mit dem `this`-Operator kann man einen Bezeichner abh�ngig machen.
  2. Man kann mit Hilfe von `using` einen Bezeichner in den aktuellen Geltungsbereich einf�hren: Im vorliegenden Beispiel bewirkt dies der Ausdruck<br/>`using BaseEx<T>::doSomething;`.
  3. Man kann einen  Bezeichner voll-qualifiziert verwenden: Im vorliegenden Beispiel w�re dies ein Ausdruck der Gestalt<br/>`BaseEx<T>::doSomething();`.

Variante 3. ist mit Vorsicht zu genie�en: Ein vormals virtueller Methodenaufruf wird unterdr�ckt, dies kann zu unerw�nschten
Nebenwirkungen f�hren. Variante 1. hat keinerlei Nebeneffekte und l�st das Problem in einfacher Weise.

---

[Zur�ck](../../Readme.md)

---

