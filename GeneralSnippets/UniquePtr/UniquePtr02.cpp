// ===============================================================================
// Unique Pointer - Zweites Beispiel
// ===============================================================================

#include <iostream>
#include <memory>

namespace UniquePointerZwei {

    class Dummy
    {
        Dummy(Dummy const&) = default;
        Dummy& operator=(Dummy const&) = default;

    public:

        Dummy() {
            std::cerr << "c'tor Dummy" << std::endl;
        }

        ~Dummy() {
            std::cerr << "d'tor Dummy" << std::endl;
        }

        void helloWorld() {
            std::cerr << "Hello World" << std::endl;
        }
    };

    std::unique_ptr<int> createUniquePointer()
    {
        std::unique_ptr<int> ptr = std::make_unique<int>(100);
        return ptr;
    }

    void test_01() {
        // creates a unique_ptr to an int with value 20
        std::unique_ptr<int> ptr1 = std::make_unique<int>(20);
        std::cerr << "ptr1: " << *ptr1 << std::endl;

        int* ip1 = ptr1.get();
        (*ip1)++;
        std::cerr << "ip: " << *ip1 << std::endl;
        std::cerr << "ptr1: " << *ptr1 << std::endl;

        // second std::unique_ptr by moving 'ptr1' to 'ptr2',
        // 'ptr1' doesn't own the object anymore
        std::unique_ptr<int> ptr2 = std::move(ptr1);
        // std::cerr << "ptr1: " << *ptr1 << std::endl;  // crashes 
        std::cerr << "ptr2: " << *ptr2 << std::endl;

        std::unique_ptr<int> ptr3;
        ptr3 = std::move(ptr2);
        int* ip3 = ptr3.get();
        (*ip3)++;
        std::cerr << "ptr3: " << *ptr3 << std::endl;

        // retrieving a unique pointer from a function
        std::unique_ptr<int> ptr4 = createUniquePointer();

        // compare with this:
        // int* foo_createUniquePointer();
        // int* p = foo_createUniquePointer();  // who has to delete p ????
    }

    void test_02() {
        // creates a unique_ptr to an Dummy object
        std::unique_ptr<Dummy> ptr = std::make_unique<Dummy>();
    }

    void test_03() {
        // creates a unique_ptr to an array of 20 ints
        std::unique_ptr<int[]> ptr2 = std::make_unique<int[]>(20);
    }
}

int main_unique_pointer_02()
{
    using namespace UniquePointerZwei;
    test_01();
    test_02();

    return 0;
}

// =================================================================================
// End-of-File
// ===============================================================================
