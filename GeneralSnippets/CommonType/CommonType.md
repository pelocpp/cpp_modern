# Klasse `std::common_type`

[Zurück](../../Readme.md)

---

[Quellcode](CommonType.cpp)

---

## Allgemeines


`std::common_type` wurde historisch gesehen für die Verwendung von
`std::duration` eingeführt. Wenn man zu einem `std::duration<int>`-Objekt
ein `std::duration<short>`-Objekt hinzufügen möchte,
sollte das Ergebnis ein `std::duration<int>`-Objekt sein.
Anstatt eine endlose Liste zulässiger Paarungen festzulegen, wurde die Entscheidung getroffen,
die Paarung an eine separate Schablone zu delegieren, die das Ergebnis unter Verwendung
der für den ternären Operator `?:` geltenden Kernsprachregeln festlegt.

Siehe das Beispiel im korrespondierenden Quellcode.

---

[Zurück](../../Readme.md)

---
