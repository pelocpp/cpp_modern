# Teil I: Variadische Templates - Einführung

[Zurück](../../Readme.md)

---

&#x21D2; [Teil II: Variadische Templates: Zugriff auf jedes einzelne Argument](VariadicTemplates_02_WorkingOnEveryArgument.md)

---

[Quellcode](VariadicTemplate_01_Introduction.cpp)

---

Ab C++ 11 gibt es in C++ die so genannten *Variadic Templates*, 
mit denen ein Template definiert werden kann,
das eine beliebige Anzahl von Parametern annehmen kann.

Grundsätzlich werden zwei neue syntaktische Elemente
für die Definition derartiger Templates benötigt:
Zum einen das so genannte *Parameter Pack* zur Deklaration des Templates,
zum anderen die *Expansion* des *Parameter Packs* in der Definition des Templates.

## Parameter Pack

Ein *Parameter Pack* ist einfach ein Name,
der einer Liste von Templateparametern anstelle eines einzelnen Parameters
zugewiesen wird. Die häufigsten zwei Arten von Templateparametern
und damit Möglichkeiten, *Parameter Packs* anzuwenden lauten:

```cpp
template <typename... TS>    // TS is a list of type parameters
template <unsigned... NS>    // NS is a list of non-type parameters (unsigned)
```

Der erste Fall tritt in der Praxis am häufigsten auf.
Wie bei „normalen“ Vorlagen können variadische Templates Funktionstemplates
oder Klassentemplates sein.
Wir können auch einzelne Parameter und *Parameter Packs* mischen,
mit der Einschränkung, dass es nur eine einzige *Parameter Pack* Definition geben kann
und diese am Ende der Parameterliste stehen muss:

```cpp
template <typename T, int N, typename... TS>
```

Zusätzlich zu *Template Parameter Packs* haben wir *Function Parameter Packs*.
Sie kommen zum Einsatz, wenn in einem variadischen Funktionstemplate
das *Template Parameter Pack* zum Definieren von Funktionsargumenten verwendet wird.
Dies sollten wir an einem Beispiel veranschaulichen:

```cpp
template <typename... ARGS>    // ARGS is the template parameter pack
void f(int i, ARGS... args) {  // args is the function parameter pack
  //...
}
```

Noch etwas formale Formulierungen gewünscht? Bitte schön: 
Wenn in Betrachtung der Funktionsschablone `f` **ARGS** ≙ **T1, T2** ist,
dann gilt **ARGS... args** ≙ **T1 t1, T2 t2** und **args... = t1, t2**.

## Expansion des Parameter Packs

Es ist nicht möglich, ein *parameter pack* anders zu verwenden als es zu erweitern.
In den meisten Fällen ergibt die Erweiterung des *parameter packs* eine durch Kommas getrennte Liste von Ausdrücken,
die die einzelnen Elemente des packs enthalten.

Die einfachste Pack-Expansion ist nur der Name des *parameter packs*,
gefolgt von der Ellipse (`...`), was zu einer durch komma-getrennten Liste der *pack*-Elemente führt:

```cpp
template <typename... ARGS>
void f(int i, ARGS... args) {
    // expand template parameter pack ARGS first,
    // then function parameter pack args
    std::tuple<ARGS...> argsTuple{ args... };
    //...
}
```

Betrachten wir ein Beispiel:

```cpp
f(21, 54.3, "foo", 47u);
```

In dem Funktionsaufruf von `f` ist `21` der `int`-Parameter, und die anderen drei Parameter
definieren **zwei** *Parameter Packs*. Das *Template Parameter Pack* `ARGS` ist die Liste der Typen
`double`, `char const*` und `unsigned`,
während das *function parameter pack* `args` die Liste mit den Werte ist `54.3`, `"foo"` und `47u` ist.

Diese einzelne Instanziierung der Funktionsvorlage entspricht quasi dem,
als hätten wir geschrieben:

```cpp
void f(int i, double args_1, char const* args_2, unsigned args_3) {
    std::tuple<double, char const*, unsigned> argsTuple{ args_1, args_2, args_3} ;
    //...
}
```

Nur um es kurz angesprochen zu haben: Bei `std::tuple` handelt es sich ebenfalls
um ein variadisches Klassentemplate.

## Ein einfaches Beispiel

Eine Funktionsschablone zur Addition beliebig vieler Zahlen
(exakter: zur Anwendung des `+`-Operators auf beliebig viele Objekte) kann
als variadisches Template so formuliert werden:

```cpp
// Non-recursive template part (regular template)
template<typename T>
T add(T v) {
    return v;
}

// Recursive template part
// Note: ... specifies a so called 'parameter pack')
template<typename T, typename ...Args>
T add(T first, Args... args) {
    return first + add(args...);
}
```

Mögliche Anwendungsfälle dieser Funktionsschablone:

```cpp
int sum = add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
std::cout << "Sum from 1 up to 10: " << sum << std::endl;

std::string stringConcat = add(
    std::string("ABC"),
    std::string("DEF"),
    std::string("GHI"),
    std::string("JKL"),
    std::string("MNO")
);
std::cout << "String Concatenation: " << stringConcat << std::endl;
```

## Ein weiteres Beispiel zur Parameter Pack Expansion

Die Ellipses direkt nach dem Namen des Parameter Packs ist die einfachste Form der Parameter Pack Expansion.
Es kann jedoch sehr wohl komplizierter sein. Im Prinzip können wir jedes Muster schreiben,
das einen Parameter Pack Namen enthält, gefolgt von einer Ellipse.
Das Ergebnis ist eine durch Kommas getrennte Liste von Mustern, wobei in jedem Muster der Pack Name
durch ein Mitglied des Packs ersetzt wird.

Nehmen wir zum Beispiel das zuvor verwendete Tupel.
Normalerweise möchten wir das "*perfect forwarding*" verwenden,
um das Tupel aus den Funktionsargumenten zu erstellen. Werfen wir einen Blick auf ein Beispiel:

```cpp
template <typename... ARGS>
void f(int i, ARGS&&... args) {
    std::tuple<ARGS...> argsTuple{ std::forward<ARGS>(args)... }; 
    //...
}
```

Wir haben hier **drei** Pack-Expansionen: `ARGS&&...` bedeutet (beachten Sie die beiden &),
dass wir eine Liste von Vorwärtsreferenzen haben.
Die `ARGS...` Expansion für die `std::tuple` Templateparameter hatten wir bereits in dem
Beispiel zuvor betrachtet.
Die dritte Erweiterung `std::forward<ARGS>(args)...` enthält **zwei** Parameter Packs:
das Template Parameter Pack `ARGS` und das Funktionsparameterpack `args`.
Immer wenn zwei Packs im Muster für eine Pack-Erweiterung erscheinen,
werden beide gleichzeitig erweitert und müssen daher die gleiche Anzahl von Elementen haben!

Die obige Funktion im Pseudo-Template-Code nach der Pack-Erweiterung würde so aussehen:

```cpp
template <typename Args_1, typename Args_2, /* etc ... */>
void f(int i, Args_1&& args_1, Args_2&& args_2, /*...*/) {
  std::tuple<Args_1, Args_2, /*...*/> argsTuple{ 
    std::forward<Args_1>(args_1),
    std::forward<Args_2>(args_2), 
    /*...*/ 
  }; 
  //...
}
```

## Leeres Parameter Pack

Ein Parameter Pack kann prinzipiell auch keine Parameter annehmen.
In diesen Fällen ergibt die Pack-Expansion eine leere Liste.
In Fällen, in denen der Pack-Expansion ein Komma vorangestellt ist,
wird dieses Komma vom Übersetzer ignoriert.
In unserem obigen Beispiel würde der Aufruf `f(22)` eine Template-Instanziierung
wie folgt ergeben:

```cpp
template<>
void f(int i /*, ignored comma before empty pack expansion */) {
  std::tuple<> argsTuple{}; 
}
```

## Wo können Parameter Pack Expansionen auftreten?

Unsere bisherigen Beispiele haben sich auf den Gebrauch von Parameter Pack Expansionen konzentriert,
um eine Folge von Template Argumenten zu erzeugen.
In der Tat können  Parameter Pack Expansionen prinzipiell überall in C ++ zum Einsatz kommen,
wo die Grammatik eine durch Kommas getrennte Liste gestattet:

| Einsatzmöglichkeiten von Parameter Pack Expansionen |
|:-------------- |
| In der Liste der Basisklassen |
| In der Liste der Basisklassen Initialisierer in einem Konstruktor |
| In der Liste von Aufrufargumenten eines Methodenaufrufs |
| In der Liste von Initialisierern (z. B. in einer geschweiften Initialisiererliste - `std::initializer_list`) |
| In der Template Parameterliste eines Klassen oder Funktionstemplate |
| In der Parameterliste eines Funktionstyps |
| Bei der Verwendung von `using`-Deklarationen |

Tabelle 1. Einsatzmöglichkeiten von Parameter Pack Expansionen.

## Der sizeof… Operator

Der `sizeof...`-Operator ist eine spezielle Form der Parameter Pack Expansion.
Es gibt einfach die Anzahl der Parameter Pack Elemente zurück und funktioniert
sowohl mit *Template Parameter Packs* als auch mit *Function Parameter Packs*:

```cpp
template <typename... Ts>
void printCount(Ts... args) {
  std::cout 
    << sizeof...(Ts) << ' '
    << sizeof...(args) << '\n';
}
```

Test des *Function Templates* am Beispiel

```cpp
printCount(22, std::optional{0}, "!");
```

*Ausgabe*:

```cpp
3 3
```

## Ein erstes Anwendungsbeispiel: Abbildung eines *Parameter Packs* auf einen Methodenaufruf

Es wird demonstriert, wie ein *parameter pack* auf einen Methodenaufruf
(hier: Konstruktor) abgebildet werden kann 
("*Unpacking a parameter pack to call a matching constructor*").

Zu diesem Zweck definieren wir eine Klasse `Unknown` mit einer Reihe
von Konstruktoren, um zu zeigen, wie das Auspacken des *parameter packs*
dem passenden Konstruktor zugeordnet wird:

Es kommt die zentrale `std::forwarding`-Anweisung zum Zuge:

```cpp
T(std::forward<Args>(args)...);
```

Siehe hierzu den [Quellcode](VariadicTemplate_01_Introduction.cpp).


## Ein zweites Anwendungsbeispiel: Verwendung eines Parameter Packs bei Smart Pointern (hier: Unique Pointern)

Siehe hierzu den [Quellcode](VariadicTemplate_01_Introduction.cpp).

---

## Literaturhinweise:

Einführende Artikel zum Thema der varadischen Templates finden sich zum Beispiel unter

[Arne Mertz Introduction](https://arne-mertz.de/2016/11/modern-c-features-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Arne Mertz More About Variadic Templates](https://arne-mertz.de/2016/11/more-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Kevin Ushey Introduction to C++ Variadic Templates](https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Craig Scott Practical uses for Variadic Templates](https://crascit.com/2015/03/21/practical-uses-for-variadic-templates/)<br>(abgerufen am 11.05.2020).

und

[Florian Weber Using Variadic Templates cleanly](https://florianjw.de/en/variadic_templates.html)<br>(abgerufen am 11.05.2020).

---

[Zurück](../../Readme.md)

---

