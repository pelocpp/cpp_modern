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

        void testExercise_01() {

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

        void testExercise_02() {

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

            pC = std::shared_ptr<X>(pB.get());
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

        struct X;
        struct Y;

        struct X
        {
            std::shared_ptr<Y> m_spY{};
        };

        struct Y
        {
            std::shared_ptr<X> m_spX{};
        };

        void testExercise_03() {

            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

            {
                std::shared_ptr<X> sp1{ std::make_shared<X>() };
                std::shared_ptr<Y> sp2{ std::make_shared<Y>() };

                sp1->m_spY = sp2;
                sp2->m_spX = sp1;

                std::cout << "UseCount sp1: " << sp1.use_count() << std::endl;
                std::cout << "   UseCount sp1->m_spY: " << sp1->m_spY.use_count() << std::endl;

                std::cout << "UseCount sp2: " << sp2.use_count() << std::endl;
                std::cout << "   UseCount sp2->m_spX: " << sp2->m_spX.use_count() << std::endl;
            }

            std::cout << "Done." << std::endl;
        }
    }

    namespace Exercise_04 {

        // =============================================================
        // Considering a "non-owning reference"

        class UnsafeWatcher {
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

        void testExercise_04a()
        {
            UnsafeWatcher watcher;

            {
                std::shared_ptr<int> sp = std::make_shared<int>(123);
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

        void testExercise_04b()
        {
            HeavyAndSafeWatcher watcher;

            {
                std::shared_ptr<int> sp = std::make_shared<int>(123);
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
                // Now we can safely ask whether *m_ptr has been
                // deallocated or not.
                if (std::shared_ptr<int> sp; (sp = m_ptr.lock()) != nullptr)
                {
                    return *sp;
                }
                else
                {
                    throw std::exception{ "No value available!" };
                }
            }
        };

        void testExercise_04c() {

            LightweightAndSafeWatcher watcher;

            {
                std::shared_ptr<int> sp = std::make_shared<int>(123);
                watcher.watch(sp);
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }

            try {
                std::cout << "Value: " << watcher.currentValue() << std::endl;
            }
            catch (std::exception ex) {
                std::cout << ex.what() << std::endl;
            }
        }

        void testExercise_04() {
            testExercise_04a();
            testExercise_04b();
            testExercise_04c();
        }
    }
}

void test_exercises_smartpointer()
{
    using namespace Exercises_SmartPointers;
    Exercise_01::testExercise_01();
    // Exercise_02::testExercise_02();   // crashes when executed
    Exercise_03::testExercise_03();
    Exercise_04::testExercise_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
