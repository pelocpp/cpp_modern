# Klasse `std::source_location`

[Zurück](../../Readme.md)

---

[Quellcode](SourceLocation.cpp)

---

Die Klasse `std::source_location` bietet eine einfache Möglichkeit,
Informationen über den Speicherort des Quellcodes zu erhalten, an dem er verwendet wird,
z. B. Dateiname, Zeilennummer und Funktionsname:

*Beispiel*:

```cpp
01: static void log(
02:     const std::string_view message, 
03:     const std::source_location location = std::source_location::current())
04: {
05:     std::println("File:          {}", location.file_name());
06:     std::println("Function Name: {}", location.function_name());
07:     std::println("Column :       {}", location.column());
08:     std::println("Line:          {}", location.line());
09:     std::println();
10: }
11: 
12: template<typename T>
13: static void function(T x)
14: {
15:     log(x);
16: }
17: 
18: static void test_01() {
19: 
20:     log("Hello World!");
21:     function("Hello Function!");
22: }
```

*Ausgabe*:

```
File:          C:\Development\GitRepositoryCPlusPlus\Cpp_Modern\GeneralSnippets\SourceLocation\SourceLocation.cpp
Function Name: void __cdecl StdSourceLocation::test_01(void)
Column :       9
Line:          28

File:          C:\Development\GitRepositoryCPlusPlus\Cpp_Modern\GeneralSnippets\SourceLocation\SourceLocation.cpp
Function Name: void __cdecl StdSourceLocation::function<const char*>(const char *)
Column :       9
Line:          23
```

*Bemerkung*:<br />
Die Zeilennummern in der Ausgabe beziehen sich auf den Quellcode im Original.
Dort befinden sich die Aufrufe der `log`-Methode in den Zeilen 23 bzw. 28 und nicht
wie verkürzt im Beispielcode oben dargestellt in den Zeilen 15 und 20.

---

## Literaturhinweise

Ein interessanter Artikel &bdquo;Modern C++ flow diagnostic tools&rdquo;
zur Klasse `std::source_location` findet sich [hier](https://learnmoderncpp.com/2022/08/24/modern-c-flow-diagnostic-tools/).

---

[Zurück](../../Readme.md)

---
