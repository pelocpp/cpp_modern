// =====================================================================================
// RAII01.cpp
// =====================================================================================

module modern_cpp:raii;

import :dummy;

namespace RAIIDemo {

    template <class TFinalizer>
    class RAII {
    public:
        // c'tor
        explicit RAII(TFinalizer finalizer)
            : m_finalizer{ finalizer }
        {
        }

        // d'tor
        ~RAII() {
            m_finalizer();
        }

        // prevent copy semantics
        RAII(const RAII&) = delete;
        RAII& operator= (const RAII&) = delete;

    private:
        TFinalizer m_finalizer;
    };

    static void test_01()
    {
        {
            Dummy* ptr = new Dummy{ 1 };
            if (ptr == nullptr) {
                return;
            }

            RAII raii{ [&]() { delete ptr; } };
        }

        std::cout << "Done." << std::endl;
    }

    static void test_02()
    {
        // test RAII idiom upon a loop break
        do {
            Dummy* ptr = new Dummy{ 1 };
            if (ptr == nullptr) {
                break;
            }

            RAII raii{ [&]() { delete ptr; } };
            break;
        } while (false);

        std::cout << "Done." << std::endl;
    }

    static void test_03()
    {
        // test RAII idiom upon exception being thrown
        try {
            Dummy* ptr = new Dummy{ 1 };
            if (ptr == nullptr) {
                return;
            }

            RAII raii{ [&]() { delete ptr; } };
            throw 99;
        }
        catch (int n) {
            std::cout << "Exception " << n << " occurred!" << std::endl;
        }

        std::cout << "Done." << std::endl;
    }

    static void test_04()
    {
        // test RAII idiom with two encapsulated resources:
        // Note order of destructor calls

        {
            Dummy* ptr1 = new Dummy{ 1 };
            Dummy* ptr2 = new Dummy{ 2 };

            RAII raii1{ [&]() { delete ptr1; } };
            RAII raii2{ [&]() { delete ptr2; } };
        }

        std::cout << "Done." << std::endl;
    }

    template <class TFinalizer>
    class RAIIContainer
    {
    public:
        RAIIContainer(TFinalizer&& finalizer) : m_raii{ finalizer } {}

    private:
        RAII<TFinalizer> m_raii;
    };

    static void test_05()
    {
        Dummy* ptr = new Dummy{ 1 };
        if (ptr == nullptr) {
            return;
        }

        {
            RAIIContainer cont{ [&]() { delete ptr; } };
        }

        std::cout << "Done." << std::endl;
    }
}

void main_raii()
{
    using namespace RAIIDemo;
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
