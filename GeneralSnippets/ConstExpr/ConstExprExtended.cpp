// =====================================================================================
// constexpr extended
// =====================================================================================

#include <iostream>
#include <limits>
#include <initializer_list>

namespace ConstExprExtended {

#if MY_COMPILER_DOESNT_ACCEPT_THIS_EXAMPLE

    template<typename T>
    class List
    {
        template<typename T2>
        friend std::ostream& operator<<(std::ostream&, const List<T2>&);
    public:
        constexpr List();
        constexpr List(std::initializer_list<T>);
        constexpr T head() const;
        constexpr List<T> tail() const;
        constexpr List<T> add(T) const;
        constexpr List<T> merge(List<T>) const;
        constexpr List<T> reverse() const;
        template<typename Filter>
        constexpr List<T> filter(Filter) const;
        constexpr List<T> sort() const;
        constexpr T sum() const;
    private:
        int length;
        T array[std::numeric_limits<int>::max() >> 2];
    };

    template<typename T>
    constexpr List<T>::List()
        : length{ 0 }
        , array{ 0 }
    {
    }

    template<typename T>
    constexpr List<T>::List(std::initializer_list<T> l)
        : length{ static_cast<int>(l.size()) }
        , array{ 0 }
    {
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            array[it - l.begin()] = *it;
        }
    }

    template<typename T>
    constexpr T List<T>::head() const
    {
        return array[0];
    }

    template<typename T>
    constexpr List<T> List<T>::tail() const
    {
        List<T> l;
        l.length = length - 1;
        for (int i = 0; i < l.length; ++i)
        {
            l.array[i] = array[i + 1];
        }
        return l;
    }

    template<typename T>
    constexpr List<T> List<T>::add(T t) const
    {
        List<T> l{ *this };
        l.array[l.length++] = t;
        return l;
    }

    template<typename T>
    constexpr List<T> List<T>::merge(List<T> l) const
    {
        for (int i = l.length - 1; i >= 0; --i)
        {
            l.array[i + length] = l.array[i];
        }
        for (int i = 0; i < length; ++i)
        {
            l.array[i] = array[i];
        }
        l.length += length;
        return l;
    }

    template<typename T>
    constexpr List<T> List<T>::reverse() const
    {
        List<T> l;
        l.length = length;
        for (int i = 0; i < l.length; ++i)
        {
            l.array[i] = array[length - i - 1];
        }
        return l;
    }

    template<typename T>
    template<typename Filter>
    constexpr List<T> List<T>::filter(Filter f) const
    {
        List<T> l;
        for (int i{ 0 }; i < length; ++i)
        {
            if (f(array[i]))
            {
                l = l.add(array[i]);
            }
        }
        return l;
    }

    template<typename T>
    struct LT
    {
        T pivot;
        constexpr bool operator()(T t) const
        {
            return t < pivot;
        }
    };

    template<typename T>
    struct GE
    {
        T pivot;
        constexpr bool operator()(T t) const
        {
            return t >= pivot;
        }
    };

    template<typename T>
    constexpr List<T> List<T>::sort() const
    {
        if (length == 0)
        {
            return *this;
        }
        return tail().filter(LT<T> {head()}).sort().add(head())
            .merge(tail().filter(GE<T> {head()}).sort());
    }

    template<typename T>
    constexpr T List<T>::sum() const
    {
        if (length == 0)
        {
            return T{};
        }
        return head() + tail().sum();
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const List<T>& l)
    {
        os << '{';
        for (int i{ 0 }; i < l.length - 1; ++i)
        {
            os << l.array[i] << ", ";
        }
        return os << l.array[l.length - 1] << '}';
    }

    inline constexpr List<int> range(int a, int b, int c = 1)
    {
        List<int> l;
        while (a < b)
        {
            l = l.add(a);
            a += c;
        }
        return l;
    }

#endif

    void test_01() {
        // my compiler doesn't accept this statement :-)

        // constexpr std::size_t n = range(0, 300).reverse().sort().sum();
        // std::cout << n << std::endl;
    }
}

void main_constexpr_extended()
{
    using namespace ConstExprExtended;
    test_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
