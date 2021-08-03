// =====================================================================================
// Uniform Initialization
// =====================================================================================

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

namespace UniformInitialization {

    // =================================================================================
    // built-in types: default initialization of miscellaneous variables rsp. objects   

    void test_01()
    {
        int n{};                 // n equals 0
        float f{};               // f equals 0.0
        double d{};              // d equals 0.0
        std::string s{};         // s equals ""
        std::vector<float> v{};  // v equals an empty vector

        std::cout << "n: " << n << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "s: " << s << std::endl;
        std::cout << "v.size(): " << v.size() << std::endl;
    }

    // =================================================================================
    // built-in types: non default initialization of miscellaneous variables rsp. objects

    void test_02()
    {
        int n{ 1 };                // n equals 1
        float f{ 1.5f };           // f equals 1.5
        double d{ 2.5 };           // d equals 2.5
        std::string s{ "123" };    // s equals "123"

        std::cout << "n: " << n << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "s: " << s << std::endl;
    }

    // =================================================================================
    // standard STL container

    void test_03()
    {
        std::vector<int> myArray{ 1, 2, 3, 4, 5 };
        std::map<std::string, int> myMap{ { "Hans", 1958 }, { "Sepp", 1956 } };

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

    void test_04()
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

    void test_05()
    {
        int intArray[]{ 1, 2, 3, 4, 5 };

        for (int n : intArray) {
            std::cout << n << ", ";
        }
        std::cout << std::endl;
    }

    // =================================================================================
    // user-defined types (classes)

    class SomeClass
    {
    private:
        int m_a;
        double m_b;

    public:
        SomeClass() : m_a{ }, m_b{ } {}
        SomeClass(int a, double b = 0.0) : m_a{ a }, m_b{ b } {}

        void operator() () { std::cout << "a: " << m_a << ", b: " << m_b << std::endl; }
    };

    void test_06()
    {
        SomeClass obj1 {}; 
        SomeClass obj2 { 42, 1.2 };
        SomeClass obj3 { 42 };

        obj1();
        obj2();
        obj3();
    }

    // =================================================================================
    // user-defined POD types (struct, 'plain-old-data')

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

    void test_07()
    {
        MyDataStruct s{ 42, 1.2 };
        std::cout << "a: " << s.m_a << ", b: " << s.m_b << std::endl;

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

    void test_08()
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
    test_06();
    test_07();
    test_08();
}

// =====================================================================================
// End-of-File
// =====================================================================================
