// =====================================================================================
// Allocator
// =====================================================================================

#include <cstddef>
#include <new>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "../Global/Dummy.h"

namespace Allocator {

    void test_01_allocator() {

        std::allocator<int> myIntAlloc;    // default allocator for ints
        int* ip = myIntAlloc.allocate(3);  // space for three ints
        *ip = 123;       // access memory (write)
        *(ip+1) = 456;   // access memory (write)
        *(ip+2) = 789;   // access memory (write)

        std::cout << ip[0] << std::endl;   // access memory (read)
        std::cout << ip[1] << std::endl;   // access memory (read)
        std::cout << ip[2] << std::endl;   // access memory (read)

        // note: size (2. parameter for deallocate not necessarily needed, but:
        // std::allocator is an abstraction over an underlying memory model

        myIntAlloc.deallocate(ip, 3);  // deallocate space for ints
    }

    // Minimalistic C++11 allocator with debug output
    template <typename Tp>
    struct MyAlloc {

        // An allocator that is used to acquire/release memory
        // and to construct/destroy the elements in that memory.
        // The type must meet the requirements of Allocator.
        // The behavior is undefined if Allocator::value_type is not the same as Tp
        typedef Tp value_type;

        MyAlloc() = default;

        template <class T>
        MyAlloc(const MyAlloc<T>& alloc) {
            // std::cout << __FUNCSIG__ << std::endl;
        }

        Tp* allocate(std::size_t n);
        void deallocate(Tp* p, std::size_t n);
    };

    template <class Tp>
    Tp* MyAlloc<Tp>::allocate(std::size_t n) {
        n = n * sizeof(Tp);
        std::cout << "allocating " << n << " bytes" << std::endl;
        return static_cast<Tp*>(::operator new(n));
    }

    template <class Tp>
    void MyAlloc<Tp>::deallocate(Tp* p, std::size_t n) {
        std::cout << "deallocating " << n * sizeof(Tp) << " bytes" << std::endl;
        ::operator delete(p);
    }

    template <class T, class U>
    bool operator==(const MyAlloc<T>&, const MyAlloc<U>&) { 
        return true; 
    }

    template <class T, class U>
    bool operator!=(const MyAlloc<T>&, const MyAlloc<U>&) { 
        return false; 
    }

    constexpr int Max = 50;

    void test_02_allocator() {

        std::cout << "Not using reserve: \n";

        std::vector<int, MyAlloc<int>> v1;

        for (int n = 0; n < Max; ++n) {
            std::cout << "    ==> push_back(" << n << ")" << std::endl;
            v1.push_back(n);
        }
    }

    void test_03_allocator() {

        std::cout << "Using reserve: \n";

        std::vector<int, MyAlloc<int>> v1;
        v1.reserve(Max);

        for (int n = 0; n < Max; ++n) {
            std::cout << "    ==> push_back(" << n << ")" << std::endl;
            v1.push_back(n);
        }
    }

    /*
    * Note:
    *
    * a) Watch difference between executions with and without
    *    'vec.reserve' invocation
    * 
    * b) Watch difference between vector containers with and without
    *    user-defined allocator
    */

    constexpr int AnotherMax = 5;

    void test_04a_allocator() {

        std::cout << "Insertion: push_back - Object by LValue reference" << std::endl;

        // std::vector<Dummy> vec;
        std::vector<Dummy, MyAlloc<Dummy>> vec;

        // vec.reserve(AnotherMax);  // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            Dummy dummy(n);
            vec.push_back(dummy);
        }
    }

    void test_04b_allocator() {

        std::cout << "Insertion: push_back - Object by RValue reference" << std::endl;

        // std::vector<Dummy> vec;
        std::vector<Dummy, MyAlloc<Dummy>> vec;

        vec.reserve(AnotherMax); // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            vec.push_back(Dummy(n));
        }
    }

    void test_04c_allocator() {

        std::cout << "Insertion: emplace_back" << std::endl;

        // std::vector<Dummy> vec;
        std::vector<Dummy, MyAlloc<Dummy>> vec;

        vec.reserve(AnotherMax);   // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            vec.emplace_back(n);
        }
    }
}

int main_allocator()
{
    using namespace Allocator;
    test_01_allocator();
    test_02_allocator();
    test_03_allocator();

    test_04a_allocator();
    test_04b_allocator();
    test_04c_allocator();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
