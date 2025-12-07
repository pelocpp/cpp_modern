# Unique Pointer: Klasse `std::unique_ptr`

[Zurück](../../Readme.md)

---

[Quellcode](UniquePtr.cpp)

---

## Inhalt

  * [&bdquo;It's about ownership&rdquo;](#link1)
  * [Die Klasse `std::unique_ptr` unterstützt Arrays](#link2)
  * [Das *Source*-*Sink*-Pattern mit `std::unique_ptr<T>`-Objekten](#link3)
  * [Verpacken von Resource Handles in `std::unique_ptr`-Objekten](#link4)
  * [Verpacken von Win32 HANDLEs in `std::unique_ptr`-Objekten](#link5)
  * [Literaturhinweise](#link6)

---

## &bdquo;It's about ownership&rdquo; <a name="link1"></a>

#### Exklusiver Besitz: `std::unique_ptr<T>`

###### Geteilter Besitz: `std::shared_ptr<T>`

###### Temporärer Besitz: `std::weak_ptr<T>`

---

## Die Klasse `std::unique_ptr` unterstützt Arrays <a name="link2"></a>

Beispiel:

```cpp
01: // creates a unique_ptr to an array of 5 A objects
02: std::unique_ptr<A[]> ptr{ std::make_unique<A[]>(5) };
```

---

## Das *Source*-*Sink*-Pattern mit `std::unique_ptr<T>`-Objekten <a name="link3"></a>

`std::unique_ptr<T>`-Objekte sind weder kopierbar (Kopier-Konstruktor)
noch ist eine Wertzuweisung (`operator=`) möglich.

Dies schließt interessanterweise nicht aus, dass man Funktionen/Methoden schreiben kann,
die einen Parameter des Typs `std::unique_ptr<T>` (*by-value*) haben,
also nicht vom Typ `std::unique_ptr<T>&` (*by-reference*)!

Wir zeigen die Vorgehensweise an einem Beispiel auf &ndash;
in der Praxis sprechen wir vom *Source*-*Sink*-Pattern:

> Eine Funktion kreiert (`new`) eine Ressource, eine andere gibt sie wieder frei (`delete`).
Natürlich kommt in diesem Pattern bzgl. des `std::unique_ptr<T>`-Objekts die Move-Semantik zum Tragen.
Sie muss in diesem Beispiel nur nicht explizit formuliert werden,
da der Rückgabewert des Erzeugers ein temporäres Objekt ist und infolgedessen der
Verschiebe-Konstruktor automatisch aufgerufen wird.

Im [Quellcode](UniquePtr.cpp) finden Sie hierzu ein Beispiel vor.

---

## Verpacken von Resource Handles in `std::unique_ptr`-Objekten <a name="link4"></a>

Standardmäßig arbeiten Smart Pointer (`std::unique_ptr`, `std::shared_ptr`) mit Zeigern,
aber man kann ihre Funktionalität auch verwenden,
um diese auf die Verwaltung von zum Beispiel Betriebssystem-Ressourcen anzuwenden.

Wir betrachten ein Beispiel zu den beiden Funktionen `fopen` und `fclose` aus der CRT.
`fopen` liefert einen Zeiger auf eine `FILE`-Struktur zurück.

Vergisst man bei einer geöffneten Datei diese zu schließen,
riskiert man möglicherweise Speicherlecks oder auch, dass die Datei gesperrt oder sogar beschädigt wird.

Im [Quellcode](UniquePtr.cpp) finden Sie ein Beispiel an Hand der Klasse `std::unique_ptr` vor,
das eine `FILE`-Struktur (genauer: einen Zeiger, der auf eine `FILE`-Struktur verweist)
durch ein `std::unique_ptr`-Objekt verwaltet.

---

## Verpacken von Win32 HANDLEs in `std::unique_ptr`-Objekten <a name="link5"></a>

Ähnliche Überlegungen, wie sie zum Verpacken von Resource Handles angestellt wurden,
kann man speziell auch für Win32 HANDLEs anstellen.

*Beispiel*:

```cpp
01: struct HANDLE_Deleter
02: {
03:     void operator() (HANDLE handle) const
04:     {
05:         if (handle != INVALID_HANDLE_VALUE) {
06:             ::CloseHandle(handle);
07:         }
08:     }
09: };
10: 
11: using HANDLE_UniquePtr = std::unique_ptr<void, HANDLE_Deleter>;
12: 
13: static HANDLE_UniquePtr make_Win32_HANDLE(HANDLE handle)
14: {
15:     if (handle == INVALID_HANDLE_VALUE || handle == nullptr) {
16:         return HANDLE_UniquePtr{ nullptr };
17:     }
18: 
19:     return HANDLE_UniquePtr{ handle };
20: }
21: 
22: void test()
23: {
24:     const auto* fileName{ L"..\\GeneralSnippets\\UniquePtr\\UniquePtr.cpp" };
25: 
26:     HANDLE  hFile = ::CreateFile (
27:         fileName,                                       // file to open
28:         GENERIC_READ,                                   // open for reading
29:         FILE_SHARE_READ,                                // share for reading
30:         NULL,                                           // default security
31:         OPEN_EXISTING,                                  // existing file only
32:         FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,   // normal file
33:         NULL
34:     );
35: 
36:     HANDLE_UniquePtr uniquePtr { make_Win32_HANDLE(hFile ) };
37: 
38:     if (! uniquePtr) {
39:         return;
40:     }
41:     else {
42: 
43:         char buffer[512] = { 0 };
44:         OVERLAPPED ol = { 0 };
45: 
46:         if (::ReadFileEx(hFile, buffer, sizeof(buffer) - 1, &ol, NULL) == 0) {
47: 
48:             std::cout << "Done." << std::endl;
49:             return;
50:         }
51:         else
52:         {
53:             std::cout << "First part of File:" << std::endl;
54:             std::cout << buffer << std::endl;
55:         }
56:     }
57: }
```

---

## Literaturhinweise <a name="link6"></a>

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
