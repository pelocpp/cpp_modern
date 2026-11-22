// =====================================================================================
// TypeErasure_Bookstore.cpp - Static versus Dynamic Polymorphism
// =====================================================================================

module modern_cpp:type_erasure;

import std;
import scoped_timer;

// =====================================================================================

namespace {

#ifdef _DEBUG
     constexpr std::size_t MaxIterations = 10'000'000;     // debug
     constexpr std::size_t NumberOfMedia = 1'000'000;      // debug
#else
     constexpr std::size_t MaxIterations = 100'000'000;    // release
     constexpr std::size_t NumberOfMedia = 10'000'000;      // debug
#endif

}

// =====================================================================================
// Classic Implementation: Using Inheritance, Polymorphism, virtual methods
// =====================================================================================

namespace BookStoreUsingDynamicPolymorphism {

    struct IMedia
    {
        virtual ~IMedia() = default;

        [[nodiscard]] virtual double getPrice() const = 0;
        [[nodiscard]] virtual std::size_t getCount() const = 0;
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
        Book(std::string author, std::string title, double price, std::size_t count)
            : m_author{ std::move(author) }, m_title{ std::move(title) }, m_price{ price }, m_count{ count }
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
        Movie(std::string title, std::string director, double price, std::size_t count)
            : m_title{ std::move(title) }, m_director{ std::move(director) }, m_price{ price }, m_count{ count }
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

    static void test_bookstore_dynamic_polymorphism_01() {

        // Note: The braced-list construction does not work here
        // because unique_ptr objects need push_back plus std::move.

        std::vector<std::unique_ptr<IMedia>> stock;

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

    static void test_bookstore_dynamic_polymorphism_02() {

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

    static void test_bookstore_dynamic_polymorphism_03() {

        Bookstore bookstore{
            std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12),
            std::make_unique<Movie>("Spectre", "Sam Mendes", 8.99, 6)
        };

        bookstore.addMedia(std::make_unique<Book>("C#", "Anders Hejlsberg", 21.99, 8));
        bookstore.addMedia(std::make_unique<Movie>("Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3));

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_dynamic_polymorphism_04() {

        std::println("Benchmark - Measuring Method Calls - using Polymorphism");

        std::unique_ptr<IMedia> cBook{ std::make_unique<Book>("C", "Dennis Ritchie", 11.99, 12) };

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            total += cBook->getCount() * cBook->getPrice();
        }
        std::println("Total: {}", total);

        std::print("Done: ");
    }

    static void test_bookstore_dynamic_polymorphism_05() {

        std::println("Benchmark - Measuring insertions into an empty bookstore");

        Bookstore bookstore;

        ScopedTimer watch;

        for (std::size_t i{}; i != NumberOfMedia; ++i)
        {
            bookstore.addMedia(
                std::make_unique<Book>(
                    "Python",
                    "Guido van Rossum",
                    11.99,
                    12
                )
            );
        }
    }
}

// =====================================================================================
// Alternate Modern C++ Implementation: Using std::variant, std::visit, Variadic Templates
// =====================================================================================

namespace BookStoreUsingStaticPolymorphism {

    class Book
    {
    private:
        std::string m_author;
        std::string m_title;
        double      m_price;
        std::size_t m_count;

    public:
        // c'tor
        Book(std::string author, std::string title, double price, std::size_t count)
            : m_author{ std::move(author) }, m_title{ std::move(title) }, m_price{ price }, m_count{ count }
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
        Movie(std::string title, std::string director, double price, std::size_t count)
            : m_title{ std::move(title) }, m_director{ std::move(director) }, m_price{ price }, m_count{ count }
        {}

        // getter / setter
        const std::string& getTitle() const { return m_title; }
        const std::string& getDirector() const { return m_director; }

        double getPrice() const { return m_price; }
        std::size_t getCount() const { return m_count; }
    };

    template<typename T>
    concept MediaConcept = requires(const T& media)
    {
        { media.getPrice() } -> std::convertible_to<double>;
        { media.getCount() } -> std::convertible_to<std::size_t>;
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
            requires (sizeof...(TArgs) > 0 && (std::constructible_from<StockType, TArgs&&> && ...))
        explicit Bookstore(TArgs&&... items)
        {
            m_stock.reserve(sizeof...(TArgs));
            (m_stock.emplace_back(std::forward<TArgs>(items)), ...);
        }

        // template member method
        template <typename T>
            requires std::constructible_from<StockType, T&&>
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
                        return element.getPrice() * element.getCount();
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

    static void test_bookstore_static_polymorphism_01() {

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

    static void test_bookstore_static_polymorphism_02() {

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

    static void test_bookstore_static_polymorphism_03() {

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };
        Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

        using MyBookstore = Bookstore<Book, Movie>;

        MyBookstore bookstore{ { cBook, movieBond } };

        Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 8 };
        bookstore.addMedia(csharpBook);

        std::size_t count{ bookstore.count() };
        std::println("Count of elements in Bookstore: {}", count);
    }

    static void test_bookstore_static_polymorphism_04() {

        std::println("Benchmark - Measuring Method Calls - using Static Polymorphism");

        Book cBook{ "C", "Dennis Ritchie", 11.99, 12 };

        ScopedTimer watch;

        double total{};
        for (std::size_t i{}; i != MaxIterations; ++i) {
            total += cBook.getCount() * cBook.getPrice();
        }

        std::println("Total: {}", total);
        std::print("Done: ");
    }

    static void test_bookstore_static_polymorphism_05() {

        std::println("Benchmark - Measuring insertions into an empty bookstore");

        Bookstore<Book, Movie> bookstore;

        ScopedTimer watch;

        for (std::size_t i{}; i != NumberOfMedia; ++i)
        {
            bookstore.addMedia(
                Book {
                    "Python",
                    "Guido van Rossum",
                    11.99,
                    12
                }
            );
        }
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

    static void test_bookstore_static_polymorphism_06() {

        // verifying concept 'MediaConcept'
        Bookstore<Book, BluRay, Movie> bookstore;
    }

    static_assert(MediaConcept<Book>);
    static_assert(MediaConcept<Movie>);
    static_assert(MediaConcept<BluRay>);
    static_assert(! MediaConcept<std::string>);
}

// =====================================================================================

void main_type_erasure_bookstore()
{
    BookStoreUsingDynamicPolymorphism::test_bookstore_dynamic_polymorphism_01();  // creating a book store - media objects provided outside
    BookStoreUsingDynamicPolymorphism::test_bookstore_dynamic_polymorphism_02();  // creating a book store - media objects provided inside
    BookStoreUsingDynamicPolymorphism::test_bookstore_dynamic_polymorphism_03();  // demonstrating 'addMedia'
    BookStoreUsingDynamicPolymorphism::test_bookstore_dynamic_polymorphism_04();  // measuring (virtual) method calls
    BookStoreUsingDynamicPolymorphism::test_bookstore_dynamic_polymorphism_05();  // measuring insertions into an empty bookstore

    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_01();    // creating a book store - media objects provided outside
    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_02();    // creating a book store - media objects provided inside
    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_03();    // demonstrating 'addMedia'
    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_04();    // measuring (static) method calls 
    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_05();    // measuring insertions into an empty bookstore 
    BookStoreUsingStaticPolymorphism::test_bookstore_static_polymorphism_06();    // verifying concept 'MediaConcept' with a BlueRay media
}

// =====================================================================================
// End-of-File
// =====================================================================================
