# Regular Expressions

[Zurück](../../Readme.md)

---

[Quellcode](RegExpr.cpp)

---

## Klasse `std::regex`

Um einen regulären Ausdruck verwenden zu können, benötigt man ein Objekt der Klasse `std::basic_regex`.
Dazu gibt es wiederum die Klasse `std::regex`,
wenn die zu untersuchende Zeichenkette vom Typ eines C-Arrays oder ein `std::string`-Objekt ist.

Der reguläre Ausdruck selbst ist als Zeichenkette als erster Parameter an den Konstruktor der `std::regex`-Klasse zu übergeben.

## Syntax regulärer Ausdrücke

In der folgenden Tabelle finden Sie &ndash; in einem gekürzten Umfang &ndash; die Syntax regulärer Ausdrücke vor:

###### {#tabelle_1_regexp_syntax}

| Ausdruck | Bedeutung |
| :---- | :---- | 
| `ab` | `a` gefolgt von `b` |
| <code>a&#124;b</code> | Alternative: `a` oder `b` |
| . | beliebiges Zeichen |
| `a?` | 0 oder 1 mal `a` |
| `a*` | 0 oder mehr mal `a` |
| `a+` | 1 oder mehr mal `a` |
| `a{n,m}` | `n` bis `m` mal `a` |
| `()` | Gruppierung |
| `^` oder `$` | am Anfang oder Ende der Zeichenkette |
| `[`*klasse*`]` | Zeichen aus einer Klasse |
| `\d` `\w` `\s` | Klassenkürzel |

*Tabelle* 1: Überblick über die Syntax regulärer Ausdrücke.

Beispiele für Zeichen aus einer Klasse sind `[[digit]]`, `[[alpha]]`, `[[alnum]]`, `[[space]]` usw.
Die Klassenkürzel `\d` `\w` `\s` sind gleichbedeutend mit  `[[digit]]`, `[[alnum]]` und `[[space]]`.

## Algorithmen und Iteratoren

Es gibt drei Funktionen, um den in einem `std::regex`-Objekt gekapselten regulären Ausdruck
auf eine Zeichenfolge anzuwenden:

> `std::regex_match` &ndash;
  Wendet den regulären Ausdruck auf eine ganze Zeichenfolge an.

> `std::regex_search` &ndash;
Wendet den regulären Ausdruck auf einen beliebigen Teil einer Zeichenfolge an.

> `std::regex_replace` &ndash;
Ersetzt das Vorkommen eines regulären Ausdrucks durch formatierten Ersatztext.

Es gibt auch *Regex*-Iteratoren, die man verwenden kann, um die Menge aller Übereinstimmungen mit einem regulären Ausdruck zu erhalten,
wenn eine Zielzeichenkette analysiert wird:

> `std::regex_iterator` &ndash;
Durchläuft alle gefundenen *Regex*-Übereinstimmungen innerhalb einer Zeichenfolge.

## Ein erstes Beispiel: `std::regex_match`

```cpp
std::string names[] = {
    "foo.txt", 
    "bar.txt", 
    "baz.dat", 
    "anyfile" 
};

std::regex re{ "[a-z]+\\.txt" };

for (const auto& name : names) {
    bool result{ std::regex_match(name, re) };
    std::cout << std::boolalpha << name << ": " << result << std::endl;
}
```

*Ausgabe*:

```
foo.txt: true
bar.txt: true
baz.dat: false
anyfile: false
```

Man beachte die folgende Subtilität des regulären Ausdrucks:
In dem regulären Ausdruck soll ein Punkt '.' enthalten sein.
Also kein Punkt im Sinne der Syntax regulärer Ausdrücke als Stellvertreter für ein beliebiges Zeichen,
sondern ein '.' als Trennzeichen zwischen dem vorderen und hinteren Teil eines Dateinamens.
Damit kommt "." nicht in Betracht. "\\." wiederum wäre richtig, da aber das Backslash-Zeichen
eine Escape-Sequenz einleitet, muss es richtig "\\\\." heißen!

## *Erfassungsgruppen* versus *Nichterfassungsgruppen* (*Capturing Groups* versus *Non-Capturing Groups*)

Wird eine Zeichenkette gegen einen regulären Ausdruck überprüft,
lassen sich einzelne Bestandteile der Zeichenkette &ndash; so genannte Gruppen &ndash; erkennen und damit auch extrahieren.
Dazu müssen im regulären Ausdruck die Gruppen mit `(` und `)` als solche markiert werden.
Das Erfassen dieser Gruppen, im Englischen auch als *Capturing Group* bezeichnet, lässt sich nun mit `?:` steuern:
Ohne Verwendung von `?:` wird ein bestimmter Bestandteil einer Zeichenkette erfasst,
mit Verwendung von `?:` wird er nicht in das Resultat übernommen. Man spricht in diesem Fall 
von einer *Non-Capturing Group*.

Wir betrachten dies an einem Beispiel, um URLs mit den Bestandteilen
&bdquo;Protokoll&rdquo;, &bdquo;Domain&rdquo; und &bdquo;Pfad&rdquo; zu analysieren:

```cpp
std::regex re{ "(https?|s?ftp)://([^/\r\n]+)(/[^\r\n]*)?" };

std::string paths[] = {
    "http://stackoverflow.com/",
    "https://stackoverflow.com/questions/tagged/regex",
    "sftp://home/remote_username/filename.zip",
    "ftp://home/ftpuser/remote_test_dir",
};

for (const auto& path : paths) {
    std::smatch sm;
    bool success{ std::regex_match(path, sm, re) };
    if (success) {
        std::string protocol{ sm[1] };
        std::string domain{ sm[2] };
        std::string dir{ sm[3] };
        std::cout
            << "Valid URL: " << path << " ==> " 
            << protocol << "-" << domain << "-" << dir << std::endl;
    }
    else {
        std::cout << "Invalid URL: " << path << std::endl;
    }
}
```

*Ausgabe*:

```
Valid URL: http://stackoverflow.com/ ==> http-stackoverflow.com-/
Valid URL: https://stackoverflow.com/questions/tagged/regex ==> https-stackoverflow.com-/questions/tagged/regex
Valid URL: sftp://home/remote_username/filename.zip ==> sftp-home-/remote_username/filename.zip
Valid URL: ftp://home/ftpuser/remote_test_dir ==> ftp-home-/ftpuser/remote_test_dir
```

Interessiert man sich *nicht* für das Protokoll, dann kann man den regulären Ausdrücken 
so abwandeln:

```
(?:https?|s?ftp)://([^/\r\n]+)(/[^\r\n]*)?
```

Aus der ersten *Capturing Group* mache ich mit Hilfe von `?:` eine *Non-Capturing Group*.
Damit erhalte ich als Resultat bei der Ausführung:

```
Valid URL: http://stackoverflow.com/ ==> stackoverflow.com - /
Valid URL: https://stackoverflow.com/questions/tagged/regex ==> stackoverflow.com - /questions/tagged/regex
Valid URL: sftp://home/remote_username/filename.zip ==> home - /remote_username/filename.zip
Valid URL: ftp://home/ftpuser/remote_test_dir ==> home - /ftpuser/remote_test_dir
```

Das dazugehörige Quellcode-Fragment sieht nun so aus:

```cpp
std::regex re("(?:https?|s?ftp)://([^/\r\n]+)(/[^\r\n]*)?");

std::string paths[] = {
    "http://stackoverflow.com/",
    "https://stackoverflow.com/questions/tagged/regex",
    "sftp://home/remote_username/filename.zip",
    "ftp://home/ftpuser/remote_test_dir",
};

for (const auto& path : paths) {
    std::smatch sm;
    bool success{ std::regex_match(path, sm, re) };
    if (success) {
        std::string domain = sm[1];
        std::string dir = sm[2];
        std::cout << 
            "Valid URL: " << path << " ==> " 
            << domain << " - " << dir << std::endl;
    }
    else {
        std::cout << "Invalid URL: " << path << std::endl;
    }
}
```

## Ein zweites Beispiel: Erkennen eines Datums mit regulären Ausdrücken

Wir betrachten als zweites Beispiel die Aufforderung zur Eingabe eines Datums im Format

```
year/month/day
```

wobei `year` aus vier Ziffern, `month` eine Zahl zwischen 1 und 12, und `day` eine Zahl zwischen 1 und 31 ist.
Wir wollen nun zwei reguläre Ausdrücke betrachten, die eine entsprechende Analyse vornehmen.

*Variante* 1:

<pre>
<b>\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])</b>
</pre>

Wir geben eine kurze Beschreibung der einzelnen Bestandteile des regulären Ausdrucks:

  * <b>`\d{4}`</b><br/>
    Dieser Teil akzeptiert eine beliebige Folge von 4 Ziffern, also 1234, 2020, 0001 usw.
    Beachte die Verwendung eines Klassenkürzels `\d`.
  * <b>`(?:0?[1-9]|1[0-2])`</b><br/>
    Dieser Teil des regulären Ausdrucks ist in runden Klammern, um die Vorrangregeln richtig zu beachten.
    Auf Grund der Einleitung mit `?:` handelt es sich um eine *Non-Capturing Group*, wir sind am Ergebnis nicht interessiert.
    Der innere Teil des Ausdrucks besteht aus zwei Alternativen, getrennt durch `|`:
    - <b>`0?[1-9]`</b><br/>
      Dieser Teil akzeptiert eine beliebige Zahl von 1 bis 9, optional mit einer vorangestellten 0.
      Zum Beispiel 1, 2, 9, 03, 06 usw.
    - <b>`1[0-2]`</b><br/>
      Dieser Teil akzeptiert 10, 11 oder 12. Nichts weiter sonst!
  * <b>`(?:0?[1-9]|[1-2][0-9]|3[0-1])`</b><br/>
    Dieser Teil ist wiederum eine *Non-Capturing Group*, er besteht aus drei Unterteilen:
    - <b>`0?[1-9]`</b><br/>
      Dieser Teil akzeptiert eine beliebige Zahl von 1 bis 9, optional mit einer vorangestellten 0.
      Zum Beispiel 1, 2, 9, 03, 06 usw.
      Die Zahlen 0, 10, 11, usw. werden nicht akzeptiert.
    - <b>`[1-2][0-9]`</b><br/>
      Dieser Teil akzeptiert alle Zehlen zwischen 10 und 29, jeweils inklusive, und sonst nichts weiter.
    - <b>`3[0-1]`</b><br/>
      Dieser Teil akzeptiert 30 oder 31 und nichts weiter sonst!

Da es sich bei den Teilausdrücken stets um *Non-Capturing Groups* handelt, werden die akzeptierten Teilzeichenketten
von `std::regex_match` nicht in das Resultat-Objekt (`std::smatch`) aufgenommen.
Damit wollen wir eine zweite Variante betrachten:

*Variante* 2:

<pre>
<b>(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])</b>
</pre>

Betrachten Sie genau die Unterschiede zur ersten Variante:

  * <b>`(\d{4})`</b><br/>
    Dieser Teil analysiert eine beliebige Folge von 4 Ziffern, also 1234, 2020, 0001 usw.
    Der Teilausdruck ist eine *Capturing Group*.
  * <b>`(0?[1-9]|1[0-2])`</b><br/>
    Dieser Teil des regulären Ausdrucks ist in runden Klammern, um die Vorrangregeln richtig zu beachten.
    Der Teilausdruck ist eine *Capturing Group*.
    Der innere Teil des Ausdrucks besteht aus zwei Alternativen, getrennt durch `|`:
    - <b>`0?[1-9]`</b><br/>
      Wie oben.
    - <b>`1[0-2]`</b><br/>
      Wie oben.
  * <b>`(0?[1-9]|[1-2][0-9]|3[0-1])`</b><br/>
    Dieser Teil ist wiederum eine *Capturing Group*.
    - <b>`0?[1-9]`</b><br/>
      Wie oben.
    - <b>`[1-2][0-9]`</b><br/>
      Wie oben.
    - <b>`3[0-1]`</b><br/>
      Wie oben.

Für beide Varianten finden Sie im *Quellcode* eine Anwendung vor.
Hier das Beispiel mit der Auswertung der Zeichenkette:

*Code-Fragment*:

```cpp
std::regex re{ "(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])" };

std::string dates[] = {
    "2000/06/15",
    "200/6/15",
    "2020/0/32",
    "0001/1/1"
};

for (const auto& date : dates) {
    std::smatch sm;
    bool success{ std::regex_match(date, sm, re) };
    if (success) {
        int year{ stoi(sm[1] };
        int month{ stoi(sm[2] };
        int day{ stoi(sm[3] };
        std::cout
            << "Valid date:   " << date << " ==> " << year
            << "-" << month << "-" << day << std::endl;
    }
    else {
        std::cout << "Invalid date: " << date << std::endl;
    }
}
```

*Ausgabe*:

```
Valid date:   2000/06/15 ==> 2000-6-15
Invalid date: 200/6/15
Invalid date: 2020/0/32
Valid date:   0001/1/1 ==> 1-1-1
```

---

## Literaturhinweise

Zum Testen von regulären Ausdrücken gibt es zwei empehlenswerte Seiten:

&bdquo;[RegExr is an online tool to learn, build, & test Regular Expressions](https://regexr.com/)&rdquo;

und

&bdquo;[Free PCRE-based regular expression debugger with real time explanation, error detection and highlighting](https://regex101.com/)&rdquo;

Das Thema der *Capturing Groups* findet man Hinweise hier:

[What is a non-capturing group in regular expressions?](https://stackoverflow.com/questions/3512471/what-is-a-non-capturing-group-in-regular-expressions)

und 

[?: Notation in Regular Expression](https://stackoverflow.com/questions/36524507/notation-in-regular-expression/36524548)

---

[Zurück](../../Readme.md)

---
