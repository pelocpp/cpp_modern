// =====================================================================================
// std::common_type
// =====================================================================================

#include <iostream>
#include <type_traits>

namespace CommonType {

    template <typename T>
    class Number {
    private:
        T m_value;

    public:
        Number() : m_value(T{}) {}
        Number(T value) : m_value(value) {}

        T operator()() const { // functor
            return m_value;
        }
    };

    template <typename T, typename U>
    Number<typename std::common_type<T, U>::type> operator+ (
        const Number<T>& lhs,
        const Number<U>& rhs)
    {
        using result_type = typename std::common_type<T, U>::type;
        result_type result;
        result = lhs() + rhs();
        return result;
    }

    void test_commontype_01()
    {
        std::cout << "std::common_type demonstration:" << std::endl;

        Number<int> intNumber(123);
        std::cout << intNumber() << std::endl;

        Number<long> longNumber(321);
        std::cout << longNumber() << std::endl;

        Number<std::common_type<int, long>::type> result;
        result = intNumber() + longNumber();
        std::cout << result() << std::endl;

        Number<double> doublenumber(123.456);
        std::cout << doublenumber() << std::endl;

        Number<short> shortNumber(321);
        std::cout << shortNumber() << std::endl;

        Number<std::common_type<double, long>::type> anotherResult = shortNumber() + doublenumber();
        std::cout << anotherResult() << std::endl;
    }

    // do you notice the difference using operator+ between these two examples?
    void test_commontype_02()
    {
        std::cout << "More std::common_type demonstration:" << std::endl;

        Number<double> number(123.456);
        std::cout << number() << std::endl;

        Number<long> longNumber(321);
        std::cout << longNumber() << std::endl;

        Number<std::common_type<double, long>::type> result;
        result = number + longNumber;
        std::cout << result() << std::endl;
    }
}

void main_common_type()
{
    using namespace CommonType;
    test_commontype_01();
    test_commontype_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================