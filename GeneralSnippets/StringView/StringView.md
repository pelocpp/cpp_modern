# Klasse `std::string_view`

[Zurück](../../Readme.md)

---

[Quellcode](StringView.cpp)

---

*Allgemeines*:

Eine Instanz von `std::string_view` ist eine *Sicht* auf eine Zeichenkette,
die nicht verändert werden kann.
Man kann die Klasse `std::string_view` als eine Schnittstelle für die Kasse `std::string` ansehen,
die nur alle lesenden Methoden enthält.
Als Parameter verhält sich damit der `std::string_view`-Datentyp weitestgehend
wie eine konstante String-Referenz (`const std::string&`).

Der Zweck der beiden Alternativen (`std::string_view` versus `const std::string&`) besteht
darin, in einer Methode auf eine Zeichenkette lesend zuzugreifen,
ohne diese zu kopieren. Es geht also um das Optimieren von Speicherplatz und Rechenleistung.
Und darin ist `std::string_view` noch besser als `const std::string&`.
 
Zum Beispiel, weil eine `std::string_view`-Instanz auch ohne Overhead aus einem
klassischen C-String (`const char*`) konstruiert werden kann.
Das geht mit `const std::string&` nicht.
Zum anderen ist es auch möglich, einen Teilstring *ohne zusätzliche Speicherplatzanforderung*
als `std::string_view` an eine Funktion zu übergeben.

Wir betrachten dazu einige Code-Snippets:

*Beispiel*:

```cpp
void test_01()
{
    std::string s = "12345";
    std::cout << s << std::endl;

    s[2] = '!';
    std::cout << s << std::endl;

    std::string_view sv(s);
    std::cout << sv << std::endl;
    // sv[2] = '?';  // 'sv': you cannot assign to a variable that is const
}

uint32_t countUpperCaseChars(std::string_view sv ) {
    uint32_t result{};
    for (char c : sv) {
        if (std::isupper(c)) {
            ++result;
        }
    }
    return result;
}

void test_02()
{
    std::string_view sv("DiesIstEinLangerSatz");
    uint32_t count = countUpperCaseChars(sv);
    std::cout << "countUpperCaseChars: " << count << std::endl;

    std::string s = "AuchDasWiederIstEinLangerSatz";
    count = countUpperCaseChars(s);
    std::cout << "countUpperCaseChars: " << count << std::endl;

    count = countUpperCaseChars("NurKurzJetzt");
    std::cout << "countUpperCaseChars: " << count << std::endl;

    // works too 
    count = countUpperCaseChars({&s[25]}); // "Satz"
    std::cout << "countUpperCaseChars: " << count << std::endl;

    // works too
    count = countUpperCaseChars({ &s[26], 2 }); // "at"
    std::cout << "countUpperCaseChars: " << count << std::endl;
}
```

*Ausgabe* von `test_01`:

```cpp
12345
12!45
12!45
```

*Ausgabe* von `test_02`:

```cpp
countUpperCaseChars: 5
countUpperCaseChars: 7
countUpperCaseChars: 3
countUpperCaseChars: 1
countUpperCaseChars: 0
```

*Hinweis*:
Wenn Sie von nun an eine Funktion schreiben, die eine Zeichenfolge benötigt,
denken Sie an `std::string_view` als Parametertyp.
Es ist nicht erforderlich, eine `std::string_view`-Referenz zu verwenden!
Ein `std::string_view`-Objekt ist sehr "billig" zu kopieren,
daher ist es vollkommen in Ordnung, es als Wert zu übergeben.
Grundsätzlich enthält eine `std::string_view`-Instanz nur einen Zeiger auf eine Zeichenfolge
und deren Länge.

```cpp
template <class _Elem, class _Traits>
class basic_string_view { // wrapper for any kind of contiguous character buffer
public:
    constexpr basic_string_view() noexcept : _Mydata(), _Mysize(0) {}
    ...

    const_pointer _Mydata;
    size_type _Mysize;
};
```

Ein `std::string_view`-Parameter akzeptiert jede Art von Zeichenfolge,
z.B. ein klassisches C++-`std::string`-Objekt, eine `const char*` Zeichenfolge im C-Stil
oder ein Zeichenkettenliteral, alles ohne Kopieren!

---

[Zurück](../../Readme.md)

---

