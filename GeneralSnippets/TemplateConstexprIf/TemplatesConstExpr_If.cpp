// =====================================================================================
// TemplatesConstExpr_If.cpp // Templates und bedingte Compilierung (if constexpr) 
// =====================================================================================

module modern_cpp:templates_constexpr_if;

namespace TemplateConstExprIf {

    template <typename T>
    class Adder
    {
    private:
        T m_val;

    public:
        Adder(T v) : m_val{ v } {}

        template <typename U>
        T addSingle(U x) const {
            return m_val + x;
        }

        template <typename U>
        T addToVector(U x)
        {
            // create a copy of the member vector
            T vecCopy(m_val);

            for (auto& n : vecCopy) {
                n += x;
            }
            return vecCopy;
        }

        // template member function
        template <typename U>
        T add(U x) const {
            if constexpr (std::is_same<T, std::vector<U>>::value) {

                // create a copy of the member vector
                T vecCopy(m_val);

                for (auto& n : vecCopy) {
                    n += x;
                }
                return vecCopy;
            }
            else {
                return m_val + x;
            }
        }
    };

    static void test_01() {
        Adder<int> intAdder(123);
        int n = intAdder.addSingle(456);
        std::cout << n << std::endl;

        Adder<float> floatAdder(1.5);
        float f = floatAdder.addSingle(2);
        std::cout << f << std::endl;

        Adder<std::string> stringAdder("ABC");
        std::string s = stringAdder.addSingle(std::string("XYZ"));
        std::cout << s << std::endl;

        std::vector<int> numbers{ 1, 2, 3 };
        Adder<std::vector<int>> intVecAdder(numbers);
        std::vector<int> numbersResult = intVecAdder.addToVector(10);
        for (int n : numbersResult)
            std::cout << n << ' ';
        std::cout << std::endl;

        std::vector<std::string> strings{ "A", "B", "C" };
        Adder<std::vector<std::string>> intStringAdder(strings);
        std::vector<std::string> stringResult =
            intStringAdder.addToVector(std::string{ "Z" });
        for (std::string s : stringResult)
            std::cout << s << ' ';
        std::cout << std::endl;
    }

    static void test_02() {
        Adder<int> intAdder(123);
        int n = intAdder.add(456);
        std::cout << n << std::endl;

        Adder<float> floatAdder(1.5);
        float f = floatAdder.add(2);
        std::cout << f << std::endl;

        Adder<std::string> stringAdder("ABC");
        std::string s = stringAdder.add(std::string("XYZ"));
        std::cout << s << std::endl;

        std::vector<int> numbers{ 1, 2, 3 };
        Adder<std::vector<int>> intVecAdder(numbers);
        std::vector<int> numbersResult = intVecAdder.add(10);
        for (int n : numbersResult)
            std::cout << n << ' ';
        std::cout << std::endl;

        std::vector<std::string> strings{ "A", "B", "C" };
        Adder<std::vector<std::string>> intStringAdder(strings);
        std::vector<std::string> stringResult =
            intStringAdder.add(std::string{ "Z" });
        for (std::string s : stringResult)
            std::cout << s << ' ';
        std::cout << std::endl;
    }
}

void main_constexpr_if()
{
    using namespace TemplateConstExprIf;
    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
