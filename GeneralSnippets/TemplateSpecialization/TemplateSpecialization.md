# Template Spezialisierung

[Zur�ck](../../Readme.md)

---

[Quellcode](TemplateSpecialization_01.cpp)

---

## Template Spezialisierung

Mit Hilfe der Template Spezialisierung k�nnen
unterschiedliche Template Implementierungen in
Abh�ngigkeit von den Parametern gew�hlt werden.

Performance ist ein h�ufiger Grund f�r die Template Spezialisierung, aber nicht der Einzige.
Man kann beispielsweise ein Template auch spezialisieren, um mit bestimmten Objekten zu arbeiten,
die nicht der normalen Schnittstelle entsprechen, die von der generischen Vorlage erwartet wird.
Diese Betrachtungen bzw. Ausnahmef�lle k�nnen mit zwei Arten der Templatespezialisierung behandelt werden:

  * der expliziten Template Spezialisierung (&bdquo;*Explicit Template Specialization*&rdquo;)
  * der teilweisen (partiellen) Template Spezialisierung (&bdquo;*Partial Template Specialization*&rdquo;)


#### Explizite Template Spezialisierung

Die explizite Template Spezialisierung &ndash; auch als *Full Template Specialization* bezeichnet &ndash; 
stellt eine Template Definition f�r einen bestimmten Parametersatz dar (z.B. `MyContainer<bool>`).

Es lassen sich mit einer solchen Definition Sonderf�lle behandeln.


#### Partielle Template Spezialisierung

Sie stellt eine Teil-Spezialisierung dar, bei der
nicht alle Parameter des prim�ren (nicht spezialisierten) Klassen-Templates ersetzt werden.

Sie repr�sentiert damit eine Menge von Parametern, wie z.B. `MyContainer<const T*>` mit beliebigem `T`. 

*Hinweis*:
Das Feature der partiellen Template Spezialisierung kann nicht auf Funktions-Templates angewendet werden.

#### Allgemeine Eigenschaften der Template Spezialisierung:

  * Wenn sowohl eine explizite als auch eine partielle Spezialisierung passen,
  wird die explizite Spezialisierung ausgew�hlt.
  * Passt keine Spezialisierung, wird das prim�re Template genommen.

---

## Beispiel einer expliziten Template Spezialisierung

Mit der expliziten Template Spezialisierung k�nnen Sie eine bestimmte Implementierung
f�r eine bestimmte Kombination von Template Parametern schreiben.

Beispiel: 

```cpp
01: template<typename T>
02: class GenericSorter
03: {
04: public:
05:     static void sort(std::vector<T>&) { /* ... */ }
06: };
```

Wenn wir eine schnellere (oder andere spezialisierte) M�glichkeit haben,
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

Der Compiler w�hlt dann die am besten geeignete Schablone aus:

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

F�r Klassen Templates (nicht: Funktions-Templates) kann man Teilspezialisierungen definieren,
die nicht alle Parameter der prim�ren (nicht spezialisierten) Klassenvorlage ersetzen.

Betrachten wir dazu das folgende Beispiel. Die erste Vorlage ist die prim�re Klassenvorlage:

```cpp
01: template<typename T>
02: class GenericSorter
03: {
04: public:
05:     static void sort(std::vector<T>&) { /* ... */ }
06: };
```

Wir k�nnen `T` f�r den Fall spezialisieren, dass der aktuelle Template Parameter ein Zeiger-Datentyp ist,
also ein `T*` ist:

```cpp
01: template<typename T>
02: class GenericSorter<T*>
03: {
04: public:
05:     static void sort(std::vector<T*>&) { /* ... */ }
06: };
```

Der Compiler w�hlt nun im folgenden Beispiel die Templates so aus:

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

[Zur�ck](../../Readme.md)

---
