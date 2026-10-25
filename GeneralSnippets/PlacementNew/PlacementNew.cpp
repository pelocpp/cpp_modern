// =====================================================================================
// PlacementNew.cpp
// =====================================================================================

module modern_cpp:placement_new;

import std;

namespace {

    class User
    {
    private:
        std::string m_name;
        int m_age;

    public:
        User(const std::string& name, int age)
            : m_name{ name }, m_age{ age }
        {
            std::cout << "c'tor User" << std::endl;
        }

        ~User() {
            std::cout << "d'tor User" << std::endl;
        }

        User(const User& other) 
            : m_name{ other.m_name }, m_age{ other.m_age }
        {
            std::cout << "copy c'tor: " << m_name << " - " << m_age << '.' << std::endl;
        }

        User(User&& other) noexcept 
            : m_name{ std::move(other.m_name) }, m_age{ other.m_age }
        {
            std::cout << "move c'tor: " << m_name << " - " << m_age << '.' << std::endl;
        }

        // getter
        double getAge () const { return m_age; }
        std::string getName() const { return m_name; }

        // public interface
        void print() const {
            std::cout << "Name: " << m_name << " - Age: " << m_age << '.' << std::endl;
        }
    };

    // =================================================================================

    unsigned char global_memory[ sizeof(User) ];

    void placement_new_01()
    {
        auto* user{ ::new (global_memory) User{"John" , 50} };
        user->print();
        user->~User();
    }

    void placement_new_02()
    {
        auto* memory{ std::malloc(sizeof(User)) };
        auto* user{ ::new (memory) User{"John" , 50} };
        user->print();
        user->~User();
        std::free(memory);
    }

    void placement_new_03()
    {
        auto* memory{ std::malloc(sizeof(User)) };
        auto* user_ptr{ reinterpret_cast<User*>(memory) };
        std::uninitialized_fill_n(user_ptr, 1, User{ "John" , 50 });
        user_ptr->print();
        std::destroy_at(user_ptr);
        std::free(memory);
    }

    void placement_new_04()
    {
        auto* memory{ std::malloc(sizeof(User)) };
        auto* user_ptr{ reinterpret_cast<User*>(memory) };
        std::construct_at(user_ptr, User{ "John" , 50 });
        user_ptr->print();
        std::destroy_at(user_ptr);
        std::free(memory);
    }

    // -----------------------------------------------------------------------------

    template <class T>
    class Vector
    {
    private:
        T* m_data;

    public:
        Vector() : m_data{ new T[10] } {}
        ~Vector() { delete[] m_data; }
    };

    void placement_new_05()
    {
        Vector<int> a;
        // Vector<User> b;  // Error: User type doesn't have a default c'tor
    }

    void placement_new_06()
    {
        std::size_t capacity{ 2 };

        auto* memory{ std::malloc(sizeof(User) * capacity) };

        auto* data{ reinterpret_cast<User*>(memory) };

        User* node = ::new (static_cast<void*>(&data[0])) User{ "John", 30 };

        node->print();

        User* node2 = ::new (static_cast<void*>(&data[1])) User{ "Jack", 50 };

        node2->print();
    }

    // ===========================================================

    template <class T>
    class VectorEx
    {
    private:
        std::size_t m_capacity;
        std::size_t m_size;
        T* m_data;

    public:
        VectorEx() :
            m_capacity{ 10 },
            m_size{},
            m_data{ reinterpret_cast<T*>(std::malloc(sizeof(T) * m_capacity)) }
        {}

        ~VectorEx()
        {
            while (m_size) {
                pop_back();
            }

            std::free(m_data);
        }

        void push_back(const T& value)
        {
            T* ptr{ m_data + m_size };
            new (ptr) T{ value };
            ++m_size;
        }

        void push_back(T&& value)
        {
            T* ptr{ m_data + m_size };
            new (ptr) T{ std::move(value) };
            ++m_size;
        }

        void pop_back() {

            --m_size;
            m_data[m_size].~T();
        }
    };

    void placement_new_07()
    {
        VectorEx<User> vec;

        for (int i{}; i < 5; ++i) {
            vec.push_back(User{ "Sepp", 40 });
        }
    }
}

void main_placement_new()
{
    placement_new_01(); 
    placement_new_02();
    placement_new_03();
    placement_new_04();
    placement_new_05();
    placement_new_06();
    placement_new_07();
}

// =====================================================================================
// End-of-File
// =====================================================================================
