# Das *Copy-and-Swap* Idiom

[Zurück](../../Readme.md)

---

[Quellcode](CopySwapIdiom.cpp)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Eine &bdquo;nicht optimale&rdquo; Realisierung](#link2)
  * [Eine verbesserte Realisierung: Das *Copy-and-Swap* Idiom](#link3)

---

## Allgemeines <a name="link1"></a>

Das *Copy-and-Swap*-Idiom wurde eingeführt, um zwei Ziele zu erreichen:
  * Realisierung der Kopier-Konstruktoren und Zuweisungsoperatoren (sowohl &bdquo;kopierende&rdquo; als auch &bdquo;verschiebende&rdquo; Semantik)
  auf eine einfache Weise (Vermeidung von Code-Duplikationen).
  * Bereitstellung der so genannten *Strong Exception Guarantee*.


---

## Eine &bdquo;nicht optimale&rdquo; Realisierung <a name="link2"></a>

Naive Realisierungen, wie man sie in vielen Büchern vorfindet,
würden einen Wertzuweisungs-Operator mehr oder weniger so implementieren:


```cpp
01: BigData& BigData::operator= (const BigData& other) {
02: 
03:     // prevent self-assignment
04:     if (this == &other) {
05:         return *this;
06:     }
07: 
08:     // delete old buffer
09:     delete[] m_data;
10: 
11:     // allocate a new buffer
12:     m_size = other.m_size;
13:     m_data = new int[m_size];
14: 
15:     // copy buffer
16:     for (int i = 0; i != m_size; ++i) {
17:         m_data[i] = other.m_data[i];
18:     }
19: 
20:     return *this;
21: }
```

Folgende Nachteile sind in dieser Realisierung vorhanden:

  * Verhinderung einer Selbstzuweisung (Zeile 4):<br />
Eine Selbstzuweisung bei Objekten mit Instanzdaten führt in Zeile 9
dazu, dass die Daten des aktuellen Objekts &ndash; und damit eben auch
die Daten des Objekte `other` auf der rechten Seite &ndash; der Wertzuweisung gelöscht würden,
bevor sie kopiert werden.
Natürlich ist dies ein Anwendungsfehler des Benutzers der Klasse,
aber in allen Fällen, in denen das Programm korrekt ist,
führt diese Prüfung dazu, den Ablauf des Programms zu verlangsamen.
Eine Selbstzuweisung kommt prinzipiell selten vor, daher wäre eine Realisierung wünschenswert,
die ohne eine derartige Prüfung auskommt.

  * *Basic Exception Guarantee*:<br />
Die vorliegende Realisierung bietet nur eine *Basic Exception Guarantee*.
Wenn ein Aufruf vom `new int[m_size]` fehlschlägt, liegt das Objekt `*this`
bereits in einem geänderten Zustand vor: Die Größenangabe `m_size` ist falsch
und die Daten sind verloren gegangen. Mit einer alternativen Realisierung
könnte man diese Probleme beheben:

```cpp
01: BigData& BigData::operator= (const BigData& other) {
02: 
03:     // prevent self-assignment
04:     if (this == &other) {
05:         return *this;
06:     }
07: 
08:     // get the new data ready before we replace the old
09:     size_t tmpNewSize = other.m_size;
10:     int* tmpNewData = nullptr;
11: 
12:     if (tmpNewSize > 0) {
13:         tmpNewData = new int[tmpNewSize];
14:     }
15: 
16:     // copy buffer
17:     for (int i = 0; i != tmpNewSize; ++i) {
18:         tmpNewData[i] = other.m_data[i];
19:     }
20: 
21:     // replace old data with new data - all are non-throwing operations
22:     delete[] m_data;
23:     m_size = tmpNewSize;
24:     m_data = tmpNewData;
25: 
26:     return *this;
27: }
```

  * Code-Duplizierung:<br />
Der Zuweisungsoperator `operator=` dupliziert effektiv Quellcode,
den wir bereits anderswo geschrieben haben: Das sollte man in jedem Fall vermeiden!
Man könnte argumentieren, dass der Kern des Zuweisungsoperators
nur aus zwei Anweisungen besteht (Wertzuweisung der Längenangabe, Erstellen einer Kopie),
aber bei komplexeren Objekten kann die Realisierung doch aufwändiger werden!


---

## Eine verbesserte Realisierung: Das *Copy-and-Swap* Idiom <a name="link3"></a>

Mit Hilfe einer `swap`-Funktion kann der Zuweisungs-Operator nun auf folgende, 
sehr einfache Weise realisiert werden:

```cpp
01: BigData& BigData::operator= (BigData other) {
02: 
03:     swap(*this, other);
04: 
05:     return *this;
06: }
```

Die `swap`-Funktion sieht dabei so aus:

```cpp
01: void BigData::swap(BigData& data1, BigData& data2) noexcept {
02:     std::swap(data1.m_data, data2.m_data);
03:     std::swap(data1.m_size, data2.m_size);
04: }
```

Beachte folgende wichtige Eigenschaft in der Realisierung des Zuweisungs-Operators:


> Geänderte Signatur des Operators `operator=`<br />

Das Parameterargument `other` wird als Wert übernommen:

`BigData& BigData::operator= (BigData other)`;

Auf diese Weise sind beim Aufrufen der Funktion alle neuen Daten bereits zugewiesen,
kopiert und stehen so zur Verwendung bereit.

Dadurch erhalten wir die *Strong Exception Guarantee* kostenlos! 
Die Funktion wird nicht aufgerufen, wenn die Erstellung der Kopie fehlschlägt,
und es ist daher nicht möglich, den Status von `*this` zu ändern. 

---

[Zurück](../../Readme.md)

---
