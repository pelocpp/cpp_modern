// =====================================================================================
// Template Template Parameter
// =====================================================================================

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <optional>
#include <utility>

namespace TemplateTemplateParameter01 {

    //template <template <typename, typename...> class Container>
    //void bar(const Container<T>& c, const T& t)
    //{
    //    //
    //}

    //template<template <class> class ContainerT, class ValueT>
    //void foo(const ContainerT<ValueT>& c)
    //{
    //    typedef ContainerT<ValueT> type;
    //    for (typename  type::iterator it = c.begin(); it != c.end(); ++it)
    //    {
    //        // do some stuff
    //    }
    //}

    //template <template<typename> class ContainerT, typename ValueT>
    //void foo(const ContainerT<ValueT>& c)
    //{
    //    typedef ContainerT<ValueT> type1;
    //    for (typename type1::iterator it = c.begin(); it != c.end(); ++it)
    //    {
    //        // do some stuff
    //    }
    //}

    //template <template<typename> class ContainerT, typename ValueT>
    //void foo(const ContainerT<ValueT>& c)
    //{
    //    typedef ContainerT<ValueT> type1;
    //    for (typename type1::iterator it = c.begin(); it != c.end(); ++it)
    //    {
    //        // do some stuff
    //    }
    //}

    template <template <typename, typename> class Container, typename Value, typename Allocator = std::allocator<Value> >
    void bar(const Container<Value, Allocator>& container, const Value& t)
    {
        container.push_back(t);
        container.push_back(t);
        container.push_back(t);
        container.push_back(t);
        container.push_back(t);

        for (const auto& elem : container) {
            std::cout << elem << std::endl;
        }
    }

    //void _test_01_template_template_parameter() {

    //    std::vector<int> intVector;
    //    std::list<std::string> stringList;

    //    //foo(intVector);
    //    //foo(stringList);

    //}

    void _test_02_template_template_parameter() {

        std::vector<int> intVector;
        bar(intVector, 123);

        //std::vector<float> c;
        //bar(c, 1.2f);

        //std::list<std::string> stringList;
        //bar(stringList, std::string("werwer"));
    }
}

namespace TemplateTemplateParameter02 {

    template <typename T,
        template <typename E, typename Allocator = std::allocator<E>> class Container = std::vector>
    class Grid
    {
    public:
        explicit Grid(size_t width = kDefaultWidth, size_t height = kDefaultHeight);
        virtual ~Grid() = default;

        // Explicitly default a copy constructor and assignment operator.
        Grid(const Grid& src) = default;
        Grid<T, Container>& operator=(const Grid& rhs) = default;

        // Explicitly default a move constructor and assignment operator.
        Grid(Grid&& src) = default;
        Grid<T, Container>& operator=(Grid&& rhs) = default;

        std::optional<T>& at(size_t x, size_t y);
        const std::optional<T>& at(size_t x, size_t y) const;

        size_t getHeight() const { return mHeight; }
        size_t getWidth() const { return mWidth; }

        void testMe();

        static const size_t kDefaultWidth = 10;
        static const size_t kDefaultHeight = 10;

    private:
        void verifyCoordinate(size_t x, size_t y) const;

        std::vector<Container<std::optional<T>>> mCells;
        size_t mWidth = 0, mHeight = 0;

        Container<T> m_anotherContainer;
    };

    template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
    Grid<T, Container>::Grid(size_t width, size_t height)
        : mWidth(width)
        , mHeight(height)
    {
        mCells.resize(mWidth);
        for (auto& column : mCells) {
            column.resize(mHeight);
        }
    }

    template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
    void Grid<T, Container>::testMe() 
    {
        m_anotherContainer.push_back(1);
        m_anotherContainer.push_back(2);
        m_anotherContainer.push_back(3);

        for (const auto& elem : m_anotherContainer) {
            std::cout << elem << std::endl;
        }
    }


    template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
    void Grid<T, Container>::verifyCoordinate(size_t x, size_t y) const
    {
        if (x >= mWidth || y >= mHeight) {
            throw std::out_of_range("");
        }
    }

    template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
    const std::optional<T>& Grid<T, Container>::at(size_t x, size_t y) const
    {
        verifyCoordinate(x, y);
        return mCells[x][y];
    }

    template <typename T, template <typename E, typename Allocator = std::allocator<E>> class Container>
    std::optional<T>& Grid<T, Container>::at(size_t x, size_t y)
    {
        return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
    }

    void _test_02_template_template_parameter() {

        //Grid<int, std::vector> myGrid;
        //myGrid.at(1, 2) = 3;
        //std::cout << myGrid.at(1, 2).value_or(0) << std::endl;

        Grid<int, std::vector> myGrid2;
        myGrid2.testMe();

    }
}


int main() {

    using namespace TemplateTemplateParameter01;
   //  using namespace TemplateTemplateParameter02;

    _test_02_template_template_parameter();
  //   _test_02_template_template_parameter();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
