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

    // 'shared ptr' approach
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

    static void test_02()
    {
        std::shared_ptr<int> ptr{ loadSharedPointer() };
        std::println("Outer scope: {}", ptr.use_count());

        storeSharedPointer(ptr);
        std::println("Outer scope: {}", ptr.use_count());
        // no explicit delete on object ptr: shared ptr goes out of scope!
    }

    static void test_03()
    {
        // you can create a const shared pointer from a non-const pointer 
        std::shared_ptr<int> ptr1{ new int{ 123 } };
        const std::shared_ptr<const int> ptr2{ ptr1 };

        // *ptr2 = 456;  // error: 'ptr2': you cannot assign to a variable that is const

        int dummy{ *ptr2 };
        const int* ip{ ptr2.get() };
    }

    static void storeSharedPointerEx(const std::shared_ptr<const int>& ptr)
    {
        std::println("Inner scope: {}", ptr.use_count());
        // *ptr = 456;
    }

    static void test_04()
    {
        std::shared_ptr<int> ptr1{ new int{ 123 } };

        const std::shared_ptr<const int> ptr2{ ptr1 };

        storeSharedPointerEx(ptr1);
        storeSharedPointerEx(ptr2);
    }
}

void main_shared_ptr() 
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace SharedPointer;
    test_01();
    test_02();
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
