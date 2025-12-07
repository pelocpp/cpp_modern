// =====================================================================================
// SharedPtr.cpp // std::shared_ptr
// =====================================================================================

module;

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

module modern_cpp:shared_ptr;

namespace SharedPointer {

    static void test_01() {

        // 'ptr1' is a shared pointer for a new instance of an int
        std::shared_ptr<int> ptr1{ new int{ 123 } };
        // or
        // std::shared_ptr<int> ptr1{ std::make_shared<int>(123) };
        // or
        // auto ptr1{ std::make_shared<int>(123) };

        // access value behind smart pointer
        int n{ *ptr1 };
        std::println("ptr1:        {}", n);

        // access value using raw pointer
        int* ip{ ptr1.get() };
        (*ip)++;
        int m{ *ip };
        std::println("*ip:         {}", m);

        // access value - again - behind smart pointer
        m = *ptr1;
        std::println("*ptr1:       {}", m);

        /* create several smart pointers that share the same object
        */
        // 1.) copy-construction
        std::shared_ptr<int> ptr2{ ptr1 };

        // 2.) assignment-operator
        std::shared_ptr<int> ptr3;
        ptr3 = ptr1;

        // retrieve number of different shared_ptr instances managing the same object
        std::println("use_count:   {}", ptr1.use_count());
        std::println("use_count:   {}", ptr2.use_count());
        std::println("use_count:   {}", ptr3.use_count());

        // access object through different shared_ptr instances
        std::println("Value:       {}", *ptr1);
        std::println("Value:       {}", *ptr2);
        std::println("Value:       {}", *ptr3);

        // shared ptr are going out of scope right now!
    }

    // ===========================================================================

    static std::shared_ptr<int> loadSharedPointer()
    {
        std::shared_ptr<int> tmp{ std::make_shared<int>(123) };
        return tmp;
    }

    // note: play with 'call-by-value' or 'call-by-reference'
    static void storeSharedPointer(std::shared_ptr<int> ptr)
    {
        std::println("Inner scope: {}", ptr.use_count());
    }

    static void test_02()
    {
        std::shared_ptr<int> ptr{ loadSharedPointer() };
        std::println("Outer scope: {}", ptr.use_count());

        storeSharedPointer(ptr);
        std::println("Outer scope: {}", ptr.use_count());
        // no explicit delete on object ptr: shared ptr goes out of scope!
    }

    // ===========================================================================
    // std::unique_ptr with arrays

    class A {
    public:
        A() {
            std::println("Constructor A called");
        }

        ~A() {
            std::println("Destructor A called");
        }
    };

    static void test_03()
    {
        // shared pointer - prior to C++17
        A* ip{ new A[3] };
        std::shared_ptr<A> sp{ ip, std::default_delete<A[]>() };
        std::println();
        sp.reset();
        std::println();

        // shared pointer - C++ 17 
        std::shared_ptr<A[]> sp2 = std::make_shared<A[]>(3);
        std::println();
        sp2.reset();
        std::println();
    }
}

// =====================================================================================

void main_shared_ptr() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace SharedPointer;
    test_01();
    test_02();  // interaction with functions/methods
    test_03();  // support of arrays
}

// =====================================================================================
// End-of-File
// =====================================================================================
