// =====================================================================================
// Variadic Templates - Else If
// =====================================================================================

#include <iostream>
#include <string>
#include <functional>

namespace VariadicTemplatesElseIf {

    // Yet under construction

    // https://www.fluentcpp.com/2020/04/24/else-before-if/

    template<class...Ts, class F>
    F for_each_arg(F f, Ts&&...a) {
        return (void)std::initializer_list<int>{(std::ref(f)((Ts&&)a), 0)...}, f;
    }

    struct ConsiderBranch
    {
        bool hasExecutedABranch = false;
        template<typename Branch>
        void operator()(Branch&& branch)
        {
            if (!hasExecutedABranch && std::forward<Branch>(branch).condition() == true)
            {
                std::forward<Branch>(branch).action();
                hasExecutedABranch = true;
            }
        }
    };

    template<typename MainBranch, typename... SecondaryBranches>
    void normally(MainBranch&& mainBranch, SecondaryBranches&& ... secondaryBranches)
    {
        auto considerBranch = ConsiderBranch{};
        auto resultOfConsideringSecondaryBranches = for_each_arg(considerBranch, secondaryBranches...);
        if (!resultOfConsideringSecondaryBranches.hasExecutedABranch)
        {
            std::forward<MainBranch>(mainBranch)();
        }
    }

    template<typename Action>
    struct Unless_branch
    {
    public:
        Unless_branch(bool condition, Action action) : condition_(condition), action_(std::move(action)) {}
        void action() const { action_(); }
        bool condition() const { return condition_; };
    private:
        bool condition_;
        Action action_;
    };

    struct unless
    {
    public:
        explicit unless(bool condition) : condition_(condition) {}

        template<typename Action>
        Unless_branch<Action> operator()(Action&& action)
        {
            return Unless_branch<Action>(condition_, std::forward<Action>(action));
        }
    private:
        bool condition_;
    };

    void test_01() {
        bool edgeCase1 = false;
        bool edgeCase2 = false;
        std::string text;

        normally
        ([&text]()
            {
                text = "normal case\n";
            },
            unless(edgeCase1)
                ([&text]()
                    {
                        text = "edge case 1\n";
                    }
                    ),
                unless(edgeCase2)
                        ([&text]()
                            {
                                text = "edge case 2";
                            }
                    )
         );
    }

    void test_02 () {

        bool edgeCase1 = true;
        bool edgeCase2 = false;
        std::string text;

        auto lambda1 = [&text]() { text = "normal case\n"; };
        const auto lambda2 = [&text]() { text = "edge case 1\n"; };
        const auto lambda3 = [&text]() { text = "edge case 2"; };

        normally (
           // std::function<decltype(lambda1)>,
           lambda1,
            unless(edgeCase1) (lambda2),
            unless(edgeCase2) (lambda3)
        );

        //normally
        //([&text]()
        //{
        //    text = "normal case\n";
        //},
        //unless(edgeCase1)
        //([&text]()
        //{
        //    text = "edge case 1\n";
        //}),
        //unless(edgeCase2)
        //([&text]()
        //{
        //    text = "edge case 2";
        //}));

        std::cout << text << '\n';
    }
}

void main_variadic_else_if()
{
    using namespace VariadicTemplatesElseIf;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
