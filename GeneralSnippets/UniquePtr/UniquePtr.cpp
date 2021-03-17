// ===============================================================================
// std::unique_ptr
// ===============================================================================

#include <iostream>
#include <memory>

namespace UniquePointer {

    std::unique_ptr<int> loadUniquePointer()
    {
        std::unique_ptr<int> ptr = std::make_unique<int>(100);
        return ptr;
    }

    void storeUniquePointer(std::unique_ptr<int>& ptr)
    {
        std::cout << "*ptr:    " << *ptr << std::endl;
        (*ptr)++;
        std::cout << "*ptr:    " << *ptr << std::endl;

        // take ownership right now:
        // std::unique_ptr<int> ptr2 = std::move(ptr);
    }

    void test_01() {

        // create a unique_ptr to an int with value 123
        std::unique_ptr<int> ptr1 = std::unique_ptr<int>(new int{ 123 });
        // or
        // std::unique_ptr<int> ptr1 = std::make_unique<int>(123);

        // access value behind smart pointer
        std::cout << "*ptr1:   " << *ptr1 << std::endl;

        // access value using raw pointer
        int* ip1 = ptr1.get();
        (*ip1)++;
        std::cout << "*ip:     " << *ip1 << std::endl;

        // access value - again - behind smart pointer
        std::cout << "*ptr1:   " << *ptr1 << std::endl;

        // second std::unique_ptr by moving 'ptr1' to 'ptr2',
        // 'ptr1' doesn't own the object anymore
        std::unique_ptr<int> ptr2 = std::move(ptr1);
        // std::cout << "*ptr1: " << *ptr1 << std::endl;  // crashes 
        std::cout << "*ptr2:   " << *ptr2 << std::endl;

        std::unique_ptr<int> ptr3;
        ptr3 = std::move(ptr2);
        int* ip3 = ptr3.get();
        (*ip3)++;
        std::cout << "*ptr3:   " << *ptr3 << std::endl;

        // retrieving a unique pointer from a function
        std::unique_ptr<int> ptr4 = loadUniquePointer();
        std::cout << "*ptr4:   " << *ptr4 << std::endl;

        // provide a function with a unique pointer: who owns the pointer now?
        storeUniquePointer(ptr4);

        // does this work?
        std::cout << "*ptr4:   " << *ptr4 << std::endl;
    }

    void test_02() {
        // creates a unique_ptr to an array of 20 ints
        std::unique_ptr<int[]> ptr = std::make_unique<int[]>(20);
    }
}

void main_unique_ptr()
{
    using namespace UniquePointer;
    test_01();
    test_02();
}

// =================================================================================
// End-of-File
// =================================================================================
