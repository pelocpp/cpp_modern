# Templates und statischer Polymorphismus

[Zurück](../../Readme.md)

---

[Quellcode](TemplateStaticPolymorphism.cpp)

---

Man kann - speziell für Programmiersprachen, die Polymorphismus unterstützen - zwei Varianten des Polymorphismus
unterscheinden:

  * statischer Polymorphismus
  * dynamischer Polymorphismus

Prinzipiell bedeutet der klassische (dynamische) Polymorphismus, dass die Auswahl des Aufrufs einer Methode bzw. Funktion
in Abhängigkeit des tatsächlich zur Laufzeit vorliegenden Objekts erfolgt.

Sind Schablonen (Templates) im Spiel, kann diese Festlegung statisch (also zur Übersetzungszeit) erfolgen.

Eine Gegenüberstellung der beiden Varianten findet im vorliegenden Code-Snippet statt.

Gegenüberstellung "Statischer vs. dynamischer Polymorphismus in C++":

  * Vorteile dynamischer Polymorphismus in C++:

    Unterstützung heterogener Datenstrukturen, etwa einer Liste graphischer Objekte.

    Die Schnittstelle ist durch eine Basisklasse fest definiert.

  * Vorteile statischer Polymorphismus in C++:

    Erhöhte Typsicherheit.

    Die fehlende Beschränkung auf eine Basisklasse erweitert den potentiellen Anwendungsbereich.

---

[Zurück](../../Readme.md)

---

