// =====================================================================================
// IsTransparent.cpp // is_transparent
// =====================================================================================

module modern_cpp:is_transparent;

namespace IsTransparent {

    // =================================================================================
    // demonstration of a problem with user defined classes and keys

    class Employee
    {
    private:
        std::size_t m_id;
        std::string m_name;

    public:
        // c'tor
        explicit Employee(std::size_t id, const std::string& name)
            : m_id{ id }, m_name{ name }
        {}

        // getter
        std::size_t getId() const { return m_id; }
        std::string getName() const { return m_name; }

        // operators - add / remove comment
        bool operator<(const Employee& other) const
        {
            return m_id < other.m_id;
        }
    };

    static void test_01()
    {
        std::set<Employee> employees // does not compile - enable operator< in class Employee
        {
            Employee{ 1, "John" },
            Employee{ 2, "Bill" }
        };
    }

    // =================================================================================
    // demonstration of a problem with user defined classes and keys

    class AnotherEmployee
    {
    private:
        std::size_t m_id;
        std::string m_name;

    public:
        // c'tor
        explicit AnotherEmployee(std::size_t id, const std::string& name)
            : m_id{ id }, m_name{ name }
        {}

        // getter
        std::size_t getId() const { return m_id; }
        std::string getName() const { return m_name; }
    };

    struct CompareId
    {
        using is_transparent = void;   // add / remove comment

        bool operator() (const AnotherEmployee& employee1, const AnotherEmployee& employee2) const
        {
            return employee1.getId() < employee2.getId();
        }

        bool operator() (std::size_t id, const AnotherEmployee& employee) const  // add / remove comment
        {
            return id < employee.getId();
        }

        bool operator() (const AnotherEmployee& employee, std::size_t id) const  // add / remove comment
        {
            return employee.getId() < id;
        }
    };

    static void test_02()
    {
        std::set<AnotherEmployee, CompareId> employees
        {
            AnotherEmployee{ 1, "John" },
            AnotherEmployee{ 2, "Bill" }
        };

        auto pos = employees.find(1);    // still does not compile - remove *all* comments in class CompareId

        std::println("Name: {}", pos->getName());
    }

    // =================================================================================
    // demonstration of a problem with redundant type conversion operations

    static void test_03()
    {
        std::set<std::string> strings;

        std::string one{ "one" };

        strings.insert(one);

        strings.insert("two");   // is there a (performance) problem ???

        auto pos = strings.find("one");
    }

    static void test_04()
    {
        // using is_transparent implicitly

        std::set<std::string, std::less<>> strings;  // std::less<> is transparent, look at source code of std::less<>

        strings.insert("one");
        strings.insert("two");

        auto pos = strings.find("one");
    }

    struct MyCompare
    {
        // we can also demonstrate this explicitly using a custom comparator

        using is_transparent = void;   // add / remove comment

        bool operator() (const std::string& a, const std::string& b) const
        {
            return a < b;
        }

        bool operator() (const std::string& a, const char* b) const  // add / remove comment
        {
            return a < b;
        }

        bool operator() (const char* a, const std::string& b) const  // add / remove comment
        {
            return a < b;
        }
    };

    static void test_05()
    {
        std::set<std::string, MyCompare> strings;

        strings.insert("one");
        strings.insert("two");

        auto pos = strings.find("one");
    }

    // =================================================================================
    // Prerequisites for is_transparent

    static void test_06()
    {
        std::set<std::string, std::less<>> strings;   // since C++14

        strings.insert("two");                        // `insert` does not have a heterogeneous variant; a `std::string` is still created here.
        auto pos = strings.find("one");               // template<class K> find(const K&), no temporary std::string
    }

    // =================================================================================
    // Demonstration of whether conversion takes place
    // Variant: Custom key type.
    // Custom key type with output in the constructor.
    // This allows you to see the conversion directly.

    class Key
    {
    private:
        std::string m_s;

    public:
        Key(const std::string& s) : m_s{ s }
        {
            std::println("-> No Conversion: std::string& -> Key");
        }

        Key(const char* cp) : m_s{ cp }
        {
            std::println("-> Conversion: const char* -> Key");
        }

        friend bool operator<(const Key& a, const Key& b) { return a.m_s < b.m_s; }
        friend bool operator<(const Key& a, const char* b) { return a.m_s < b; }
        friend bool operator<(const char* a, const Key& b) { return a < b.m_s; }
    };

    static void test_07()
    {
        std::set<Key> normal;
        normal.insert("one");                         // conversion (necessary)
        std::puts("find in normal std::set:");
        auto pos1 = normal.find("one");               // conversion

        std::set<Key, std::less<>> transparent;
        transparent.insert("one");                    // conversion (necessary)
        std::puts("find in transparent std::set:");
        auto pos2 = transparent.find("one");          // no output, no conversion
    }

    // =================================================================================
    // Implementing a transparent comparator involves defining a function object
    // with an is_transparent type and overloads for operator() that can compare different types.
    // Here's a simplified example using std::set:

    struct CaseInsensitiveCompare
    {
        using is_transparent = void;

        bool operator() (const std::string& a, const std::string& b) const {
            
            return std::lexicographical_compare(
                a.begin(),
                a.end(),
                b.begin(),
                b.end(),
                [](char ac, char bc) {
                    return std::tolower(ac) < std::tolower(bc); 
                }
            );
        }

        bool operator() (char a, const std::string& b) const {

            return std::lexicographical_compare(&a, &a + 1, b.begin(), b.end(),
                [](char ac, char bc) { 
                    return std::tolower(ac) < std::tolower(bc);
                }
            );
        }

        bool operator() (const std::string& a, char b) const {

            for (char ch : a) {
                if (std::tolower(ch) == std::tolower(b)) {
                    return true;
                }
            }

            return false;
        }
    };

    static void test_08()
    {
        std::set<std::string, CaseInsensitiveCompare> s = { "Alpha", "beta", "Gamma" };

        std::println("{}", s.find("alpha") != s.end());   // true

        std::println("{}", s.find('G') != s.end());       // true
    }
}

void main_is_transparent()
{
    using namespace IsTransparent;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
}

// =====================================================================================
// End-of-File
// =====================================================================================
