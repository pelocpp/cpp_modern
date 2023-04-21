// =====================================================================================
// Allocator02.cpp // Allocator
// =====================================================================================

module;

// GCC support
#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

module modern_cpp:allocator;

import :dummy;

namespace AllocatorWithObject {

    // Minimalistic C++11 allocator with debug output
    template <typename T>
    struct MyAlloc {

        // An allocator that is used to acquire/release memory
        // and to construct/destroy the elements in that memory.
        // The type must meet the requirements of Allocator.
        // The behavior is undefined if Allocator::value_type is not the same as T
        typedef T value_type;

        MyAlloc() = default;

        template <class TP>
        MyAlloc(const MyAlloc<TP>& alloc) {
            std::cout << __FUNCSIG__ << std::endl;
        }

        T* allocate(size_t n);
        void deallocate(T* p, size_t n);
    };

    template <class T>
    T* MyAlloc<T>::allocate(size_t n) {
        n = n * sizeof(T);
        std::cout << "allocating " << n << " bytes" << std::endl;
        return static_cast<T*>(::operator new(n));
    }

    template <class T>
    void MyAlloc<T>::deallocate(T* p, size_t n) {
        std::cout << "deallocating " << n * sizeof(T) << " bytes" << std::endl;
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

    /*
     * Note:
     *
     * Watch difference between executions with and without
     * 'vec.reserve' invocation
     */

    constexpr int AnotherMax = 5;

    void test_01a_allocator() {

        std::cout << "Insertion: push_back - Object by LValue reference" << std::endl;
        std::vector<Dummy, MyAlloc<Dummy>> vec;
        // vec.reserve(AnotherMax);  // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            Dummy dummy(n);
            vec.push_back(dummy);
        }
    }

    void test_01b_allocator() {

        std::cout << "Insertion: push_back - Object by RValue reference" << std::endl;
        std::vector<Dummy, MyAlloc<Dummy>> vec;
        // vec.reserve(AnotherMax); // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            vec.push_back(Dummy(n));
        }
    }

    void test_01c_allocator() {

        std::cout << "Insertion: emplace_back" << std::endl;
        std::vector<Dummy, MyAlloc<Dummy>> vec;
        // vec.reserve(AnotherMax);   // put into comments ... or not
        for (int n = 0; n < AnotherMax; ++n) {
            vec.emplace_back(n);
        }
    }
}

void main_allocator_02()
{
    using namespace AllocatorWithObject;
    test_01a_allocator();
    test_01b_allocator();
    test_01c_allocator();
}

// =====================================================================================
// End-of-File
// =====================================================================================
