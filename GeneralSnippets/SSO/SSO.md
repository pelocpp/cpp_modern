# Small String Optimization (SSO)

[Zurück](../../Readme.md)

---

[Quellcode](SSO.cpp)

---

In vielen C++ -Implementierungen werden Objekte der STL-Klasse `std::string`
durch eine interessante Optimierung unterstützt: Die *Small String Optimization* (*SSO*).
Dies bedeutet, dass kurze Zeichenketten eine besondere Behandlung erfahren:
Es gibt einen Unterschied, wie Zeichenketten wie `"ABC"`, `"Jack"` oder eben `"Modern C++ has a lot of some awesome features that every developer should know"`
in einem `std::string-Objekt` gespeichert werden.

Im Allgemeinen weist eine typische String-Klasse den Speicherplatz für den Text des Strings dynamisch aus dem Heap zu,
indem der `new`-Operator verwendet wird.
Die Quintessenz ist, dass die dynamische Speicherzuweisung mit `new` immer einen gewissen Overhead mit sich bringt,
der gerade bei sehr kurzen Zeichenketten nicht unbedingt sein muss.

In vielen C++Implementierungen reserviert eine Anforderung für sehr kurze Zeichenketten einen kleinen Pufferbereich,
der im `std::string`-Objekt eingebettet ist.
Ist eine Zeichenkette kurz genug, kommt es zur *Small String Optimization* (SSO):
Die Zeichenkette wird in diesem Puffer aufbewahrt,
ohne eine dynamische Speicheranforderung auszulösen. 

Damit stehen wir vor der Frage, wie &ldquo;kurz&rdquo; müssen Zeichenketten sein, um die SSO auszulösen?
Betrachten Sie dazu das folgende Code-Fragment: Die Methode `capacity` eines leeren `std::string`-Objekts gibt an,
wie groß der in einem `std::string`-Objekt vorhandene, interne Datenbereich ist,
um die Zeichenkette aufzunehmen und damit die Heap-Anforderung zu umgehen:

```cpp
auto size = sizeof(std::string);
auto capacity = std::string{}.capacity();
auto small = std::string(capacity, '*');
auto big = std::string(capacity + 1, '#');

std::cout << "sizeof  : " << size << std::endl;
std::cout << "Capacity: " << capacity << std::endl;
std::cout << "Small   : " << small.capacity() << ": " << small << std::endl;
std::cout << "Big     : " << big.capacity() << ": " << big << std::endl;
```

Die Ausgabe auf meinem Rechner lautet:

```
sizeof  : 40
Capacity: 15
Small   : 15: ***************
Big     : 31: ################
```

---

[Zurück](../../Readme.md)

---

