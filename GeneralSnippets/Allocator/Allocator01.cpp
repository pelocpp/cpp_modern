// =====================================================================================
// Allocator01.cpp // Allocator
// =====================================================================================

module;

// GCC support
#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

module modern_cpp:allocator;

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

    constexpr int Max = 50;

    void test_02_allocator() {

        std::vector<int, MyAlloc<int>> vec;
        // v1.reserve(Max);  // put into comments ... or not

        for (int n = 0; n < Max; ++n) {
            std::cout << "    ==> push_back(" << n << ")" << std::endl;
            vec.push_back(n);
        }
    }
}

void main_allocator_01()
{
    using namespace Allocator;
    test_01_allocator();
    test_02_allocator();
}

// =====================================================================================
// End-of-File
// =====================================================================================
