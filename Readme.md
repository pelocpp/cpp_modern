# C++ General Snippets

## Überblick

C++ ist eine high-level, general-purpose Programmiersprache, 
die von Bjarne Stroustrup als Erweiterung der Programmiersprache C bzw. "C mit Klassen" erstellt wurde.
Die Sprache hat sich im Laufe der Zeit erheblich erweitert, und modernes C++ verfügt jetzt
über objektorientierte, generische und funktionale Funktionen sowie über Funktionen zur Low-Level Speichermanipulation.
Es wird fast immer als kompilierte Sprache implementiert, und viele Anbieter bieten für C++ Compiler an,
darunter die Free Software Foundation, LLVM, Microsoft, Intel, Oracle und IBM.
Daher ist es auf vielen Plattformen verfügbar.

## Literaturverzeichnis

Jedes Jahr gibt es immer noch zahlreiche Neuerscheinungen zum Thema C++, die auf den Markt kommen. 
Sich aus der Fülle an alter und neuer C++-Literatur für einen Titel zu entscheiden,
fällt oftmals gar nicht so leicht.
Aus diesem Grund habe ich im Folgenden eine [Liste](GeneralSnippets/Literatur/Literature.md)
zusammengestellt,
welche Bücher bei mir derzeit hoch im Kurs stehen und die meiner Meinung nach absolut lesenswert sind. 

## Katalog aller Code-Snippets

In diesem Projekt sind zahlreiche kleinere Code-Snippets abgelegt, um die diversen Features von C++ 11/14/17 demonstrieren zu können.
Es folgt eine tabellarische Auflistung dieser Unterverzeichnisse.
In der ersten Tabelle wiederholen wir einige Grundlagen von C++. Die Neuerungen von C++ 11/14/17 
schließen sich in Tabelle 2 an:

| Unterverzeichnis | Thematik |
|:-------------- |-----------------------------------------|
| [Allocator](GeneralSnippets/Allocator/StdAllocator.md) | Container und Speicher-Allokatoren |
| [Array Decay](GeneralSnippets/ArrayDecay/ArrayDecay.md) | Arrays und Pointer |
| [Casts](GeneralSnippets/Casts/Casts.md) | Typumwandlungen `static_cast`, `dynamic_cast`, `const_cast` und `reinterpret_cast` |
| [ConstructursOrder](GeneralSnippets/ConstructursOrder/CtorDtorOrder.md)  | Reihenfolge der Aufrufe von Konstruktoren und Destruktoren |
| [TemplatesFunctionBasics](GeneralSnippets/TemplatesFunctionBasics/TemplatesFunctions.md) | Grundlagen zu Funktionstemplates |
| [InputOutputStreams](GeneralSnippets/InputOutputStreams/Streams.md) | Streams manipulieren und formatieren |
| [MemoryLeaks](GeneralSnippets/MemoryLeaks/MemoryLeaksDetection.md) | CRT (C-Runtime-Library) Memory Leak Detection |
| [ParametersWithConstAndRef](GeneralSnippets/ParametersWithConstAndRef/ConstDeclarations.md)  | Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich |

Tabelle 1. Grundlagen-Code-Snippets.

---

| Unterverzeichnis | Thematik |
|:-------------- |-----------------------------------------|
| [Accumulate](GeneralSnippets/Accumulate/StdAccumulate.md) | STL-Algorithmus `std::accumulate` und Lambda-Funktionen in der Anwendung |
| [Any](GeneralSnippets/Any/StdAny.md) | Neue STL-Utility Klasse `std::any` |
| [Array](GeneralSnippets/Array/StdArray.md) | Neue STL-Utility Klasse `std::array` |
| [ConstExpr](GeneralSnippets/ConstExpr/Constexpr.md) | Methoden, die der Compiler zur Übersetzungszeit ausführt |
| [Explicit](GeneralSnippets/Explicit/Explicit.md) | Schlüsselwort `explicit` |
| [Initialization](GeneralSnippets/Initialization/UniformInitialization.md) | Einheitliches Initialisierungs-Konzept |
| [InitializerList](GeneralSnippets/InitializerList/StdInitializerList.md) | Klasse `std::initializer_list<T>` |
| [Lambda](GeneralSnippets/Lambda/Lambda.md) | Lambda-Funktionen |
| [Literals](GeneralSnippets/Literals/Literals.md) | Benutzerdefinierte Literale |
| [MetaProgramming](GeneralSnippets/MetaProgramming/Metaprogramming01.md) | Programmierung zur Übersetzungszeit |
| [Optional](GeneralSnippets/Optional/Optional.md) | Neue STL-Utility Klasse `std::optional` |
| [PerfectForwarding](GeneralSnippets/PerfectForwarding/PerfectForwarding.md) | Perfect Forwarding (`std::forward`) |
| [RAII](GeneralSnippets/RAII/RAII.md) | RAII-Idiom (*Resource acquisition is Initialization*) |
| [ReferenceWrapper](GeneralSnippets/ReferenceWrapper/ReferenceWrapper.md)  | Beispiele zum Einsatz eines Referenz-Wrappers |
| [RValueLValue](GeneralSnippets/RValueLValue/RValueLValue.md) | LValue- und RValue Referenzen |
| [UniquePointer](GeneralSnippets/UniquePtr/UniquePtr.md) | Klasse `std::unique_ptr<T>` |
| [SharedPointer](GeneralSnippets/SharedPtr/SharedPtr.md) | Klasse `std::shared_ptr<T>` |
| [WeakPointer](GeneralSnippets/WeakPtr/WeakPtr.md) | Klasse `std::weak_ptr<T>` |
| [StaticAssert](GeneralSnippets/StaticAssert/StaticAssertion.md) | Compile-Time Makro `static_assert` |
| [StructuredBinding](GeneralSnippets/StructuredBinding/StructuredBinding.md) | Eine neue Möglichkeit der Rückgabe mehrerer Werte |
| [TemplateConstexprIf](GeneralSnippets/TemplateConstexprIf/ConstExpr_If.md) | Templates und bedingte Compilierung (`if constexpr`) |
| [TemplatesClassBasics](GeneralSnippets/TemplatesClassBasics/TemplatesBasics.md) | Grundlagen zu Klassentemplates |
| [TemplateStaticPolymorphism](GeneralSnippets/TemplateStaticPolymorphism/TemplatesStaticPolymorphism.md) | Templates und statischer Polymorphismus |
| [TemplateTemplateParameter](GeneralSnippets/TemplateTemplateParameter/TemplateTemplateParameter.md) | Template Template Parameter |
| [Tuples](GeneralSnippets/Tuple/StdTuple.md) | Neue STL-Utility Klasse `std::tuple` |
| [TypeTraits](GeneralSnippets/TypeTraits/TypeTraits.md) | Typmerkmale |
| [VariadicTemplates](GeneralSnippets/VariadicTemplates/VariadicTemplates_01_Introduction.md) | Templates mit variabler Argumentanzahl (Variadische Templates) |
| [VariadicTemplates](GeneralSnippets/VariadicTemplates/VariadicTemplates_10_Folding.md) | *Folding Expressions* |
| [Variant](GeneralSnippets/Variant/StdVariant.md)  | Neue STL-Utility Klasse `std::variant` |

Tabelle 2. Spracherweiterungen C++ 11/C++ 14/C++ 17.

---
