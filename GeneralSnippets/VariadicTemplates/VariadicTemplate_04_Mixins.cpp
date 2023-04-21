// =====================================================================================
// VariadicTemplate_04_Mixins.cpp // Variadic Templates - Mixins
// =====================================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplatesMixins {

    // ===================================================================
    // basics of "varidiac inheritance" explained
 
    // need some classes with default constructors
    class A { public: A() = default; };
    class B { public: B() = default; };
    class C { public: C() = default; };

    template<typename ... TS>
    class X : public TS...
    {
    public:
        X(const TS&... mixins) : TS{ mixins } ... {}
    };

    void test_00() 
    {
        A a{};
        B b{};
        C c{};
        X<A, B> xAB{ a, b };
        // X<B, A> xBA{};   // Error, needs arguments
        X<C> xC{ c };
        X<> xNoBases{};

        X<A, B, C>  xabc{ a, b, c };
    }

    // ===================================================================
    // Variant 1: "copy-paste" style 

    class SlotA
    {
    public:
        int m_value{};
    };

    class SlotB
    {
    public:
        std::string m_value{};
    };

    // Note:
    // private inheritance, no one can access directly 
    // to the slots other than Repository itself
    class MyRepository : private SlotA, private SlotB
    {
    public:
        void setSlotA(const int& value)
        {
            // access the base-class's value: since we have multiple bases
            // with a 'value' field, we need to "force" the access to SlotA.
            SlotA::m_value = value;
        }

        int getSlotA() 
        {
            return SlotA::m_value;
        }

        void setSlotB(const std::string& value)
        {
            SlotB::m_value = value;
        }

        std::string getSlotB()
        {
            return SlotB::m_value;
        }
    };

    void test_01() 
    {
        MyRepository repo{};

        repo.setSlotA(123);
        std::cout << repo.getSlotA() << std::endl; // printing 123

        repo.setSlotB(std::string{ "ABC" });
        std::cout << repo.getSlotB() << std::endl; // printing "ABC"
    }

    // ===================================================================
    // Variant 2: "varidiac inheritance" style 

    template <typename T>
    class Slot
    {
    protected:
        T& get()
        {
            return m_value;
        }

        void set(const T& value)
        {
            m_value = value;
        }

    private:
        T m_value{};
    };

    template <typename... TSlots>
    class Repository : private TSlots...  // inherit private from our slots...
    {
    public:
        template <typename T> // select type
        T& get()
        {
            return Slot<T>::get(); // select base class
        }

        template <typename T>
        void set(const T& value)
        {
            Slot<T>::set(value);
        }
    };

    void test_02() 
    {
        using MyRepo = Repository<Slot<int>, Slot<std::string>>;

        MyRepo repo{};

        repo.set<std::string>(std::string{ "XYZ" });
        repo.set(987); // note type deduction: we pass an int, so it writes to the int slot

        std::cout << repo.get<int>() << std::endl; // printing 987
        std::cout << repo.get<std::string>() << std::endl; // printing "XYZ"
    }

    // ===================================================================
    // Variant 3: improving variant 2: several slots with same type
    //
    // and
    //
    // ===================================================================
    // Variant 4: adding 'emplace' mechanism for sample class 'Person'

    void test_03_error() 
    {
         // RepositoryEx < Slot<int>, Slot<int> > repo{};
         // error: 'VariadicTemplatesMixins::Slot<int>' is already a direct base
    }

    struct DefaultSlotKey; // forward definition sufficient

    template <typename T, typename Key = DefaultSlotKey>
    class SlotEx
    {
    protected:
        T& get()
        {
            return m_value;
        }

        void set(const T& value)
        {
            m_value = value;
        }

        template <typename... TArgs>
        void emplace(const TArgs&... args)
        {
            m_value = T{ args... }; // assigment (might use move semantics)
        }

        // or

        // using "Perfect Forwarding":
        //template <typename... TArgs>
        //void emplace(TArgs&& ... args)
        //{
        //    m_value = T{ std::forward<TArgs>(args) ... }; // assigment (might use move semantics)
        //}

    private:
        T m_value;
    };

    template <typename... TSlots>
    class RepositoryEx : private TSlots...  // inherit private from our slots...
    {
    public:
        template <typename T, typename Key = DefaultSlotKey>
        T& get()
        {
            return SlotEx<T, Key>::get(); // select base class
        }

        template <typename T, typename Key = DefaultSlotKey>
        void set(const T& value)
        {
            SlotEx<T, Key>::set(value);
        }

        template <typename T, typename Key = DefaultSlotKey, typename... TArgs>
        void emplace(const TArgs&... args)
        {
            SlotEx<T, Key>::emplace(args...);
        }

        // or

        // using "Perfect Forwarding":
        //template <typename T, typename Key = DefaultSlotKey, typename... TArgs>
        //void emplace(TArgs&& ... args)
        //{
        //    SlotEx<T, Key>::emplace(std::forward<TArgs>(args)...);
        //}
    };

    // demonstrating several slots with same type
    void test_03()
    {
        // again forward definition sufficient, definitions not needed
        struct Key1;
        struct Key2;

        // repository definition with keys
        using MyRepoEx =
            RepositoryEx<SlotEx<int>, SlotEx<std::string, Key1>, SlotEx<std::string, Key2>>;

        MyRepoEx repo{};

        repo.set(12345); // note type deduction: we pass an int, so it writes to the int slot
        repo.set<std::string, Key1>("ABC");
        repo.set<std::string, Key2>("123");

        std::cout << repo.get<int>() << std::endl; // printing 12345
        std::cout << repo.get<std::string, Key1>() << std::endl; // printing "ABC"
        std::cout << repo.get<std::string, Key2>() << std::endl; // printing "123"
    }

    // ===================================================================
    // Variant 4: adding 'emplace' mechanism for sample class 'Person'

    class Person 
    {
    private:
        std::string m_name;
        int m_age;

    public:
        Person() : m_name{}, m_age{} {}

        Person(const std::string& name, const int age)
        : m_name{ name }, m_age{age } {}

        // just for testing: if move-assignment is available, copy-assignment is ignored !!!
        Person& operator= (const Person& person) {
            // prevent self-assignment
            if (this == &person)
                return *this;

            // assign right side
            m_name = person.m_name;
            m_age = person.m_age;

            return *this;
        }

        Person& operator= (Person&& person) noexcept  { 
            // prevent self-assignment
            if (this == &person)
                return *this;

            // assign right side
            m_name = person.m_name;
            m_age = person.m_age;

            // reset source  object, ownership has been moved
            person.m_name.clear();
            person.m_age = 0;

            return *this;
        }

        std::string operator()() { 
            std::ostringstream oss; 
            oss << m_name << " [" << m_age << "]";
            return  oss.str();
        }
    };

    // demonstrating 'emplace' mechanism
    void test_04() 
    {
        using MyRepo = RepositoryEx<SlotEx<Person>, SlotEx<std::string>>;

        MyRepo repo{};

        repo.emplace<std::string>(std::string{ "ABCDEFGHIJK" });
        std::cout << repo.get<std::string>() << std::endl; // printing "ABCDEFGHIJK"

        repo.emplace<Person>(std::string{ "Hans" }, 21);
        std::cout << repo.get<Person>()() << std::endl; // printing "Hans [21]"
    }
}

void main_variadic_templates_mixins()
{
    using namespace VariadicTemplatesMixins;
    test_00();
    test_01();
    test_02();
    test_03();
    test_03_error();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
