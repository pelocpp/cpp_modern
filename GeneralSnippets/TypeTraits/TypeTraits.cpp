// =====================================================================================
// TypeTraits.cpp // Typmerkmale // Type Traits
// =====================================================================================

module modern_cpp:type_traits;

namespace TypeTraits_Simple_Demo
{
    // primary template
    template <typename T>
    struct is_this_a_floating_point
    {
        static constexpr bool value = false;
    };

    // explicit (full) specialization
    template <>
    struct is_this_a_floating_point<float>
    {
        static constexpr bool value = true;
    };

    template <>
    struct is_this_a_floating_point<double>
    {
        static constexpr bool value = true;
    };

    template <>
    struct is_this_a_floating_point<long double>
    {
        static constexpr bool value = true;
    };

    void test_1a()
    {
        static_assert(is_this_a_floating_point<float>::value);
        static_assert(is_this_a_floating_point<double>::value);
        static_assert(is_this_a_floating_point<long double>::value);

        static_assert(! is_this_a_floating_point<int>::value);
        static_assert(! is_this_a_floating_point<bool>::value);
    }

    template <typename T>
    void process_a_floating_point(T value)
    {
        static_assert(is_this_a_floating_point<T>::value);
        std::cout << "processing a real number: " << value << std::endl;
    }

    void test_1b()
    {
        process_a_floating_point(42.0);
        // process_a_floating_point(42);  // does'n t compile: static assertion fails
    }

    void test_01()
    {
        test_1a();
        test_1b();
    }
}

// =================================================================================

namespace TypeTraits_Second_Simple_Demo
{
    // primary template
    template <typename T>
        struct my_remove_reference {
        using type = T;
    };

    // explicit (partial) specialization
    template <typename T>
    struct my_remove_reference<T&> {
        using type = T;
    };

    // primary template
    template<class T, class U>
    struct my_is_same
    {
        static constexpr bool value = false;
    };

    // template (partial) specialization  
    template<class T>
    struct my_is_same<T, T>
    {
        static constexpr bool value = true;
    };

    void test_02_a()
    {
        using SomeType = const double&;
        using SomeTypeWithoutRef = std::remove_reference<SomeType>::type;
        using SomeTypeWithoutRefAndConst = std::remove_const<SomeTypeWithoutRef>::type;

        static_assert(std::is_same<SomeTypeWithoutRefAndConst, double>::value == true);

        using SomeTypeWithoutRef2 = my_remove_reference<SomeType>::type;
        using SomeTypeWithoutRefAndConst2 = std::remove_const<SomeTypeWithoutRef2>::type;

        static_assert(std::is_same<SomeTypeWithoutRefAndConst2, double>::value == true);
    }

    void test_02_b()
    {
        static_assert(my_is_same<int, double>::value == false);
        static_assert(my_is_same<int, int>::value == true);
    }

    void test_02()
    {
        test_02_a();
        test_02_b();
    }
}

// =================================================================================

namespace TypeTraits_Conditional_Compilation_Demo {

    class Widget
    {
    private:
        int m_id;
        std::string m_name;

    public:
        Widget() : Widget { 0, ""} {}
        Widget (int id, std::string name) : m_id{ id}, m_name{ name } {}

        std::ostream& write(std::ostream& os) const
        {
            os << m_id << ", " << m_name << '\n';
            return os;
        }
    };

    class Gadget
    {
    private:
        int m_id;
        std::string m_name;

    public:
        Gadget() : Gadget{ 0, "" } {}
        Gadget(int id, std::string name) : m_id{ id }, m_name{ name } {}

        int getId() const { return m_id; }
        std::string getName() const { return m_name; }
    };

    std::ostream& operator <<(std::ostream& os, const Gadget& gadget)
    {
        os << gadget.getId() << ", " << gadget.getName() << '\n';
        return os;
    }

    void test_3a()
    {
        Widget widget{ 1, "I'm a Widget" };
        Gadget gadget{ 2, "I'm a Gadget" };

        widget.write(std::cout);
        std::cout << gadget;
    }

    template <typename T>
    struct uses_write
    {
        static constexpr bool value = false;
    };

    template <>
    struct uses_write<Widget>
    {
        static constexpr bool value = true;
    };

    // primary (class) template
    template <bool>
    struct Serializer
    {
        template <typename T>
        static void serialize(std::ostream& os, T const& value)
        {
            os << value;
        }
    };

    template<>
    struct Serializer<true>
    {
        template <typename T>
        static void serialize(std::ostream& os, T const& value)
        {
            value.write(os);
        }
    };

    // free function template - based on class Serializer<T>
    template <typename T>
    void serialize(std::ostream& os, T const& obj)
    {
        Serializer<uses_write<T>::value>::serialize(os, obj);
    }

    void test_3b()
    {
        Widget widget{ 1, "I'm a Widget" };
        Gadget gadget{ 2, "I'm a Gadget" };

        serialize(std::cout, widget);
        serialize(std::cout, gadget);
    }

    void test_3c()
    {
        Widget widget{ 1, "I'm a Widget" };
        Gadget gadget{ 2, "I'm a Gadget" };

        serialize<Widget>(std::cout, widget);
        serialize<Gadget>(std::cout, gadget);
    }

    void test_03()
    {
        test_3a();
        test_3b();
        test_3c();
    }
}

// =================================================================================

namespace TypeTraits_Iterator_Demo
{
    void whichIterator(const std::input_iterator_tag)
    {
        std::cout << "[Input Iterator]" << std::endl;
    }

    void whichIterator(const std::output_iterator_tag)
    {
        std::cout << "[Output Iterator]" << std::endl;
    }

    void whichIterator(const std::forward_iterator_tag)
    {
        std::cout << "[Forward Iterator]" << std::endl;
    }

    void whichIterator(const std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Iterator Iterator]" << std::endl;
    }

    void whichIterator(const std::random_access_iterator_tag)
    {
        std::cout << "[Random Access Iterator]" << std::endl;
    }

    template <typename TIterator>
    auto getIteratorType(const TIterator&)
    {
        typename std::iterator_traits<TIterator>::iterator_category tag{};
        return tag;
    }

    void test_4a()
    {
        std::vector<int> vec;
        whichIterator(getIteratorType(vec.begin()));

        // oder:
        std::vector<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::vector<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_4b()
    {
        std::list<int> list;
        whichIterator(getIteratorType(list.begin()));

        // oder:
        std::list<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::list<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_4c()
    {
        std::forward_list<int> fwlist;
        whichIterator(getIteratorType(fwlist.begin()));

        // oder:
        std::forward_list<int>::iterator it;
        whichIterator(getIteratorType(it));

        // oder:
        std::forward_list<int>::iterator::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_4d()
    {
        std::ifstream source;
        std::istream_iterator<int> input(source);
        whichIterator(getIteratorType(input));

        // oder:
        std::istream_iterator<int> it{};
        whichIterator(getIteratorType(it));

        // oder:
        std::istream_iterator<int>::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_4e()
    {
        std::ofstream source;
        std::ostream_iterator<int> output(source);
        whichIterator(getIteratorType(output));

        // oder:
        // std::ostream_iterator<int> has no default c'tor

        // oder:
        std::ostream_iterator<int>::iterator_category iter_cat{};
        whichIterator(iter_cat);
    }

    void test_04()
    {
        test_4a();
        test_4b();
        test_4c();
        test_4d();
        test_4e();
    }
}

// =================================================================================

namespace TypeTraits_Second_Iterator_Demo
{
    template <typename Iterator>
    using ValueType = typename Iterator::value_type;

    template <typename Iterator>
    using Category = typename Iterator::iterator_category;

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::forward_iterator_tag)
    {
        std::cout << "[Forward Iterator] ";
        Iterator pos = it;
        for (size_t i{}; i != position; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::bidirectional_iterator_tag)
    {
        std::cout << "[Bidirectional Access] ";
        Iterator pos = it;
        for (size_t i{}; i != position; ++i)
            ++pos;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t position, std::random_access_iterator_tag)
    {
        std::cout << "[Random Access] ";
        Iterator pos = it + position;
        return *pos;
    }

    template <typename Iterator>
    ValueType<Iterator> getAt(Iterator it, size_t size)
    {
        Category<Iterator> category{};
        return getAt(it, size, category);
    }

    void test_05() 
    {
        std::forward_list<char> charList{ 'A', 'B', 'C', 'D', 'E' };
        char ch = getAt(charList.begin(), 3);
        std::cout << "std::forward_list: " << ch << std::endl;

        std::list<int> intList{ 1, 2, 3, 4, 5 };
        int value = getAt(intList.begin(), 3);
        std::cout << "std::list:     " << value << std::endl;

        std::vector<int> doubleVector{ 10, 20, 30, 40, 50 };
        double d = getAt(doubleVector.begin(), 3);
        std::cout << "std::vector:          " << d << std::endl;
    }
}

// =================================================================================

namespace TypeTraits_Demo_Remove_Reference
{
    template<typename Container>
    void sort_01(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            [](auto n1, auto n2) -> bool {
                return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_02(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            [](typename Container::value_type n1, typename Container::value_type n2) {
                return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_03(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            []( decltype (container[0]) n1, 
                decltype (container[0]) n2) {
                    return n1 < n2;
            }
        );
    }

    template<typename Container>
    void sort_04(Container& container)
    {
        std::sort(
            std::begin(container),
            std::end(container),
            []( std::remove_reference<decltype (container[0])>::type n1,
                std::remove_reference<decltype (container[0])>::type n2) {
                    return n1 < n2;
            }
        );
    }

    void test_06()
    {
        std::vector<int> vec{ 5, 4, 6, 3, 7, 2, 8, 1, 9 };

        sort_01<std::vector<int>>(vec);
        sort_02<std::vector<int>>(vec);
        sort_03<std::vector<int>>(vec);
        sort_04<std::vector<int>>(vec);

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;
    }
}

// =================================================================================

void main_type_traits()
{
    using namespace TypeTraits_Simple_Demo;
    using namespace TypeTraits_Second_Simple_Demo;
    using namespace TypeTraits_Conditional_Compilation_Demo;
    using namespace TypeTraits_Iterator_Demo;
    using namespace TypeTraits_Second_Iterator_Demo;
    using namespace TypeTraits_Demo_Remove_Reference;

    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
