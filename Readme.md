# Modern C++ Snippets

###### Preamble

*Herb Sutter*: *"The world is built on C++ (and its C subset)"*

---

## Überblick

**C++** ist eine high-level, general-purpose Programmiersprache, 
die von Bjarne Stroustrup als Erweiterung der Programmiersprache C erfunden wurde.
*Cfront* war der ursprüngliche Compiler für C ++ (damals bekannt als "*C with Classes*") aus der Zeit um 1983,
der C ++ in C konvertierte. Entwickelt wurde der Übersetzer von Bjarne Stroustrup bei AT&T Bell Labs.

Die Sprache hat sich im Laufe der Zeit erheblich erweitert, und modernes C++ verfügt jetzt
über objektorientierte, generische und funktionale Möglichkeiten sowie über Funktionen zur Low-Level Speichermanipulation.
Es wird fast immer als kompilierte Sprache implementiert, und viele Anbieter bieten für C++ Compiler an,
darunter die Free Software Foundation, LLVM, Microsoft, Intel, Oracle und IBM.
C++ ist daher auf sehr vielen Plattformen verfügbar.

---

## Literaturverzeichnis

Jedes Jahr gibt es immer noch zahlreiche Neuerscheinungen zum Thema C++, die auf den Markt kommen. 
Sich aus der Fülle an alter und neuer C++-Literatur für einen Titel zu entscheiden,
fällt oftmals gar nicht so leicht.
Aus diesem Grund habe ich im Folgenden eine Liste mit Büchern zusammengestellt,
die bei mir derzeit hoch im Kurs stehen und meiner Meinung nach absolut lesenswert sind. 

[Zum Literaturverzeichnis](GeneralSnippets/Literatur/Literature.md).

---

## Inhaltsverzeichnis

Es ist nicht einfach, bei der Menge an Ergänzungen, Erweiterungen und Neuerungen der Sprache C++ den Überblick
zu behalten. Das von mir zusammengestellte Inhaltsverzeichnis unternimmt zumindest den Versuch,
den größten Teil dieser Sprachergänzungen nach gewissen systematischen und methodischen Gesichtspunkten
so zu gliedern und zusammenzufassen, um bei deren Betrachtung den &ldquo;roten Faden&rdquo; nicht zu verlieren. 

[Zum Inhaltsverzeichnis](GeneralSnippets/Agenda/Agenda.md).

---

## Aufgaben

Einige kleinere Aufgaben (samt Musterlösungen) sind diesem Repository ebenfalls beigefügt.
Sie können bei weitem nicht den gesamten Stoffumfang des *Modern C++* Sprachumfangs abdecken,
dienen aber dem Zweck, die "graue Materie" an der einen oder anderen Stelle etwas aufzuhellen:

[Zu den Aufgaben](GeneralSnippets/Exercises/Exercises.md).

---

## Katalog aller Grundlagen-Code-Snippets

In diesem Projekt sind zahlreiche kleinere Code-Snippets abgelegt, um die diversen Features von C++&ndash;11/14/17 demonstrieren zu können.
Es folgt eine tabellarische Auflistung dieser Unterverzeichnisse.
In der ersten Tabelle wiederholen wir einige Grundlagen von C++, die immer wieder 
zu Fragen führen:

| Unterverzeichnis | Thematik |
|:-------------- |-----------------------------------------|
| [Allocator](GeneralSnippets/Allocator/StdAllocator.md) | Container und Speicher-Allokatoren |
| [ArrayDecay](GeneralSnippets/ArrayDecay/ArrayDecay.md) | Arrays und Pointer |
| [BackInserter](GeneralSnippets/BackInserter/BackInserter.md) | `std::back_inserter` Iterator |
| [Casts](GeneralSnippets/Casts/Casts.md) | Typumwandlungen `static_cast`, `dynamic_cast`, `const_cast` und `reinterpret_cast` |
| [ConstructursOrder](GeneralSnippets/ConstructursOrder/CtorDtorOrder.md)  | Reihenfolge der Aufrufe von Konstruktoren und Destruktoren |
| [*Erase-Remove* Idiom](GeneralSnippets/EraseRemoveIdiom/EraseRemoveIdiom.md) | Das *Erase-Remove*-Idiom |
| [TemplatesFunctionBasics](GeneralSnippets/TemplatesFunctionBasics/TemplatesFunctions.md) | Grundlagen zu Funktionstemplates |
| [TemplateSpecialization](GeneralSnippets/TemplateSpecialization/TemplateSpecialization.md) | Template Spezialisierung (Template Specialization) |
| [InputOutputStreams](GeneralSnippets/InputOutputStreams/Streams.md) | Streams manipulieren und formatieren |
| [MemoryLeaks](GeneralSnippets/MemoryLeaks/MemoryLeaksDetection.md) | CRT (C-Runtime-Library) Memory Leak Detection |
| [ParametersWithConstAndRef](GeneralSnippets/ParametersWithConstAndRef/ConstDeclarations.md)  | Die Deklarationen `int& const`, `int const&`, `const& int` und `const int&` im Vergleich |
| [VirtualBaseClassDestructor](GeneralSnippets/VirtualBaseClassDestructor/VirtualBaseClassDestructor.md) | Virtuelle Destruktoren (einer Basisklasse) |

Tabelle 1. Grundlagen-Code-Snippets.

## Katalog aller Modern-C++-Code-Snippets

In der folgenden Tabelle sind alle Neuerungen von C++&ndash;11/14/17 aufgeführt:

| Unterverzeichnis | Thematik |
|:-------------- |-----------------------------------------|
| [Accumulate](GeneralSnippets/Accumulate/StdAccumulate.md) | STL-Algorithmus `std::accumulate` und Lambda-Funktionen in der Anwendung |
| [Any](GeneralSnippets/Any/StdAny.md) | Neue STL-Utility Klasse `std::any` |
| [Apply](GeneralSnippets/Apply/Apply.md) | `std::apply`, `std::integer_sequence` und `std::make_integer_sequence` |
| [Array](GeneralSnippets/Array/StdArray.md) | Neue STL-Utility Klasse `std::array` |
| [ConstExpr](GeneralSnippets/ConstExpr/ConstExpr.md) | Methoden, die der Compiler zur Übersetzungszeit ausführt |
| [CommonType](GeneralSnippets/CommonType/CommonType.md) | Utility `std::common_type` |
| [CRTP](GeneralSnippets/CRTP/CRTP.md) | Curiously Recurring Template Pattern (CRTP) |
| [DeclType](GeneralSnippets/DeclType/decltype.md) | `decltype` und `std::declval` |
| [DefaultInitialization](GeneralSnippets/DefaultInitialization/DefaultInitialization.md)| Default-Initialisierung für Member-Variablen |
| [Explicit](GeneralSnippets/Explicit/Explicit.md) | Schlüsselwort `explicit` |
| [ExpressionTemplates](GeneralSnippets/ExpressionTemplates/ExpressionTemplates.md) | Expression Templates |
| [FileSystem](GeneralSnippets/FileSystem/FileSystem.md) | C++ 17 FileSystem Library |
| [FunctionalProgramming](GeneralSnippets/FunctionalProgramming/FunctionalProgramming.md) | Funktionale Programmierung |
| [InitializerList](GeneralSnippets/InitializerList/StdInitializerList.md) | Klasse `std::initializer_list<T>` |
| [Invoke](GeneralSnippets/Invoke/StdInvoke.md) | `std::invoke`: "*Uniformly invoking anything callable*" |
| [Lambda](GeneralSnippets/Lambda/Lambda.md) | Lambda-Funktionen |
| [Literals](GeneralSnippets/Literals/Literals.md) | Benutzerdefinierte Literale |
| [MetaProgramming](GeneralSnippets/MetaProgramming/Metaprogramming01.md) | Programmierung zur Übersetzungszeit |
| [MoveSemantics](GeneralSnippets/MoveSemantics/MoveSemantics.md) | *Move Semantics* / Verschiebesemantik |
| [Optional](GeneralSnippets/Optional/Optional.md) | Neue STL-Utility Klasse `std::optional` |
| [PerfectForwarding](GeneralSnippets/PerfectForwarding/PerfectForwarding_01.md) | Perfect Forwarding (`std::forward`) |
| [RAII](GeneralSnippets/RAII/RAII.md) | RAII-Idiom (*Resource acquisition is Initialization*) |
| [Random](GeneralSnippets/Random/Random.md) | Generierung von Zufallszahlen |
| [ReferenceWrapper](GeneralSnippets/ReferenceWrapper/ReferenceWrapper.md)  | Beispiele zum Einsatz eines Referenz-Wrappers |
| [RegExpr](GeneralSnippets/RegExpr/RegExpr.md) | Reguläre Ausdrücke |
| [RValueLValue](GeneralSnippets/RValueLValue/RValueLValue.md) | LValue- und RValue Referenzen |
| [SFINAE_EnableIf](GeneralSnippets/SFINAE_EnableIf/Sfinae.md) | SFINAE und `std::enable_if` |
| [SharedPointer](GeneralSnippets/SharedPtr/SharedPtr.md) | Klasse `std::shared_ptr<T>` |
| [SSO](GeneralSnippets/SSO/SSO.md) | *Small String Optimization* |
| [StandardLibrarySTL](GeneralSnippets/StandardLibrarySTL/StandardLibrarySTL.md) | Die C++ Standard Template Library (STL): Ergänzungen |
| [StaticAssert](GeneralSnippets/StaticAssert/StaticAssertion.md) | Compile-Time Makro `static_assert` |
| [StringView](GeneralSnippets/StringView/StdStringView.md) | Klasse `std::string_view` |
| [StructuredBinding](GeneralSnippets/StructuredBinding/StructuredBinding.md) | Eine neue Möglichkeit der Rückgabe mehrerer Werte |
| [TemplateConstexprIf](GeneralSnippets/TemplateConstexprIf/ConstExpr_If.md) | Templates und bedingte Compilierung (`if constexpr`) |
| [TemplatesClassBasics](GeneralSnippets/TemplatesClassBasics/TemplatesBasics.md) | Grundlagen zu Klassentemplates |
| [TemplateStaticPolymorphism](GeneralSnippets/TemplateStaticPolymorphism/TemplatesStaticPolymorphism.md) | Templates und statischer Polymorphismus |
| [TemplateTemplateParameter](GeneralSnippets/TemplateTemplateParameter/TemplateTemplateParameter.md) | Template Template Parameter |
| [Transform](GeneralSnippets/Transform/Transform.md) | STL-Algorithmus `std::transform` und Lambda-Funktionen in der Anwendung |
| [Tuples](GeneralSnippets/Tuple/StdTuple.md) | Neue STL-Utility Klasse `std::tuple` |
| [TypeTraits](GeneralSnippets/TypeTraits/TypeTraits.md) | Typmerkmale |
| [UniformInitialization](GeneralSnippets/UniformInitialization/UniformInitialization.md) | Einheitliches Initialisierungs-Konzept |
| [UniquePointer](GeneralSnippets/UniquePtr/UniquePtr.md) | Klasse `std::unique_ptr<T>` |
| [VariadicTemplates](GeneralSnippets/VariadicTemplates/VariadicTemplates_01_Introduction.md) | Templates mit variabler Argumentanzahl (Variadische Templates) |
| [Folding](GeneralSnippets/VariadicTemplates/VariadicTemplates_10_Folding.md) | *Folding Expressions* |
| [Variant](GeneralSnippets/Variant/StdVariant.md)  | Neue STL-Utility Klasse `std::variant` |
| [VirtualOverrideFinal](GeneralSnippets/VirtualOverrideFinal/VirtualOverrideFinal.md) | Neue Schlüsselwörter `override` und `final` |
| [WeakPointer](GeneralSnippets/WeakPtr/WeakPtr.md) | Klasse `std::weak_ptr<T>` |

Tabelle 2. Spracherweiterungen C++&ndash;11/14/17.

---
