# Wertsemantik versus Referenzsemantik

[Zurück](Architecture.md)

---

## Allgemeines

In einer Programmiersprache beschreiben die Begriff *Wertsemantik* und *Referenzsemantik*
(im engl. *Value-based*- und *Reference-based Semantics*) Vorgehensweisen,
wie Objekte gespeichert, kopiert und an Funktionen übergeben werden.

## Überblick

C++ unterstützt beide Arten dieser Semantiken,
standardmäßig wird die *Value-based Semantics* (Wertsemantik) eingesetzt.
Einer der vielen Gründe, warum C++ eine so vergleichsweise komplexe und deshalb schwer zu erlernende Programmiersprache ist,
hat eben damit zu tun, dass beide Arten dieser Semantiken vorhanden sind (siehe dazu auch *Tabelle* 1). 


| Programmiersprache | Wertsemantik | Referenzsemantik |
|:-|:-|:-|
| C++  | &#9989; | &#9989; |
| C#  | &#10060; (ausgenommen `struct`) | &#9989; |
| Java  | &#10060; | &#9989; |
| Python | &#10060; | &#9989; |

*Tabelle* 1: Wert- und Referenzsemantik von unterschiedlichen Programmiersprachen im Vergleich.

Viele andere Sprachen (wie C#, Java oder Python) unterstützen für Objekte nur die Referenzsemantik.

Da diese Sprachen zeitlich betrachtet nach C++ erfunden/konzipiert wurden, hat man versucht, einige der Erfahrungen
aus dem Sprachentwurf von C++ mit einzubringen. Eine dieses Konsequenzen dürfte sicherlich gewesen sein,
auf die Wertsemantik in C#/Java etc. zu verzichten, um die Komplexität der neu entwickelten Sprachen einfacher zu halten.

Von dieser strengen Regel gibt es Ausnahmen: Elementare Datentypen (`int`, `double`) liegen immer als Wert vor (auf dem Stack).
Ferner kann man in C# von der standardmäßig vorhandenen Referenzsemantik abweichen, wenn man Objekte mit dem Schlüsselwort `struct` definiert.
Auf diese Weise kommen sie auf dem Stack zu liegen.
Diese Vorgehensweise stellt im Großen und Ganzen aber eher eine Ausnahme in C#&ndash;Programmen dar.


### Wertsemantik (*Value-based Semantics*)

Hier steht der Inhalt (Wert) eines Objekts im Vordergrund, nicht seine Identität.

  * Kopierverhalten:<br />Bei einer Zuweisung (`a = b;`) wird eine unabhängige Kopie des Objekts erstellt.
    Änderungen an `a` beeinflussen `b` nicht.
  * Speicherung:<br />Objekte werden direkt (z. B. auf dem Stack oder im globalen Datensegment) gespeichert,
    was oft schnelleren Zugriff ermöglicht, da keine zusätzliche Indirektion über Pointer nötig ist.
    Der Inhalt (Wert) eines Objekts befindet sich bei Wertsemantik nicht auf dem Heap.
  * Standard in C++:<br />Alle eingebauten Typen (`int`, `double`) und benutzerdefinierten Klassen (`struct`, `class`) folgen standardmäßig diesem Prinzip.
  * Vorteile:<br />Höhere Sicherheit (direkter Zugriff über eine vorhandene Adresse/statisches Binden,
    keine Probleme mit ungültigen Adressen), bessere Performance durch Cache-Lokalität.


### Referenzsemantik (*Reference-based Semantics*)

Hier steht die Identität eines Objekts im Vordergrund. Variablen sind lediglich &bdquo;Labels&rdquo; oder &bdquo;Aliase&rdquo; für ein existierendes Objekt.

  * Kopierverhalten:<br />Bei einer Zuweisung (`a = b;`) wird lediglich die Adresse (Pointer/Referenz) kopiert.
    Mehrere Zeiger-/Referenzvariablen zeigen auf dasselbe physische Objekt im Speicher.
    Das Objekt selbst kann auf dem Heap, dem Stack oder im globalen Datensegment liegen.
    Objekte, die auf dem Heap liegen, sind ausschließlich über Zeiger (Pointer) erreichbar.
    Objekte, die auf dem Stack oder im globalen Datensegment liegen, können über Referenzen (Alias) und über Zeiger (Pointer) angesprochen werden.
    Die Schreibweise mit Referenzen führt zu leichter lesbarem Quellcode.
    Änderungen über eine Referenz oder einen Pointer sind für alle sichtbar.
  * Explizite Nutzung:<br />In C++ muss Referenzsemantik explizit durch die Verwendung von Pointern/Zeigern (`*`) oder durch Referenzen (`&`) erzwungen werden.
    Soll das Objekt auf dem Heap liegen, muss der entsprechende Speicher mit dem `new`-Operator reserviert und mit dem `delete`-Operator wieder freigegeben werden.
    Objekte auf dem Heap sind nur über Zeiger/Pointer erreichbar.
  * Vorteile:<br />Vermeidung teurer Kopien bei großen Objekten, Ermöglichung von Polymorphismus (dynamisches Binden). 


### Ein Vergleich auf einen Blick

Wertsemantik und Referenzsemantik im Vergleich:

| Merkmal | Wertsemantik | Referenzsemantik |
|:-|:-|:-|
| Zuweisung  | Erstellt eine neue, unabhängige Kopie. | Kopiert nur den Verweis auf das Original. Möchte man das Original kopieren, muss dies explizit veranlasst werden. |
| Identität  | Unwichtig: nur der Wert zählt.         | Zentral: Alias für dasselbe Objekt. |
| Effizienz  | Potenziell teurer durch Kopieraufwand. | Effizienter für große Datenmengen, da keine Kopien entstehen. |
| Sicherheit | Sicherer (kein unerwartetes Aliasing). | Risiko von ungültigen Zeigern/Adressen/Referenzen. |

*Tabelle* 2: Wert- und Referenzsemantik im Vergleich.

---

[Zurück](Architecture.md)

---
