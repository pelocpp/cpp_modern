# Auslassen von Kopier- oder Verschiebe-Operationen &ndash; *Copy/Move Elision*

[Zur�ck](../../Readme.md)

---

[Quellcode](CopyMoveElision.cpp)

---

## Allgemeines:

Was versteht man unter *Copy and Move Elision*?

Wenn in einer C++-Funktion das `return`-Schl�sselwort ein Objekt
eines nicht primitiven Typs als Argument besitzt
(ggf. als Resultat einer Berechnung eines Ausdrucks),
kopiert die Ausf�hrung dieser `return`-Anweisung das Ergebnis des Ausdrucks direkt
in den R�ckgabe-Slot (*Stack Frame*) der **aufrufenden** Funktion.

Auf diese Weise wird vermieden, dass noch innerhalb der Funktion eine �berfl�ssige Kopie
des Resultatobjekts am Stack angelegt wird. Daher auch der Ausdruck &bdquo;*Elision*&rdquo; bzw. &bdquo;*Auslassen*&rdquo;:
Das Erzeugen eines &ndash; nicht zwingend notwendigen &ndash; tempor�ren (lokalen) Objekts
wird &bdquo;*ausgelassen*&rdquo;.

Siehe dazu das Beispiel im korrespondierenden Quellcode.

---

## Obligatorisches Auslassen von Kopier- oder Verschiebe-Operationen

Nicht immer ist es m�glich, dass ein C++&ndash;Compiler zwischen den zwei M�glichkeiten des
Erzeugens oder Nicht-Erzeugens tempor�rer Objekte ausw�hlen kann.
In manchen Situationen schreibt der C++ Sprachstandard ein obligatorisches Auslassen der
an sich erwarteten Kopier- bzw. Verschiebe-Operation vor:

```cpp
return Foo{};
```

---

## Optionales Auslassen von Kopier- oder Verschiebe-Operationen

Wenn der zur�ckgegebene Wert ein *benanntes* Objekt ist,
kann der Compiler auf das Erzeugen des tempor�ren Objekts verzichten, muss dies aber nicht:

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

## Visual C++ &ndash; Compiler Flag `/Zc:nrvo` 

Mit dem Visual C++ Compiler (ab Version 17.4) kann man das *optionale* Auslassen
von Kopier-/Verschiebeoperationen explizit mit dem Flag `/Zc:nrvo` aktivieren oder
deaktivieren (`/Zc:nrvo-`):

<img src="CopyMoveElision.png" width="600">

*Abbildung* 1: Compiler Flag `/Zc:nrvo`.

Es ist nicht m�glich, das *obligatorische* Entfernen von Kopier-/Verschiebeoperationen zu deaktivieren.


Mit Hilfe dieses Compiler Flags k�nnen Sie das Beispielprogramm von oben auf folgende zwei Arten
ausf�hren:

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

## Literaturhinweise:

Die Informationen zu diesem Thema stammen zum gr��ten Teil aus dem Artikel

[Improving Copy and Move Elision](https://devblogs.microsoft.com/cppblog/improving-copy-and-move-elision/) (abgerufen am 7.7.2023).

von Bran Hagger.

---

[Zur�ck](../../Readme.md)

---
