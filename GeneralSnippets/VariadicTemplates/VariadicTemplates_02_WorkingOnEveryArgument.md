# Teil II: Variadische Templates - Zugriff auf jedes einzelne Argument

[Zur�ck](../../Readme.md)

---

&#x21D2; [Teil III: Variadische Templates: Anwendungsfall "Summe von Summen"](VariadicTemplates_03_SumOfSums.md)

&#x21D0; [Teil I: Variadische Templates - Einf�hrung](VariadicTemplates_01_Introduction.md)

---

[Quellcode](VariadicTemplate_02_WorkingOnEveryArgument.cpp)

---

Grunds�tzlich gibt es zwei M�glichkeiten, um Funktionsparameterpacks zu bearbeiten:
Verwendung der Pack-Erweiterung "im Ganzen" oder der rekursive Aufruf derselben Funktion,
wobei diese bei jedem Aufruf ein einzelnes Argument aus dem Parameter Pack extrahiert.

## Parameter Pack Expansions Trick mit Hilfe von `std::initializer_list`

Manchmal m�chten wir einfach f�r jedes Argument des Parameter Packs eine Funktion aufrufen.
Die Pack-Expansion funktioniert jedoch nur an Stellen, an denen durch Kommas getrennte Listen zul�ssig sind.
Dies ist offensichtlich keine durch Kommas getrennte Liste:

```cpp
doSomething(arg1);
doSomething(arg2);
...
doSomething(argN);
```

Es verwundert also nicht, dass folgendes Code-Fragment nicht kompilierbar ist:

```cpp
template <typename... TArgs>
void doSomethingForAll(TArgs const&... args) {
    doSomething(args)...;
}
```

Mit der C++-Klasse `std::initializer_list` gibt es eine M�glichkeit,
die Expansion des Parameter Packs in ein �bersetzungsf�higes Code-Fragment zu delegieren:

```cpp
template <typename... Args>
void doSomethingForAll(Args const&... args) {
  auto list = { doSomething(args)... };
}
```

Dieses Fragment m�ssen Sie genau betrachten: Die Variable `list` wird hier als
`std::initializer_list`-Objekt vorbelegt - mit welchen Werten
auch immer, die von `doSomething` zur�ckgeliefert werden. Die Erzeugung eines 
`std::initializer_list`-Objekts ist direkt im Quellcode nicht erkennbar,
da dies durch die *Uniform Initialization Syntax* sehr kompakt formulierbar ist,
also ohne Verwendung des `std::initializer_list`-Bezeichners!

Wir betrachten das Funktionstemplate `doSomethingForAll` am Aufruf von

```cpp
doSomethingForAll(1, '!', 5.5);
```

und werfen einen Blick mit *CppInsight.io* auf das Cross-Compilat:

```cpp
/* First instantiated from: insights.cpp:21 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void doSomethingForAll<int, char, double>(const int & __args0, const char & __args1, const double & __args2)
{
  std::initializer_list<int> list = std::initializer_list<int> {
    (doSomething(__args0) , 0), 
    (doSomething(__args1) , 0), 
    (doSomething(__args2) , 0)
  };
}
#endif
```

Voil� - hier haben wir die `std::initializer_list`!. Ich habe den Output nur noch leicht 
umformatiert, damit das Ganze auf einer GitHub-Seite besser dargestellt wird. Ein Beispiel
f�r den Aufruf von `doSomethingForAll` mit einer konkreten `doSomething`-Funktion finden Sie
im korrespondierenden Code-Snippet vor!

Bei genauem Hinschauen erkennen Sie, dass da jede Menge zus�tzlicher Kommas vorhanden sind,
die wir so nicht erwartet haben.

Da Aufrufe von `doSomething` zu einer Mixtur unterschiedlicher Typen f�hren k�nnen,
bei denen auch `void` zul�ssig ist, kann es zu �bersetzungsfehlern kommen (*cannot initialize an array element of type 'const int' with an rvalue of type 'void'*).
Ein weiterer Trick besteht nun darin, einen Ausdruck als Erweiterungsmuster so zu erstellen,
dass zwar immer dieselbe Funktion aufgerufen wird (egal, welchen R�ckgabewert sie besitzt),
aber immer ein ganz anderer Wert als Argument f�r das `std::initializer_list`-Objekt genommen wird.
Mit dem Komma-Operator ist dies einfach:

```cpp
template <typename... TArgs>
void doSomethingForAll(const TArgs& ... args) {
    std::initializer_list<int> list = { (doSomething(args), 0)... };
}
```

Jetzt sind die Funktionsaufrufe nur ein Nebeneffekt,
und das Ergebnis wird `std::initializer_list<int>` ausschlie�lich mit Nullen f�llen.
Genau diese Schablone habe ich bei der Betrachtung mit *CppInsight.io* verwendet!

## C++ 17 `constexpr if`

Wir betrachten eine Variation des letzten Beispiels:
Angenommen, wir m�chten alle durch Kommas getrennten Argumente unserer Funktion mit `std::cout` ausgeben.
Wir k�nnten den obigen Trick verwenden, mit der Funktion `doSomething`,
die den Wert plus ein Komma ausgibt.
Das Problem liegt dann beim letzten Argument, dem kein Komma folgen sollte,
das aber von `doSomething` nicht erkannt werden kann.

Mit C++ 17 haben wir `constexpr if` und k�nnen diese Anforderung wie folgt umsetzen:

```cpp
template <typename HEAD, typename... TAIL>
void print(const HEAD& head, const TAIL&... tail) {
    std::cout << head;
    if constexpr (sizeof...(tail) > 0) {
        std::cout << ", ";
        print(tail...);
    }
}
```

Hier wird der Hauptteil des `if`-Zweiges nur kompiliert,
wenn `tail` mindestens ein Element enth�lt. Ohne `constexpr if` w�rde
dies zu einem Kompilierungsfehler f�hren,
da der Compiler nicht die entsprechende `print`-Funktion f�r einen Aufruf
mit null Argumenten findet!


## Literaturhinweise

Die Beispiele stammen aus

[Arne Mertz More About Variadic Templates](https://arne-mertz.de/2016/11/more-variadic-templates/)<br>(abgerufen am 11.05.2020).

---

[Zur�ck](../../Readme.md)

---

