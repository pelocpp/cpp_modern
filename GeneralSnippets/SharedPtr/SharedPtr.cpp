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

#include "../Global/Dummy.h"

namespace SharedPointer {

    // classical approach
    Dummy* createDummy() {
        return new Dummy;
    }

    void doSomething(Dummy* dummy) {

        dummy->sayHello();

        // note: what happens, if delete is called on dummy?
        // delete dummy;
    }

    // 'shared ptr' approach
    std::shared_ptr<Dummy> createDummy2() {
        
        return std::make_shared<Dummy>();
        // same as:
        // return std::shared_ptr<Dummy>(new Dummy);
    }

    // note: play with 'call-by-value' or 'call-by-reference'
    void doSomething2(const std::shared_ptr<Dummy> ptr) {

        ptr->sayHello();

        std::cout << "inner use_count: " << ptr.use_count() <<  std::endl;

        // note: what happens, if delete is called on ptr?
        // you don't do that!
    }

    void test_01() {
        std::cout << "Begin-of-program" << std::endl;
        // creation:
        // 'firstShared' is a shared pointer for a new instance of 'Dummy' 
        std::shared_ptr<Dummy> firstShared = std::make_shared<Dummy>();

        // create several smart pointers that share the same object
        std::shared_ptr<Dummy> secondShared(firstShared);
        // 1st way: Copy constructing

        std::shared_ptr<Dummy> thirdShared;
        thirdShared = firstShared;
        // 2nd way: Assigning

        std::cout << "use_count: " << firstShared.use_count() << std::endl;
        std::cout << "use_count: " << secondShared.use_count() << std::endl;
        std::cout << "use_count: " << thirdShared.use_count() << std::endl;

        std::cout << "End-of-program" << std::endl;
    }

    void test_02() {
        std::cout << "Begin-of-program" << std::endl;
        Dummy* dummy = createDummy();
        doSomething(dummy);
        delete dummy;
        std::cout << "End-of-program" << std::endl;
    }

    void test_03() {
        std::cout << "Begin-of-program" << std::endl;
        std::shared_ptr<Dummy> ptr = createDummy2();
        std::cout << "outer use_count: " << ptr.use_count() << std::endl;
        doSomething2(ptr);
        std::cout << "outer use_count: " << ptr.use_count() << std::endl;
        // no explicit delete on Object ptr - shared ptr goes out of scope!
        std::cout << "End-of-program" << std::endl;
    }
}

int main_shared_ptr()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    using namespace SharedPointer;
    test_01();
    test_02();
    test_03();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
