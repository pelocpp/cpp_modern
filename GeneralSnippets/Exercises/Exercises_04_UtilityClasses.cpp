// =====================================================================================
// Exercises_04_UtilityClasses.cpp
// =====================================================================================

module modern_cpp_exercises:utility_classes;

namespace Exercises_UtilityClasses {

    namespace Exercise_01 {

        // generic visitor (matching all types in the variant)
        auto visitor = [](auto const& elem) -> void {
            std::cout << elem << std::endl;
        };

        static void testExercise_01a() {

            std::variant<int, double, std::string> var{ 123.456 };

            std::visit(visitor, var);

            var = 10;
            std::visit(visitor, var);

            var = std::string{ "ABCDE" };
            std::visit(visitor, var);
        }

        // improved generic visitor
        auto improvedVisitor = [](auto const& elem) {

            using Type = decltype(elem);

            using TypeWithoutReference =
                std::remove_reference<Type>::type;

            using TypeWithoutReferenceAndConst =
                std::remove_const<TypeWithoutReference>::type;

            if constexpr (std::is_same<TypeWithoutReferenceAndConst, int>::value == true)
            {
                std::cout << "int: " << elem << std::endl;
            }
            else if constexpr (std::is_same<TypeWithoutReferenceAndConst, double>::value == true)
            {
                std::cout << "double: " << elem << std::endl;
            }
            else if constexpr (std::is_same<TypeWithoutReferenceAndConst, std::string>::value == true)
            {
                std::cout << "std::string: " << elem << std::endl;
                size_t len = elem.size();
                std::cout << "Length: " << len << std::endl;
            }
            else
            {
                std::cout << "Unknown data type" << std::endl;
            }
        };

        static void testExercise_01b() {

            std::variant<int, double, std::string> var{ 123.456 };

            std::visit(improvedVisitor, var);

            var = 10;
            std::visit(improvedVisitor, var);

            var = std::string{ "ABCDE" };
            std::visit(improvedVisitor, var);
        }

        static void testExercise_01() {
            testExercise_01a();
            testExercise_01b();
        }
    }

    namespace Exercise_02 {

        static std::optional<int> toInt(const std::string& s)
        {
            std::optional<int> result{ std::nullopt };
            
            try
            {
                int n{ std::stoi(s) };

                // want input string to be consumed entirely (there are several ways
                // to accomplish this each with advantages and disadvantages)
                std::string tmp{ std::to_string(n) };
                if (tmp.length() != s.length())
                    throw std::invalid_argument("input string illegal");

                result = n;
            }
            catch (const std::invalid_argument&)
            {
                std::cerr << "Bad input: std::invalid_argument" << std::endl;
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Integer overflow: std::out_of_range" << std::endl;
            }

            return result;
        }

        template <typename T>
        std::optional<T> toNumber(std::string s)
        {
            std::optional<T> result{ std::nullopt };

            try
            {
                if constexpr (std::is_same<T, int>::value || std::is_same<T, short>::value)
                {
                    int i{ std::stoi(s) };
                    std::string tmp{ std::to_string(i) };
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(i);
                }
                if constexpr (std::is_same_v<T, long>)
                {
                    long l{ std::stol(s) };
                    std::string tmp{ std::to_string(l) };
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(l);
                }
                if constexpr (std::is_same_v<T, long long>)
                {
                    long long ll{ std::stoll(s) };
                    std::string tmp{ std::to_string(ll) };
                    if (tmp.length() != s.length())
                        throw std::invalid_argument("input string illegal");

                    result.emplace(ll);
                }
            }
            catch (const std::invalid_argument&)
            {
                std::cerr << "Bad input: std::invalid_argument" << std::endl;
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Integer overflow: std::out_of_range" << std::endl;
            }

            return result;
        }

        static void testExercise_03a() {
            std::optional<int> i1{ toInt("123") };
            if (i1.has_value()) {
                std::cout << i1.value() << std::endl;
            }

            std::optional<int> i2{ toInt("-987654321") };
            if (i2.has_value()) {
                std::cout << i2.value() << std::endl;
            }

            std::optional<int> i3{ toInt("123ABC") };
            if (i3.has_value()) {
                std::cout << i3.value() << std::endl;
            }

            std::optional<int> i4{ toInt("ABC123") };
            if (i4.has_value()) {
                std::cout << i4.value() << std::endl;
            }
        }

        static void testExercise_03b() {

            std::optional<short> i1{ toNumber<short>("32767") };
            if (i1.has_value()) {
                std::cout << i1.value() << std::endl;
            }

            std::optional<int> i2{ toNumber<int>("2147483647") };
            if (i2.has_value()) {
                std::cout << i2.value() << std::endl;
            }

            std::optional<long int> i3{ toNumber<long int>("2147483647") };
            if (i3.has_value()) {
                std::cout << i3.value() << std::endl;
            }

            std::optional<long long> i4{ toNumber<long long>("9223372036854775807") };
            if (i4.has_value()) {
                std::cout << i4.value() << std::endl;
            }
        }

        static void testExercise_03() {
            testExercise_03a();
            testExercise_03b();
        }
    }

    namespace Exercise_03 {

        // https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/

        static void testExercise_04a()
        {
            std::variant<int, std::string> myVariant;
            myVariant = 123;
            std::cout << std::get<int>(myVariant) << std::endl;
            myVariant = std::string("ABC");
            std::cout << std::get<std::string>(myVariant) << std::endl;
        }

        // ----------------------------------------------------------------------------------

        struct MyPrintVisitor
        {
            void operator()(const int& value) { std::cout << "int: " << value << std::endl; }
            void operator()(const std::string& value) { std::cout << "std::string: " << value << std::endl; }
        };

        // oder

        struct AllInOneVisitor
        {
            template <class T>
            void operator()(const T& value) { std::cout << value << std::endl; }
        };

        // oder

        struct MyModifyingVisitor
        {
            template <class T>
            void operator()(T& value) { value += value; }
        };

        // oder

        auto lambdaAllInOneVisitor = [](const auto& value) {
            std::cout << value << std::endl;
        };

        // ----------------------------------------------------------------------------------

        static void testExercise_04b()
        {
            std::variant<int, std::string> myVariant;
            myVariant = 123;
            std::visit(MyPrintVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(MyPrintVisitor{}, myVariant);

            myVariant = 123;
            std::visit(AllInOneVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(AllInOneVisitor{}, myVariant);

            myVariant = 123;
            std::visit(MyModifyingVisitor{}, myVariant);
            std::visit(MyPrintVisitor{}, myVariant);
            myVariant = std::string("456");
            std::visit(MyModifyingVisitor{}, myVariant);
            std::visit(MyPrintVisitor{}, myVariant);

            myVariant = 123;
            std::visit(lambdaAllInOneVisitor, myVariant);
            myVariant = std::string("456");
            std::visit(lambdaAllInOneVisitor, myVariant);
        }

        static void testExercise_04c()
        {
            std::vector<std::variant<int, std::string>> hetVec;

            hetVec.emplace_back(12);
            hetVec.emplace_back(std::string("34"));
            hetVec.emplace_back(56);
            hetVec.emplace_back(std::string("78"));

            // print them
            for (const auto& var : hetVec) {
                std::visit(MyPrintVisitor{}, var);
            }

            // modify them
            for (auto& var : hetVec) {
                std::visit(MyModifyingVisitor{}, var);
            }

            // print them again
            for (const auto& var : hetVec) {
                std::visit(MyPrintVisitor{}, var);
            }
        }

        template <typename... Types>
        class HeterogeneousContainer
        {
        private:
            std::vector<std::variant<Types...>> m_values;

        public:
            // visitor
            template <class TVisitor>
            void visit(TVisitor&& visitor) {
                for (auto& value : m_values) {
                    std::visit(visitor, value);
                }
            }

            // accessor
            std::vector<std::variant<Types...>>& Values() {
                return m_values;
            };
        };

        static void testExercise_04d()
        {
            HeterogeneousContainer<int, std::string> hetCont;

            hetCont.Values().emplace_back(12);
            hetCont.Values().emplace_back(std::string("34"));
            hetCont.Values().emplace_back(56);
            hetCont.Values().emplace_back(std::string("78"));

            // print them
            hetCont.visit(lambdaAllInOneVisitor);
            std::cout << std::endl;

            // modify them
            hetCont.visit(MyModifyingVisitor{});

            // print again
            hetCont.visit(lambdaAllInOneVisitor);
            std::cout << std::endl;
        }

        static void testExercise_04() {
            testExercise_04a();
            testExercise_04b();
            testExercise_04c();
            testExercise_04d();
        }
    }
}

void test_exercises_utility_classes()
{
    Exercises_UtilityClasses::Exercise_01::testExercise_01();
    Exercises_UtilityClasses::Exercise_02::testExercise_03();
    Exercises_UtilityClasses::Exercise_03::testExercise_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
