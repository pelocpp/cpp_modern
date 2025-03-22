// =====================================================================================
// CommonType.cpp // std::common_type
// =====================================================================================

module modern_cpp:common_type;

namespace CommonType {

    template <typename T>
    class Number {
    private:
        T m_value;

    public:
        Number() : Number{ T{} } {}

        Number(T value) : m_value{ value } {}

        T operator()() const {
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

    // or with trailing return type notation:
    //template <typename T, typename U>
    //auto operator+ (
    //    const Number<T>& lhs,
    //    const Number<U>& rhs) -> Number<typename std::common_type<T, U>::type>
    //{
    //    using result_type = typename std::common_type<T, U>::type;
    //    result_type result;
    //    result = lhs() + rhs();
    //    return result;
    //}

    static void test_commontype_01()
    {
        std::cout << "std::common_type demonstration:" << std::endl;

        Number<int> intNumber(123);
        std::cout << intNumber() << std::endl;

        Number<long> longNumber(321);
        std::cout << longNumber() << std::endl;

        Number<std::common_type<int, long>::type> result;
        result = intNumber() + longNumber();
        std::cout << result() << std::endl;

        Number<short> shortNumber(321);
        std::cout << shortNumber() << std::endl;

        Number<double> doubleNumber(123.456);
        std::cout << doubleNumber() << std::endl;

        Number<std::common_type<short, double>::type> anotherResult = shortNumber() + doubleNumber();
        std::cout << anotherResult() << std::endl;
    }

    // do you notice the difference using operator+ between these two examples?
    // (hint: the debugger may help ...)
    static void test_commontype_02()
    {
        std::cout << "More std::common_type demonstration:" << std::endl;

        Number<double> doubleNumber(123.456);
        std::cout << doubleNumber() << std::endl;

        Number<long> longNumber(321);
        std::cout << longNumber() << std::endl;

        Number<std::common_type<double, long>::type> result;
        result = doubleNumber + longNumber;
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
