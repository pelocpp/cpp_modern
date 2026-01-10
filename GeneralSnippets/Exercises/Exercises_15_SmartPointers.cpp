// =====================================================================================
// Exercises_15_SmartPointers.cpp
// =====================================================================================

module;

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <cassert>

module modern_cpp_exercises:smart_pointers;

namespace Exercises_SmartPointers {

    namespace Exercise_01 {

        // =============================================================
        // Counting references :) 

        static void testExercise() {

            class X {};

            std::shared_ptr<X> pA;
            std::shared_ptr<X> pB;
            std::shared_ptr<X> pC;

            pA = std::make_shared<X>();     // use-count always starts at 1
            assert(pA.use_count() == 1);

            pB = pA;                        // make a copy of the pointer; use-count is now 2
            assert(pA.use_count() == 2);
            assert(pB.use_count() == 2);

            pC = std::move(pA);             // moving the pointer keeps the use-count at 2
            assert(pA == nullptr);
            assert(pB.use_count() == 2);
            assert(pC.use_count() == 2);

            pB = nullptr;                   // decrement the use-count back to 1

            assert(pA == nullptr);
            assert(pB == nullptr);
            assert(pC.use_count() == 1);
        }
    }

    namespace Exercise_02 {

        // =============================================================
        // Don't double-manage!

        static void testExercise() {

            class X
            {
            public:
                X() : m_value{ 123 } {}
                int getValue() const { return m_value; }

            private:
                int m_value;
            };

            std::shared_ptr<X> pA{ new X{} };    // use-count always starts at 1
            std::shared_ptr<X> pB;
            std::shared_ptr<X> pC;
            assert(pA.use_count() == 1);

            pB = pA;           // make a copy of the pointer; use-count is now 2
            assert(pA.use_count() == 2);
            assert(pB.use_count() == 2);

            pC = std::shared_ptr<X>{ pB.get() };
            // ERROR! Don't double-manage a raw pointer!
            // Give never the same pointer to a shared_ptr object again,
            // which would tell this shared_ptr to manage it -- twice!
            assert(pA.use_count() == 2);
            assert(pB.use_count() == 2);
            assert(pC.use_count() == 1);

            pC = nullptr;   // or pC.reset();
            // pC's use-count drops to zero,
            // shared_ptr calls "delete" on the X object
            assert(pA.use_count() == 2);
            assert(pB.use_count() == 2);
            assert(pC == nullptr);

            int value = (*pB).getValue();     // accessing the freed object yields undefined behavior
            std::cout << "Value: " << value << std::endl;
        }
    }

    namespace Exercise_03 {

        // =============================================================
        // Considering a "non-owning reference"

        class UnsafeWatcher
        {
        private:
            int* m_ptr;

        public:
            UnsafeWatcher() : m_ptr{ nullptr } {}

            void watch(const std::shared_ptr<int>& sp)
            {
                m_ptr = sp.get();
            }

            int currentValue() const
            {
                return *m_ptr;  // m_ptr might have been released !
            }
        };

        static void testExercise_01()
        {
            UnsafeWatcher watcher;

            {
                std::shared_ptr<int> sp{ std::make_shared<int>(123) };
                watcher.watch(sp);
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }

            std::cout << "Value: " << watcher.currentValue() << std::endl;
        }

        class HeavyAndSafeWatcher {
        private:
            std::shared_ptr<int> m_ptr;

        public:
            HeavyAndSafeWatcher() {}

            void watch(const std::shared_ptr<int>& sp)
            {
                m_ptr = sp;
            }

            int currentValue() const
            {
                return *m_ptr;  // m_ptr is always alive!
            }
        };

        static void testExercise_02()
        {
            HeavyAndSafeWatcher watcher;

            {
                std::shared_ptr<int> sp{ std::make_shared<int>(123) };
                watcher.watch(sp);
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }

            std::cout << "Value: " << watcher.currentValue() << std::endl;
        }

        class LightweightAndSafeWatcher {
        private:
            std::weak_ptr<int> m_ptr;

        public:
            LightweightAndSafeWatcher() = default;

            void watch(const std::shared_ptr<int>& sp)
            {
                m_ptr = sp;
            }

            int currentValue() const
            {
                // Now we can safely ask whether *m_ptr has been deallocated or not
                std::shared_ptr<int> sp{ m_ptr.lock() };
                if (sp != nullptr)
                {
                    return *sp;
                }
                else
                {
                    throw std::exception{ "No value available!" };
                }
            }
        };

        static void testExercise_03() {

            LightweightAndSafeWatcher watcher;

            {
                std::shared_ptr<int> sp{ std::make_shared<int>(123) };
                watcher.watch(sp);
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }

            try {
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }
            catch (const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }

        static void testExercise() {
            testExercise_01();
            testExercise_02();
            testExercise_03();
        }
    }

    namespace Exercise_04 {

        // =============================================================
        // MyString implementation using std::shared_ptr

        // Note:
        //     This is a theoretical implementation of the task.
        //     In practice, there is exactly one owner of the string within the class.
        //     Therefore, the class `std: :unique_ptr` would be the appropriate implementation method.

        // Note the side effects of both implementations:
        // 
        //     The Rule of Zero could be applied to the `MyStringSP` class.
        //     However, the resulting behavior of the `MyStringSP` class is incorrect,
        //     because copies of `MyStringSP` objects are not real copies (shallow-copy behavior)!
        // 
        //     The Rule of Zero is not applicable to the `MyStringUP` class,
        //     because attempting to copy or assign `MyStringUP` objects results in error messages.
        //     The copy constructor and the assignment operator must be explicitly implemented
        //     (with deep-copy behavior).
        // 
        //     In both implementations, a destructor can be omitted.
        //     The destructor of a `std::shared_ptr` or a `std::unique_ptr` object
        //     is automatically called as being a child object of a parent object in both cases.

        class MyStringSP
        {
        private:
            std::shared_ptr<char[]> m_string;
            std::size_t             m_length;

        public:
            // default c'tor
            MyStringSP() : m_length{} {}

            // user defined c'tor
            MyStringSP(const char* string)
            {
                m_length = std::strlen(string);
                m_string = std::make_shared<char[]>(m_length + 1);
                std::memcpy(m_string.get(), string, m_length + 1);  // incl. copying '\0'
            }

            // no destructor necessary

            // public interface
            void print()
            {
                if (m_string.get() == nullptr) {
                    std::println("<null>");
                }
                else {
                    std::println("{}", m_string.get());
                }
            }

            // getter
            std::size_t length() const { return m_length; }

            // subscript operator
            char& operator[] (int index) {

                if (index >= m_length) {
                    throw std::out_of_range("Wrong index!");
                }

                return m_string.get()[index];
            }

            // copy c'tor
            MyStringSP(const MyStringSP& other) {

                // shallow (flat) copy
                // m_string = other.m_string;
                // m_length = other.m_length;

                // or deep copy
                m_length = other.m_length;
                m_string = std::make_shared<char[]>(m_length + 1);
                std::memcpy(m_string.get(), other.m_string.get(), m_length + 1); // copying '\0'
            }

            MyStringSP& operator=(const MyStringSP& other) {

                if (this == &other) {
                    return *this;
                }

                // shallow (flat) copy
                // m_string = other.m_string;
                // m_length = other.m_length;

                // or deep copy
                m_length = other.m_length;
                m_string = std::make_shared<char[]>(m_length + 1);
                std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'

                return *this;
            }

            // move c'tor
            MyStringSP(MyStringSP&& other) noexcept {

                m_string = std::move(other.m_string);
                m_length = other.m_length;
                other.m_length = 0;
            }

            // move assignment
            MyStringSP& operator=(MyStringSP&& other) noexcept {

                if (this == &other) {
                    return *this;
                }

                m_string = std::move(other.m_string);
                m_length = other.m_length;
                other.m_length = 0;

                return *this;
            }
        };

        // =============================================================
        // MyString implementation using std::unique_ptr

        class MyStringUP
        {
        private:
            std::unique_ptr<char[]> m_string;
            std::size_t             m_length;

        public:
            // default c'tor
            MyStringUP() : m_length{} {}

            // user defined c'tor
            MyStringUP(const char* string)
            {
                m_length = std::strlen(string);
                m_string = std::make_unique<char[]>(m_length + 1);
                std::memcpy(m_string.get(), string, m_length + 1);  // copying '\0'
            }

            // no destructor necessary
            
            // public interface
            void print()
            {
                if (m_string.get() == nullptr) {
                    std::println("<null>");
                }
                else {
                    std::println("{}", m_string.get());
                }
            }

            // subscript operator
            char& operator[] (int index) {

                if (index >= m_length) {
                    throw std::out_of_range("Wrong index!");
                }

                return m_string.get()[index];
            }

            // copy c'tor
            MyStringUP(const MyStringUP& other) {

                m_length = std::strlen(other.m_string.get());
                m_string = std::make_unique<char[]>(m_length + 1);
                std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'
            }

            // copy assignment
            MyStringUP& operator=(const MyStringUP& other) {

                if (this == &other) {
                    return *this;
                }

                m_length = std::strlen(other.m_string.get());
                m_string = std::make_unique<char[]>(m_length + 1);
                std::memcpy(m_string.get(), other.m_string.get(), m_length + 1);  // copying '\0'

                return *this;
            }

            // move c'tor
            MyStringUP(MyStringUP&& other) noexcept {

                m_string = std::move(other.m_string);
                m_length = other.m_length;
                other.m_length = 0;
            }

            // move assignment
            MyStringUP& operator=(MyStringUP&& other) noexcept {

                if (this == &other) {
                    return *this;
                }

                m_string = std::move(other.m_string);
                m_length = other.m_length;
                other.m_length = 0;

                return *this;
            }
        };

        // =============================================================
        // test routines

        static void testExercise_00()
        {
            MyStringSP ms1{ };
            ms1.print();
            MyStringUP ms2{ };
            ms2.print();
        }

        static void testExercise_01()
        {
            MyStringSP ms1{ "123" };
            ms1.print();

            MyStringSP ms2{ "ABCDE" };
            ms2.print();

            ms1 = ms2;   // assignment 
            ms1.print();

            ms2[0] = '?';

            ms1.print();
            ms2.print();
        }

        static void testExercise_02()
        {
            MyStringSP ms1{ "ABCDE" };
            ms1.print();

            MyStringSP ms2{ ms1 };  // copy construction
            ms2.print();

            ms2[0] = '?';

            ms1.print();
            ms2.print();
        }

        static void testExercise_10()
        {
            MyStringUP ms1{ "123" };
            ms1.print();

            MyStringUP ms2{ "ABCDE" };
            ms2.print();

            ms1 = ms2;    // assignment 
            ms1.print();

            ms2[0] = '?';

            ms1.print();
            ms2.print();
        }

        static void testExercise_11()
        {
            MyStringUP ms1{ "ABCDE" };
            ms1.print();

            MyStringUP ms2{ ms1 };  // copy construction
            ms2.print();

            ms2[0] = '?';

            ms1.print();
            ms2.print();
        }

        static void testExercise_20()
        {
            MyStringSP ms1{ "ABCDE" };
            ms1.print();

            MyStringSP ms2{ ms1 };  // copy construction
            ms2.print();

            ms1 = ms2;              // copy assignment
            ms1.print();
        }

        static void testExercise_21()
        {
            MyStringSP ms1{ "ABCDE" };
            ms1.print();

            MyStringSP ms2{ std::move(ms1) };  // move construction
            ms1.print();
            ms2.print();

            ms1 = std::move(ms2);              // move assignment
            ms1.print();
            ms2.print();
        }

        static void testExercise_22()
        {
            MyStringUP ms1{ "ABCDE" };
            ms1.print();

            MyStringUP ms2{ ms1 };             // copy construction
            ms2.print();

            ms1 = ms2;                         // copy assignment
            ms1.print();
        }

        static void testExercise_23()
        {
            MyStringUP ms1{ "ABCDE" };
            ms1.print();

            MyStringUP ms2{ std::move(ms1) };  // move construction
            ms1.print();
            ms2.print();

            ms1 = std::move(ms2);              // move assignment
            ms1.print();
            ms2.print();
        }

        static void testExercise() {

            // default c'tors
            testExercise_00();

            // MyStringSP
            testExercise_01();  // testing assignment
            testExercise_02();  // testing copy construction

            // MyStringUP
            testExercise_10();  // testing assignment
            testExercise_11();  // testing copy construction

            // MyStringSP
            testExercise_20();  // testing copy semantics
            testExercise_21();  // testing move semantics

            // MyStringUP
            testExercise_22();  // testing copy semantics
            testExercise_23();  // testing move semantics
        }
    }

    namespace Exercise_05 {

        // =========================================================
        // helper method 'countDigits'

        static std::size_t countDigits(std::size_t n)
        {
            std::size_t count{};

            // do-while ensures that 0 is counted as 1 digit
            do {
                n /= 10;
                ++count;
            } while (n != 0);

            return count;
        }

        // =========================================================
        // Variant 1: return std::unique_ptr directly
        // (move semantics and/or copy-move elision behind the scenes)

        static std::unique_ptr<std::size_t[]> splitToDigits(
            std::size_t   number,
            std::size_t&  count,
            bool&         success)
        {
            count = countDigits(number);

            std::unique_ptr<std::size_t[]> digits{ std::make_unique<std::size_t[]>(count) };

            if (digits == nullptr) {
                success = false;
                return digits;
            }
            else {
                std::size_t index{};
                do {
                    std::size_t digit = number % 10;
                    number /= 10;
                    digits[count - index - 1] = digit;
                    ++index;
                } while (number != 0);

                success = true;
                return digits;
            }
        }

        // =========================================================
        // Variant 2: return values by reference parameters

        static bool splitToDigitsByRef(
            std::size_t                     number,
            std::unique_ptr<std::size_t[]>& digits,
            std::size_t&                    count)
        {
            count = countDigits(number);

            digits = std::make_unique<std::size_t[]>(count);

            if (digits == nullptr) {
                return false;
            }
            else {
                std::size_t index{};
                do {
                    std::size_t digit = number % 10;
                    number /= 10;
                    digits[count - index - 1] = digit;
                    ++index;
                } while (number != 0);

                return true;
            }
        }

        // =========================================================
        // Variant 3: struct

        struct DigitsSplitting
        {
            std::size_t                    m_number;
            std::unique_ptr<std::size_t[]> m_digits;
            std::size_t                    m_count;
            bool                           m_success;
        };

        static DigitsSplitting splitToDigits(std::size_t number)
        {
            DigitsSplitting splitting{ number };

            auto count{ countDigits(number) };

            std::unique_ptr<std::size_t[]> digits{ std::make_unique<std::size_t[]>(count) };

            if (digits == nullptr) {
                splitting.m_success = false;
                return splitting;
            }
            else {
                std::size_t index{};

                do {
                    std::size_t digit = number % 10;
                    number /= 10;
                    digits[count - index - 1] = digit;
                    ++index;
                } while (number != 0);

                splitting.m_digits = std::move(digits);
                splitting.m_count = count;
                splitting.m_success = true;

                return splitting;
            }
        }

        // =========================================================
        // Variant 4: std::tuple

        using SplittedDigitsTuple =
            std::tuple<std::size_t, std::unique_ptr<std::size_t[]>, std::size_t, bool>;

        static SplittedDigitsTuple splitToDigitsTuple(std::size_t number)
        {
            SplittedDigitsTuple splitting{ number, nullptr, 0, false };

            auto count{ countDigits(number) };

            auto digits{ std::make_unique<std::size_t[]>(count) };

            if (digits == nullptr) {
                return splitting;
            }
            else {
                std::size_t index{};

                do {
                    std::size_t digit = number % 10;
                    number /= 10;
                    digits[count - index - 1] = digit;
                    ++index;
                } while (number != 0);

                std::get<1>(splitting) = std::move(digits);
                std::get<2>(splitting) = count;
                std::get<3>(splitting) = true;

                return splitting;
            }
        }

        // =========================================================
        // Variant 5: std::optional

        using SplittedDigitsPair =
            std::pair<std::unique_ptr<std::size_t[]>, std::size_t>;

        static std::optional<SplittedDigitsPair> splitToDigitsOptional(std::size_t number)
        {
            std::optional<SplittedDigitsPair> result{};

            auto count{ countDigits(number) };

            auto digits{ std::make_unique<std::size_t[]>(count) };

            if (digits == nullptr) {
                return result;
            }
            else {
                std::size_t index{};

                do {
                    std::size_t digit = number % 10;
                    number /= 10;
                    digits[count - index - 1] = digit;
                    ++index;
                } while (number != 0);

                result = std::pair{ std::move(digits) , count };

                return result;
            }
        }

        // =========================================================

        static void test_returning_unique_ptr_variant_01()
        {
            // return std::unique_ptr directly
            // (Move Semantics or Copy-Move Elision)

            std::size_t number{ 12345 };
            std::size_t count{};
            bool success{};

            std::unique_ptr<std::size_t[]> buffer{ splitToDigits(number, count, success) };

            if (success) {

                std::span<size_t> digits{ buffer.get(), count };

                std::println("Splitting of {}:", number);
                for (std::size_t i{}; auto digit : digits) {

                    std::println("{}: {}", i, digit);
                    ++i;
                }
            }
        }

        static void test_returning_unique_ptr_variant_02()
        {
            // pass all parameters by reference

            std::size_t number{ 54321 };
            std::size_t count{};
            std::unique_ptr<std::size_t[]> buffer{};

            bool success{ splitToDigitsByRef(number, buffer, count) };

            if (success) {

                std::span<size_t> digits{ buffer.get(), count };

                std::println("Splitting of {}:", number);
                for (std::size_t i{}; auto digit : digits) {

                    std::println("{}: {}", i, digit);
                    ++i;
                }
            }
        }

        static void test_returning_unique_ptr_variant_03()
        {
            // returning a struct

            std::size_t number{ 13524 };

            DigitsSplitting splitting{ splitToDigits(number) };

            if (splitting.m_success) {

                std::span<size_t> digits{ splitting.m_digits.get(), splitting.m_count };

                std::println("Splitting of {}:", number);
                for (std::size_t i{}; auto digit : digits) {

                    std::println("{}: {}", i, digit);
                    ++i;
                }
            }
        }

        static void test_returning_unique_ptr_variant_04()
        {
            // returning a tuple

            std::size_t number{ 53142 };

            const auto& [digit, buffer, count, success] { splitToDigitsTuple(number) };

            if (success) {

                std::span<size_t> digits{ buffer.get(), count };

                std::println("Splitting of {}:", number);
                for (std::size_t i{}; auto digit : digits) {

                    std::println("{}: {}", i, digit);
                    ++i;
                }
            }
        }

        static void test_returning_unique_ptr_variant_05()
        {
            // returning a std::optional

            std::size_t number{ 15243 };

            auto result{ splitToDigitsOptional(number) };

            if (result.has_value()) {

                const auto& [buffer, count] = result.value();

                std::span<size_t> digits{ buffer.get(), count };

                std::println("Splitting of {}:", number);
                for (std::size_t i{}; auto digit : digits) {

                    std::println("{}: {}", i, digit);
                    ++i;
                }
            }
            std::println();
        }

        // =========================================================

        void testExercise()
        {
            test_returning_unique_ptr_variant_01();
            test_returning_unique_ptr_variant_02();
            test_returning_unique_ptr_variant_03();
            test_returning_unique_ptr_variant_04();
            test_returning_unique_ptr_variant_05();
        }
    }
}

void test_exercises_smartpointer()
{
    using namespace Exercises_SmartPointers;

    //Exercise_01::testExercise();
    //// Exercise_02::testExercise();   // crashes when executed
    //Exercise_03::testExercise();
    //Exercise_04::testExercise();
    Exercise_05::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
