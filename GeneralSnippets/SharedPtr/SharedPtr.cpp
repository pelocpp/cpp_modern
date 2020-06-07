// =====================================================================================
// std::shared_ptr
// =====================================================================================

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <iostream>
#include <memory>

namespace SharedPointer {

    // 'shared ptr' approach
    std::shared_ptr<int> loadSharedPointer() {
        std::shared_ptr<int> tmp = std::make_shared<int>(456);
        return tmp;
    }

    // note: play with 'call-by-value' or 'call-by-reference'
    void storeSharedPointer(const std::shared_ptr<int> ptr) {
        std::cout << "inner scope: " << ptr.use_count() <<  std::endl;
    }

    void test_01() {

        // 'ptr1' is a shared pointer for a new instance of an int
        std::shared_ptr<int> ptr1 = std::shared_ptr<int>(new int{ 123 });
        // or
        // std::shared_ptr<int> ptr1 = std::make_shared<int>(123);

        // access value behind smart pointer
        std::cout << "ptr1:       " << *ptr1 << std::endl;

        // access value using raw pointer
        int* ip1 = ptr1.get();
        (*ip1)++;
        std::cout << "*ip:        " << *ip1 << std::endl;

        // access value - again - behind smart pointer
        std::cout << "*ptr1:      " << *ptr1 << std::endl;

        // create several smart pointers that share the same object:
        //
        // 1.) copy-construction
        std::shared_ptr<int> ptr2(ptr1);

        // 2.) assignment-operator
        std::shared_ptr<int> ptr3;
        ptr3 = ptr1;

        // retrieve number of different shared_ptr instances managing the same object
        std::cout << "use_count:  " << ptr1.use_count() << std::endl;
        std::cout << "use_count:  " << ptr2.use_count() << std::endl;
        std::cout << "use_count:  " << ptr3.use_count() << std::endl;

        // access object through different shared_ptr instances
        std::cout << "value:      " << *ptr1 << std::endl;
        std::cout << "value:      " << *ptr2 << std::endl;
        std::cout << "value:      " << *ptr3 << std::endl;
    }

    void test_02() {
        std::shared_ptr<int> ptr = loadSharedPointer();
        std::cout << "outer scope: " << ptr.use_count() << std::endl;
        storeSharedPointer(ptr);
        std::cout << "outer scope: " << ptr.use_count() << std::endl;
        // no explicit delete on object ptr: shared ptr goes out of scope!
    }
}

void main_shared_ptr()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace SharedPointer;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
