# Streams manipulieren und formatieren

[Zurück](../../Readme.md)

---

[Quellcode](InputOutputStreams.cpp)

---

Folgende Aspekte zur Ein- und Ausgabe mit C++-Streams werden an Beispielen aufgezeigt:

  * Unformatierte Ausgabe mit `put` und `write`
  * Methoden für die Behandlung von Fehlern bei Streams (`good`, `bad` und `fail`)
  * Formatierung der Ausgabe mit Manipulatoren
  * Die `boolalpha` und `noboolalpha` Manipulatoren zur Steuerung der Ausgabe von `bool`-Werten
  * Die `showbase`, `dec`, `hex` und `oct` Manipulatoren zur Steuerung der Ausgabe von ganzzahligen Werten
  * Die Manipulatoren `internal`, `left` und `right` zur Ausrichtung der Ausgabe
  * Die Bedeutung des `setw`-Manipulators bei der Ausgabe
  * Der `setfill`-Manipulator
  * Manipulatoren ohne Parameter selbst schreiben
  * Manipulatoren mit Parametern selbst schreiben


Ausgabe des Code-Snippets zur Steuerung der Ausgabe von `bool`-Werten:

```cpp
true
false
true
0
1
```

Ausgabe des Code-Snippets zur Steuerung der Ausgabe von ganzzahligen Werten:

```cpp
255
0xff
0x64
0377
0377
255
```

Ausgabe des Code-Snippets zur Ausrichtung der Ausgabe:

```cpp
-      123
-123
      -123
       987
987
       987
```


Ausgabe des Code-Snippets zur Erläuterung des `setfill`-Manipulators:

```cpp
.....12345
12345
...............12345
12345
     12345
```


Ausgabe des Code-Snippets zu "*Manipulatoren ohne Parameter selbst schreiben*":

```cpp
Some Text # Some Text
some text # some text
```


Ausgabe des Code-Snippets zu "*Manipulatoren mit Parametern selbst schreiben*":

```cpp
AAA!AAA
AAA!AAA
AAA!!AAA
AAA!!!AAA
AAA!!!!AAA
```

---

[Zurück](../../Readme.md)

---
