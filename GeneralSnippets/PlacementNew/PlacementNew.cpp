// =====================================================================================
// PlacementNew.cpp
// =====================================================================================

module modern_cpp:placement_new;

namespace PlacementNew {

    class User
    {
    private:
        std::string m_name;
        int         m_age;

    public:
        User(std::string name, int age)
            : m_name{ name }, m_age{ age }
        {
            std::cout << "C'tor User" << std::endl;
        }

        ~User() {
            std::cout << "D'tor User" << std::endl;
        }

        void print() const {
            std::cout << "Name: " << m_name << " - Age: " << m_age << '.' << std::endl;
        }
    };

    unsigned char global_memory[sizeof(class User)];

    static void test_00()
    {
        auto* user{ ::new (global_memory) User{"John" , 50} };
        user->print();
        user->~User();
    }

    static void test_01()
    {
        auto* memory{ std::malloc(sizeof(class User)) };
        auto* user{ ::new (memory) User{"John" , 50} };
        user->print();
        user->~User();
        std::free(memory);
    }

    // https://www.sandordargo.com/blog/2022/02/02/stl-alogorithms-tutorial-part-30-memory-header

    static void test_02()
    {
        auto* memory{ std::malloc(sizeof(class User)) };
        auto* user_ptr{ reinterpret_cast<User*>(memory) };
        std::uninitialized_fill_n(user_ptr, 1, User{ "John" , 50 });
        user_ptr->print();
        std::destroy_at(user_ptr);
        std::free(memory);
    }

    static void test_03()
    {
        auto* memory{ std::malloc(sizeof(class User)) };
        auto* user_ptr{ reinterpret_cast<User*>(memory) };
        std::construct_at(user_ptr, User{ "John" , 50 });
        user_ptr->print();
        std::destroy_at(user_ptr);
        std::free(memory);
    }

    // ===========================================================

    template <class T>
    class Vector
    {
    private:
        size_t m_capacity;
        size_t m_size;
        T* m_data;

    public:
        Vector() :
            m_capacity{ 10 },
            m_size{},
            m_data{ new T[m_capacity] }
        {}

        ~Vector()
        {
            delete[] m_data;
        }
    };

    class Point
    {
    private:
        int m_x;
        int m_y;

    public:
        Point(int a, int b) : m_x{ a }, m_y{ b } {}

        Point(const Point& other) : m_x{ other.m_x }, m_y{ other.m_y } {
            std::cout << "copy c'tor: " << m_x << ", y: " << m_y << '.' << std::endl;
        }

        Point(Point&& other) : m_x{ other.m_x }, m_y{ other.m_y } {
            std::cout << "move c'tor: " << m_x << ", y: " << m_y << '.' << std::endl;
        }

        ~Point()
        {
            std::cout << "d'tor" << std::endl;
        }

        // getter
        double X() const { return m_x; }
        double Y() const { return m_y; }

        // public interface
        void print() const {
            std::cout << "x: " << m_x << ", y: " << m_y << '.' << std::endl;
        }
    };

    //class Point {
    //public:
    //    // c'tors
    //    Point() : Point{ 0.0, 0.0 } {}
    //    Point(double x, double y) : m_x{ x }, m_y{ y } {}

    //    // getter
    //    double X() const { return m_x; }
    //    double Y() const { return m_y; }

    //private:
    //    double m_x;
    //    double m_y;
    //};

    static void test_04()
    {
        Vector<int> a;
        // Vector<Point> b;  // ERror: Point type does not have a default constructor
    }

    static void test_05()
    {
        size_t capacity{ 10 };

        auto* memory{ std::malloc(sizeof(class Point) * capacity) };

        auto* data{ reinterpret_cast<class Point*>(memory) };

        class Point* node = new (static_cast<void*>(&data[0])) Point{ 123, 456 };

        node->print();

        class Point* node2 = new (static_cast<void*>(&data[1])) Point{ 654, 321 };

        node2->print();
    }

    // ===========================================================

    template <class T>
    class VectorEx
    {
    private:
        size_t m_capacity;
        size_t m_size;
        T* m_data;

    public:
        VectorEx() :
            m_capacity{ 10 },
            m_size{},
            m_data{ static_cast<T*>(std::malloc(sizeof(T) * m_capacity)) }
            // m_data{ new T[m_capacity] }
        {}

        void push_back(const T& value) {
            //void* ptr = m_data + (m_size++);
            //new (ptr) T(value);

            void* ptr = m_data + m_size;
            new (ptr) T{ value };
            m_size++;
        }

        void push_back(T&& value) {
            //void* ptr = m_data + (m_size++);
            //new (ptr) T(value);

            void* ptr = m_data + m_size;
            new (ptr) T{ std::move(value) };
            m_size++;
        }

        void pop_back() {
            // m_data[m_size--].~T();

            m_size--;
            m_data[m_size].~T();

        }

        ~VectorEx()
        {
            while (m_size) {
                pop_back();
            }

            std::free(m_data);
        }
    };

    static void test_06()
    {
        VectorEx<Point> vec;

        for (int i{}; i < 5; ++i) {
            vec.push_back(Point{ i, i });
        }
    }

    // ===========================================================


}

void main_placement_new()
{
    using namespace PlacementNew;

    test_01(); 
    test_02();
    test_03();
    test_04();
    test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
