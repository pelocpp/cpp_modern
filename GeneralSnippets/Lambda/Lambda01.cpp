// =====================================================================================
// Lambda01.cpp // Lambda Methods
// =====================================================================================

module modern_cpp:lambda;

// =====================================================================================
// Lambdas: Anonymous Function Objects

static void print(int n)
{
    std::print("{} ", n);
}

class Printer
{
public:
    void operator() (int n) {
        std::print("{} ", n);
    }
};

static void lambda_01_modern()
{
    std::vector<int> vec{ 1, 2, 3 };

    std::for_each(
        vec.begin(),
        vec.end(),
        [](int n) {
            std::print("{} ", n);
        }
    );

    std::println();
}

static void lambda_01_classic()
{
    std::vector<int> vec{ 1, 2, 3 };

    std::for_each(
        vec.begin(),
        vec.end(),
        print
    );

    std::println();
}

static void lambda_01_more_classic()
{
    std::vector<int> vec{ 1, 2, 3 };

    Printer printer{};

    std::for_each(
        vec.begin(),
        vec.end(),
        printer
    );

    std::println();
}

static void lambda_01()
{
    lambda_01_modern();
    lambda_01_classic();
    lambda_01_more_classic();
}

// =====================================================================================
// Capture Clause

static void lambda_02_01()
{
    std::vector<int> vec{ 1, 2, 3 };

    std::string header{ ">>> " };

    std::for_each(
        vec.begin(),
        vec.end(),
        [&header](int n) {
            std::println("{}{} ", header, n);
        }
    );
}

static void lambda_02_02()
{
    int n{ 1 };
    int m{ 2 };

    auto l1{ [=] { std::println("Copy:      {} {}", n, m); } };
    auto l2{ [&] { std::println("Reference: {} {}", n, m); } };
    auto l3{ [&, m] { std::println("Both:      {} {}", n, m); } };
    auto l4{ [=, &m] { std::println("More both: {} {}", n, m); } };

    n = 3;
    m = 4;

    l1();
    l2();
    l3();
    l4();
}

static void lambda_02()
{
    lambda_02_01();
    lambda_02_02();
}

// =====================================================================================
// Generic Lambdas

static void lambda_03()
{
    std::vector<int> vec{ 1, 2, 3 };

    std::for_each(
        vec.begin(),
        vec.end(),
        [](auto n) {
            std::print("{} ", n);
        }
    );

    std::println();
}

// =====================================================================================
// Closure Type / Closure Object

static void lambda_04_01()
{
    std::string s{ "Hello" };

    auto func = [=]() { std::print("{}", s); };

    func();

    std::println();
}

static void lambda_04_01_transformed()
{
    std::string s{ "Hello" };

    class LambdaClosure
    {
    private:
        std::string m_s;

    public:
        LambdaClosure(const std::string& s) : m_s{ s } {}

        inline void operator() () const { std::print("{}", m_s); }
    };

    LambdaClosure func = LambdaClosure{ s };

    func.operator() ();

    std::println();
}

static void lambda_04_02()
{
    std::string s{ "Hello" };

    auto func = [&]() { std::print("{}", s); };

    func();

    std::println();
}

static void lambda_04_02_transformed()
{
    std::string s{ "Hello" };

    class LambdaClosure
    {
    private:
        std::string& m_s;

    public:
        LambdaClosure(std::string& s) : m_s{ s } {}

        inline void operator() () const { std::print("{}", m_s); }
    };

    LambdaClosure func = LambdaClosure{ s };

    func.operator() ();

    std::println();
}

static void lambda_04()
{
    lambda_04_01();
    lambda_04_01_transformed();
    lambda_04_02();
    lambda_04_02_transformed();
}

// =====================================================================================
// Trailing Return Type

static void lambda_05()
{
    auto getValue = [](bool condition) -> std::variant<int, std::string> {

        if (condition) {
            return 123; // int
        }
        else {
            return std::string{ "Hello World" };  // std::string
        }
        };

    auto value{ getValue(false) };
}

// =====================================================================================
// mutable

static void lambda_06()
{
    std::size_t value{ 123 };

    auto increment = [=]() mutable -> std::size_t {

        ++value;
        return value;
        };

    value = increment(); std::println("{}", value);
    value = increment(); std::println("{}", value);
    value = increment(); std::println("{}", value);
}

// =====================================================================================
// Capture Initialization (Closure Objects with state)

static void lambda_07()
{
    auto increment = [start = 123]() mutable -> std::size_t {

        ++start;
        return start;
        };

    std::size_t value{ 0 };

    value = increment(); std::println("{}", value);
    value = increment(); std::println("{}", value);
    value = increment(); std::println("{}", value);
}

// =====================================================================================
// Storing lambdas as std::function

static void lambda_08_01()
{
    auto lambdaOne = []() { std::println("One"); };
    auto lambdaTwo = []() { std::println("Two"); };

    std::vector<std::function<void()>> myLambdas;

    myLambdas.push_back(lambdaOne);
    myLambdas.push_back(lambdaTwo);

    for (const auto& lambda : myLambdas) {
        lambda();
    }
}

static void lambda_08_02()
{
    std::function<int(int, int, int)> lambdaWithThreeParams{
        [](int x, int y, int z) { return x + y + z; }
    };

    auto sum{ lambdaWithThreeParams(1, 2, 3) };

    std::println("1+2+3={}", sum);
}

static void lambda_08()
{
    lambda_08_01();
    lambda_08_02();
}

// =====================================================================================
// Storing lambdas as function pointer

static void lambda_09_01()
{
    auto lambda1 = []() { std::println("1"); };
    auto lambda2 = []() { std::println("2"); };

    //int x{ 123 };
    //auto lambda3 = [x]() { std::println("{}", x); };

    std::vector<void(*)()> myLambdas;

    myLambdas.push_back(lambda1);
    myLambdas.push_back(lambda2);
    // myLambdas.push_back(lambda3);

    for (const auto& lambda : myLambdas) {
        lambda();
    }
}

static void lambda_09_02()
{
    int(*lambdaWithThreeParams)(int, int, int) {
        [](int x, int y, int z) { return x + y + z; }
    };

    auto sum{ lambdaWithThreeParams(10, 11, 12) };

    std::println("10+11+12={}", sum);
}

static void lambda_09()
{
    lambda_09_01();
    lambda_09_02();
}

// =====================================================================================
// Lambdas as First-Class Citizens

static auto helper_a() {

    int n{ 1 };
    int m{ 2 };

    auto lambda{ [=] { std::println("Copy:      {} {}", n, m); } };
    return lambda;
}

static auto helper_b() {

    int n{ 1 };
    int m{ 2 };

    auto lambda{ [&] { std::println("Reference: {} {}", n, m); } };
    return lambda;             // I would't do this never ever :-)
}

static void lambda_10()
{
    auto outerLambda1{ helper_a() };
    auto outerLambda2{ helper_b() };

    outerLambda1();
    outerLambda2();
}

// =====================================================================================
// Lambdas and constexpr

static constexpr auto sum = [](int a, int b) { return a + b; };

static constexpr auto power = [](int m, std::size_t n) {

    auto result = m;
    for (std::size_t i{ 1 }; i != n; ++i) {
        result *= m;
    }
    return result;
    };

static void lambda_11()
{
    constexpr auto result{ sum(10, 11) };         // sum = 21 at compile time
    constexpr auto twoPowerTen{ power(2, 10) };   // twoPowerTen = 1024 at compile time
    constexpr auto fivePowerTen{ power(5, 10) };  // fivePowerTen = 9765625 at compile time
}

// =====================================================================================
// IIFE - Immediately Invoked Functional Expressions

// Without IIFE

static constexpr int complexValueComputation(int x) {
    if (x > 10) {
        return x * 2;
    }
    return x + 5;
}

static constexpr auto value = complexValueComputation(5);

// With IIFE

static constexpr auto anotherValue = [](int x)
    {
        if (x > 10) {
            return x * 2;
        }
        return x + 5;
    }(5);

static constexpr auto squareNumbers = []() {
    std::array<int, 10> temp{};
    for (int i = 0; i < 10; ++i) {
        temp[i] = i * i;
    }
    return temp;
    }();

static void lambda_12()
{
}

// =====================================================================================
// Generalized Lambda Capture

static void lambda_13()
{
    class SampleClass
    {
    private:
        std::string m_text;
    public:
        SampleClass() : m_text{ "Doing something" } {}
        void doSomething() { std::println("{}", m_text); };
    };

    std::unique_ptr<SampleClass> ptr{ std::make_unique<SampleClass>() };

    // Does not compile: by-value capture with move-only type (!)
    // auto lambda = [=] () { ptr->doSomething(); };

    // Compiles: by-reference capture with move-only type (!)
    auto lambda = [&]() { ptr->doSomething(); };

    // Compiles: "Generalized Lambda Capture"
    auto lambda2 = [ptrSampleClass = std::move(ptr)]() {
        ptrSampleClass->doSomething();
    };
    lambda2();

    ptr = std::make_unique<SampleClass>();

    // Compiles too: Same name for captured variable and internal variable of lambda object
    auto lambda3 = [ptr = std::move(ptr)]() {
        ptr->doSomething();
    };
    lambda3();
}

// =====================================================================================
// Move-only Lambdas

static void lambda_14_01()
{
    std::unique_ptr<std::string> ptr{ std::make_unique<std::string>("12345") };

    // lambda capturing a move-only type
    auto lambda{ [ptr = std::move(ptr)]() { return *ptr; } };

    auto value{ lambda() };               // invoking lambda
    std::println("{}", value);

    // auto lambda2{ lambda };            // lambda cannot be copied

    auto lambda2{ std::move(lambda) };    // lambda can be moved

    value = lambda2();                    // invoking lambda2
    std::println("{}", value);
}

static void lambda_14_02()
{
    std::unique_ptr<std::string> ptr{ std::make_unique<std::string>("ABCDE") };

    // lambda capturing a move-only type
    auto lambda = [ptr = std::move(ptr)]() { return *ptr; };

    // std::function<std::string()> func{ std::move(lambda) };         // error: 'The target function object type must be copy constructible

    std::move_only_function<std::string()> func{ std::move(lambda) };  // lambda can be moved into a std::move_only_function wrapper object

    // auto value{ lambda() };        // crashes (!), object has been moved!

    auto value{ func() };             // works
    std::println("{}", value);
}


static void lambda_14()
{
    lambda_14_01();
    lambda_14_02();
}


// =====================================================================================
// C++20: "Variadic Capture"

template <typename... TArgs>
auto createTask(TArgs&&... args) {

    // moving all arguments into the lambda object
    return [...args = std::forward<TArgs>(args)]() mutable {

        // helper function
        auto process = [](auto& arg) {
            std::println("{}", arg);
            };

        // folding over a comma: process all arguments
        (process(args), ...);
    };
}

static void lambda_15()
{
    double d{ 123.0 };
    std::string s{ "ABCDE" };

    // move ownership of parameters to lambda
    auto task{ createTask(std::move(d), std::move(s)) };

    if (s.empty()) {
        std::println("s is empty");
    }

    // delayed execution
    task();
}

// =====================================================================================
// noexcept

static void lambda_16()
{
    auto multiplyByTwo = [](int x) noexcept { return x * 2; };

    auto result = multiplyByTwo(10);

    std::println("Result: {}", result);
}

// =====================================================================================

void main_lambdas()
{
    lambda_01();
    lambda_02();
    lambda_03();
    lambda_04();
    lambda_05();
    lambda_06();
    lambda_07();
    lambda_08();
    lambda_09();
    lambda_10();
    lambda_11();
    lambda_12();
    lambda_13();
    lambda_14();
    lambda_15();
    lambda_16();

}

// =====================================================================================
// End-of-File
// =====================================================================================
