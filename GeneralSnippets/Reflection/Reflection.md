# Reflection in C++

[Zurück](../../Readme.md)

---

[Quellcode](Reflection.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Erste Schritte](#link2)
  * [Weitere Beispiele](#link3)
  * [Literaturhinweise](#link4)


---

## Allgemeines  <a name="link1"></a>

---

#### Hinweis

Das C++ 26 Reflection-API wird aktuell von Microsoft Visual C++ nicht unterstützt.

Es gibt für den Compiler Explorer (Godbolt) einen Link, der eine spezielle Umgebung bereitstellt,
in der man den aktuellen Stand der Reflection-API Entwicklung testen und ausprobieren kann:

[https://compiler-explorer.com/z/M4KjvfM9M](https://compiler-explorer.com/z/M4KjvfM9M)

---

## Erste Schritte <a name="link2"></a>

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
typename[:r:] x = 123;       // same as: int x = 123;
typename[:^char:] c = '*';   // same as: char c = '*';

static_assert(std::same_as<decltype(x), int>);
static_assert(std::same_as<decltype(c), char>);
assert(x == 123);
assert(c == '*');
```

Man kann sich das wie &bdquo;Quote&rdquo; (`^^`) und &bdquo;Unquote&rdquo; (`[: :]`) vorstellen &ndash; jedoch direkt in die Sprache integriert.

---

## Weitere Beispiele <a name="link3"></a>

Im folgenden sind eine Reihe von Textdateien mit Reflection-Beispielen vorhanden:

[Reflection_00: Beispiel aus Compiler Explorer](Reflection_00_Compiler_Explorer.txt)<br />
[Reflection_01: Simple Example](Reflection_01.txt)<br />
[Reflection_02: Enum -> String und Enum -> String](Reflection_02.txt)


Erläuterungen zum Beispiel &bdquo;Enum -> String und Enum -> String&rdquo;:

`^E`: Reflektiert den Typ der Enumeration (holt die Metadaten in den Compiler).
`std::meta::identifier_of(e)`: Liefert zur Compilezeit den exakten Namen des Enumerators als Text zurück.
`[:e:]` (Splicer): Wandelt das Metadaten-Objekt `e` wieder zurück in echten C++-Code um – in diesem Fall wird daraus der echte Wert (z. B. `Color::Red`) an die Stelle im Code eingesetzt.


---

## Literaturhinweise <a name="link4"></a>

Die elementaren Erläuterungen der grammatikalischen Spracherweiterungen
stammen aus [Programmiersprache: Reflection in C++26](https://www.heise.de/blog/Programmiersprache-Reflection-in-C-26-9920405.html).

Eine ganze Serie von Beispielen zu diesem Thema findet man in einer Artikelserie von Andreas Müller.

Die Serie startet mit [diesem](https://starsurgeon.medium.com/c-with-reflection-a-whole-new-language-157e9d243fee) Artikel,
die Folgeartikel sind am Ende
des ersten Artikels mit der Überschrift &bdquo;C++ with Reflection &ndash; &bdquo;A whole new language&rdquo; &ndash; Part 1: From enum to string … and back again&rdquo;
am Ende aufgeführt.

Der Quellcode der Artikelserie wird auch durch ein Github-Repository [cpp_reflection_blog](https://github.com/starsurgeon/cpp_reflection_blog) begleitet.

---

[Zurück](../../Readme.md)

---
