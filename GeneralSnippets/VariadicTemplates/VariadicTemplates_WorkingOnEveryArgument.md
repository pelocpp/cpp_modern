# Variadische Templates: Zugriff auf jedes einzelne Argument

// https://arne-mertz.de/2016/11/more-variadic-templates/

Grundsätzlich gibt es zwei Möglichkeiten, um Funktionsparameterpacks zu bearbeiten:
Verwendung der Pack-Erweiterung "im Ganzen" oder der rekursive Aufruf derselben Funktion,
wobei diese bei jedem Aufruf ein einzelnes Argument aus dem Parameter Pack extrahiert.

## Parameter Pack Expansion Trick mit Hilfe von `std::initializer_list`

Manchmal möchten wir einfach für jedes Argument des Parameter Packs eine Funktion aufrufen.
Die Pack-Expansion funktioniert jedoch nur an Stellen, an denen durch Kommas getrennte Listen zulässig sind.
Dies ist offensichtlich keine durch Kommas getrennte Liste:

```cpp
  doSomething(arg1);
  doSomething(arg2);
  ...
  doSomething(argN);
```

Es verwunderert also nicht, dass das folgenden Code-Fragment nicht kompilierbar ist:

```cpp
template <class... ARGS>
void doSomethingForAll(ARGS const&... args) {
  doSomething(args)...;
}
```

Mit der C++-Klasse `std::initializer_list` gibt es eine Möglichkeit,
die Expansion des Parameter Packs in ein übersetzungsfähiges Code-Fragment zu delegieren:

```cpp
template <class... Args>
void doSomethingForAll(Args const&... args) {
  auto list = { doSomething(args)... };
}
```

Dieses Fragment müssen Sie genau betrachten: Die Variable `list` wird hier als
`std::initializer_list`-Objekt vorbelegt - mit welchen Werten
auch immer, die von `doSomething` zurückgeliefert werden. Die Erzeugung eines 
`std::initializer_list`-Objekt ist direkt im Quellcode nicht erkennbar,
da dies durch die *Uniform Initialization Syntax* auch sehr kompakt formulierbar ist,
also eben ohne Verwendung des `std::initializer_list`-Bezeichners!

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

Voilà - hier haben wir die `std::initializer_list`!. Ich haben den Output nur noch leicht 
umformatiert, damit das Ganze auf einer GitHub-Seite besser dargestellt wird.

Bei genauem Hinschauen erkennen Sie, dass da jede Menge zusätzlicher Kommas vorhanden sind,
die wir so nicht erwartet haben.

Da Aufrufe von `doSomething` zu eine Mixtur unterschiedlicher Typen führen kann, bei denen auch `void` 
zulässig ist, kann es zu Übersetzungsfehlern kommen (*cannot initialize an array element of type 'const int' with an rvalue of type 'void'*).
Ein weiterer Trick besteht nun darin, einen Ausdruck als Erweiterungsmuster so zu erstellen,
dass zwar immer dieselbe Funktion aufgerufen wird (egal, welchen Rückgabewert sie besitzt),
aber immer ein ganz anderer Wert als Argument für das `std::initializer_list`-Objekt genommen wird.
Mit dem Komma-Operator ist dies einfach:

```cpp
template <class... Args>
void doSomethingForAll(Args const&... args) {
  std::initializer_list<int> list = { (doSomething(args), 0)... };
}
```

Jetzt sind die Funktionsaufrufe nur ein Nebeneffekt,
und das Ergebnis wird `std::initializer_list<int>` ausschließlich mit Nullen füllen.
Genau diese Schablone habe ich bei der Betrachtung mit *CppInsight.io* verwendet!

## C++ 17 `constexpr if`

Wir betrachten eine Variation des letzten Beispiels:
Angenommen, wir möchten alle durch Kommas getrennten Argumente unserer Funktion mit `cout` ausgeben.
Wir könnten den obigen Trick verwenden, mit der Funktion `doSomething`,
die den Wert plus ein Komma ausgibt.
Das Problem liegt dann beim letzten Argument, dem kein Komma folgen sollte,
das aber von `doSomething` nicht erkannt werden kann.

Mit C++ 17 haben wir `constexpr if` und können diese Anforderung wie folgt umsetzen:

```cpp
template <class Head, class... Tail>
void print(const Head& head, const Tail&... tail) {
    std::cout << head;
    if constexpr (sizeof...(tail) > 0) {
        std::cout << ", ";
        print(tail...);
    }
}
```

Hier wird der Hauptteil des `if`-Zweiges nur kompiliert,
wenn `tail` mindestens ein Element enthält. Ohne `constexpr if` würde
dies zu einem Kompilierungsfehler führen,
da der Compiler nicht die entsprechende `print`-Funktion für einen Aufruf
mit null Argumenten findet!

Wie immer kann jede Rekursion in eine Iteration konvertiert werden!
Für variadischen Templates sprechen wir dann von einer Parameter Pack Expansion:

```cpp
template <class Head, class... Tail>
void print1(const Head& head, const Tail&... tail) {
    std::cout << head;
    (void)std::initializer_list<int>{ ((std::cout << ", " << tail), 0)... };
}
```

Ausgabe mit *CppInsight.io*:

```cpp
/* First instantiated from: insights.cpp:47 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void print1<int, char, double>(const int & head, const char & __tail1, const double & __tail2)
{
  std::cout.operator<<(head);
  static_cast<void>(std::initializer_list<int> {
    ((std::operator<<(std::operator<<(std::cout, ", "), __tail1)) , 0), 
    ((std::operator<<(std::cout, ", ").operator<<(__tail2)) , 0)
  });
}
#endif
```
