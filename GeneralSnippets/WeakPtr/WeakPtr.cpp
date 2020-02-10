// =====================================================================================
// Weak Pointer
// =====================================================================================

#include <iostream>
#include <memory>

#include "../Global/Dummy.h"

namespace WeakPointer {

    void test_01() {

        std::cout << "Begin-of-program" << std::endl;
        std::weak_ptr<Dummy> weak;

        {
            std::cout << "Begin-of-Scope" << std::endl;

            std::shared_ptr<Dummy> ptr = std::make_shared<Dummy>();

            std::cerr << "Usage count shared_ptr: " << ptr.use_count() << std::endl;

            weak = ptr;

            std::cerr << "Is weak ptr expired: " << weak.expired() << std::endl;

            // need shared pointer to access weak pointer
            std::shared_ptr<Dummy> tempPtr = weak.lock(); 
            std::cerr << "Usage count shared_ptr: " << ptr.use_count() << std::endl;

            // access weak pointer via shared pointer
            tempPtr->sayHello();

            std::cout << "End-of-Scope" << std::endl;
        }

        std::cerr << "Is weak ptr expired: " << weak.expired() << std::endl;
        std::cout << "End-of-program" << std::endl;
    }
}

int main_weak_pointer()
{
    using namespace WeakPointer;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
