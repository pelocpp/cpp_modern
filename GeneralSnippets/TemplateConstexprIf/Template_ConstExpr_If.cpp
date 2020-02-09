// =====================================================================================
// Templates und bedingte Compilierung (if constexpr) 
// =====================================================================================

#include <iostream>
#include <vector>
#include <string>

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
            T copy(m_val);

            for (auto& n : copy) {
                n += x;
            }
            return copy;
        }

        template <typename U>
        T add(U x) const {
            if constexpr (std::is_same_v<T, std::vector<U>>) {
            // if constexpr (std::is_same<T, std::vector<U>>::value) {

                // create a copy of the member vector
                T copy(m_val);

                for (auto& n : copy) {
                    n += x;
                }
                return copy;
            }
            else {
                return m_val + x;
            }
        }
    };

    void test_01_constexpr_if () {

        Adder<int> intAdder(121);
        int n = intAdder.addSingle(212);
        std::cout << n << std::endl;

        float f = Adder<float>{1.5}.addSingle(2);
        std::cout << f << std::endl;

        std::string s = 
            Adder<std::string>{ std::string ("ABC")}.addSingle(std::string("XYZ"));
        std::cout << s << std::endl;

        std::vector<int> numbers{ 1, 2, 3 };
        std::vector<int> numbersResult = 
            Adder<std::vector<int>>{numbers}.addToVector(10);
        for (int elem : numbersResult)
            std::cout << elem << ' ';
        std::cout << std::endl;

        std::vector<std::string> stringVec{ "A", "B", "C" };
        std::vector<std::string> stringResult = 
            Adder<std::vector<std::string>>{stringVec}.addToVector(std::string{ "Z" });
        for (std::string s : stringResult)
            std::cout << s << ' ';
    }

    void test_02_constexpr_if() {
        Adder<int> intAdder(121);
        int n = intAdder.add(212);
        std::cout << n << std::endl;

        float f = Adder<float>{ 1.5 }.add(2);
        std::cout << f << std::endl;

        std::string s =
            Adder<std::string>{ std::string("ABC") }.add(std::string("XYZ"));
        std::cout << s << std::endl;

        std::vector<int> numbers{ 1, 2, 3 };
        std::vector<int> numbersResult =
            Adder<std::vector<int>>{ numbers }.add(10);
        for (int elem : numbersResult)
            std::cout << elem << ' ';
        std::cout << std::endl;

        std::vector<std::string> stringVec{ "A", "B", "C" };
        std::vector<std::string> stringResult =
            Adder<std::vector<std::string>>{ stringVec }.add(std::string{ "Z" });
        for (std::string s : stringResult)
            std::cout << s << ' ';
    }
}

int main_constexpr_if ()
{
    using namespace TemplateConstExprIf;
    test_01_constexpr_if();
    std::cout << std::endl;
    test_02_constexpr_if();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
