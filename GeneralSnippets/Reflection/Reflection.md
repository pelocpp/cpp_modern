# Reflection in C++

[Zurück](../../Readme.md)

---

[Quellcode](Reflection.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Literaturhinweise](#link2)


---

## Allgemeines

---

## Hinweis

Das C++ 26 Reflection-API wird aktuell von Microsoft Visual C++ nicht unterstützt.

Es gibt für den Compiler Explorer (Godbolt) einen Link, der eine spezielle Umgebung bereitstellt,
in der man den aktuellen Stand der Reflection-API Entwicklung testen und ausprobieren kann:

[https://compiler-explorer.com/z/M4KjvfM9M](https://compiler-explorer.com/z/M4KjvfM9M)

---

## Erste Schritte

Durch Reflection bekommt C++ zwei neue Operatoren:

### Der Reflection-Operator `^^` 

Der Reflexionsoperator erzeugt einen so genannten &bdquo;Reflexionswert&rdquo; aus seinem Operanden,
zum Beispiel `^int` oder `^char`:

*Beispiel*:

```cpp
constexpr auto r = ^int;
```

Ein Reflexionswert ist eine Darstellung von Programmelementen als konstanter Ausdruck.

Reflexionswerte können von Typen, Aufzählungen, Funktionen etc. gebildet werden.

### Der Splice-Operator `[: ... :]`

Unter Splicing versteht man den Vorgang, bei dem eine Reflexionswert wieder in echten C++-Code umgewandelt wird.

Ist `r` eine Reflection einer Entität, so fügt `[:r:]` die entsprechende Entität (bzw. den Ausdruck oder Typ) an dieser Stelle in das Programm ein.

*Beispiel*:

```cpp
typename[:r:] x = 123;       // Same as: int x = 123;
typename[:^char:] c = '*';  // Same as: char c = '*';

static_assert(std::same_as<decltype(x), int>);
static_assert(std::same_as<decltype(c), char>);
assert(x == 42);
assert(c == '*');
```

Man kann sich das wie „Quote“ (`^^`) und „Unquote“ (`[: :]`) vorstellen – jedoch direkt in die Sprache integriert.

---

## Literaturhinweise <a name="link2"></a>


A)

https://www.heise.de/blog/Programmiersprache-Reflection-in-C-26-9920405.html

https://starsurgeon.medium.com/c-with-reflection-a-whole-new-language-157e9d243fee


WEITER : enum to string



https://github.com/starsurgeon/cpp_reflection_blog













Die Beispiele zu dem Verpacken von Resource Handles in `std::unique_ptr<T>`-Objekten
stammen aus einem Artikel von

[Wrapping Resource Handles in Smart Pointers](https://www.cppstories.com/2016/10/wrapping-resource-handles-in-smart/) (abgerufen am 5.7.2024).


Auch in das C++&ndash;Umfeld dringen bisweilen *Fake*-*News* ein:

[No New New: Das Ende von Zeigern in C++](https://www.heise.de/blog/No-New-New-4009347.html) (abgerufen am 13.06.2022).

&bdquo;*Vor zwei Wochen fand das ISO-C++-Standardisierungsmeeting in Jacksonville statt.*
*Das Standardisierungskomitee entschied, dass Zeiger mit C++ 20 deprecated und mit C++23 mit hoher Wahrscheinlichkeit entfernt werden.*&rdquo;
Alles weitere hierzu können Sie dem zitierten Artikel entnehmen :)

Ein interessanter &ndash; und inhaltlich zutreffenderer &ndash; Artikel zum Thema &bdquo;Smart Pointer&rdquo; findet sich unter

[unique_ptr, shared_ptr, weak_ptr, or reference_wrapper for class relationships](https://www.nextptr.com/tutorial/ta1450413058/unique_ptr-shared_ptr-weak_ptr-or-reference_wrapper-for-class-relationships)<br>(abgerufen am 20.12.2021).

---

[Zurück](../../Readme.md)

---
