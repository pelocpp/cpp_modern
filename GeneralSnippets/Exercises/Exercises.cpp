// =====================================================================================
// Exercices
// =====================================================================================

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <chrono>
#include <functional>
#include <map>

namespace Exercise_01 {

    template <typename T>
    inline T minimum(const T& t) { return t; }

    template <typename T, typename ...P>
    inline typename std::common_type<T, P...>::type
    minimum(const T& t, const P& ...p)
    {
        typedef typename std::common_type<T, P...>::type res_type;
        return std::min(res_type(t), res_type(minimum(p...)));
    }

    // oder etwas knapper

    //template <typename T>
    //inline T minimum(const T& t) { return t; }

    //template <typename T, typename ...P>
    //inline auto minimum(const T& t, const P& ...p)
    //{
    //    using res_type = std::common_type_t<T, P...>;
    //    return std::min(res_type(t), res_type(minimum(p...)));
    //}

    void testExercise() {
        auto min1 = minimum(-7, 3.7f, 9u, -2.6);
        std::cout << "min1: " << min1 << ", type: " << typeid(min1).name() << std::endl;

        auto min2 = minimum(-7, 3.7f, 9u, -42.6);
        std::cout << "min2: " << min2 << ", type: " << typeid(min2).name() << std::endl;

        auto min3 = minimum(123, (short)456, (long)789);
        std::cout << "min3: " << min3 << ", type: " << typeid(min3).name() << std::endl;
    }
}

namespace Exercise_02 {

#define SOLUTION 

    class HugeArray {
    private:
        size_t m_len;
        int* m_data;

    public:
        HugeArray();        // default c'tor
        HugeArray(size_t);  // user-defined c'tor
        ~HugeArray();       // d'tor

        // copy semantics
        HugeArray(const HugeArray&);  // copy c'tor
        HugeArray& operator=(const HugeArray&);  // copy assignment

#if defined (SOLUTION)
        // move semantics
        HugeArray(HugeArray&&) noexcept;  // move c'tor
        HugeArray& operator= (HugeArray&&) noexcept; // move assignment
#endif
    };

    HugeArray::HugeArray() : m_len(0), m_data(nullptr) {
        std::cout << "default c'tor" << std::endl;
    }

    HugeArray::HugeArray(size_t len) : m_len(len), m_data(new int[len]) {
        std::cout << "c'tor (size_t):  " << len << " allocated" << std::endl;
    }

    HugeArray::~HugeArray() {
        std::cout << "d'tor:           " << m_len << " relased" << std::endl;
        delete[] m_data;
    }

    // copy semantics
    HugeArray::HugeArray(const HugeArray& other) {
        std::cout << "COPY c'tor:      " << other.m_len << " allocated" << std::endl;
        m_len = other.m_len;
        m_data = new int[other.m_len];
        std::copy(other.m_data, other.m_data + m_len, m_data);
    }

    HugeArray& HugeArray::operator=(const HugeArray& other) {
        std::cout << "COPY assignment: " << other.m_len << " assigned" << std::endl;
        if (this != &other) {
            delete[] m_data;
            m_len = other.m_len;
            m_data = new int[m_len];
            std::copy(other.m_data, other.m_data + m_len, m_data);
        }
        return *this;
    }

#if defined (SOLUTION)
    // move semantics
    HugeArray::HugeArray(HugeArray&& other) noexcept {  // move c'tor
        std::cout << "MOVE c'tor:      " << other.m_len << " allocated" << std::endl;
        m_data = other.m_data;   // shallow copy
        m_len = other.m_len;
        other.m_data = nullptr;  // reset source object, ownership has been moved
        other.m_len = 0;
    }

    HugeArray& HugeArray::operator= (HugeArray&& other) noexcept { // move-assignment
        std::cout << "MOVE assignment: " << other.m_len << " assigned" << std::endl;
        if (this != &other) {
            delete[] m_data;         // release left side
            m_data = other.m_data;   // shallow copy
            m_len = other.m_len;
            other.m_data = nullptr;  // reset source object, ownership has been moved
            other.m_len = 0;
        }
        return *this;
    }
#endif

    void testExercise() {
        std::cout << "Start:" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<HugeArray> myVec;
        HugeArray bArray(10000000);
        HugeArray bArray2(bArray);
        myVec.push_back(bArray);   // <== std::move
        bArray = HugeArray(20000000);
        myVec.push_back(HugeArray(30000000));
        auto end = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
        std::cout << "Done [" << diff.count() << " msecs]" << std::endl;
    }
}

namespace Exercise_03 {

    inline void even(const int val) {
        if (!(val % 2)) {
            std::cout << val << std::endl;
        }
    }

    struct Even {
        void operator()(const int val) {
            if (!(val % 2)) {
                std::cout << val << std::endl;
            }
        }
    };

    void testExercise01() {
        std::vector<int> values(20);

        std::generate(
            std::begin(values),
            std::end(values),
            [count = 1]() mutable { return count++; }
        );

        // function
        std::for_each(std::begin(values), std::end(values), even);

        // lambda
        std::for_each(std::begin(values), std::end(values), [](int val) {
            if (!(val % 2)) {
                std::cout << val << std::endl;
            }   
        });

        // functor
        std::for_each(std::begin(values), std::end(values), Even());
    }

    void testExercise02() {
        std::vector<int> values(20);

        std::generate(
            std::begin(values),
            std::end(values),
            [count = 1]() mutable { return count++; }
        );

        // 'divisor' defined within capture clause 
        std::for_each(std::begin(values), std::end(values), [divisor = 3](int val) {
            if (!(val % divisor)) {
                std::cout << val << std::endl;
            }
        });
        std::cout << std::endl;

        // or 'divisor' defined in outer context (scope) 
        int divisor = 5;

        // capture context by value (reference & would work also)
        std::for_each(std::begin(values), std::end(values), [=](int val) {
            if (!(val % divisor)) {
                std::cout << val << std::endl;
            }
        });
    }
}

namespace Exercise_04 {

    std::map<char, std::function<double(double, double)>> createCalculatorEx() {

        std::map<char, std::function<double(double, double)>> map;
        map.insert(std::make_pair('+', [](double a, double b) { return a + b; }));
        map.insert(std::make_pair('-', [](double a, double b) { return a - b; }));
        map.insert(std::make_pair('*', [](double a, double b) { return a * b; }));
        map.insert(std::make_pair('/', [](double a, double b) { return a / b; }));
        return map;
    }

    // or more compact

    std::map<char, std::function<double(double, double)>> createCalculator() {

        std::map<char, std::function<double(double, double)>> map;
        map['+'] = [](double a, double b) { return a + b; };
        map['-'] = [](double a, double b) { return a - b; };
        map['*'] = [](double a, double b) { return a * b; };
        map['/'] = [](double a, double b) { return a / b; };
        return map;
    }

    void testExercise01() {

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
        std::cout << "Result: " << op1 << ' ' << op << ' ' << op1 << " = " << result << '.' << std::endl;
    };

    void testExercise02() {

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
}

int main()
// int main_exercices()
{
    //using namespace Exercise_01;
    //testExercise();

    //using namespace Exercise_02;
    //testExercise();

    //using namespace Exercise_03;
    //testExercise01();
    //testExercise02();

    using namespace Exercise_04;
    //testExercise01();
    testExercise02();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
