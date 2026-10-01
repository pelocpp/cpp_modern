# Verwendung von `is_transparent`

[Zurück](../../Readme.md)

---

[Quellcode](Tuple.cpp)

---

## Allgemeines

is_transparent ist ein Marker-Typ im Vergleichsobjekt, der dem Container signalisiert, dass er find, lower_bound & Co. auch mit Argumenten anderer Typen als dem Schlüsseltyp aufrufen darf, ohne vorher ein temporäres Schlüsselobjekt zu erzeugen.



---

Eine Beispiel-Implementierung für die Klasse `std::tuple`
findet sich unter <https://eli.thegreenplace.net/2014/variadic-templates-in-c/>.

---

[Zurück](../../Readme.md)

---



// https://johnfarrier.com/transparent-comparators-in-c23/

// https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/

// https://medium.com/factset/modern-c-in-depth-transparent-comparisons-afef5900535b

