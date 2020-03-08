// =====================================================================================
// Shared Pointer
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
    std::shared_ptr<int> createObject() {
        return std::shared_ptr<int>(new int);
    }

    // note: play with 'call-by-value' or 'call-by-reference'
    void doSomething(const std::shared_ptr<int> ptr) {
        std::cout << "inner use_count: " << ptr.use_count() <<  std::endl;
    }

    void test_01() {
        std::cout << "Begin-of-program" << std::endl;
        // 'firstShared' is a shared pointer for a new instance of an int
        std::shared_ptr<int> firstShared = std::make_shared<int>(11);
        // or
        // std::shared_ptr<int> firstShared = std::shared_ptr<int>(new int(11));

        // create several smart pointers that share the same object
        // a) copy-constructing
        std::shared_ptr<int> secondShared(firstShared);

        // a) assignment
        std::shared_ptr<int> thirdShared;
        thirdShared = firstShared;

        std::cout << "use_count: " << firstShared.use_count() << std::endl;
        std::cout << "use_count: " << secondShared.use_count() << std::endl;
        std::cout << "use_count: " << thirdShared.use_count() << std::endl;

        // access object
        std::cout << "current object value: " << *firstShared << std::endl;
        std::cout << "current object value: " << *secondShared << std::endl;
        std::cout << "current object value: " << *thirdShared << std::endl;

        std::cout << "End-of-program" << std::endl;
    }

    void test_02() {
        std::cout << "Begin-of-program" << std::endl;
        std::shared_ptr<int> ptr = createObject();
        std::cout << "outer use_count: " << ptr.use_count() << std::endl;
        doSomething(ptr);
        std::cout << "outer use_count: " << ptr.use_count() << std::endl;
        // no explicit delete on Object ptr / shared ptr goes out of scope!
        std::cout << "End-of-program" << std::endl;
    }
}

int main_shared_ptr()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    using namespace SharedPointer;
    test_01();
    test_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
