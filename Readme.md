# Modern C++ Snippets

###### Preamble

<img align="right" width="80" height="120" src="Certified Expert Trainer.png" />

<br/>*Herb Sutter*:<br/>*"The world is built on C++ (and its C subset)"*

<br/>

---

## Bevor es losgeht ...

*Modern C++* mag möglicherweise für den einen oder anderen Entwickler durch seine Komplexität etwas abschreckend wirken.
Nichtsdestotrotz ist diese Programmiersprache aus der systemnahen Software-Entwicklung und vielen anderen
Einsatzbereichen nicht mehr wegzudenken.
C++ zählt zu den Programmiersprachen, die ein etwas tieferes Verständnis erfordern.
Ziel dieses Seminars/Repositories ist es, auf die größten Hürden beim Erlernen von *Modern C++* einzugehen!

<img src="Horse_Cpp.png" width="600">

Abbildung 1: Modern C++ &ndash; *Relax*!

([How To Build A Horse With Programming](https://toggl.com/blog/build-horse-programming))

---

## Überblick

**C++** ist eine high-level, general-purpose Programmiersprache, 
die von Bjarne Stroustrup als Erweiterung der Programmiersprache C erfunden wurde.
*Cfront* war der ursprüngliche Compiler für C ++ &ndash; damals bekannt als &ldquo;*C with Classes*&rdquo; &ndash; aus der Zeit um 1983,
der C ++ in C konvertierte. Entwickelt wurde der Übersetzer von Bjarne Stroustrup bei AT&T Bell Labs.

Die Sprache hat sich im Laufe der Zeit erheblich erweitert, und modernes C++ verfügt jetzt
über objektorientierte, generische und funktionale Möglichkeiten sowie über Funktionen zur Low-Level Speichermanipulation.
Es wird fast immer als kompilierte Sprache implementiert, und viele Anbieter bieten für C++ Compiler an,
darunter die Free Software Foundation, LLVM, Microsoft, Intel, Oracle und IBM.
C++ ist daher auf sehr vielen Plattformen verfügbar.

Einen genauen Abriss zur geschichtlichen Entwicklung von C++ kann man
[hier](https://en.cppreference.com/w/cpp/language/history)
nachlesen.

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

Es ist nicht einfach, bei der Menge an sprachlichen Ergänzungen, Erweiterungen und Neuerungen von C++ den Überblick
zu behalten. Das von mir zusammengestellte Inhaltsverzeichnis unternimmt den Versuch,
den größten Teil dieser Weiterentwicklung zumindest nach gewissen systematischen und methodischen Gesichtspunkten
so zu gliedern und zusammenzufassen, dass bei deren Betrachtung der &ldquo;rote Faden&rdquo; nicht verloren geht. 

[Zum Inhaltsverzeichnis](GeneralSnippets/Agenda/Agenda.md).

---

## Aufgaben

Einige kleinere Aufgaben (samt Musterlösungen) sind diesem Repository ebenfalls beigefügt.
Sie können bei weitem nicht den gesamten Stoffumfang des *Modern C++* Sprachumfangs abdecken,
dienen aber dem Zweck, die &ldquo;graue Materie&rdquo; an der einen oder anderen Stelle etwas aufzuhellen:

[Zu den Aufgaben](GeneralSnippets/Exercises/Exercises.md).

---

## Online C++ Compiler 

Online C++ Compiler können nützliche Werkzeuge sein, um ein Code-Snippet schnell kompilieren und/oder ausführen zu können,
ohne hierfür extra einen C++ Compiler installieren zu müssen.
Besonders nützlich können Online Compiler sein, um mit den neuesten Sprachfeatures zu spielen
oder auch um verschiedene Compiler vergleichen zu können.

[Weitere Details](GeneralSnippets/OnlineCppCompilers/OnlineCppCompilers.md).

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
| [Bind](GeneralSnippets/Bind/Bind.md) | `std::bind` |
| [Casts](GeneralSnippets/Casts/Casts.md) | Typumwandlungen `static_cast`, `dynamic_cast`, `const_cast` und `reinterpret_cast` |
| [ConstructursOrder](GeneralSnippets/ConstructursOrder/CtorDtorOrder.md)  | Reihenfolge der Aufrufe von Konstruktoren und Destruktoren |
| [TemplatesFunctionBasics](GeneralSnippets/TemplateFunctionBasics/TemplatesFunctionBasics.md) | Grundlagen zu Funktions-Templates |
| [TemplatesClassBasics](GeneralSnippets/TemplateClassBasics/TemplatesClassBasics.md) | Grundlagen zu Klassen-Templates |
| [TemplateSpecialization](GeneralSnippets/TemplateSpecialization/TemplateSpecialization.md) | Template Spezialisierung |
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
| [ArgumentDependentNameLookup](GeneralSnippets/ArgumentDependentNameLookup/ArgumentDependentNameLookup.md) | Argument-Dependent Name Lookup (ADL) / *Koenig*-Lookup |
| [Array](GeneralSnippets/Array/StdArray.md) | Neue STL-Utility Klasse `std::array` |
| [Attributes](GeneralSnippets/Attributes/Attributes.md) | C++ Standard Attribute |
| [Auto](GeneralSnippets/Auto/Auto.md) | `auto` |
| [ConstExpr](GeneralSnippets/ConstExpr/Constexpr.md) | Programmierung zur Übersetzungszeit mit `constexpr` |
| [CommonType](GeneralSnippets/CommonType/CommonType.md) | Utility `std::common_type` |
| [CRTP](GeneralSnippets/CRTP/CRTP.md) | Curiously Recurring Template Pattern (CRTP) |
| [DeclType](GeneralSnippets/DeclType/decltype.md) | `decltype` und `std::declval` |
| [DefaultInitialization](GeneralSnippets/DefaultInitialization/DefaultInitialization.md)| Default-Initialisierung für Member-Variablen |
| [*Erase-Remove* Idiom](GeneralSnippets/EraseRemoveIdiom/EraseRemoveIdiom.md) | Das *Erase-Remove*-Idiom |
| [Explicit](GeneralSnippets/Explicit/Explicit.md) | Schlüsselwort `explicit` |
| [ExpressionTemplates](GeneralSnippets/ExpressionTemplates/ExpressionTemplates.md) | Expression Templates |
| [FileSystem](GeneralSnippets/FileSystem/FileSystem.md) | C++ 17 FileSystem Library |
| [Folding](GeneralSnippets/Folding/VariadicTemplatesFolding.md) | *Folding Expressions* |
| [FunctionalProgramming](GeneralSnippets/FunctionalProgramming/FunctionalProgramming.md) | Funktionale Programmierung |
| [Generate](GeneralSnippets/Generate/Generate.md) | STL-Algorithmus `std::generate` |
| [GenericLambdas](GeneralSnippets/GenericLambdas/GenericLambdas.md) | Generische Lambda Ausdrücke |
| [InitializerList](GeneralSnippets/InitializerList/StdInitializerList.md) | Klasse `std::initializer_list<T>` |
| [Invoke](GeneralSnippets/Invoke/StdInvoke.md) | `std::invoke`: "*Uniformly invoking anything callable*" |
| [Lambda](GeneralSnippets/Lambda/Lambda.md) | Lambda-Funktionen |
| [Literals](GeneralSnippets/Literals/Literals.md) | Benutzerdefinierte Literale |
| [MetaProgramming](GeneralSnippets/MetaProgramming/Metaprogramming01.md) | Programmierung zur Übersetzungszeit |
| [MoveSemantics](GeneralSnippets/MoveSemantics/MoveSemantics.md) | *Move Semantics* / Verschiebesemantik |
| [Optional](GeneralSnippets/Optional/StdOptional.md) | Neue STL-Utility Klasse `std::optional` |
| [PerfectForwarding](GeneralSnippets/PerfectForwarding/PerfectForwarding_01.md) | Perfect Forwarding (`std::forward`) |
| [RAII](GeneralSnippets/RAII/RAII.md) | RAII-Idiom (*Resource acquisition is Initialization*) |
| [Random](GeneralSnippets/Random/Random.md) | Generierung von Zufallszahlen |
| [RangeBasedForLoop](GeneralSnippets/RangeBasedForLoop/RangeBasedForLoop.md) | Range-based `for` Loop |
| [ReferenceWrapper](GeneralSnippets/ReferenceWrapper/ReferenceWrapper.md)  | Beispiele zum Einsatz eines Referenz-Wrappers |
| [RegExpr](GeneralSnippets/RegExpr/RegExpr.md) | Reguläre Ausdrücke |
| [RValueLValue](GeneralSnippets/RValueLValue/RValueLValue.md) | LValue- und RValue Referenzen |
| [SFINAE_EnableIf](GeneralSnippets/SFINAE_EnableIf/Sfinae.md) | SFINAE und `std::enable_if` |
| [SharedPointer](GeneralSnippets/SharedPtr/StdSharedPtr.md) | Klasse `std::shared_ptr<T>` |
| [SSO](GeneralSnippets/SSO/SSO.md) | *Small String Optimization* |
| [StandardLibrarySTL](GeneralSnippets/StandardLibrarySTL/StandardLibrarySTL.md) | Die C++ Standard Template Library (STL): Ergänzungen |
| [StaticAssert](GeneralSnippets/StaticAssert/StaticAssertion.md) | Compile-Time Makro `static_assert` |
| [StringView](GeneralSnippets/StringView/StdStringView.md) | Klasse `std::string_view` |
| [StructuredBinding](GeneralSnippets/StructuredBinding/StructuredBinding.md) | Verknüpfung einer Liste von Bezeichnern mit einem Satz von Objekten (Variablen) |
| [TemplateConstexprIf](GeneralSnippets/TemplateConstexprIf/ConstExpr_If.md) | Templates und bedingte Compilierung (`if constexpr`) |
| [TemplateStaticPolymorphism](GeneralSnippets/TemplateStaticPolymorphism/TemplatesStaticPolymorphism.md) | Templates und statischer Polymorphismus |
| [TemplateTemplateParameter](GeneralSnippets/TemplateTemplateParameter/TemplateTemplateParameter.md) | Template Template Parameter |
| [TemplateTwoPhaseLookup](GeneralSnippets/TemplateTwoPhaseLookup/TemplateTwoPhaseLookup.md) | Two-Phase Name Lookup |
| [Transform](GeneralSnippets/Transform/Transform.md) | STL-Algorithmus `std::transform` und Lambda-Funktionen in der Anwendung |
| [TrimmingStrings](GeneralSnippets/Trim/Trim.md) | Leerzeichen am Anfang und Ende einer Zeichenkette entfernen |
| [Tuples](GeneralSnippets/Tuple/StdTuple.md) | Neue STL-Utility Klasse `std::tuple` |
| [TypeTraits](GeneralSnippets/TypeTraits/TypeTraits.md) | Typmerkmale |
| [UniformInitialization](GeneralSnippets/UniformInitialization/UniformInitialization.md) | Einheitliches Initialisierungs-Konzept |
| [UniquePointer](GeneralSnippets/UniquePtr/StdUniquePtr.md) | Klasse `std::unique_ptr<T>` |
| [VariadicTemplates](GeneralSnippets/VariadicTemplates/VariadicTemplates_01_Introduction.md) | Templates mit variabler Argumentanzahl (Variadische Templates) |
| [Variant](GeneralSnippets/Variant/StdVariant.md)  | Neue STL-Utility Klasse `std::variant` |
| [VirtualOverrideFinal](GeneralSnippets/VirtualOverrideFinal/VirtualOverrideFinal.md) | Neue Schlüsselwörter `override` und `final` |
| [WeakPointer](GeneralSnippets/WeakPtr/StdWeakPtr.md) | Klasse `std::weak_ptr<T>` |

Tabelle 2. Spracherweiterungen C++&ndash;11/14/17/20.

---
