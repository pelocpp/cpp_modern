# Smart Pointer Klassen

[Zurück](../../Readme.md)

---

## Inhalt

  * [Allgemeines](#link1)
  * [Ein alternativer Ansatz](#link2)
  * [Klasse `std::unique_ptr` &ndash; Exklusiver Besitz](#link3)
  * [Klasse `std::shared_ptr` &ndash; Geteilter Besitz](#link4)
  * [Klasse `std::weak_ptr` &ndash; Beobachter ohne Besitz / Temporärer Besitz](#link5)
  * [Weitere Details](#link6)

---

## Allgemeines <a name="link1"></a>

Smart Pointer in C++ verwalten den Lebenszyklus von Objekten auf dem Heap automatisch und verhindern Memory Leaks.

Das Problem mit dem elementaren `new`-Operator ist, dass der Aufruf des dazugehörigen `delete`-Operators fehlen kann.
Der so reservierte Speicherbereich kann auf diese Weise nie mehr anderweitig vergeben werden.

## Ein alternativer Ansatz <a name="link2"></a>

Folgende Überlegungen haben zu einem alternativen Ansatz geführt:

  * C++ ist eine objekt-orientierte Programmiersprache.
  * Folglich gibt es Klassen und Objekte.
  * Klassen/Objekte besitzen Konstruktoren und Destruktoren.
  * Wann wird speziell ein Konstruktor aufgerufen: Am Ende des Scopes des dazugehörigen Objekts.
  * Damit kann man sagen: Der Aufruf eines Konstruktor ist deterministisch &ndash; im Gegensatz zum Aufruf des `delete`-Operators, der explizit vom Anwender abzusetzen ist.
  * Idee: Man platziere / verstecke den durch `new` erhaltenen Zeiger in einer Hüllenklasse / einem Hüllenobjekt (*Wrapper*-Objekt):
    * Konstruktor des Hüllenobjekts: Bekommt auf irgendeine Weise den Zeiger übergeben.
    * Destruktor des Hüllenobjekts: Aufruf von `delete`.

Diese Idee wurde in folgenden SmartPointer-Klassen umgesetzt, die unterschiedliche Strategien in der Verwaltung des
nativen Zeigers verfolgen:

  * Klasse `std::unique_ptr`
  * Klasse `std::shared_ptr`
  * Klasse `std::weak_ptr`

## Klasse `std::unique_ptr` &ndash; Exklusiver Besitz <a name="link3"></a>

Überblick über die Haupteigenschaften:

  * Konzept: Ein Objekt hat einen *einzigen* Besitzer.
  * Kopieren: Geht nicht (kein Kopierkonstruktor).
  * Wertzuweisung: Geht nicht (kein Zuweisungsoperator `operator=`).
  * Verschieben: Geht via `std::move()` &ndash; Besitzübergabe.
  * Performance: Schnell, kein Overhead gegenüber rohen Pointern.
  * Lebensdauer: Das Objekt wird gelöscht, wenn das aktuell besitzende `std::unique_ptr`-Objekt zerstört wird.
  * Erzeugung: Bevorzugt mit `std::make_unique<T>()`.


## Klasse `std::shared_ptr` &ndash; Geteilter Besitz <a name="link4"></a>

  * Konzept: Ein Objekt hat mehrere *einzigen* Besitzer.
  * Kopieren: Geht (Kopierkonstruktor).
  * Wertzuweisung: Geht (Zuweisungsoperator `operator=`).
  * Mechanismus: Nutzt intern einen Referenzzähler (*Reference Counting*). Gewisse Ähnlichkeiten zu einem *Garbage Collector* vorhanden.
  * Lebensdauer: Das Objekt wird gelöscht, wenn das letzte besitzende `std::shared_ptr`-Objekte zerstört wird.
  * Performance: Etwas Overhead durch die Verwaltung des Referenzzählers (Threadsicher).

## Klasse `std::weak_ptr` &ndash; Temporärer Besitz <a name="link5"></a>

  * Konzept: Verweist auf ein Objekt, das von einem `std::shared_ptr`-Objekt verwaltet wird, ohne den Referenzzähler zu erhöhen.
  * Hauptzweck: Ermöglicht Zugriff auf den von einem `std::shared_ptr`-Objekt verwalteten Speicherbereich, ohne einen Besitzanspruch zu verlangen. Es ist möglich, dass dieser Speicherbereich nicht mehr existiert.
  * Weiter Zweck: Verhindert zyklische Referenzen (Memory Leaks, bei denen sich zwei Objekte gegenseitig halten).
  * Zugriff: Kann nicht direkt auf Daten zugreifen. Mit einem Aufruf von `lock()` wird temporär `std::shared_ptr` zur Verfügung gestellt.
  * Prüfung: Eine Methode `expired()` prüft, ob das Objekt bereits gelöscht wurde.

---

## Weitere Details <a name="link6"></a>

Hier geht es zur vertiefenden Betrachtung der drei Hauptklassen:

[Klasse `std::unique_ptr`](UniquePtr.md)
[Klasse `std::shared_ptr`](SharedPtr.md)
[Klasse `std::weak_ptr`](WeakPtr.md)

---

[Zurück](../../Readme.md)

---
