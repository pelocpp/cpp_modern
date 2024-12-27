# Teil I: Variadische Templates - Einführung

[Zurück](../../Readme.md)

---

&#x21D2; [Teil II: Variadische Templates: Zugriff auf jedes einzelne Argument](VariadicTemplates_02_WorkingOnEveryArgument.md)

---

[Quellcode](VariadicTemplate_01_Introduction.cpp)

---

## Inhalt

  * [Einleitung](#link1)
  * [Das *Parameter Pack*](#link2)
  * [Expansion eines Parameter Packs: Datentypen und Argumente](#link3)
  * [Ein einfaches Beispiel: `add`-Funktion mit beliebig vielen Argumenten](#link4)
  * [ Zugriff auf die einzelnen Elemente eines Parameter Packs](#link5)
  * [Leeres Parameter Pack](#link6)
  * [Wo können Parameter Pack Expansionen auftreten?](#link7)
  * [Der `sizeof...` Operator](#link8)
  * [Ein erstes Anwendungsbeispiel: Abbildung eines *Parameter Packs* auf einen Methodenaufruf](#link9)
  * [Ein zweites Anwendungsbeispiel: Verwendung eines Parameter Packs bei Smart Pointern (hier: Unique Pointern)](#link10)
  * [Literaturhinweise](#link11)

---

## Einleitung <a name="link1"></a>

Ab C++&ndash;11 gibt es in C++ die so genannten *variadischen Templates*  (*Variadic Templates*).
Darunter versteht man Klassen- oder Funktionstemplates ,
die eine beliebige Anzahl von Argumenten annehmen können.

In klassischem C++ können Templates nur eine feste Anzahl von Parametern haben,
die bei der Deklaration angegeben werden müssen.
Variadische Templates helfen jedoch, dieses Problem zu überwinden.

Das Konzept für diese Spracherweiterung wurde von *Douglas Gregor* und *Jaakko Järvi* entwickelt.

Grundsätzlich werden zwei neue syntaktische Elemente
für die Definition derartiger Templates benötigt:
Zum einen das so genannte *Parameter Pack* zur Deklaration des Templates,
zum anderen die *Expansion* des *Parameter Packs* in der Definition des Templates.

## Das *Parameter Pack* <a name="link2"></a>

Ein *Parameter Pack* ist einfach ein Name,
der einer Liste von Templateparametern anstelle eines einzelnen Parameters
zugewiesen wird. Die häufigsten zwei Arten von Templateparametern
und damit Möglichkeiten, *Parameter Packs* anzuwenden lauten:

```cpp
template <typename... TS>    // TS is a list of type parameters
template <unsigned... NS>    // NS is a list of non-type parameters (unsigned)
```

Der erste Fall tritt in der Praxis am häufigsten auf.
Wie bei &bdquo;normalen&rdquo; Vorlagen können variadische Templates Funktionstemplates
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
template <typename... TArgs>    // TArgs is the template parameter pack
void func (TArgs... args) {     // args is the function parameter pack
  //...
}
```

Noch etwas formale Formulierungen gewünscht? Bitte schön: 
Wenn in Betrachtung der Funktionsschablone `func` **TArgs** ≙ **T1, T2** ist,
dann gilt

  * **TArgs ... args** ≙ **T1 t1, T2 t2** und
  * **args ... ≙ t1, t2**


## Expansion eines Parameter Packs: Datentypen und Argumente <a name="link3"></a>

Es ist nicht möglich, ein *Parameter Pack* anders zu verwenden als es zu erweitern.
In den meisten Fällen ergibt die Erweiterung des *Parameter Packs* eine durch Kommas getrennte Liste von Ausdrücken,
die die einzelnen Elemente des *Packs* enthalten.

Die einfachste Pack-Expansion ist nur der Name des *Parameter Packs*,
gefolgt von der Ellipse (`...`), was zu einer durch komma-getrennten Liste der *Pack*-Elemente führt:

```cpp
template <typename... TArgs>
void examine_parameter_pack(TArgs ... args) {
    std::tuple<TArgs ...> tup { args ... };
}
```

oder ab C++ 20:

```cpp
void examine_parameter_pack_ex(auto ... args) {
    std::tuple tup1{ args ... };
}
```

Betrachten wir ein Beispiel:

```cpp
examine_parameter_pack(123, 123.456, std::string{ "foo" }, 789ll);
```

In dem Funktionsaufruf von `examine_parameter_pack` definieren die vier Parameter
**zwei** *Parameter Packs*. Das *Template Parameter Pack* `TArgs` ist die Liste der Typen
`int`, `double`, `std::string` und `long  long`,
während das *Function Parameter Pack* `args` die Liste mit den Werten
`123`, `123.456`, `std::string{ "foo" }` und `789ll`
darstellt.

Diese betrachtete Instanziierung der Funktionsvorlage entspricht quasi dem,
als hätten wir geschrieben:

```cpp
void examine_parameter_pack_ex_ex(int args_1, double args_2, std::string args_3, long long args_4) {
    std::tuple<int, double, std::string, long long> tup{ args_1, args_2, args_3, args_4 };
}
```

Nur um es kurz angesprochen zu haben: Bei `std::tuple` handelt es sich ebenfalls
um ein variadisches Klassentemplate.

## Ein einfaches Beispiel: `add`-Funktion mit beliebig vielen Argumenten <a name="link4"></a>

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

## Zugriff auf die einzelnen Elemente eines Parameter Packs <a name="link5"></a>

Prinzipiell ist der Zugriff auf die einzelnen Elemente eines Parameter Packs nicht vorgesehen.

Sind alle Elemente vom selben Typ,
kann man diese mit Hilfe eines `std::initializer_list`-Objekts entpacken:


```cpp
template <typename... TArgs>
void func(TArgs... args) {

    // unpack all function arguments with the help of a std::initializer_list object
    auto unpackedArgs = { args ... };

    for (auto param : unpackedArgs) {
        std::cout << "Passed Argument: " << param << std::endl;
    }

    // oder

    for (auto param : { args ... } ) {
        std::cout << "Passed Argument: " << param << std::endl;
    }
}

static void test_accessing_parameterpack()
{
    func(10, 11, 12, 13, 14, 15);
}
```


## Leeres Parameter Pack <a name="link6"></a>

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

## Wo können Parameter Pack Expansionen auftreten? <a name="link7"></a>

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

*Tabelle* 1. Einsatzmöglichkeiten von Parameter Pack Expansionen.

## Der `sizeof...` Operator <a name="link8"></a>

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

## Ein erstes Anwendungsbeispiel: Abbildung eines *Parameter Packs* auf einen Methodenaufruf <a name="link9"></a>

Es wird demonstriert, wie ein *Parameter Pack* auf einen Methodenaufruf
(hier: Konstruktor) abgebildet werden kann 
("*Unpacking a Parameter Pack to call a matching constructor*").

Zu diesem Zweck definieren wir eine Klasse `Unknown` mit einer Reihe
von Konstruktoren, um zu zeigen, wie das Auspacken des *Parameter Packs*
dem passenden Konstruktor zugeordnet wird:

Es kommt das &bdquo;*perfekte Forwarding*&rdquo; zum Zuge:

```cpp
T(std::forward<Args>(args)...);
```

Siehe hierzu den [Quellcode](VariadicTemplate_01_Introduction.cpp).


## Ein zweites Anwendungsbeispiel: Verwendung eines Parameter Packs bei Smart Pointern (hier: Unique Pointern) <a name="link10"></a>

Siehe hierzu den [Quellcode](VariadicTemplate_01_Introduction.cpp).

---

## Literaturhinweise <a name="link11"></a>

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

