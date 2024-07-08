# Two-Phase Name Lookup

[Zurück](../../Readme.md)

---

[Quellcode](TwoPhaseNameLookup.cpp)

---

## Allgemeines

  * [Allgemeines](#link1)
  * [Ein Beispiel](#link2)
  * [Two-Phase Name Lookup](#link3)

---

## Allgemeines <a name="link1"></a>

Klassen- und Funktions-Templates  werden vom C++-Compiler (mindestens) zweimal übersetzt:

  * Zum Ersten ohne eigentliche Instanziierung des Template Quellcodes. Es wird nur grob die Syntax überprüft,
    also ob zum Beispiel Syntaxfehler wie ein fehlendes `;` etc. vorhanden sind.

  * Zum Zeitpunkt der Instanziierung (also wenn der Template Parametertyp `T` bekannt ist) wird der Template Quellcode erneut überprüft,
    um sicherzustellen, dass alle Aufrufe für diesen bestimmten Typ `T` gültig sind.

*Beispiel*: Im Quellcode des Templates können Aufrufe von Funktionen bzw. Zugriffe auf öffentlich deklarierte Instanzvariablen
vorhanden sein, die für einen konkreten Parametertyp `T` möglicherweise nicht existieren.

*Hinweis*: Einige Compiler unterstützen die erste Phase nicht vollständig und verzögern stattdessen
fast die gesamte Arbeit auf die zweite Phase,
bis eine Instanziierung des Templates stattfindet.


## Ein Beispiel <a name="link2"></a>

Im Umfeld der Vererbung weist das *Two-Phase Name Lookup* ein überraschendes Verhalten auf,
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

Dieser Quellcode zieht folgenden Übersetzungsfehler nach sich:

```
error: function declaration must be available as none of the arguments depend on a template parameter
```

Die Aussage *none of the arguments depend on a template parameter* 
aus der Fehlermeldung gibt einen ersten Hinweis. `doSomething` ist ein so genannter *nicht-abhängiger* Name,
da sein Name **nicht** vom Template-Parameter `T` abhängt.
*Nicht-abhängige* Namen werden zum Zeitpunkt der Template-Definition gesucht und aufgelöst.
Folglich sucht der Compiler *nicht* in der von `T` abhängigen Basisklasse `Base<T>`.
Da außer in der Basisklasse kein weiterer Bezeichner `doSomething` 
verfügbar ist, kommt es zu einer Fehlermeldung!

*Abhängige* Namen werden zum Zeitpunkt der Template-Instanziierung aufgelöst.

## Two-Phase Name Lookup <a name="link3"></a>

Damit wären wir wieder beim Thema des *Two-Phase Name Lookups* angekommen:

  * Die erste Phase ist für das Auflösen *nicht-abhängiger* Namen zuständig.
  * Die zweite Phase ist für das Auflösen *abhängiger* Namen verantwortlich.

Es gibt drei Möglichkeiten, um im vorliegenden Fall die Suche nach einem Bezeichner
auf die abhängige Basisklasse zu erweitern, also um die nicht sinnvolle
Fehlermeldung zu beseitigen:

  1. Mit dem `this`-Operator kann man einen Bezeichner abhängig machen.
  2. Man kann mit Hilfe von `using` einen Bezeichner in den aktuellen Geltungsbereich einführen: Im vorliegenden Beispiel bewirkt dies der Ausdruck<br/>`using BaseEx<T>::doSomething;`.
  3. Man kann einen  Bezeichner voll-qualifiziert verwenden: Im vorliegenden Beispiel wäre dies ein Ausdruck der Gestalt<br/>`BaseEx<T>::doSomething();`.

Variante 3. ist mit Vorsicht zu genießen: Ein vormals virtueller Methodenaufruf wird unterdrückt, dies kann zu unerwünschten
Nebenwirkungen führen. Variante 1. hat keinerlei Nebeneffekte und löst das Problem in einfacher Weise.

---

[Zurück](../../Readme.md)

---

