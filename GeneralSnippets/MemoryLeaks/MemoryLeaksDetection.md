# Memory Leaks Detection

[Zurück](../../Readme.md)

---

[Quellcode / Klasse `BigData`](MoveSemantics.cpp)

---

Ein einfacher Memory Leak Detektor ist in der *C Run-time Library* (*CRT*) integriert.

Details seiner Funktionsweise sind hier beschrieben:

https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

Um ihn in einem C++-Programm zu aktivieren,
sind am Anfang der C++-Quelldatei folgende Zeilen hinzuzufügen:

```cpp
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
```

Die endgültige Aktivierung findet in der `main`-Funktion statt:

```cpp
int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // statements of cpp program 

    return 0;
}
```

Sind im Programm Memory Leaks vorhanden, werden diese - bei Ausführung des Programms mit dem Debugger - im *Output*-Fenster angezeigt.
So hinterlässt beispielsweise die Anweisung

```cpp
int* ip = new int[10];
```

ohne korrespondierende `delete`-Anweisung folgende Ausgaben im *Output*-Fenster nach der Programmausführung:

```cpp
Detected memory leaks!
Dumping objects ->
C:\Development\MemoryLeaks.cpp(22) : {151} normal block at 0x00934A10, 40 bytes long.
 Data: <                > CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD CD 
Object dump complete.
```

---

[Zurück](../../Readme.md)

---
