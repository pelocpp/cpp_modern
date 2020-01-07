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

// =====================================================================================
// Shared Pointer
// =====================================================================================

namespace SharedPointer {

    class Dummy
    {
        Dummy(Dummy const&) = default;
        Dummy& operator=(Dummy const&) = default;

    public:

        Dummy() = default;

        ~Dummy() {
            std::cerr << "d'tor Dummy" << std::endl;
        }

        void helloWorld() {
            std::cerr << "Hello World" << std::endl;
        }
    };

    // classical approach
    Dummy* createDummy() {
        return new Dummy;
    }

    void doSomething(Dummy* dummy) {

        dummy->helloWorld();

        // note: what happens, if delete is called on dummy?
        // delete dummy;
    }

    // 'shared ptr' approach
    std::shared_ptr<Dummy> createDummy2() {
        
        return std::make_shared<Dummy>();
        // same as:
        // return std::shared_ptr<Dummy>(new Dummy);
    }

    void doSomething2(std::shared_ptr<Dummy> const& ptr) {

        ptr->helloWorld();

        // note: what happens, if delete is called on ptr?
        // you don't do that!
    }

    void test_01() {
        std::cout << "Begin-of-program" << std::endl;
        Dummy* dummy = createDummy();
        doSomething(dummy);
        delete dummy;
        std::cout << "End-of-program" << std::endl;
    }

    void test_02() {
        std::cout << "Begin-of-program" << std::endl;
        std::shared_ptr<Dummy> ptr = createDummy2();
        doSomething2(ptr);
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
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
