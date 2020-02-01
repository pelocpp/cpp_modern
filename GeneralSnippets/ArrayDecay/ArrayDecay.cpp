// =====================================================================================
// Array Decay
// =====================================================================================

#include <iostream>
#include <cassert>

namespace ArrayDecay {

    void DisplayValue(int* p) {
        std::cout << "New size of array by passing the value : ";
        std::cout << sizeof(p) << std::endl;
    }

    void DisplayPointer(int(*p)[11]) {
        std::cout << "New size of array by passing the pointer : ";
        std::cout << sizeof(p) << std::endl;
    }

    const int n = 11;
    void DisplayReference(int(&p)[n]) {
        std::cout << "New size of array by passing reference: ";

        p[5] = 99;

        std::cout << sizeof(p) << std::endl;
    }

    void test_01_decay() {
        int arr[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
        std::cout << "Actual size of array is : ";
        std::cout << sizeof(arr) << std::endl;
        DisplayValue(arr);
        DisplayPointer(&arr);

        DisplayReference(arr);

        for (int n : arr) {
            std::cout << n << ' ';
        }
    }


    // ONE
    // simple, dangerous and useless
    template<typename T>
    void as_pointer(const T* array) {
        // a pointer
        assert(array != nullptr);
        std::cout << "ONE  " << sizeof(array) << std::endl;
    };

    // TWO
    // for above const T array[] means the same
    // but and also , minimum array size indication might be given too
    // this also does not stop the array decay into T *
    // thus size information is lost
    template<typename T>
    void by_value_no_size(const T array[100]) {
        // decayed to a pointer
        assert(array != nullptr);
        std::cout << "TWO  " << sizeof(array) << std::endl;
    }

    // THREE
    // size information is preserved
    // but pointer is asked for
    template<typename T, size_t N>
    void pointer_to_array(const T(*array)[N])
    {
        // dealing with native pointer 
        assert(array != nullptr);
        std::cout << "THREE " << sizeof(array) << std::endl;
    }

    // FOUR
    // no C equivalent
    // array by reference
    // size is preserved
    template<typename T, size_t N>
    void reference_to_array(const T(&array)[N])
    {
        // array is not a pointer here
        // it is (almost) a container
        // most of the std:: lib algorithms 
        // do work on array reference, for example
        // range for requires std::begin() and std::end()
        // on the type passed as range to iterate over
        std::cout << "FOUR " << sizeof(array) << std::endl;

        for (auto&& elem : array)
        {
            std::cout << std::endl << elem;
        }
    }

    // const char* someValues[] { __TIME__, __DATE__, __TIMESTAMP__ };
    const int  someValues[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    void test_02_decay() {
        // ONE
        as_pointer(someValues);
        // TWO
        by_value_no_size(someValues);
        // THREE
        pointer_to_array(&someValues);
        // FOUR
        reference_to_array(someValues);
    }

    int main_array_decay() {

        test_01_decay();
        // test_02_decay();
        return 0;
    }
}

// int main:allocator()
int main_array_decay()
{
    using namespace ArrayDecay;
    //test_01();
    //test_02();
    //test_03();

    //test_04a();
    //test_04b();
    //test_04c();

   //  test_05a();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
