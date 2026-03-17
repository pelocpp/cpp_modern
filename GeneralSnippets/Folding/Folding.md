# Folding-Ausdrücke

[Zurück](../../Readme.md)

---

[Quellcode](Folding.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Syntax](#link2)
  * [&bdquo;Folding über einem Komma&rdquo;](#link3)
  * [Ein Zeitvergleich: Iteration vs. Folding](#link4)
  * [C++20: &bdquo;*Variadic Capture*&rdquo;](#link5)

---

## Allgemeines <a name="link1"></a>

Ein *Folding*-Ausdruck ist ein arithmetischer Ausdruck,
der einen Operator auf alle Werte eines variadischen Parameterpacks anwendet.

*Beispiel*:

Arithmetischer Ausdruck mit Plus-Operator &ndash; Notation ohne *Folding*:

```cpp
int sum = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10;
```

Berechnung desselben Ausdrucks durch einen Folding-Ausdruck:

```cpp
auto add(auto ... args) {
    return (... + args);
}

void test() {

    int sum = add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
}
```

---

## Syntax <a name="link2"></a>


*Folding*-Audrücke lassen sich in 4 Kategorien einteilen, wie folgende Tabelle 
darstellt:

| Name | Ausdruck | Wird erweitert zu |
|:-|:-|:-|
| Unary Left Fold | (... *op* pack) | ((pack<sub>1</sub> *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Binary Left Fold | (init *op* ... *op* pack) | (((init *op* pack<sub>1</sub>) *op* pack<sub>2</sub>) *op* ...) *op* pack<sub>N</sub> |
| Unary Right Fold | (pack *op* ...) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* pack<sub>N</sub>)) |
| Binary Right Fold | (pack *op* ... *op* init) | pack<sub>1</sub> *op* (... *op* (pack<sub>N-1</sub> *op* (pack<sub>N</sub> *op* init))) |

*Tabelle* 1: *Folding*-Audrücke.

Der Addierer und ein einfacher Printer demonstrieren in den Code-Snippets *fold expressions*.

Theoretisch stehen für *Folding-Expressions* 32 Operatoren zur Verfügung.
Diese wären `+`, `-`, `*`, `/`, `%`, `^`, `&`, `|`, `=`, `<`, `>`, `<<`, `>>`, `+=`, `-=`, `*=`, `/=`, `%=`, `^=`, `&=`, `|=`, `<<=`, `>>=`, `==`, `!=`, `<=`, `>=`, `&&`, `||`, `,`, `.*` und `->*`.

---

## &bdquo;Folding über einem Komma&rdquo; <a name="link3"></a>

Ein Sonderfall des Foldings ist das sogenannte *&bdquo;Folding über einem Komma&rdquo;*.
Dieses wird ebenfalls an mehreren Beispielen veranschaulicht:

```cpp
template <typename... TArgs>
static void printerWithSeperator(TArgs ... args) {
    std::string sep = " - ";
    ((std::cout << args << sep) , ...) << std::endl;
}
```

---

## Ein Zeitvergleich: Iteration vs. Folding <a name="link4"></a>

Wir schließen dieses Kapitel mit einem Zeitvergleich ab.
Um die ersten zehn natürlichen Zahlen zu addieren, betrachten wir zwei Funktionen:

```cpp
auto add (auto ... values) {
    return (... + values);
}
```

und

```cpp
auto add (auto ... values) {
        
    auto list = { values ...};

    auto sum{ 0 };
    for (auto elem : list) {
        sum += elem;
    }

    return sum;
}
```

Wenn wir den Aufruf

```cpp
auto sum { add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) };
```

entsprechend oft wiederholen, zeichnet sich folgender Unterschied ab (*Debug*-Modus):

```
Elapsed time: 516 milliseconds.    // folding
Elapsed time: 6211 milliseconds.   // iterating
```

---

## C++20: &bdquo;*Variadic Capture*&rdquo; <a name="link5"></a>

Ab C++20 lässt sich mit Hilfe des so genannten &bdquo;*Variadic Capture*&rdquo;
(oft auch &bdquo;*Pack Expansion in Lambda Init-Capture*&rdquo; genannt)
ein komplettes variadisches Parameterpaket (*Parameter Pack*) in einen Lambda-Ausdruck einbinden.

Diese Funktionalität ermöglicht es Ihnen, eine Liste von Argumenten &bdquo;perfekt&rdquo;
an den Closure eines Lambda-Ausdrucks weiterzuleiten.
Hierdurch kann das Schreiben generischer Wrapper oder Factory-Funktionen vereinfacht werden.

*Beispiel*:

```cpp
01: template <typename... TArgs>
02: auto createDelayedPrinter(TArgs&&... args)
03: {
04:     // Variadic Capture: [...args = std::forward<Args>(args)]
05:     // This captures each element of the pack into the lambda.
06:     return [...args = std::forward<TArgs>(args)] () {
07:             
08:         // using a fold expression to print the captured pack
09:         (std::cout << ... << args) << std::endl;
10:     };
11: }
12: 
13: void test()
14: {
15:     auto printMessage = createDelayedPrinter("Hello - ", "Variadic - ", "Capture!");
16: 
17:     // doing something else ...
18: 
19:     // now invoking the wrapper object, including the parameters
20:     printMessage();
21: }
```

*Ausgabe*:

```
Hello - Variadic - Capture!
```

---

[Zurück](../../Readme.md)

---
