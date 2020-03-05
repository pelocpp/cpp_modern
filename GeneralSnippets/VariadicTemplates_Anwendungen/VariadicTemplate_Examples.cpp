// =====================================================================================
// Variadic Templates
// =====================================================================================

#include <iostream>
#include <string>

/*
 * Logische Operationen für beliebig viele Operanden
 */

namespace VariadicTemplatesExamples {

    // =============================================================
    // Logical And - with variadic template

    template<typename T>
    bool allAnd(T cond) {
        return cond;
    }

    template<typename T, typename... Ts>
    bool allAnd(T cond, Ts... conds) {
        return cond && allAnd(conds...);
    }

    // oder

    //bool allAnd() {
    //    std::cout << "a)" << std::endl;
    //    return true;
    //}
    //
    //template<typename T, typename... Ts>
    //bool allAnd(T cond, Ts... conds) {
    //    return cond && allAnd(conds...);
    //}

    void test_01() {

        bool result = allAnd(true, (1 > 2), true);
        std::cout << std::boolalpha << result << std::endl;

        result = allAnd(true, true, true);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical Or - with variadic template

    template<typename T>
    bool allOr(T cond) {
        return cond;
    }

    template<typename T, typename... Ts>
    bool allOr(T cond, Ts... conds) {
        return cond || allOr(conds...);
    }

    void test_02() {

        bool result = allOr(false, false, true);
        std::cout << std::boolalpha << result << std::endl;

        result = allAnd(false, false, false, false, false);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical And - with folding expression

    template<typename ...Args>
    bool anotherAllAnd(Args ...args) {
        return (args && ... && true);  // binary right fold (init == true)
    }

    void test_03() {

        bool result = anotherAllAnd(true, (1 > 2), true);
        std::cout << std::boolalpha << result << std::endl;

        result = anotherAllAnd(true, true, true);
        std::cout << std::boolalpha << result << std::endl;
    }

    // =============================================================
    // Logical Or - with folding expression

    template<typename ...Args>
    bool anotherAllOr(Args ...args) {
        return (args || ...);  // unary right fold
    }

    void test_04() {

        bool result = anotherAllOr(false, false, true);
        std::cout << std::boolalpha << result << std::endl;

        result = anotherAllOr(false, false, false, false, false);
        std::cout << std::boolalpha << result << std::endl;
    }
}

// =============================================================

int main_variadic_templates_examples()
{
    using namespace VariadicTemplatesExamples;
    test_01();
    test_02();
    test_03();
    test_04();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
