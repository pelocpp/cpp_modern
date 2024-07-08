# Auslassen von Kopier- oder Verschiebe-Operationen &ndash; *Copy/Move Elision*

[Zurück](../../Readme.md)

---

[Quellcode](CopyMoveElision.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Obligatorisches Auslassen von Kopier- oder Verschiebe-Operationen](#link2)
  * [Optionales Auslassen von Kopier- oder Verschiebe-Operationen](#link3)
  * [Visual C++ &ndash; Compiler Flag `/Zc:nrvo`](#link4)
  * [Literaturhinweise](#link5)

---

## Allgemeines <a name="link1"></a>

Was versteht man unter *Copy and Move Elision*?

Wenn in einer C++-Funktion das `return`-Schlüsselwort ein Objekt
eines nicht primitiven Typs als Argument besitzt
(ggf. als Resultat einer Berechnung eines Ausdrucks),
kopiert die Ausführung dieser `return`-Anweisung das Ergebnis des Ausdrucks direkt
in den Rückgabe-Slot (*Stack Frame*) der **aufrufenden** Funktion.

Auf diese Weise wird vermieden, dass noch innerhalb der Funktion eine überflüssige Kopie
des Resultatobjekts am Stack angelegt wird. Daher auch der Ausdruck &bdquo;*Elision*&rdquo; bzw. &bdquo;*Auslassen*&rdquo;:
Das Erzeugen eines &ndash; nicht zwingend notwendigen &ndash; temporären (lokalen) Objekts
wird &bdquo;*ausgelassen*&rdquo;.

Siehe dazu das Beispiel im korrespondierenden Quellcode.

---

## Obligatorisches Auslassen von Kopier- oder Verschiebe-Operationen <a name="link2"></a>

Nicht immer ist es möglich, dass ein C++&ndash;Compiler zwischen den zwei Möglichkeiten des
Erzeugens oder Nicht-Erzeugens temporärer Objekte auswählen kann.
In manchen Situationen schreibt der C++ Sprachstandard ein obligatorisches Auslassen der
an sich erwarteten Kopier- bzw. Verschiebe-Operation vor:

```cpp
return Foo{};
```

---

## Optionales Auslassen von Kopier- oder Verschiebe-Operationen <a name="link3"></a>

Wenn der zurückgegebene Wert ein *benanntes* Objekt ist,
kann der Compiler auf das Erzeugen des temporären Objekts verzichten, muss dies aber nicht:

```cpp
Foo createData() {
    Foo data{ 1 };
    return data;
}

void test {
    Foo data{ createData() };
}
```

Studieren Sie die Testausgaben dieses Beispiels an Hand des korrespondierenden Quellcodes.

---

## Visual C++ &ndash; Compiler Flag `/Zc:nrvo` <a name="link4"></a>

Mit dem Visual C++ Compiler (ab Version 17.4) kann man das *optionale* Auslassen
von Kopier-/Verschiebeoperationen explizit mit dem Flag `/Zc:nrvo` aktivieren oder
deaktivieren (`/Zc:nrvo-`):

<img src="CopyMoveElision.png" width="600">

*Abbildung* 1: Compiler Flag `/Zc:nrvo`.

Es ist nicht möglich, das *obligatorische* Entfernen von Kopier-/Verschiebeoperationen zu deaktivieren.


Mit Hilfe dieses Compiler Flags können Sie das Beispielprogramm von oben auf folgende zwei Arten
ausführen:

```
c'tor (int) [1]
d'tor [1]
```

oder 

```
c'tor (int) [1]
copy-c'tor !!!!!!!!!!! [1]
d'tor [1]
d'tor [1]
```

---

## Literaturhinweise <a name="link5"></a>

Die Informationen zu diesem Thema stammen zum größten Teil aus dem Artikel

[Improving Copy and Move Elision](https://devblogs.microsoft.com/cppblog/improving-copy-and-move-elision/) (abgerufen am 7.7.2023).

von Bran Hagger.

---

[Zurück](../../Readme.md)

---
