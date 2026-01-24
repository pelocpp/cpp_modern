// =====================================================================================
// Exercises_03_Algorithms.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:stl;

namespace Exercises_STL {

    namespace Exercise_01 {

        template <typename T>
        static void print(const std::vector<T>& v)
        {
            std::println("Size: {}, Capacity: {}", v.size(), v.capacity());

            for (auto elem : v) {
                std::print("{} ", elem);
            }
            std::println();
            std::println();
        }

        static void testExercise_01()
        {
            // "wrong" implementation (usage of invalid iterator)

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            // erase all even numbers
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
            {
                if (*it % 2 == 0) {
                    vec.erase(it);
                }
            }

            print(vec);
        }

        static void testExercise_02()
        {
            // correct implementation, but inefficient runtime behaviour

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            // erase all even numbers
            for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
            {
                if (*it % 2 == 0)
                    it = vec.erase(it);
                else
                    ++it;
            }

            print(vec);
        }

        static void testExercise_03()
        {
            // again correct implementation, but efficient (good) runtime behaviour

            std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            print(vec);

            std::vector<int>::iterator pos = std::remove_if(
                vec.begin(),
                vec.end(),
                [](auto elem) { return elem % 2 == 0; }
            );

            vec.erase(pos, vec.end());

            print(vec);
        }

        // =======================================
        // 2 benchmarks:
        // constexpr std::size_t Max = 20;
        // constexpr std::size_t NumIterations = 1;

        constexpr std::size_t Max = 5000;
        constexpr std::size_t NumIterations = 100;

        static void testExercise_benchmark_01()
        {
            std::vector<int> original(Max);

            std::iota(original.begin(), original.end(), 1);

            ScopedTimer watch{};

            for (std::size_t i{}; i != NumIterations; ++i) {

                // demonstration of inefficient implementation

                std::vector<int> vec{ original };

                // print(vec);

                for (std::vector<int>::iterator it = vec.begin(); it != vec.end();)
                {
                    if (*it % 2 == 0)
                        it = vec.erase(it);
                    else
                        ++it;
                }

                // print(vec);
            }
        }

        static void testExercise_benchmark_02()
        {
            std::vector<int> original(Max);

            std::iota(original.begin(), original.end(), 1);

            ScopedTimer watch{};

            for (std::size_t i{}; i != NumIterations; ++i) {

                // demonstration of a better, (hopefully) efficient implementation

                std::vector<int> vec{ original };

                // print(vec);

                std::vector<int>::iterator pos = std::remove_if(
                    vec.begin(),
                    vec.end(),
                    [](auto elem) { return elem % 2 == 0; }
                );

                vec.erase(pos, vec.end());

                // print(vec);
            }
        }

        static void testExercise() {

            // testExercise_01();  // crashes - by design
            testExercise_02();
            testExercise_03();

            testExercise_benchmark_01();
            testExercise_benchmark_02();
        }
    }

    namespace Exercise_02 {

        static void testExercise() {

            std::vector<int> numbers(20);

            // uses structured binding
            auto fibo = [p = std::pair{ 0, 1 }]() mutable {
                auto [a, b] = p;
                p = { b, a + b };
                return a;
            };

            // without structured binding
            auto fibo2 = [p = std::pair{ 0, 1 }]() mutable {
                int n1 = p.first;
                int n2 = p.second;
                p = { n2, n1 + n2 };
                return n1;
            };

            // using a 'state' variable in the scope / "closure"
            auto pLocal = std::pair{ 0, 1 };
            auto fibo3 = [&] {
                int n1 = pLocal.first;
                int n2 = pLocal.second;
                pLocal = { n2, n1 + n2 };
                return n1;
            };

            std::generate(
                std::begin(numbers),
                std::end(numbers),
                fibo3
            );

            for (int n : numbers) {
                std::cout << n << ' ';
            }

            std::cout << std::endl;
        }
    }

    namespace Exercise_03 {

        namespace Exercise_Phonebook_Using_StdVector {

            class PhoneBookVector
            {
            private:
                // member type
                using Entry = std::tuple<std::string, std::string, std::size_t>;

                // member data
                std::vector<Entry> m_entries;

            public:
                // public interface
                std::size_t size() const;
                bool insert(const std::string& first, const std::string& last, std::size_t number);
                bool update(const std::string& first, const std::string& last, std::size_t number);
                std::optional<std::size_t> search(const std::string& first, const std::string& last) const;
                bool remove(const std::string& first, const std::string& last);
                bool contains(const std::string& first, const std::string& last) const;
                void print() const;
            };

            // getter
            std::size_t PhoneBookVector::size() const
            {
                return m_entries.size();
            }

            // public interface
            bool PhoneBookVector::insert(const std::string& first, const std::string& last, std::size_t number)
            {
                if (contains(first, last)) {
                    return false;
                }

                auto entry = Entry{ first, last, number };
                m_entries.push_back(entry);
                return true;
            }

            bool PhoneBookVector::update(const std::string& first, const std::string& last, std::size_t number)
            {
                auto pos = std::find_if(
                    m_entries.begin(),
                    m_entries.end(),
                    [&](const auto& entry) {
                        const auto& [_first, _last, _number] = entry;
                        return _first == first && _last == last;
                    }
                );

                if (pos == m_entries.end()) {
                    return false;
                }
                else {
                    auto& entry{ *pos };
                    std::get<2>(entry) = number;
                    return true;
                }
            }

            std::optional<std::size_t> PhoneBookVector::search(const std::string& first, const std::string& last) const
            {
                auto pos = std::find_if(
                    m_entries.begin(),
                    m_entries.end(),
                    [&](const auto& entry) {
                        const auto& [_first, _last, _number] = entry;
                        return _first == first && _last == last;
                    }
                );

                if (pos == m_entries.end()) {
                    return std::nullopt;
                }
                else {
                    const auto& entry{ *pos };
                    auto number{ std::get<2>(entry) };
                    return number;
                }
            }

            bool PhoneBookVector::contains(const std::string& first, const std::string& last) const
            {
                auto pos = std::find_if(
                    m_entries.begin(),
                    m_entries.end(),
                    [&](const auto& entry) {
                        const auto& [_first, _last, _number] = entry;
                        return _first == first && _last == last;
                    }
                );

                return pos != m_entries.end();
            }

            bool PhoneBookVector::remove(const std::string& first, const std::string& last)
            {
                auto pos = std::find_if(
                    m_entries.begin(),
                    m_entries.end(),
                    [&](const auto& entry) {
                        const auto& [_first, _last, _number] = entry;
                        return _first == first && _last == last;
                    }
                );

                if (pos == m_entries.end()) {
                    return false;
                }
                else {
                    m_entries.erase(pos);
                    return true;
                }
            }

            void PhoneBookVector::print() const
            {
                std::for_each(
                    m_entries.begin(),
                    m_entries.end(),
                    [](auto const& entry) {
                        const auto& [first, last, number] = entry;
                        std::cout << first << " " << last << ": " << number << std::endl;
                    }
                );
            }
        }

        namespace Exercise_Phonebook_Using_StdUnordererMap {

            class PhoneBookMap
            {
            private:
                // member data
                std::unordered_map<std::string, std::size_t> m_entries;

            public:
                // public interface
                std::size_t size() const;
                bool insert(const std::string& first, const std::string& last, std::size_t number);
                bool update(const std::string& first, const std::string& last, std::size_t number);
                std::optional<std::size_t> search(const std::string& first, const std::string& last) const;
                bool remove(const std::string& first, const std::string& last);
                bool contains(const std::string& first, const std::string& last) const;
                void print() const;

            private:
                // helper methods
                static std::pair<std::string, std::string> getNameFromKey(const std::string&);
                static std::string getKeyFromName(const std::string&, const std::string&);
            };

            // getter
            std::size_t PhoneBookMap::size() const
            {
                return m_entries.size();
            }

            // public interface
            bool PhoneBookMap::insert(const std::string& first, const std::string& last, std::size_t number)
            {
                const auto& key{ getKeyFromName(first, last) };

                auto entry{ std::pair<std::string, std::size_t>{ key, number } };

                auto [pos, succeeded] { m_entries.insert(entry) };

                // returns a bool value set to true if and only if the insertion took place
                return succeeded;
            }

            bool PhoneBookMap::update(const std::string& first, const std::string& last, std::size_t number)
            {
                const auto& key{ getKeyFromName(first, last) };

                auto pos{ m_entries.find(key) };

                if (pos == m_entries.end()) {
                    return false;
                }
                else {
                    (*pos).second = number;
                    return true;
                }
            }

            std::optional<std::size_t> PhoneBookMap::search(const std::string& first, const std::string& last) const
            {
                const auto& key{ getKeyFromName(first, last) };

                auto pos{ m_entries.find(key) };

                if (pos == m_entries.end()) {

                    std::cout << first << " " << last << " not found!" << std::endl;
                    return std::nullopt;
                }
                else {
                    const auto& [key, number] {*pos};
                    return number;
                }
            }

            bool PhoneBookMap::contains(const std::string& first, const std::string& last) const
            {
                const auto& key{ getKeyFromName(first, last) };

                auto pos{ m_entries.find(key) };

                return pos != m_entries.end();
            }

            bool PhoneBookMap::remove(const std::string& first, const std::string& last)
            {
                const auto& key{ getKeyFromName(first, last) };

                auto numErased{ m_entries.erase(key) };

                return numErased == 1;
            }

            void PhoneBookMap::print() const
            {
                std::for_each(
                    m_entries.begin(),
                    m_entries.end(),
                    [](const auto& entry) {
                        const auto& [key, number] = entry;
                        const auto& [first, last] { getNameFromKey(key) };
                        std::cout << first << " " << last << ": " << number << std::endl;
                    }
                );
            }

            // helper methods
            std::pair<std::string, std::string> PhoneBookMap::getNameFromKey(const std::string& key)
            {
                auto pos{ key.find("_") };
                const auto& first{ key.substr(0, pos) };
                const auto& last{ key.substr(pos + 1) };

                return { first, last };
            }

            std::string PhoneBookMap::getKeyFromName(const std::string& first, const std::string& last)
            {
                return first + "_" + last;   // "Hubert", "Mueller" ==> "Hubert_Mueller"
            }
        }

        static void testExercise() {

            using namespace Exercise_Phonebook_Using_StdVector;
            using namespace Exercise_Phonebook_Using_StdUnordererMap;

            using PhoneBook = PhoneBookVector;
            //using PhoneBook = PhoneBookMap;

            PhoneBook book{};

            // testing insert
            book.insert("Franz", "Schneider", 8483);
            book.insert("Hans", "Mueller", 5326);
            book.insert("Sepp", "Meier", 7561);
            book.insert("Anton", "Huber", 4899);
            book.print();

            // testing invalid insertion
            bool succeeded{ book.insert("Franz", "Schneider", 4321) };
            if (!succeeded) {
                std::cout << "Franz Schneider already in Phonebook!" << std::endl;
            }

            // testing 'update'
            std::cout << "Updating phone number of Franz Schneider:" << std::endl;
            succeeded = book.update("Franz", "Schneider", 1234);
            book.print();

            // testing 'remove'
            std::cout << "Removing Anton Huber:" << std::endl;
            succeeded = book.remove("Anton", "Huber");
            book.print();

            // testing 'contains'
            bool found{ book.contains("Sepp", "Meier") };
            std::cout << "Found Sepp Meier: " << std::boolalpha << found << std::endl;
            found = book.contains("Otto", "Meier");
            std::cout << "Found Otto Meier: " << found << std::endl;

            // testing 'search'
            std::optional<std::size_t> numberMeier{ book.search("Sepp", "Meier") };
            if (numberMeier.has_value()) {
                std::cout << "Hans Meier: " << numberMeier.value() << std::endl;
            }
        }
    }

    namespace Exercise_04 {

        static bool andAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                true, // starting value
                [](bool first, bool next) {
                    return first and next;
                }
            );
        }

        static bool orAll(std::initializer_list<bool> vec) {

            return std::accumulate(
                std::begin(vec),
                std::end(vec),
                false, // starting value
                [](bool first, bool next) {
                    return first or next;
                }
            );
        }

        static void testExercise_01a() {
            bool result = andAll({ true, false, true });
            std::cout << std::boolalpha << result << std::endl;

            result = andAll({ true, true, true, true, true, true, true, true, true, true });
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise_01b() {
            bool result = orAll({ false, true, false });
            std::cout << std::boolalpha << result << std::endl;

            result = orAll({ false, false, false, false, false, false, false, false, false, false });
            std::cout << std::boolalpha << result << std::endl;
        }

        static void testExercise() {
            testExercise_01a();
            testExercise_01b();
        }
    }
}

void test_exercises_stl()
{
    using namespace Exercises_STL;

    Exercise_01::testExercise();
    Exercise_02::testExercise();
    Exercise_03::testExercise();
    Exercise_04::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
