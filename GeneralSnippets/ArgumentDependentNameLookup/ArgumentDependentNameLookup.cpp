// =====================================================================================
// ArgumentDependentNameLookup.cpp
// =====================================================================================

module modern_cpp:argument_dependent_name_lookup;

import std;

namespace
{
    namespace MyNamespace
    {
        class MyClass {};
        static void doSomething(MyClass) {}
        static void doSomething() {}
    }

    namespace MyProject
    {
        static void argument_dependent_name_lookup_01()
        {
            MyNamespace::MyClass obj;

            // doSomething();    // Error: 'doSomething': identifier not found

            MyNamespace::doSomething();    // works

            doSomething(obj);              // works too
        }

        static void argument_dependent_name_lookup_02()
        {
            std::cout << "Hello World" << std::endl;
        }

        static void argument_dependent_name_lookup_03()
        {
            using std::operator<<;

            std::cout << "Hello World" << std::endl;
        }

        static void argument_dependent_name_lookup_04()
        {
            std::operator<<(std::cout, "Hello World").operator<<(std::endl);
        }
    }
}

void main_argument_dependent_name_lookup()
{
    MyProject::argument_dependent_name_lookup_01();
    MyProject::argument_dependent_name_lookup_02();
    MyProject::argument_dependent_name_lookup_03();
    MyProject::argument_dependent_name_lookup_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
