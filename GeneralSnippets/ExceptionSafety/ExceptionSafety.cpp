// =====================================================================================
// ExceptionSafety.cpp // Exception Safety
// =====================================================================================

module modern_cpp:exception_safety;

namespace ExceptionSafety {

    class TwoPointers
    {
    private:
        std::unique_ptr<int> m_pi;
        std::unique_ptr<double> m_pd;

    public:
        TwoPointers(int* pi, double* pd) 
            : m_pi{ pi }, m_pd{ pd }
        {}
    };

    static void test_exception_safety()
    {
        TwoPointers tp { new int(123), new double(123.456) };
    }

    class StrongExceptionSafety {
    
        StrongExceptionSafety& operator= (const StrongExceptionSafety& other) {
            StrongExceptionSafety temp{ other };
            temp.swap(*this);
            return *this;
        }

        void swap(StrongExceptionSafety& other) noexcept {}
    };
}

void main_exception_safety()
{
}

// =====================================================================================
// End-of-File
// =====================================================================================
