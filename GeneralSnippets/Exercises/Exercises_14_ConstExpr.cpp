// =====================================================================================
// Exercises_14_ConstExpr.cpp
// =====================================================================================

module modern_cpp_exercises:const_expr;

namespace Exercises_ConstExpr {

    namespace Exercise_01 {

        // int fromString(const char* str) { return 0; }
        // double fromString(const char* str) { return 0.0; } 
        // 
        // Error: overloaded function differs only by return type 
        // from 'int fromString(const char *)'

        class FromString
        {
        private:
            std::string m_str;

        public:
            FromString(const char* str) : m_str{ str } {}

            template <typename T>
            operator T()
            {
                if constexpr (std::is_same<T, int>::value)
                {
                    return std::stoi(m_str);
                }
                else if constexpr (std::is_same<T, float>::value)
                {
                    return std::stof(m_str);
                }
                else if constexpr (std::is_same<T, double>::value)
                {
                    return std::stod(m_str);
                }
            }
        };

        static void testExercise_01() {

            using namespace Exercises_ConstExpr;

            int n{ FromString{ "123" } };
            float f{ FromString{ "45.67f" } };
            double d{ FromString{ "89.123" } };

            std::cout << n << std::endl;
            std::cout << f << std::endl;
            std::cout << d << std::endl;

            auto n1{ FromString{ "123" } };
            auto f1{ FromString{ "45.67f" } };
            auto d1{ FromString{ "89.123" } };

            auto na{ FromString{ "123" }.operator int() };
            auto fa{ FromString{ "45.67f" }.operator float() };
            auto da{ FromString{ "89.123" }.operator double() };

            std::cout << na << std::endl;
            std::cout << fa << std::endl;
            std::cout << da << std::endl;

            std::cout << static_cast<int>(n1) << std::endl;
            std::cout << static_cast<float>(f1) << std::endl;
            std::cout << static_cast<double>(d1) << std::endl;
        }
    }

    namespace Exercise_02 {

        template<typename T1, typename T2>
        constexpr bool sameType(T1, T2)
        {
            return std::is_same<T1, T2>::value;
        }

        template<typename T1, typename T2, typename... TRest>
        constexpr bool sameType(T1 arg1, T2 arg2, TRest... args)
        {
            return std::is_same<decltype(arg1), decltype(arg2)>::value && sameType(arg2, args...);
        }

        // Oder

        //template<typename T1, typename T2, typename... TRest>
        //constexpr bool sameType(T1 arg1, T2 arg2, TRest... args)
        //{
        //    return std::is_same<T1, T2>::value && sameType(arg2, args...);
        //}

        static void testExercise_01()
        {
            constexpr bool result1{ sameType(43, false, "hello") };
            std::cout << std::boolalpha << result1 << std::endl;

            constexpr bool result2{ sameType(1, 2, 3, 4, 5, 6, 7, 8, 9) };
            std::cout << std::boolalpha << result2 << std::endl;
        }
    }
}

void test_exercises_constexpr()
{
    using namespace Exercises_ConstExpr;
    Exercise_01::testExercise_01();
    Exercise_02::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
