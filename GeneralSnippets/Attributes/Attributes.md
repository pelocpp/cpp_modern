# C++ Standard Attribute

[Zurück](../../Readme.md)

---

[Quellcode](Attributes.cpp)

---

## Überblick

Im C++ Standard können Attribute in doppelten eckigen Klammern eingesetzt werden.
Die bekanntesten Attribute sind in der folgenden Tabelle aufgeführt:

| Name | Beschreibung |
|:-|:-|
| `[[noreturn]]` | Zeigt an, dass die Funktion nicht zurückkehrt. |
| `[[deprecated]]` | Zeigt an, dass die Verwendung des mit diesem Attribut deklarierten Namens zulässig ist, aber aus irgendeinem Grund davon abgeraten wird, dieses Sprachfeature einzusetzen. |
| `[[fallthrough]]` | Weist darauf hin, dass das Durchfallen des vorherigen `case`-Labels beabsichtigt ist und nicht von einem Compiler diagnostiziert werden sollte (so genanntes &bdquo;*fall-through*&rdquo;). |
| `[[nodiscard]]` | Der Compiler gibt eine Warnung aus, wenn der Rückgabewert ignoriert wird. |
| `[[maybe_unused]]` | Unterdrückt eine Compiler-Warnung, wenn eine Variable/Objekt nicht verwendet wird. |

*Tabelle* 1: Einige C++ Standard Attribute.

Daneben gibt es noch weitere, recht spezielle Attribute, wie zum Beispiel `carries_dependency`,
`likely`, `unlikely` oder `no_unique_address`.


*Hinweis*: Das Attribut `deprecated` erzeugt mit dem *Visual C++*&ndash;Compiler einen Fehler
an Stelle einer Warnung. Dies kann man abstellen, eine Beschreibung der *Visual C++*&ndash;Compilereinstellungen
diesbezüglich findet man hier:

[`deprecated` results in error instead of warning in Visual Studio](https://stackoverflow.com/questions/58228990/deprecated-results-in-error-instead-of-warning-in-visual-studio).<br>(abgerufen am 06.12.2022).

---

[Zurück](../../Readme.md)

---
