// =====================================================================================
// ArgumentDependentNameLookup.cpp
// =====================================================================================

module modern_cpp:argument_dependent_name_lookup;

namespace ArgumentDependentNameLookup
{
    namespace MyNamespace
    {
        class MyClass {};
        void doSomething(MyClass) {}
        void doSomething() {}
    }

    namespace MyProject
    {
        void test_01()
        {
            MyNamespace::MyClass obj;

            // doSomething();    // Error: 'doSomething': identifier not found

            MyNamespace::doSomething();    // works

            doSomething(obj);              // works too
        }

        void test_02()
        {
            std::cout << "Hello World" << std::endl;
        }

        void test_03()
        {
            using std::operator<<;

            std::cout << "Hello World" << std::endl;
        }

        void test_04()
        {
            std::operator<<(std::cout, "Hello World").operator<<(std::endl);
        }
    }
}



void main_argument_dependent_name_lookup()
{
    using namespace ArgumentDependentNameLookup::MyProject;
    test_01();
    test_02();
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
