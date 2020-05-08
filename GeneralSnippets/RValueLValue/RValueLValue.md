# RValue / LValue

Das nachfolgende Code-Fragment skzizziert die Umstellung einer Klasse `IntegerSet`

```cpp
class IntegerSet
{
public:
    // move semantics
    IntegerSet(IntegerSet&& set) noexcept;  // move-copy c'tor
    IntegerSet& operator= (IntegerSet&& set) noexcept; // move-assignment

private:
    // private helper methods
    void cleanup();
    void moveFrom(IntegerSet& set) noexcept;

    void swap(IntegerSet& set1, IntegerSet& set2) noexcept;  // 'swap idiom'
};

// private helper methods
void IntegerSet::cleanup() {
    delete[] m_set;
    m_set = nullptr;
    m_num = 0;
}

void IntegerSet::moveFrom(IntegerSet& set) noexcept {
    // shallow copy
    m_set = set.m_set;
    m_num = set.m_num;

    // reset source  object, because ownership has been moved
    set.m_set = nullptr;
    set.m_num = 0;
}

// move semantics - move-copy c'tor
IntegerSet::IntegerSet(IntegerSet&& set) noexcept {
    moveFrom(set);
}

// alternate realisation - move-copy c'tor - based on so called 'swap idiom'
IntegerSet::IntegerSet(IntegerSet&& set) noexcept : IntegerSet() { 
    swap(*this, set);
}

// move semantics: // move-assignment
IntegerSet& IntegerSet::operator= (IntegerSet&& set) noexcept { 
    if (this == &set)
        return *this;

    cleanup();
    moveFrom(set);

    return *this;
}

// alternate realisation - move-assignment - based on so called 'swap idiom'
IntegerSet& IntegerSet::operator= (IntegerSet&& set) noexcept {
    if (this == &set)
        return *this;

    IntegerSet tmp(std::move(set));
    swap(*this, tmp);

    return *this;
}
```

