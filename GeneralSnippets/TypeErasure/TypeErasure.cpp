// =====================================================================================
// TypeErasure.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp:type_erasure;

namespace {
    size_t MaxIterations = 1000000;
    //size_t MaxIterations = 100000;
}

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

namespace BookStoreUsingDynamicPolymorphism {

    struct IMedia
    {
        virtual ~IMedia() = default;

        virtual double getPrice() const = 0;
        virtual size_t getCount() const = 0;
    };

    class Book : public IMedia
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        size_t      m_count;

    public:
        Book(std::string author, std::string title, double price, size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {}

        // getter / setter
        std::string getAuthor() const { return m_author; }
        std::string getTitle() const { return m_title; }

        double getPrice() const override { return m_price; }
        size_t getCount() const override { return m_count; }
    };

    class Movie : public IMedia
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        size_t      m_count;

    public:
        Movie(std::string title, std::string director, double price, size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        { }

        // getter / setter
        std::string getTitle() const { return m_title; }
        std::string getDirector() const { return m_director; }

        double getPrice() const override { return m_price; }
        size_t getCount() const override { return m_count; }
    };

    class Bookstore
    {
    private:
        using Stock = std::vector<std::shared_ptr<IMedia>>;
        using StockList = std::initializer_list<std::shared_ptr<IMedia>>;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        void addMedia(const std::shared_ptr<IMedia>& media) {
            m_stock.push_back(media);
        }

        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {
                total += media->getPrice() * media->getCount();
            }

            return total;
        }

        size_t count() const {

            size_t total{};

            for (const auto& media : m_stock) {
                total += media->getCount();
            }

            return total;
        }

    private:
        Stock m_stock;
    };

    static void test_bookstore_polymorphic_01() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> javaBook{ std::make_shared<Book>("Java", "James Gosling", 17.99, 21) };
        std::shared_ptr<IMedia> cppBook{ std::make_shared<Book>("C++", "Bjarne Stroustrup", 16.99, 4) };
        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_02() {

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };
        std::shared_ptr<IMedia> movieBond{ std::make_shared<Movie>("Spectre", "Sam Mendes", 8.99, 6) };

        Bookstore bookstore{ cBook, movieBond };

        std::shared_ptr<IMedia> csharpBook{ std::make_shared<Book>("C#", "Anders Hejlsberg", 21.99, 8) };
        bookstore.addMedia(csharpBook);

        std::shared_ptr<IMedia> movieTarantino{ std::make_shared<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3) };
        bookstore.addMedia(movieTarantino);

        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_03() {

        std::println("Benchmark - Method Call - using Polymorphism");

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };

        ScopedTimer watch{};

        double total{};
        for (size_t i{}; i != MaxIterations; ++i) {
            total += cBook->getCount() * cBook->getPrice();
        }

        std::print("Done: ");
    }

    static void test_bookstore_polymorphic_04() {

        std::println("Benchmark - Iterating a Container of Shared Pointers - using Polymorphism");

        Bookstore bookstore{ };

        std::shared_ptr<IMedia> cBook{ std::make_shared<Book>("C", "Dennis Ritchie", 11.99, 12) };

        for (size_t i{}; i != 100; ++i) {
            bookstore.addMedia(cBook);
        }

        ScopedTimer watch{};

        double total{};
        for (size_t i{}; i != MaxIterations; ++i) {
            double totalBalance{ bookstore.totalBalance() };
            total += totalBalance;
        }

        std::print("Done: ");
    }
}

// =====================================================================================

namespace BookStoreUsingTypeErasure {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        size_t      m_count;

    public:
        Book(std::string author, std::string title, double price, size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        { }

        // getter / setter
        std::string getAuthor() const { return m_author; }
        std::string getTitle() const { return m_title; }

        double getPrice() const { return m_price; }
        size_t getCount() const { return m_count; }
    };

    class Movie
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        size_t      m_count;

    public:
        Movie(std::string title, std::string director, double price, size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        { }

        // getter / setter
        std::string getTitle() const { return m_title; }
        std::string getDirector() const { return m_director; }

        double getPrice() const { return m_price; }
        size_t getCount() const { return m_count; }
    };

    template<typename T>
    concept MediaConcept = requires (const T & m)
    {
        { m.getPrice() } -> std::same_as<double>;
        { m.getCount() } -> std::same_as<size_t>;
    };

    template <typename ... TMedia>
        requires (MediaConcept<TMedia> && ...)
    class Bookstore
    {
    private:
        using StockType = std::variant<TMedia ...>;
        using Stock = std::vector<StockType>;
        using StockList = std::initializer_list<StockType>;

    public:
        explicit Bookstore(StockList stock) : m_stock{ stock } {}

        // template member method
        template <typename T>
        void addMedia(const T& media) {
            // m_stock.push_back(StockType{ media });  // ausführliche Schreibweise
            m_stock.push_back(media);
        }

        // or
        void addMediaEx(const auto& media) {
            m_stock.push_back(media);
        }

        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {

                double price{};
                size_t count{};

                std::visit(
                    [&](const auto& element) {
                        price = element.getPrice();
                        count = element.getCount();
                    },
                    media
                );

                total += price * count;
            }

            return total;
        }

        size_t count() const {

            size_t total{};

            for (const auto& media : m_stock) {

                size_t count{};

                std::visit(
                    [&](const auto& element) {
                        count = element.getCount();
                    },
                    media
                );

                total += count;
            }

            return total;
        }

        // -----------------------------------------------
        // demonstrating std::visit with returning a value

        double totalBalanceEx() const {

            double total{};

            for (const auto& media : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        double price = element.getPrice();
                        size_t count = element.getCount();
                        return price * count;
                    },
                    media
                );
            }

            return total;
        }

        size_t countEx() const {

            size_t total{};

            for (const auto& element : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        return element.getCount();
                    },
                    element
                );
            }

            return total;
        }

    private:
        Stock m_stock;
    };

    static void test_bookstore_type_erasure_01() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Book javaBook{ "Java", "James Gosling", 17.99, 21 };
        Book cppBook{ "C++", "Bjarne Stroustrup", 16.99, 4 };
        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{
            cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);
        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_02() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{ cBook, movieBond };

        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };
        bookstore.addMedia(csharpBook);

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        bookstore.addMediaEx(movieTarantino);

        size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_03() {

        std::println("Benchmark - Method Call - using Type Erasure");

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };

        ScopedTimer watch{};

        double total{};
        for (size_t i{}; i != MaxIterations; ++i) {
            total += cBook.getCount() * cBook.getPrice();
        }

        std::print("Done: ");
    }

    static void test_bookstore_type_erasure_04() {

        std::println("Benchmark - Iterating a Container of std:variants - using Type Erasure");
        
        Bookstore<Book, Movie> bookstore{ };

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };

        for (size_t i{}; i != 100; ++i) {
            bookstore.addMedia(cBook);
        }

        ScopedTimer watch{};

        double total{};
        for (size_t i{}; i != MaxIterations; ++i) {
            double totalBalance{ bookstore.totalBalance() };
            total += totalBalance;
        }

        std::print("Done: ");
    }

    class BluRay
    {
    public:
        BluRay() = default;

        // getter / setter
        size_t getCount() const { return 0; }
        double getPrice() const { return 0.0; }   // put into comments
    };

    static void test_bookstore_type_erasure_05() {

        // verifying concept 'MediaConcept'
        Bookstore<Book, BluRay, Movie> bookstore{};
    }
}

// =====================================================================================

void main_type_erasure()
{
    using namespace TypeErasureUsingDynamicPolymorphism;
    using namespace TypeErasureUsingTemplateTechniques;
    using namespace TypeErasureUsingTemplateTechniquesAndConcepts;
    using namespace BookStoreUsingDynamicPolymorphism;
    using namespace BookStoreUsingTypeErasure;

    TypeErasureUsingDynamicPolymorphism::test_type_erasure_using_dynamic_polymorphism();
    TypeErasureUsingTemplateTechniques::test_type_erasure_using_template_techniques();
    TypeErasureUsingTemplateTechniquesAndConcepts::test_type_erasure_using_template_techniques();

    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_01();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_02();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_03();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_04();

    BookStoreUsingTypeErasure::test_bookstore_type_erasure_01();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_02();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_03();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================

