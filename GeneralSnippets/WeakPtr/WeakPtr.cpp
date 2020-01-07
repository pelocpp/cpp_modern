#include <iostream>
#include <memory>

// =====================================================================================
// Weak Pointer
// =====================================================================================

namespace WeakPointer {

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

    void test_01() {

        std::cout << "Begin-of-program" << std::endl;
        std::weak_ptr<Dummy> weak;

        {
            std::cout << "Begin-of-Scope" << std::endl;

            std::shared_ptr<Dummy> ptr (new Dummy);

            std::cerr << "Usage count shared_ptr: " << ptr.use_count() << std::endl;

            weak = ptr;

            std::cerr << "Weak_ptr expired: " << weak.expired() << std::endl;

            // need shared pointer to access weak pointer
            std::shared_ptr<Dummy> tempSharedPtr = weak.lock(); 
            std::cerr << "Usage count shared_ptr: " << ptr.use_count() << std::endl;

            // access weak pointer via shared pointer
            tempSharedPtr->helloWorld();

            std::cout << "End-of-Scope" << std::endl;
        }

        std::cerr << "Weak_ptr expired: " << weak.expired() << std::endl;
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
