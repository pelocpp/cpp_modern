// =====================================================================================
// UniformInitialization.cpp // Uniform Initialization / Brace Initialization
// =====================================================================================

module modern_cpp:uniform_initialization;

namespace UniformInitialization {

    // =================================================================================
    // built-in types: default initialization of miscellaneous variables

    void test_01()
    {
        int n{};              // n equals 0
        float f{};            // f equals 0.0
        double d{};           // d equals 0.0
        unsigned long l{};    // l equals 0
        size_t i{};           // i equals 0

        std::cout << "n: " << n << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "l: " << l << std::endl;
        std::cout << "i: " << i << std::endl;
    }

    // =================================================================================
    // built-in types: non default initialization of miscellaneous variables

    void test_02()
    {
        int n{ 1 };          // n equals 1
        float f{ 1.5f };     // f equals 1.5
        double d{ 2.5 };     // d equals 2.5

        std::cout << "n: " << n << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "d: " << d << std::endl;
    }

    // =================================================================================
    // user-defined types: structs

    struct Struct
    {
        int m_i;
        int m_j;
    };

    void test_03()
    {
        [[ maybe_unused]] struct Struct obj0;         // uninitialized !!!
        struct Struct obj1 {};                        // obj1.m_i => 0, obj1.m_j => 0
        struct Struct obj2 { 1, 2 };                  // obj2.m_i => 1, obj2.m_j => 2
        struct Struct obj3 { 3 };                     // obj3.m_i => 3, obj3.m_j => 0
        // gcc: warning: missing initializer for member 'Struct::m_j'
    }

    // struct with constructor
    struct StructWithCTor
    {
        int m_i;
        int m_j;

        StructWithCTor(int i, int j) : m_i{ 2 * i }, m_j{ 2 * j } {}
    };

    void test_04()
    {
        struct StructWithCTor obj { 5, 6 };        // obj.m_i => 10, obj.m_j => 12
    }

    // =================================================================================
    // user-defined types: classes

    class Class
    {
    private:
        int m_a;
        int m_b;

    public:
        Class(int a, int b) : m_a{ a }, m_b{ b } {}
    };

    void test_05()
    {
        Class obj{ 11, 12 };  // obj.m_a => 11, obj.m_b => 12
    }

    class AnotherClass
    {
    private:
        int m_a;
        double m_b;

    public:
        AnotherClass() : m_a{ }, m_b{ } {}
        AnotherClass(int a, double b = 0.0) : m_a{ a }, m_b{ b } {}

        void operator() () { std::cout << "a: " << m_a << ", b: " << m_b << std::endl; }
    };

    void test_05_01()
    {
        AnotherClass obj1{};
        AnotherClass obj2{ 42, 1.2 };
        AnotherClass obj3{ 42 };

        obj1();
        obj2();
        obj3();
    }

    // =================================================================================
    // standard STL container

    void test_06()
    {
        std::vector<int> myArray{ 1, 2, 3, 4, 5 };

        std::map<std::string, int> myMap
        {
            { "Hans", 1958 },
            { "Sepp", 1956 } 
        };

        std::for_each(
            std::begin(myArray), 
            std::end(myArray),
            [](int value) {
                std::cout << value << ", ";
            }
        );
        std::cout << std::endl;

        std::for_each(
            std::begin(myMap),
            std::end(myMap),
            [](const std::pair<std::string, int>& value) {
                std::cout << value.first << " - " << value.second << std::endl;
            }
        );

        // or shorter
        std::for_each(
            std::begin(myMap),
            std::end(myMap),
            [](const auto& value) {
                std::cout << value.first << " - " << value.second << std::endl;
            }
        );
    }

    // =================================================================================
    // dynamically allocated arrays

    void test_07()
    {
        int* pi = new int[5]{ 1, 2, 3, 4, 5 };
        double* pd = new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 };

        for (int i = 0; i < 5; i++) {
            std::cout << pi[i] << ", ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 5; i++) {
            std::cout << pd[i] << ", ";
        }
        std::cout << std::endl;

        delete[] pi;
        delete[] pd;
    }

    // =================================================================================
    // statically allocated arrays

    void test_08()
    {
        int intArray[]{ 1, 2, 3, 4, 5 };

        for (int n : intArray) {
            std::cout << n << ", ";
        }
        std::cout << std::endl;
    }

    // =================================================================================
    // Nested Structures / *Brace Elision* 

    struct Inner {
        int m_array[2];
    };

    void test_09()
    {
        [[ maybe_unused]] Inner inner1; // uninitialized
        Inner inner2{ };                // m_array[0] => 0 & m_array[1] => 0
        Inner inner3{ { 1, 2 } };       // Direct initialization
        Inner inner4{ 1, 2 };           // Uses Brace Elision (!) of m_array
    }

    void test_09_01()
    {
        // "regular" case:
        // outer braces for the std::array,
        // inner set for the (nested) C-style array.
        std::array<int, 4> values1 { { 1, 2, 3, 4 } };

        // Brace-elided initialization
        std::array<int, 4> values2{ 1, 2, 3, 4 };
    }

    // =================================================================================
    // user-defined POD types (struct, 'plain-old-data')
    // C++ designated initializers

    struct MyDataStruct
    {
        int m_a;
        double m_b;
    };

    class MyDataClass {
    public:
        int m_x;
        double m_y;

        void operator()()
        {
            std::cout << "x: " << m_x << ", y: " << m_y << std::endl;
        }
    };

    void test_10()
    {
        MyDataStruct s{ 42, 1.2 };
        std::cout << "a: " << s.m_a << ", b: " << s.m_b << std::endl;

        // or - using C++ designated initializers:
        MyDataStruct s2{ .m_a = 43, .m_b = 1.3 };
        std::cout << "a: " << s2.m_a << ", b: " << s2.m_b << std::endl;

        // initialization of public attributes of an arbitrary object
        MyDataClass obj1{ 111, 1.23 };
        MyDataClass obj2{ 123, 99.9 };
        obj1();
        obj2();
    }

    // =================================================================================
    // combinations of these uniform initialization rules

    class MyAnotherClass {
    private:
        int m_data[5];
        int m_n;

    public:
        MyAnotherClass() : m_data{ 10, 20, 30, 40, 50 }, m_n{ 98 } {}
        MyAnotherClass(int a, int b, int c, int d, int e)
            : m_data{ a, b, c, d, e }, m_n{ 99 } {}
        MyAnotherClass(int a, int b, int c, int d, int e, int f)
            : m_data{ a, b, c, d, e }, m_n{ f } {}

    public:
        void operator()() {
            std::cout << "m_n: " << m_n << std::endl;
            for (size_t i{ }; i < 5; i++) {
                std::cout << i << ": " << m_data[i] << std::endl;
            }
        }
    };

    class MyYetAnotherClass {
    private:
        std::vector<int> m_vec;

    public:
        MyYetAnotherClass() : m_vec{ 50, 51, 52 } {}

    public:
        void operator()() 
        {
            for (size_t i{ }; i < m_vec.size(); i++) {
                std::cout << i << ": " << m_vec[i] << std::endl;
            }
        }
    };

    void test_11()
    {  
        MyAnotherClass obj1;
        MyAnotherClass obj2{ 11, 12, 13, 14, 15 };
        MyAnotherClass obj3{ 21, 22, 23, 24, 25, 26 };
        obj1();
        obj2();
        obj3();

        MyYetAnotherClass obj{};
        obj();
    }
}

void main_uniform_initialization()
{
    using namespace UniformInitialization;

    test_01(); 
    test_02();
    test_03();
    test_04();
    test_05();
    test_05_01();
    test_06();
    test_07();
    test_08();
    test_09();
    test_09_01();
    test_10();
    test_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================



