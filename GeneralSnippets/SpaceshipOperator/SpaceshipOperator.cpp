// =====================================================================================
// SpaceshipOperator.cpp
// =====================================================================================

//#include <algorithm>
//#include <compare>
//#include <print>
//#include <string>
//
//// https://towardsdev.com/cpp20-spaceship-operator-three-way-comparison-b1213302bf93

module;

#include <cctype>

module modern_cpp:spaceship_operator;

namespace Comparison_Problem_Classic
{
    struct Version
    {
        int major;
        int minor;
        int patch;
    };

    // operator<
    bool operator<(const Version& a, const Version& b) {
        if (a.major != b.major) return a.major < b.major;
        if (a.minor != b.minor) return a.minor < b.minor;
        return a.patch < b.patch;
    }

    // remaining 5 implementations
    bool operator>(const Version& a, const Version& b) {
        return b < a;
    }

    bool operator<=(const Version& a, const Version& b) {
        return !(b < a);
    }

    bool operator>=(const Version& a, const Version& b) {
        return !(a < b);
    }

    bool operator==(const Version& a, const Version& b) {
        return a.major == b.major && a.minor == b.minor && a.patch == b.patch;
    }

    bool operator!=(const Version& a, const Version& b) {
        return !(a == b);
    }

    void comparison_01()
    {
        std::println("spaceship_01");

        struct Version firstVersion { 1, 1, 1 };
        struct Version anotherVersion { 1, 1, 1 };

        //auto result = (firstVersion == anotherVersion);
        //result = (firstVersion != anotherVersion);

        if (firstVersion < anotherVersion) {
            std::println("firstVersion is older");  // compiles, works
        }

        if (firstVersion > anotherVersion) {
            std::println("firstVersion is newer");  // compiles, compilation error: no operator>
        }

        if (firstVersion == anotherVersion) {
            std::println("same version");           // compilation error: no operator==
        }
    }
}

// ======================================================================================

namespace Comparison_Categories
{
    void comparison_categories_01_strong()
    {
        std::println("int");

        int a = 1;
        int b = 2;

        auto result = a <=> b;    //  std::strong_ordering

        if (result < 0) {
            std::println("a < b");
        }
        if (result <= 0) {
            std::println("a < b");
        }
        if (result > 0) {
            std::println("a < b");
        }
        if (result >= 0) {
            std::println("a > b");
        }
        if (result == 0) {
            std::println("a < b");
        }
        if (result != 0) {
            std::println("a == b");
        };
    }

    void comparison_categories_02_partial()
    {
        std::println("double");

        double a = 1.5;
        double b = 2.5;

        auto result = a <=> b;    //  std::partial_ordering

        if (result < 0) {
            std::println("a < b");
        }
        if (result <= 0) {
            std::println("a < b");
        }
        if (result > 0) {
            std::println("a < b");
        }
        if (result >= 0) {
            std::println("a > b");
        }
        if (result == 0) {
            std::println("a < b");
        }
        if (result != 0) {
            std::println("a == b");
        }
    }

    // Note: No, there is no fundamental data type or standard library (STL) data type in C++
    // whose native three-way comparison operator (<=>) returns std::weak_ordering.

    // How to enforce std::weak_orderingstd::weak_ordering is meant to be a deliberate, user - chosen semantic.
    // It is used when two objects can be considered mathematically "equivalent" without being completely identical
    // or substitutable in every function.If you want a type to use std::weak_ordering, you must manually define it.
    // The classic textbook example is a case-insensitive string wrapper

    class CaseInsensitiveString
    {
    private:
        std::string m_str;

    public:
        CaseInsensitiveString() = default;
        CaseInsensitiveString(std::string str) : m_str{ str } {}

        // explicitly enforce weak_ordering
        std::weak_ordering operator <=> (const CaseInsensitiveString& other) const {

            // compare lengths or transform characters to lowercase
            std::string a{ m_str };
            std::string b{ other.m_str };

            std::transform(a.begin(), a.end(), a.begin(), ::tolower);
            std::transform(b.begin(), b.end(), b.begin(), ::tolower);

            return a <=> b;  // std::string's <=> returns strong_ordering,
                             // but we return std::weak_ordering to signal "equivalent, not equal"
        }

        bool operator== (const CaseInsensitiveString& other) const {
            return (*this <=> other) == 0;
        }
    };

    void comparison_categories_03_weak()
    {
        CaseInsensitiveString s1{ "Hello" };
        CaseInsensitiveString s2{ "hello" };

        // evaluation returns std::weak_ordering::equivalent;
        // they are equivalent, but NOT identical/substitutable (e.g., s1.str != s2.str)

        auto result = s1 <=> s2;

        if (result == std::weak_ordering::equivalent) {
            std::println("s1 and s2 are equivalent!");
        }
    }
}

namespace Comparison_With_Spaceship_Operator
{
    struct AnyType
    {
        int m_x;
        int m_y;

        // custom implementation of <=>
        std::strong_ordering operator<=>(const AnyType& other) const noexcept {

            // 1. compare first attribute
            if (auto cmp = m_x <=> other.m_x; cmp != 0) {
                return cmp;
            }

            // 2. compare the second attribute if the first was equal
            return m_y <=> other.m_y;
        }

        // Important: The == operator MUST be defined separately:
        // bool operator==(const AnyType&) const = default;
    };

    void spaceship_01_struct_any_type_01()
    {
        AnyType a{ 1, 2 };
        AnyType b{ 2, 1 };

        auto result = a <=> b;    //  std::strong_ordering

        if (result < 0) {
            std::println("a < b");
        }
        if (result <= 0) {
            std::println("a <= b");
        }
        if (result > 0) {
            std::println("a > b");
        }
        if (result >= 0) {
            std::println("a >= b");
        }
        if (result == 0) {
            std::println("a == b");
        }
        if (result != 0) {
            std::println("a != b");
        }
    }

    void spaceship_01_struct_any_type_02()
    {
        AnyType a{ 1, 2 };
        AnyType b{ 2, 1 };

        auto result = a <=> b;    //  std::strong_ordering

        if (a < b) {
            std::println("a < b");
        }
        if (a <= b) {
            std::println("a < b");
        }
        if (a > b) {
            std::println("a < b");
        }
        if (a >= b) {
            std::println("a > b");
        }

        //if (a == b) {    // does not compile
        //    std::println("a < b");
        //}
        //if (a != b) {     // does not compile
        //    std::println("a == b");
        //}
    }
}

namespace Comparison_With_Spaceship_Operator
{
    struct Version {
        int major;
        int minor;
        int patch;

        auto operator<=>(const Version&) const = default;

        //std::strong_ordering operator<=>(const Version& other) const {
        //    if (auto cmp = major <=> other.major; cmp != 0) return cmp;
        //    if (auto cmp = minor <=> other.minor; cmp != 0) return cmp;
        //    return patch <=> other.patch;
        //}
    };

    void spaceship_01_struct_version()
    {
        struct Version firstVersion{ 1, 1, 1 };
        struct Version anotherVersion{ 1, 1, 1 };

        auto result = (firstVersion == anotherVersion);
        std::println("result: {}", result);

        result = (firstVersion != anotherVersion);
        std::println("result: {}", result);
    }

    void spaceship_02_struct_version()
    {
        struct Version firstVersion { 1, 2, 0 };
        struct Version anotherVersion { 1, 3, 0 };

        auto result = (firstVersion < anotherVersion);
        std::println("result: {}", result);

        result = (firstVersion != anotherVersion);
        std::println("result: {}", result);
    }
}

void main_spaceship_operator()
{
    Comparison_Problem_Classic::comparison_01();

    Comparison_Categories::comparison_categories_01_strong();
    Comparison_Categories::comparison_categories_02_partial();
    Comparison_Categories::comparison_categories_03_weak();

    Comparison_With_Spaceship_Operator::spaceship_01_struct_version();
    Comparison_With_Spaceship_Operator::spaceship_02_struct_version();
}