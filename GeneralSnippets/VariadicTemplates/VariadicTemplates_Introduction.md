# Variadische Templates: Einführung

Ab C++ 11 gibt es in C++ die so genannten *variadic Templates*, 
mit denen ein einzelnes Template definiert werden kann,
das eine beliebige Anzahl von Parametern annehmen kann.

Grundsätzlich werden zwei neue syntaktische Elemente
für die Definition derartiger Templates benötigt:
Zum einen das so genannte *parameter pack* zur Deklaration des Templates,
zum anderen die *Expansion* des *parameter packs* in der Definition des Templates.

## Parameter Pack

Ein *Parameter Pack* ist einfach ein Name,
der einer Liste von Templateparametern anstelle eines einzelnen Parameters
zugewiesen wird. Es gibt drei Arten von Templateparametern
und damit drei Möglichkeiten, *parameter packs* anzuwenden:

```cpp
template <class... TS>                     // TS is a list of type parameters
template <unsigned... NS>                  // NS is a list of non-type parameters (unsigned)
template <template <class T>... class US>  // US is a list of template template parameters
```

Der erste Fall tritt in der Praxis am häufigsten auf.
Wie bei „normalen“ Vorlagen können variadische Templates Funktionstemplates
oder Klassentemplates sein.
Wir können auch einzelne Parameter und *parameter packs* mischen,
mit der Einschränkung, dass es nur eine einzige *parameter pack* Definition geben kann
und diese am Ende der Parameterliste stehen muss:

```cpp
template <class T, int N, class... TS>
```

Zusätzlich zu Template *parameter packs* haben wir *function parameter packs*.
Sie kommen zum Einsatz, wenn in einem variadischen Funktionstemplate
das Template *parameter pack* zum Definieren von Funktionsargumenten verwendet wird.
Dies sollten wir an einem Beispiel veranschaulichen:

```cpp
template <class... ARGS>       // ARGS is the template parameter pack
void f(int i, ARGS... args) {  // args is the function parameter pack
  //...
}
```

## Expansion des Parameter Packs

Es ist nicht möglich, ein *parameter pack* zu verwenden, außer es zu erweitern.
In den meisten Fällen ergibt die Erweiterung des *parameter packs* eine durch Kommas getrennte Liste von Ausdrücken,
die die einzelnen Elemente des packs enthalten.

Die einfachste Pack-Expansion ist nur der Names des packs,
gefolgt von der Ellipse (...), was zu einer durch komma-getrennten Liste der pack-Elemente führt:

```cpp
template <class... ARGS>
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
definieren **zwei** *parameter packs*. Das Template *parameter pack* `ARGS` ist die Liste der Typen
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

Nur um es kurz angesprochen zu haben: Bei `std::tuple` handelt es sich evenfalls
um ein variadisches Klassentemplate.

## Ein weiteres Beispiel zur Parameter Pack Expansion

Die Ellipses direkt nach dem Namen des Parameter packs ist die einfachste Form der Parameter Pack Expansion.
Es kann jedoch sehr wohl komplizierter sein. Im Prinzip können wir jedes Muster schreiben,
das einen Parameter Pack Namen enthält, gefolgt von einer Ellipse.
Das Ergebnis ist eine durch Kommas getrennte Liste von Mustern, wobei in jedem Muster der Pack Name
durch ein Mitglied des Packs ersetzt wird.

Nehmen wir zum Beispiel das zuvor verwendete Tupel.
Normalerweise möchten wir das "*perfect forwarding*" verwenden ,
um das Tupel aus den Funktionsargumenten zu erstellen. Werfen wir einen Blick auf ein Beispiel:

```cpp
template <class... ARGS>
void f(int i, ARGS&&... args) {
    std::tuple<ARGS...> argsTuple{ std::forward<ARGS>(args)... }; 
    //...
}
```

Wir haben hier **drei** Pack-Expansionen: `ARGS&&...` bedeutet (beachten Sie die beiden &),
dass wir eine Liste von Vorwärtsreferenzen habeb.
Die `ARGS...` Expansion für die `std::tuple` Templateparameter hatten wir bereits in dem
Beispiel zuvor betrachtet.
Die dritte Erweiterung `std::forward<ARGS>(args)...` enthält **zwei** Parameter Packs:
das Template Parameter Pack `ARGS` und das Funktionsparameterpack `args`.
Immer wenn zwei Packs im Muster für eine Pack-Erweiterung erscheinen,
werden beide gleichzeitig erweitert und müssen daher die gleiche Anzahl von Elementen haben!

Die obige Funktion im Pseudo-Template-Code nach der Pack-Erweiterung würde folgendermaßen aussehen:

```cpp
template <class Args_1, class Args_2, /* etc ... */>
void f(int i, Args_1&& args_1, Args_2&& args_2, /*...*/) {
  std::tuple<Args_1, Args_2, /*...*/> argsTuple{ std::forward<Args_1>(args_1), std::forward<Args_2>(args_2), /*...*/ }; 
  //...
}
```

## Leeres Parameter Pack

Ein Parameter Pack kann prinzipiell auch keine Parameter annehmen.
In diesen Fällen ergibt die Pack-Expansion eine leere Liste.
In Fällen, in denen der Pack-Expansion ein Komma vorangestellt ist,
wird dieses Komma vom Übersetzer ignoriert.
In unserem obigen Beispiel würde der Aufruf `f(22)` eine Tempalteinstanziierung
wie folgt ergeben:

```cpp
template<>
void f(int i /*, ignored comma before empty pack expansion */) {
  std::tuple<> argsTuple{}; 
}
```

## Der sizeof… Operator

Der `sizeof...`-Operator ist eine spezielle Form der Parameter Pack Expansion.
Es gibt einfach die Anzahl der Parameter Pack Elemente zurück und funktioniert
sowohl mit *Template parameter packs* als auch mit *Function parameter packs*:

```cpp
template <class... Ts>
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


## Literaturhinweise:

Einführende Artikel zum Thema der varadischen Templates finden sich zum Beispiel unter

[Arne Mertz Introduction](https://arne-mertz.de/2016/11/modern-c-features-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Arne Mertz More About Variadic Templates](https://arne-mertz.de/2016/11/more-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Kevin Ushey Introduction to C++ Variadic Templates](https://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/)<br>(abgerufen am 11.05.2020).

[Craig Scott Practical uses for Variadic Templates](https://crascit.com/2015/03/21/practical-uses-for-variadic-templates/)<br>(abgerufen am 11.05.2020).

und

[Florian Weber Using Variadic Templates cleanly](https://florianjw.de/en/variadic_templates.html)<br>(abgerufen am 11.05.2020).
