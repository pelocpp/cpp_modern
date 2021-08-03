# Neue Schlüsselwörter `override` und `final`

[Zurück](../../Readme.md)

---

[Quellcode](VirtualOverrideFinal.cpp)

---

## Schlüsselwort `override`

### Ein Beispiel

```cpp
class Base
{
public:
    virtual void func(int);
};

class Derived : public Base
{
public:
    void func(int) override;
};

void Base::func(int n)
{
public:
    std::cout << "Base::func [" << n << "]" << std::endl;
}

void Derived::func(int n)
{
    std::cout << "Derived::func " << n << "]" << std::endl;
}
```

### Vorteile bezüglich der Verwendung von `override`

Hätten wir einen der folgenden Fehler gemacht, würde uns der Übersetzer bei
Verwendung von `override` nun neuerdings darauf aufmerksam machen:

  * In Klasse `Derived`: `void fumc(int) override;` - Tippfehler im Namen der Funktion
  * In Klasse `Derived`: `void func(long) override;` - Fehler bei einem Formalparametertyp
  * In Klasse `Base`: `void func(int);` - Schlüsselwort `virtual` in Klasse `Base` vergessen

---

## Schlüsselwort `final`

Mit dem neuen Schlüsselwort `final` lassen sich Methoden und Klassen markieren,
die nicht mehr überschrieben werden dürfen.

### Ein Beispiel

```cpp
class Driver
{
public:
    virtual void send(int) {};
};

class KeyboardDriver : public Driver
{
public:
    void send(int) final {};  // cannot be overriden anymore
};

class MouseDriver final : public Driver // cannot be used as base class anymore
{
public:
    void send(int) {};  // cannot be overriden anymore
};
```

### Beispiele bezüglich der Verwendung von `final`

Unter Verwendung von `final` wird zum Beispiel verhindert, dass die folgenden Anweisungen
zulässig sind:

```cpp
class TrackballDriver : public MouseDriver
{};
```

```cpp
class SpecialKeyboardDriver : public KeyboardDriver
{
public:
    void send(int) final;
};
```

---

[Zurück](../../Readme.md)

---
