# Aufgaben zu generischen Lambdas

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---

[Lösungen](Exercises_16_Generic_Lambdas.cpp)

---

### Überblick

| Aufgabe | Beschreibung |
| :- | :- |
| *Aufgabe* 1 | Personensuche<br/>(Voraussetzungen: Algorithmus `std::find_if`) |

*Tabelle* 1: Aufgaben zu generischen Lambdas.

---

## Aufgabe 1: Personensuche

#### Voraussetzungen: Algorithmus `std::find_if`

Wir haben bei den generischen Lambdas das so genannte Feature
der *Automatic Type Deduction* kennen gelernt:

```cpp
auto isGreaterThanFifty = [](auto n) { return n > 50; };
```

Mit diesem Lambda-Ausdruck haben wir `std::vector`-Objekte mit
`int` und `double`-Werten durchsucht.
Nun wollen wir `Person`-Objekte ins Spiel bringen:

```cpp
class Person
{
private:
    std::string m_name;
    size_t m_age;

    ...
};
```

Erweitern bzw. realisieren Sie die Klasse `Person` so, dass
man in einem `std::vector<Person>`-Objekt Personen eines bestimmten Alters,
also in unserem Beispiel älter als 50 Jahre &ndash; mit demselben Lambda-Ausdruck von oben
durchsuchen kann:

```cpp
int main()
{
    std::vector<Person> personValues{
        Person{ "Hans", 40 },
        Person{ "Sepp", 60 }
    };

    // use generic lambda with a vector of Persons
    auto pos = std::find_if(
        std::begin(personValues),
        std::end(personValues),
        isGreaterThanFifty
    );
    if (pos != std::end(personValues)) {
        std::cout << "Found Person:  " << (*pos).getName() << std::endl;
    }
}
```

---

[Lösungen](Exercises_16_Generic_Lambdas.cpp)

---

[Zurück](/GeneralSnippets/Exercises/Exercises.md)

---
