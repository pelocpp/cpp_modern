// =====================================================================================
// Exercises_02_Lambdas.cpp
// =====================================================================================

module modern_cpp_exercises:lambdas;

import std;

namespace Exercises_Lambdas {

    namespace Exercise_01 {

        static bool evenOrOdd(int val) {

            if ((val % 2) == 0) {
                std::cout << val << " is even." << std::endl;
                return true;
            }
            else {
                std::cout << val << " is odd." << std::endl;
                return false;
            }
        }

        struct EvenOrOdd
        {
            bool operator() (int val) const {

                if ((val % 2) == 0) {
                    std::cout << val << " is even." << std::endl;
                    return true;
                }
                else {
                    std::cout << val << " is odd." << std::endl;
                    return false;
                }
            }
        };

        auto lambda = [](int val) -> bool {

            if ((val % 2) == 0) {
                std::cout << val << " is even." << std::endl;
                return true;
            }
            else {
                std::cout << val << " is odd." << std::endl;
                return false;
            }
        };

        static void testExercise_01a() {

            // testing C-style function
            int value = 14;
            auto result = evenOrOdd(value);
            std::cout 
                << "evenOrOdd of " << value << ": " 
                << std::boolalpha << result << std::endl;

            // testing callable object
            EvenOrOdd callableObj;
            value = 15;
            result = callableObj(value);
            std::cout
                << "evenOrOdd of " << value << ": "
                << std::boolalpha << result << std::endl;

            // testing lambda
            value = 16;
            result = lambda(value);
            std::cout
                << "evenOrOdd of " << value << ": "
                << std::boolalpha << result << std::endl;
        }

        static void testExercise_01b() {

            std::vector<int> values(20);

            std::generate(
                std::begin(values),
                std::end(values),
                [count = 1]() mutable { return count++; }
            );

            // function
            std::for_each(
                std::begin(values), 
                std::end(values),
                evenOrOdd
            );

            // lambda
            std::for_each(
                std::begin(values), 
                std::end(values), 
                [] (int val) {
                    if ((val % 2) == 0) {
                        std::cout << val << " is even." << std::endl;
                    }
                    else {
                        std::cout << val << " is odd." << std::endl;
                    }
                }
            );

            // callable object
            std::for_each(
                std::begin(values),
                std::end(values),
                EvenOrOdd{}
            );
        }

        static void testExercise_01c() {

            std::vector<int> values(20);

            std::generate(
                std::begin(values),
                std::end(values),
                [count = 1]() mutable { return count++; }
            );

            // 'divisor' defined within capture clause 
            std::for_each(
                std::begin(values), 
                std::end(values),
                [divisor = 3] (int val) {
                    if (!(val % divisor)) {
                        std::cout << val << " can be divided by " << divisor << std::endl;
                    }
                    else {
                        std::cout << val << " cannot be divided by " << divisor << std::endl;
                    }
                }
            );
            std::cout << std::endl;

            // or 'divisor' defined in outer context (scope) 
            int divisor = 5;

            // capture context by value (reference & would work also)
            std::for_each(
                std::begin(values),
                std::end(values),
                [=] (int val) {
                    if (!(val % divisor)) {
                        std::cout << val << " can be divided by " << divisor << std::endl;
                    }
                    else {
                        std::cout << val << " cannot be divided by " << divisor << std::endl;
                    }
                }
            );
        }

        static void testExercise()
        {
            testExercise_01a();
            testExercise_01b();
            testExercise_01c();
        }
    }

    namespace Exercise_02 {

        static std::map<char, std::function<double(double, double)>> createCalculator() {

            std::map<char, std::function<double(double, double)>> map;
            map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
            map.insert(std::make_pair('-', [](double a, double b) { return a - b; }));
            map.insert(std::make_pair('*', [](double a, double b) { return a * b; }));
            map.insert(std::make_pair('/', [](double a, double b) { return a / b; }));
            return map;
        }

        // or more compact

        static std::map<char, std::function<double(double, double)>> createCalculatorEx() {

            std::map<char, std::function<double(double, double)>> map;
            map['+'] = [](double a, double b) { return a + b; };
            map['-'] = [](double a, double b) { return a - b; };
            map['*'] = [](double a, double b) { return a * b; };
            map['/'] = [](double a, double b) { return a / b; };
            return map;
        }

        // or still more compact

        static std::map<char, std::function<double(double, double)>> createCalculatorExEx()
        {
            return {
                { '+', [](double a, double b) {return a + b; } },
                { '-', [](double a, double b) {return a - b; } },
                { '*', [](double a, double b) {return a * b; } },
                { '/', [](double a, double b) {return a / b; } }
            };
        }

        static void testExercise_02a() {

            std::map<char, std::function<double(double, double)>> calculator = createCalculator();
            double op1, op2;
            char op;

            std::cout << "Enter first Operand: ";
            std::cin >> op1;
            std::cout << "Enter second Operand: ";
            std::cin >> op2;
            std::cout << "Enter operation (+, -, *, /): ";
            std::cin >> op;

            // do the math
            double result = calculator[op](op1, op2);
            std::cout << "Result: " << op1 << ' ' << op << ' ' << op2 << " = " << result << '.' << std::endl;
        };

        static void testExercise_02b() {

            std::map<char, std::function<double(double, double)>> calculator = createCalculator();

            // do some math operations
            std::cout << "1.5 + 2.7 = " << calculator['+'](1.5, 2.7) << std::endl;
            std::cout << "1.5 - 2.7 = " << calculator['-'](1.5, 2.7) << std::endl;
            std::cout << "1.5 * 2.7 = " << calculator['*'](1.5, 2.7) << std::endl;
            std::cout << "1.5 / 2.7 = " << calculator['/'](1.5, 2.7) << std::endl;

            // add a new operation
            calculator.insert(std::make_pair('^', [](double a, double b) { return std::pow(a, b); }));
            std::cout << "1.5 ^ 2.5 = " << calculator['^'](1.5, 2.5) << std::endl;
        };

        static void testExercise()
        {
            // testExercise_02a();  // needs console input
            testExercise_02b();
        }
    }

    namespace Exercise_03 {

        static void testExercise_03a()
        {
            // Output:
            // Variable: 1
            // Variable: 2
            // Variable: 3
            // Variable: 1

            // When the lambda is called, the lambda captures a copy of @variable.
            // When the lambda increments @variable from 1 to 2 and 3, it increments its own copy, not the original value.
            // But: The original value of @variable is preserved across calls to the lambda!

            int variable{ 1 };

            auto lambda{ [variable]() mutable {
                std::cout << "Variable: " << variable << std::endl;
                variable++;
                }
            };

            // invoke lambda three times
            lambda();
            lambda();
            lambda();

            std::cout << "Variable: " << variable << std::endl << std::endl;
        }

        static void testExercise_03b()
        {
            // Output:
            // 10
            // 11
            // 12
            // 13
            // 14
            // 15
            // 16
            // 17
            // 15

            auto L = [val = 10]() mutable { std::cout << val++ << std::endl; };
            L();
            L();
            L();
            L();
            L();
            auto LC = L;
            LC();
            LC();
            LC();
            L();
        }

        static void testExercise_03c()
        {
            // Output:
            // 1
            // 2
            // 2

            // Rather than printing 1, 2, 3, the code prints 2 twice. When we created @otherCount as a copy of @count,
            // we created a copy of @count in its current state. @count‘s i was 1, so @otherCount‘s i is 1 as well.
            // Since @otherCount is a copy of @count, they each have their own @i.

            int i{ };

            // create a lambda named 'count'
            auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

            // invoke lambda
            count();

            // create a copy of lambda 'count'
            auto otherCount{ count };

            // invoke both lambda 'count' and the copy
            count();
            otherCount();
            std::cout << std::endl;
        }

        static void invoke(const std::function<void(void)>& fn)
        {
            fn();
        }

        static void testExercise_03d()
        {
            // Output:
            // 1
            // 1
            // 1

            // This exhibits the same problem as the prior example in a more obscure form:
            // When std::function is created with a lambda, 
            // the std::function internally makes a copy of the lambda object.
            // Thus, the call to fn() is actually being executed on the copy of our lambda, not the actual lambda.

            // See also:
            // https://stackoverflow.com/questions/23515058/creating-stdfunction-with-lambda-causes-superfluous-copying-of-the-lambda-obje

            int i{ };

            // increments and prints its local copy of @i
            auto count{ [i]() mutable { std::cout << ++i << std::endl; } };

            invoke(count);
            invoke(count);
            invoke(count);
            std::cout << std::endl;
        }

        static void testExercise_03e()
        {
            // Output:
            // 1
            // 2
            // 3

            // See testExercise_03d - using 'std::function' instead of 'auto'

            int i{ };

            std::function<void(void)> count { 
                [i]() mutable {
                    std::cout << ++i << std::endl;
                }
            };

            invoke(count);
            invoke(count);
            invoke(count);
            std::cout << std::endl;
        }

        static void testExercise()
        {
            testExercise_03a();
            testExercise_03b();
            testExercise_03c();
            testExercise_03d();
            testExercise_03e();
        }
    }
}

void test_exercises_lambdas()
{
    using namespace Exercises_Lambdas;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
    Exercise_03::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
