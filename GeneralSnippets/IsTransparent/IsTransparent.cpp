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
}

void main_is_transparent()
{
    using namespace IsTransparent;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
