# `std::apply`, `std::integer_sequence` und `std::make_integer_sequence`

Oder auch

## &ldquo;*Generierung von Integer-Sequenzen zur Kompilierungszeit*&rdquo;

[Zurück](../../Readme.md)

---

[Quellcode](Apply.cpp)

---

In einigen Situationen kann es nützlich sein, zur Übersetzungszeit Folgen ganzer Zahlen zu generieren.
In diesem Beispiel zeigen wir auf, wie dies in C++ geht und geben ein Beispiel für deren Verwendung.

## *Compile Time* `int` Zahlenfolgen

Wir erstellen nun ganzzahlige Sequenzen, die wie folgt aussehen:

```cpp
sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>
```

Betrachten Sie hierzu die folgenden Klassendefinitionen:

```cpp
// class definition (type which holds sequences)
template <int ... NS>
struct sequence
{};

// helper class template declaration
template <int ... NS>
struct sequence_helper;

// helper class template: recursion case
template <int N, int ... NS>
struct sequence_helper<N, NS...>
{
    using type = typename sequence_helper<N-1, N-1, NS...>::type;
};

// recursion termination
template <int ... NS>
struct sequence_helper<0, NS ...>
{
    using type = sequence<NS ...>;
};

template <int N>
using make_index_sequence = typename sequence_helper<N>::type;
```

Der Zweck in der Definition von `struct sequence` besteht ausschließlich darin, Zahlenfolgen zu &ldquo;tragen&rdquo;.
Beachten Sie, dass es sich um eine leere Klasse handelt, die tatsächlich definiert ist (da sie einen leeren Definitionskörper `{}`  hat).
Dies ist wichtig, da diese Klasse in einigen Anwendungsfällen instanziiert wird.

Die Klasse `sequence_helper` wird verwendet, um eine ganzzahlige Sequenz rekursiv zu generieren.
Betrachten wir die Abbildung vom Schritt `N` auf den Schritt `N-1` etwas genauer:
Von der Zahlenfolge `NS...` wird die erste Zahl &ldquo;entnommen&rdquo; und dekrementiert (`N-1`).
Danach wird ihr Wert zweimal verwendet:

  * Der erste Wert geht in die rekursive Template Klassendefinition ein, damit die irgendwann zum Abbruch der Rekursion führt. 
  * Der zweite Wert wird in die Sequenz aufgenommen.

`make_index_sequence` schließlich ist eine `using`-Klausel, die einen `sequence`-Typ definiert,
der quasi als Schnittstelle für den Endbenutzer fungiert.

Am besten betrachten wir das Ganze am Beispiel von

```cpp
auto seq = make_index_sequence<4>{};
```

  * `make_index_sequence<4>{};` ist definiert als `sequence_helper<4>::type`
  * `sequence_helper<4>::type` ist rekursiv definiert als `sequence_helper<3, 3>::type`
  * `sequence_helper<3, 3>::type` ist rekursiv definiert als  `sequence_helper<2, 2, 3>::type`
  * `sequence_helper<2, 2, 3>::type` ist rekursiv definiert als  `sequence_helper<1, 1, 2, 3>::type`
  * `sequence_helper<1, 1, 2, 3>::type` ist rekursiv definiert als `sequence_helper<0, 0, 1, 2, 3>::type` 
  * `sequence_helper<0, 0, 1, 2, 3>::type` ist auf Grund der Abbruchbedingung definiert als `sequence<0, 1, 2, 3>;`

Damit resultiert der Ausdruck `make_index_sequence<4>{}` letzten Endes in `sequence<0, 1, 2, 3>{}`.

## Ein Anwendungsbeispiel: `std::tuple`

Wir betrachten eine Funktion `f`, die einen bestimmten Satz von Parametern bestimmten Typs akzeptiert:

```cpp
void f (double, float, int);
```

Und ein `std::tuple` Objekt, das Variablen genau desgleichen Typs enthält:

```cpp
std::tuple<double, float, int> someTuple;
```

Um `f` mit den Werten des `someTuple`-Objekts aufzurufen, könnte man folgenden Code schreiben:

```cpp
f(std::get<0>(someTuple),std::get<1>(someTuple),std::get<2>(someTuple));
```

Dies ist nicht besonders schön zu lesen und vor allem auch fehleranfällig,
da möglicherweise falsche Indizes verwendet werden. 

Es wäre schöner, einen Funktions-Wrapper zu haben, der eine Semantik wie
„Verwenden Sie diese Funktion und dieses Tupel. Nehmen Sie dann automatisch alle Tupelwerte aus dem Tupel, um die Funktion mit ihnen aufzurufen“:

```cpp
unpack_and_call(f, someTuple);
```

Schauen wir uns an, wie dies mit *Compile Time* `int` Zahlenfolgen umgesetzt werden kann:

```cpp
void f(double x, std::string y, int z) 
{
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl;
}

template <typename TFUNC, typename TUPLE, int ... TINDICES>
static void tuple_call_(TFUNC func, TUPLE tuple, sequence<TINDICES...>)
{
    func(std::get<TINDICES>(tuple) ...);
}

template <typename TFUNC, typename ... TS>
static void tuple_call(TFUNC func, std::tuple<TS ...> tuple)
{
    tuple_call_(func, tuple, make_index_sequence<sizeof...(TS)> {});
}
```

Damit lässt sich eine Anwendung wie folgt schreiben:

```cpp
void test()
{
    std::tuple<double, std::string, int> someTuple = std::make_tuple<>(123.456, std::string("ABC"), 789);
    f(std::get<0>(someTuple), std::get<1>(someTuple), std::get<2>(someTuple));
    tuple_call(f, someTuple); // same effect
}
```

Okay, diese Vorarbeiten hätten wir nicht zwingend erbringen müssen: In der C++-Standardbibliothek
gibt es die Funktion `tuple_call` bereits schon in Gestalt von `std::apply`:

```cpp
void test()
{
    std::tuple<double, std::string, int> someTuple = std::make_tuple<>(123.456, std::string("ABC"), 789);
    f(std::get<0>(someTuple), std::get<1>(someTuple), std::get<2>(someTuple));
    std::apply(f, someTuple); // same effect
}
```

---

## Literaturhinweise:

Die Beispiel zu diesem Snippet sind angelehnt an

[Jacek's C++ Blog: "Generating Integer Sequences at Compile Time"](https://blog.galowicz.de/2016/06/24/integer_sequences_at_compile_time/)

[Details of `std::make_index_sequence` and `std::index_sequence`](https://stackoverflow.com/questions/49669958/details-of-stdmake-index-sequence-and-stdindex-sequence)

[Iterating with std::integer_sequence](https://riptutorial.com/cplusplus/example/4331/iterating-with-std--integer-sequence)

---

[Zurück](../../Readme.md)

---
