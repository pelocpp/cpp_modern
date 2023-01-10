# Template Spezialisierung

[Zurück](../../Readme.md)

---

[Quellcode](TemplateSpecialization_01.cpp)

---

## Template Spezialisierung

Mit Hilfe der Template Spezialisierung können
unterschiedliche Template Implementierungen in
Abhängigkeit von den Parametern gewählt werden.

Performance ist ein häufiger Grund für die Template Spezialisierung, aber nicht der Einzige.
Man kann beispielsweise ein Template auch spezialisieren, um mit bestimmten Objekten zu arbeiten,
die nicht der normalen Schnittstelle entsprechen, die von der generischen Vorlage erwartet wird.
Diese Betrachtungen bzw. Ausnahmefälle können mit zwei Arten der Templatespezialisierung behandelt werden:

  * der expliziten Template Spezialisierung (&ldquo;*Explicit Template Specialization*&rdquo;)
  * der teilweisen (partiellen) Template Spezialisierung (&ldquo;*Partial Template Specialization*&rdquo;)


#### Explizite Template Spezialisierung

Die explizite Template Spezialisierung &ndash; auch als *Full Template Specialization* bezeichnet &ndash; 
stellt eine Template Definition für einen bestimmten Parametersatz dar (z.B. `MyContainer<bool>`).

Es lassen sich mit einer solchen Definition Sonderfälle behandeln.


#### Partielle Template Spezialisierung

Sie stellt eine Teil-Spezialisierung dar, bei der
nicht alle Parameter des primären (nicht spezialisierten) Klassen-Templates ersetzt werden.

Sie repräsentiert damit eine Menge von Parametern, wie z.B. `MyContainer<const T*>` mit beliebigem `T`. 

*Hinweis*:
Das Feature der partiellen Template Spezialisierung kann nicht auf Funktions-Templates angewendet werden.

#### Allgemeine Eigenschaften der Template Spezialisierung:

  * Wenn sowohl eine explizite als auch eine partielle Spezialisierung passen,
  wird die explizite Spezialisierung ausgewählt.
  * Passt keine Spezialisierung, wird das primäre Template genommen.

---

## Beispiel einer expliziten Template Spezialisierung

Mit der expliziten Template Spezialisierung können Sie eine bestimmte Implementierung
für eine bestimmte Kombination von Template Parametern schreiben.

Beispiel: 

```cpp
01: template<typename T>
02: class GenericSorter
03: {
04: public:
05:     static void sort(std::vector<T>&) { /* ... */ }
06: };
```

Wenn wir eine schnellere (oder andere spezialisierte) Möglichkeit haben,
speziell mit Vektoren von `char`-Variablen (Zeichen) umzugehen,
dann kann man die Klasse `GenericSorter` explizit spezialisieren:

```cpp
01: template<>
02: class GenericSorter<char>
03: {
04: public:
05:     static void sort(std::vector<char>&) { /* ... */ }
06: };
```

Der Compiler wählt dann die am besten geeignete Schablone aus:

```cpp
01: void main() {
02:     std::vector<int>  intVector;
03:     std::vector<char> charVector;
04: 
05:     GenericSorter<int>::sort(intVector);    // calls sort<std::vector<int>&>
06:     GenericSorter<char>::sort(charVector);  // calls specialized sort<std::vector<char>&>
07: }

```

## Beispiel einer partiellen Template Spezialisierung

Für Klassen Templates (nicht: Funktions-Templates) kann man Teilspezialisierungen definieren,
die nicht alle Parameter der primären (nicht spezialisierten) Klassenvorlage ersetzen.

Betrachten wir dazu das folgende Beispiel. Die erste Vorlage ist die primäre Klassenvorlage:

```cpp
01: template<typename T>
02: class GenericSorter
03: {
04: public:
05:     static void sort(std::vector<T>&) { /* ... */ }
06: };
```

Wir können `T` für den Fall spezialisieren, dass der aktuelle Template Parameter ein Zeiger-Datentyp ist,
also ein `T*` ist:

```cpp
01: template<typename T>
02: class GenericSorter<T*>
03: {
04: public:
05:     static void sort(std::vector<T*>&) { /* ... */ }
06: };
```

Der Compiler wählt nun im folgenden Beispiel die Templates so aus:

```cpp
01: void main() {
02:     std::vector<int> intVector;
03:     std::vector<int*> pointerVector;
04: 
05:     GenericSorter<int>::sort(intVector);       // calls sort<std::vector<int>&>
06:     GenericSorter<int*>::sort(pointerVector);  // calls specialized sort<std::vector<char>&>
07: }
```

---

[Zurück](../../Readme.md)

---
