// =====================================================================================
// BraceInitialization.cpp // Uniform Initialization / Brace Initialization
// =====================================================================================

module modern_cpp:brace_initialization;

namespace BraceInitialization {

    // =================================================================================
    // Brace initialization does not allow narrowing:
    static void test_00()
    {
        double dval{ 123.456 };
        int ival{ 123 };

        double d1 = ival;      // Compiles
        // double d2{ ival };  // Error: "conversion from 'int' to 'double' requires a narrowing conversion"
    }

    // =================================================================================
    // built-in types: default initialization of miscellaneous variables

    static void test_01()
    {
        int n{};                   // n equals 0
        float f{};                 // f equals 0.0
        double d{};                // d equals 0.0
        unsigned long l{};         // l equals 0
        size_t i{};                // i equals 0

        std::println("n: {}", n);
        std::println("f: {}", f);
        std::println("d: {}", d);
        std::println("l: {}", l);
        std::println("i: {}", i);

    }

    // =================================================================================
    // built-in types: non default initialization of miscellaneous variables

    static void test_02()
    {
        int n{ 1 };                // n equals 1
        float f{ 2.5f };           // f equals 2.5
        double d{ 3.5 };           // d equals 3.5
        unsigned long l{ 4l };     // l equals 4
        size_t i{ 5 };             // i equals 5

        std::println("n: {}", n);
        std::println("f: {}", f);
        std::println("d: {}", d);
        std::println("l: {}", l);
        std::println("i: {}", i);
    }

    // =================================================================================
    // user-defined types: structs

    struct Struct
    {
        int m_i;
        int m_j;
    };

    static void test_03()
    {
        [[ maybe_unused]]
        struct Struct obj0;                           // uninitialized !!!

        struct Struct obj1 {};                        // obj1.m_i => 0, obj1.m_j => 0

        struct Struct obj2 { 1, 2 };                  // obj2.m_i => 1, obj2.m_j => 2

        // designated initializer syntax
        struct Struct obj3 { .m_i = 1, .m_j = 2 };    // obj2.m_i => 1, obj2.m_j => 2

        struct Struct obj4 { 3 };                     // obj3.m_i => 3, obj3.m_j => 0
        // gcc: warning:
        // missing initializer for member 'Struct::m_j'
    }

    // struct with constructor
    struct StructWithCTor
    {
        int m_i;
        int m_j;

        StructWithCTor(int i, int j) : m_i{ 2 * i }, m_j{ 2 * j } {}
    };

    static void test_04()
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

    static void test_05()
    {
        Class obj{ 11, 12 };  // obj.m_a => 11, obj.m_b => 12
    }

    class AnotherClass
    {
    private:
        int    m_a;
        double m_b;

    public:
        AnotherClass() : m_a{ }, m_b{ } {}

        AnotherClass(int a, double b = 0.0) : m_a{ a }, m_b{ b } {}

        void operator() () { std::println("a: {}, b: {}", m_a, m_b); }
    };

    static void test_06()
    {
        AnotherClass obj1{};
        AnotherClass obj2{ 123, 123.456 };
        AnotherClass obj3{ 123 };

        obj1();
        obj2();
        obj3();
    }

    // =================================================================================
    // standard STL container

    static void test_07()
    {
        std::vector<int> myVector{ 1, 2, 3, 4, 5 };

        std::map<std::string, int> myMap
        {
            { "Hans", 1958 },
            { "Sepp", 1956 } 
        };

        std::for_each(
            myVector.begin(),
            myVector.end(),
            [](int value) {
                std::print("{}, ", value);
            }
        );
        std::println();

        std::for_each(
            myMap.begin(),
            myMap.end(),
            [](const std::pair<const std::string, int>& value) {
                std::println("{} - {}", value.first, value.second);
            }
        );

        // or shorter
        std::for_each(
            myMap.begin(),
            myMap.end(),
            [](const auto& value) {
                std::println("{} - {}", value.first, value.second);
            }
        );
    }

    // =================================================================================
    // dynamically allocated arrays

    static void test_08()
    {
        int* pi{ new int[5] { 1, 2, 3, 4, 5 } };
        double* pd{ new double[5] { 1.0, 2.0, 3.0, 4.0, 5.0 } };

        for (size_t i{}; i != 5; i++) {
            std::println("{}, ", pi[i]);
        }
        std::println();

        for (size_t i{}; i != 5; i++) {
            std::println("{}, ", pi[i]);
        }
        std::println();

        delete[] pi;
        delete[] pd;
    }

    // =================================================================================
    // statically allocated arrays

    static void test_09()
    {
        [[ maybe_unused]]
        int intArray1[10];

        int intArray2[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        int intArray3[]  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        int intArray4[10]{ 1, 2, 3 };

        int intArray5[10]{ 1 };

        int intArray6[10]{ 0 };

        int intArray7[10]{ };
    }

    // =================================================================================
    // Nested Structures / *Brace Elision*

        // POD - C-kompatibel
    struct Point
    {
        int x;
        int y;
    };

    // POD // C-kompatibel
    struct Rectangle
    {
        struct Point leftUpper;
        struct Point rightLower;
    };

    static void test_10()
    {
        Rectangle r1{ {1, 2}, {3, 4} };
        Rectangle r2{ {}, {} };
        Rectangle r3{ };
        Rectangle r4{ 1, 2, 3, 4 };
        Rectangle r5{ 1, 2 };
    }

    // ---------------------------------------------------------------------------------

    struct Inner {
        int m_array[2];
    };

    static void test_11()
    {
        [[ maybe_unused]]
        Inner inner1;                       // uninitialized
        
        Inner inner2{ };                    // m_array[0] => 0 & m_array[1] => 0
        
        Inner inner3{ { 1, 2 } };           // Direct initialization
        
        Inner inner4{ 1, 2 };               // Uses Brace Elision (!) of m_array
    }

    static void test_12()
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
        int    m_a;
        double m_b;
    };

    class MyDataClass {
    public:
        int    m_x;
        double m_y;

        void operator()() const
        {
            std::println("x: {}, y: {}", m_x, m_y);
        }
    };

    static void test_13()
    {
        MyDataStruct s{ 123, 123.456 };
        std::println("a: {}, b: {}", s.m_a, s.m_b);

        // or - using C++ designated initializers:
        MyDataStruct s2{ .m_a = 123, .m_b = 123.456 };
        std::println("a: {}, b: {}", s2.m_a, s2.m_b);

        // initialization of public attributes of an arbitrary object
        MyDataClass obj1{ 123, 123.456 };
        MyDataClass obj2{ 456, 654.321 };
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
            : m_data{ a, b, c, d, e }, m_n{ 99 }
        {}
        
        MyAnotherClass(int a, int b, int c, int d, int e, int f)
            : m_data{ a, b, c, d, e }, m_n{ f }
        {}

    public:
        void operator()() {
            std::println("m_n: {}", m_n);

            for (size_t i{}; i != 5; i++) {
                std::println("{}: {}", i, m_data[i]);
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
            for (size_t i{}; i != m_vec.size(); i++) {
                std::println("{}: {}", i, m_vec[i]);

            }
        }
    };

    static void test_14()
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

void main_brace_initialization()
{
    using namespace BraceInitialization;

    test_00();
    test_01(); 
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
    test_07();
    test_08();
    test_09();
    test_10();
    test_11();
    test_12();
    test_13();
    test_14();
}

// =====================================================================================
// End-of-File
// =====================================================================================



