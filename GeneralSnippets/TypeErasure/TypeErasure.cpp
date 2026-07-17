// =====================================================================================
// TypeErasure.cpp
// =====================================================================================

module modern_cpp:type_erasure;

// =====================================================================================

namespace TypeErasureUsingDynamicPolymorphism {

    struct IAnimal
    {
        virtual ~IAnimal() = default;
        virtual std::string see() const = 0;
        virtual std::string say() const = 0;
    };

    class Dog : public IAnimal
    {
    public:
        virtual std::string see() const override { return "dog"; }
        virtual std::string say() const override { return "woof"; }
    };

    class Cat : public IAnimal
    {
    public:
        virtual std::string see() const override { return "cat"; }
        virtual std::string say() const override { return "meow"; }
    };

    using AnimalPointer = std::shared_ptr<IAnimal>;

    using Animals = std::vector<AnimalPointer>;

    static void test_type_erasure_using_dynamic_polymorphism()
    {
        AnimalPointer animal1{ std::make_shared<Cat>() };
        AnimalPointer animal2{ std::make_shared<Dog>() };

        Animals animals{ animal1, animal2 };

        for (const auto& animal : animals) {
            std::println("{}: {}", animal->see(), animal->say());
        }
        std::println();
    }
}

// =====================================================================================

namespace TypeErasureUsingTemplateTechniques {

    class Dog
    {
    public:
        std::string see() const { return "dog"; }
        std::string say() const { return "woof"; }
    };

    class Cat
    {
    public:
        std::string see() const { return "cat"; }
        std::string say() const { return "meow"; }
    };

    class PolymorphicObjectWrapper
    {
    public:
        template<typename T>
        PolymorphicObjectWrapper(const T& obj) :
            m_wrappedObject{ std::make_shared<ObjectModel<T>>(obj) }
        {}

        std::string see() const
        {
            return m_wrappedObject->see();
        }

        std::string say() const
        {
            return m_wrappedObject->say();
        }

    private:
        struct ObjectConcept
        {
            virtual ~ObjectConcept() = default;
            virtual std::string see() const = 0;
            virtual std::string say() const = 0;
        };

        template<typename T>
        struct ObjectModel final : public ObjectConcept
        {
            ObjectModel(const T& object) : m_object{ object } {}

            std::string see() const override
            {
                return m_object.see();
            }

            std::string say() const override
            {
                return m_object.say();
            }

        private:
            T m_object;
        };

        std::shared_ptr<ObjectConcept> m_wrappedObject;
    };

    using Animals = std::vector<PolymorphicObjectWrapper>;

    static void test_type_erasure_using_template_techniques()
    {
        Animals animals{ Cat(), Dog() };

        for (const auto& animal : animals) {
            std::println("{}: {}", animal.see(), animal.say());
        }
        std::println();
    }
}

// =====================================================================================

namespace TypeErasureUsingTemplateTechniquesAndConcepts {

    class Dog
    {
    public:
        std::string see() const { return "dog"; }
        std::string say() const { return "woof"; }
    };

    class Cat
    {
    public:
        std::string see() const { return "cat"; }
        std::string say() const { return "meow"; }
    };

    template<typename T>
    concept ClassActingLikeAnAnimal = requires (const T & o)
    {
        { o.see() } -> std::same_as<std::string>;
        { o.say() } -> std::same_as<std::string>;
    };

    class PolymorphicObjectWrapper
    {
    public:
        template<typename T>
            requires ClassActingLikeAnAnimal<T>
        PolymorphicObjectWrapper(const T& obj) :
            m_wrappedObject{ std::make_shared<ObjectModel<T>>(obj) }
        {}

        std::string see() const
        {
            return m_wrappedObject->see();
        }

        std::string say() const
        {
            return m_wrappedObject->say();
        }

    private:
        struct ObjectConcept
        {
            virtual ~ObjectConcept() = default;
            virtual std::string see() const = 0;
            virtual std::string say() const = 0;
        };

        template<typename T>
            requires ClassActingLikeAnAnimal<T>
        struct ObjectModel final : public ObjectConcept
        {
            ObjectModel(const T& object) : m_object{ object } {}

            std::string see() const override
            {
                return m_object.see();
            }

            std::string say() const override
            {
                return m_object.say();
            }

        private:
            T m_object;
        };

        std::shared_ptr<ObjectConcept> m_wrappedObject;
    };

    using Animals = std::vector<PolymorphicObjectWrapper>;

    static void test_type_erasure_using_template_techniques()
    {
        Animals animals{ Cat(), Dog() };

        for (const auto& animal : animals) {
            std::println("{}: {}", animal.see(), animal.say());
        }
        std::println();
    }
}

// =====================================================================================


namespace TypeErasure_StdFunction_Simple_Implementation {

//
//
//
//    // ======================================================================================
//
//    // HIER ZU TYPE ERASURE ............
//
//
//#include <functional>
//#include <future>
//#include <iostream>
//#include <memory>
//#include <print>
//#include <utility>

    // primary template declaration
    template<typename TSignature>
    class SimpleFunction;

    // template specialization for signature 'void()'
    template<>
    class SimpleFunction<void()> {
    private:

        // the interface for type erasure
        struct CallableInvoker
        {
            virtual ~CallableInvoker() = default;
            virtual void invoke() = 0;
        };

        // the concrete implementation that holds the actual function object
        template<typename TObject>
        struct CallableHolder : CallableInvoker
        {
            TObject m_callable;

            CallableHolder(TObject callable)
                : m_callable(std::move(callable))
            {}

            void invoke() override {
                m_callable();  // calling the callable
            }
        };

        // we use std::unique_ptr to manage the lifetime on the heap
        std::unique_ptr<CallableInvoker> m_invoker;

    public:
        // default constructor (creates an empty function)
        SimpleFunction() = default;

        // template constructor: accepts ANY callable object (function, lambda, etc.)
        template<typename TFunc>
        SimpleFunction(TFunc func)
            : m_invoker(std::make_unique<CallableHolder<TFunc>>(std::move(func)))
        {}

        // function call operator()
        void operator()() const {

            if (m_invoker == nullptr) {
                throw std::runtime_error("Error: Calling an empty SimpleFunction!");
            }
            return m_invoker->invoke();
        }
    };

    // template specialization for signatures like 'TReturn(TArgs...)'
    template<typename TReturn, typename... TArgs>
    class SimpleFunction<TReturn(TArgs ...)> {
    private:

        // method 'invoke' now returns the type 'TReturn'
        struct CallableInvoker
        {
            virtual ~CallableInvoker() = default;
            virtual TReturn invoke(TArgs ... args) = 0;
        };

        // the concrete implementation of method 'invoke' also returns 'TReturn'
        template<typename TObject>
        struct CallableHolder : CallableInvoker
        {
            TObject m_callable;

            CallableHolder(TObject callable)
                : m_callable(std::move(callable))
            {}

            TReturn invoke(TArgs ... args) override {
                return m_callable(std::forward<TArgs>(args)...);  // calling the callable with the passed arguments
            }
        };

        std::unique_ptr<CallableInvoker> m_invoker;

    public:
        SimpleFunction() = default;

        template<typename TFunc>
        SimpleFunction(TFunc func)
            : m_invoker(std::make_unique<CallableHolder<TFunc>>(std::move(func)))
        {}

        // operator() now returns 'TReturn' and accepts 'TArgs ...'
        TReturn operator()(TArgs ... args) const {

            if (m_invoker == nullptr) {
                throw std::runtime_error("Error: Calling an empty SimpleFunction!");
            }
            return m_invoker->invoke(std::forward<TArgs>(args)...);
        }
    };

    // ===================================================================================

    // free function
    static void hello_world() {
        std::println("Hello from the free function!");
    }

    static void test_simple_function_type_erasure_01()
    {
        // pass the free function to our SimpleFunction object
        SimpleFunction<void()> func{ hello_world };

        // calling like a normal function
        func();
    }

    static void test_simple_function_type_erasure_02()
    {
        int counter = 123;

        // define a lambda with state (capture)
        auto lambda = [counter]() {
            std::println("Hello from Lambda: {}", counter);
        };

        // pass the lambda to a SimpleFunction object
        SimpleFunction<void()> func{ lambda };

        // calling like a normal function
        func();
    }

    // free function with paramters
    static int add(int a, int b) {
        return a + b;
    }

    static void test_simple_function_type_erasure_03()
    {
        // signature: returns an int, takes two ints
        SimpleFunction<int(int, int)> func{ add };

        int result{ func(10, 5) };

        std::println("Result of the free function: {}", result);
    }

    static void hello_world_slow(std::string s) {
        std::println("hello_world_slow: {}", s);
    }

    static void hello_world_fast(const std::string& s) {
        std::println("hello_world_fast: {}", s);
    }

    static void test_simple_function_type_erasure_04()
    {
        SimpleFunction<void(std::string)> func1{ hello_world_slow };
        std::string hello{ "Hello" };
        func1(hello);  // passing by copy

        SimpleFunction<void(const std::string&)> func2{ hello_world_fast };
        func2(hello);
        func2(std::string{ "More Hello" });  // passing by reference
    }

    void test_type_erasure_simple_function()
    {
        test_simple_function_type_erasure_01();
        test_simple_function_type_erasure_02();
        test_simple_function_type_erasure_03();
        test_simple_function_type_erasure_04();
    }
}


// =====================================================================================

void main_type_erasure()
{
    using namespace TypeErasureUsingDynamicPolymorphism;
    using namespace TypeErasureUsingTemplateTechniques;
    using namespace TypeErasureUsingTemplateTechniquesAndConcepts;
    using namespace TypeErasure_StdFunction_Simple_Implementation;

    //TypeErasureUsingDynamicPolymorphism::test_type_erasure_using_dynamic_polymorphism();
    //TypeErasureUsingTemplateTechniques::test_type_erasure_using_template_techniques();
    //TypeErasureUsingTemplateTechniquesAndConcepts::test_type_erasure_using_template_techniques();
    TypeErasure_StdFunction_Simple_Implementation::test_type_erasure_simple_function();
}

// =====================================================================================
// End-of-File
// =====================================================================================

