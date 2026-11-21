// =====================================================================================
// TypeErasure_Bookstore.cpp - Static versus Dynamic Polymorphism
// =====================================================================================

module modern_cpp:type_erasure;

import std;
import scoped_timer;

// =====================================================================================

namespace {
    std::size_t MaxIterations = 1'000'000;
}

// =====================================================================================
// Classic Implementation: Using Inheritance, Polymorphism, virtual methods
// =====================================================================================

namespace BookStoreUsingDynamicPolymorphism {

    struct IMedia
    {
        virtual ~IMedia() = default;

        virtual double getPrice() const = 0;
        virtual std::size_t getCount() const = 0;
    };

    template <typename T>
    concept MediaPtr = std::convertible_to<T, std::unique_ptr<IMedia>>;

    class Book : public IMedia
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        std::size_t m_count;

    public:
        // c'tor
        Book(const std::string& author, const std::string& title, double price, std::size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {}

        // getter / setter
        const std::string& getAuthor() const { return m_author; }
        const std::string& getTitle() const { return m_title; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        std::size_t getCount() const override { return m_count; }
    };

    class Movie : public IMedia
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        std::size_t m_count;

    public:
        // c'tor
        Movie(const std::string& title, const std::string& director, double price, std::size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        { }

        // getter / setter
        const std::string& getTitle() const { return m_title; }
        const std::string& getDirector() const { return m_director; }

        // interface 'IMedia'
        double getPrice() const override { return m_price; }
        std::size_t getCount() const override { return m_count; }
    };

    class Bookstore
    {
    public:
        using Stock = std::vector<std::unique_ptr<IMedia>>;

    private:
        Stock m_stock;

    public:
        // c'tor(s)
        Bookstore() = default;

        explicit Bookstore(Stock stock) : m_stock(std::move(stock)) {}

        template <MediaPtr... TArgs>
            requires (sizeof...(TArgs) > 0)
        explicit Bookstore(TArgs&&... items)
        {
            m_stock.reserve(sizeof...(TArgs));
            (m_stock.emplace_back(std::forward<TArgs>(items)), ...);
        }

        // public interface
        [[nodiscard]]
        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {
                total += media->getPrice() * media->getCount();
            }

            return total;
        }

        [[nodiscard]]
        std::size_t count() const {

            std::size_t total{};

            for (const auto& media : m_stock) {
                total += media->getCount();
            }

            return total;
        }

        void addMedia(std::unique_ptr<IMedia> media) {
            m_stock.push_back(std::move(media));
        }
    };

    static void test_bookstore_polymorphic_01() {

        // Note: The braced-list construction does not work here
        // because unique_ptr objects need push_back plus std::move.

        Bookstore::Stock stock;

        stock.push_back(std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12));
        stock.push_back(std::make_unique<Movie>("Spectre", "Sam Mendes", 8.99, 6));
        stock.push_back(std::make_unique<Book>("Java", "James Gosling", 17.99, 21));
        stock.push_back(std::make_unique<Book>("C++", "Bjarne Stroustrup", 16.99, 4));
        stock.push_back(std::make_unique<Book>("C#", "Anders Hejlsberg", 21.99, 8));
        stock.push_back(std::make_unique<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3));

        Bookstore bookstore{ std::move(stock) };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_02() {

        Bookstore bookstore{
            std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12),
            std::make_unique<Book>("Java", "James Gosling", 17.99, 21),
            std::make_unique<Book>("C++", "Bjarne Stroustrup", 16.99, 4),
            std::make_unique<Book>("C#", "Anders Hejlsberg", 21.99, 8),

            std::make_unique<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3),
            std::make_unique<Movie>("Spectre", "Sam Mendes", 8.99, 6)
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_03() {

        Bookstore bookstore{
            std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12),
            std::make_unique<Movie>("Spectre", "Sam Mendes", 8.99, 6)
        };

        bookstore.addMedia(std::make_unique<Book>("C#", "Anders Hejlsberg", 21.99, 8));
        bookstore.addMedia(std::make_unique<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3));

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_polymorphic_04() {

        std::println("Benchmark - Method Call - using Polymorphism");

        std::unique_ptr<IMedia> cBook{ std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12) };

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            total += cBook->getCount() * cBook->getPrice();
        }
        std::println("Total: {}", total);

        std::print("Done: ");
    }

    static void test_bookstore_polymorphic_05() {

        std::println("Benchmark - Iterating a Container of Unique  Pointers - using Polymorphism");

        Bookstore bookstore;

        for (std::size_t i{}; i != 100; ++i) {
            bookstore.addMedia(std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12));
        }

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            double totalBalance{ bookstore.totalBalance() };
            total += totalBalance;
        }
        std::println("Total: {}", total);

        std::print("Done: ");
    }

    class BluRay
    {
    public:
        BluRay() = default;

        // getter / setter
        std::size_t getCount() const { return 0; }
        double getPrice() const { return 0.0; }   // put into comments
    };

    static void test_bookstore_type_erasure_06() {

        // verifying concept 'MediaConcept'
        //Bookstore<Book, BluRay, Movie> bookstore;

        Bookstore bookstore;

    //    bookstore.addMedia(std::make_unique<BluRay>());
    }
}

// =====================================================================================
// Alternate Modern C++ Implementation: Using std::variant, std::visit, Variadic Templates
// =====================================================================================

namespace BookStoreUsingTypeErasure {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        std::size_t m_count;

    public:
        // c'tor
        Book(const std::string& author, const std::string& title, double price, std::size_t count)
            : m_author{ author }, m_title{ title }, m_price{ price }, m_count{ count }
        {}

        // getter / setter
        const std::string& getAuthor() const { return m_author; }
        const std::string& getTitle() const { return m_title; }

        double getPrice() const { return m_price; }
        std::size_t getCount() const { return m_count; }
    };

    class Movie
    {
    private:
        std::string m_title;
        std::string m_director;
        double      m_price;
        std::size_t m_count;

    public:
        // c'tor
        Movie(const std::string& title, const std::string& director, double price, std::size_t count)
            : m_title{ title }, m_director{ director }, m_price{ price }, m_count{ count }
        {}

        // getter / setter
        const std::string& getTitle() const { return m_title; }
        const std::string& getDirector() const { return m_director; }

        double getPrice() const { return m_price; }
        std::size_t getCount() const { return m_count; }
    };

    template<typename T>
    concept MediaConcept = requires (const std::remove_cvref<T>::type& media)
    {
        { media.getPrice() } -> std::same_as<double>;
        { media.getCount() } -> std::same_as<std::size_t>;
    };

    template <MediaConcept ... TMedia>
        requires (sizeof...(TMedia) > 0)
    class Bookstore
    {
    public:
        using StockType = std::variant<TMedia ...>;
        using Stock = std::vector<StockType>;

    private:
        Stock m_stock;

    public:
        // c'tor(s)
        Bookstore() = default;

        explicit Bookstore(Stock stock) : m_stock(std::move(stock)) {}

        template <typename... TArgs>
            requires (sizeof...(TArgs) > 0 && (std::constructible_from<StockType, TArgs> && ...))
        explicit Bookstore(TArgs&&... items)
        {
            m_stock.reserve(sizeof...(TArgs));
            (m_stock.emplace_back(std::forward<TArgs>(items)), ...);
        }

        // template member method
        template <typename T>
            requires std::constructible_from<StockType, T>
        void addMedia(T&& item) {
            m_stock.emplace_back(std::forward<T>(item));
        }

        // public interface
        [[nodiscard]]
        double totalBalance() const {

            double total{};

            for (const auto& media : m_stock) {

                total += std::visit(
                    [](const auto& element) {
                        double price = element.getPrice();
                        std::size_t count = element.getCount();
                        return price * count;
                    },
                    media
                );
            }

            return total;
        }

        [[nodiscard]]
        std::size_t count() const {

            std::size_t total{};

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
    };

    static void test_bookstore_type_erasure_01() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Book javaBook{ "Java", "James Gosling", 17.99, 21 };
        Book cppBook{ "C++", "Bjarne Stroustrup", 16.99, 4 };
        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };

        Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        // Note: The braced-list construction works here because variants are copyable
        MyBookstore bookstore{
            { cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino }
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);
        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_02() {

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{
            Book { "C", "Dennis Ritchie", 11.99, 12 },
            Book { "Java", "James Gosling", 17.99, 21 },
            Book { "C++", "Bjarne Stroustrup", 16.99, 4 },
            Book { "C#", "Anders Hejlsberg", 21.99, 8 },

            Movie { "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 },
            Movie { "Spectre", "Sam Mendes", 8.99, 6 }
        };

        double balance{ bookstore.totalBalance() };
        std::println("Total value of Bookstore: {:.{}f}", balance, 2);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_03() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{ { cBook, movieBond } };

        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };
        bookstore.addMedia(csharpBook);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_type_erasure_04() {

        std::println("Benchmark - Method Call - using Type Erasure");

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            total += cBook.getCount() * cBook.getPrice();
        }
        std::println("Total: {}", total);

        std::print("Done: ");
    }

    static void test_bookstore_type_erasure_05() {

        std::println("Benchmark - Iterating a Container of std:variants - using Type Erasure");
        
        Bookstore<Book, Movie> bookstore;

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };

        for (std::size_t i{}; i != 100; ++i) {
            bookstore.addMedia(cBook);
        }

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            double totalBalance{ bookstore.totalBalance() };
            total += totalBalance;
        }
        std::println("Total: {}", total);

        std::print("Done: ");
    }

    // =====================================================================================

    class BluRay
    {
    public:
        BluRay() = default;

        // getter / setter
        std::size_t getCount() const { return 0; }
        double getPrice() const { return 0.0; }   // put into comments
    };

    static void test_bookstore_type_erasure_06() {

        // verifying concept 'MediaConcept'
        Bookstore<Book, BluRay, Movie> bookstore;
    }
}

// =====================================================================================

void main_type_erasure_bookstore()
{
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_01();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_02();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_03();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_04();
    BookStoreUsingDynamicPolymorphism::test_bookstore_polymorphic_05();

    BookStoreUsingTypeErasure::test_bookstore_type_erasure_01();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_02();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_03();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_04();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_05();
    BookStoreUsingTypeErasure::test_bookstore_type_erasure_06();

}

// =====================================================================================
// End-of-File
// =====================================================================================
