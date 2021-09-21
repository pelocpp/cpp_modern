# Template Template Parameter

[Zurück](../../Readme.md)

---

[Quellcode](TemplateTemplateParameter_01.cpp)

---

Als Parameter für Templates können neben realen Typen auch wiederum Klassentemplates fungieren.

Die Syntax derartiger Templates sieht dann so aus:

```cpp
template < template <typename> class T> >
class X
{
};
```

In den Beispielen betrachten wir ein Funktions-Template und ein Klassentemplate,
die beide in den Template-Parametern ein Klassentemplate als Stellvertreter für einen STL-Container übergeben bekommen.

Ein weiteres Beispiel zum Thema *Template Template Parameter* findet sich hier:

https://stackoverflow.com/questions/32351697/optional-range-check-based-on-template-parameter

---

[Zurück](../../Readme.md)

---

