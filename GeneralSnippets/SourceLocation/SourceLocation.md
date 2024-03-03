# Klasse `std::source_location`

[Zur�ck](../../Readme.md)

---

[Quellcode](SourceLocation.cpp)

---

Die Klasse `std::source_location` bietet eine einfache M�glichkeit,
Informationen �ber den Speicherort des Quellcodes zu erhalten, an dem er verwendet wird,
z. B. Dateiname, Zeilennummer und Funktionsname.

*Beispiel*:

```cpp
01: static void log(
02:     const std::string_view message, 
03:     const std::source_location location = std::source_location::current()) {
04: 
05:     std::println("File:          {}", location.file_name());
06:     std::println("Function Name: {}", location.function_name());
07:     std::println("Column :       {}", location.column());
08:     std::println("Line:          {}", location.line());
09:     std::println("");
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
[Collection of Modern C++-Code Examples - Copyright (C) 2019-2024 Peter Loos]
File:          C:\Development\GitRepositoryCPlusPlus\Cpp_Modern\GeneralSnippets\SourceLocation\SourceLocation.cpp
Function Name: void __cdecl StdSourceLocation::test_01(void)
Column :       9
Line:          28

File:          C:\Development\GitRepositoryCPlusPlus\Cpp_Modern\GeneralSnippets\SourceLocation\SourceLocation.cpp
Function Name: void __cdecl StdSourceLocation::function<const char*>(const char *)
Column :       9
Line:          23
```

---

[Zur�ck](../../Readme.md)

---
