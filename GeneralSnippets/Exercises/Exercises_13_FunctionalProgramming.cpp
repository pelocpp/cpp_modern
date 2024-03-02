// =====================================================================================
// Exercises_13_FunctionalProgramming.cpp
// =====================================================================================

module modern_cpp_exercises:functional_programming;

namespace Exercises_FunctionalProgramming {

    namespace Exercise_01 {

        // -------------------------------------------------------------------------------------
        // Teilaufgabe 1:
        // -------------------------------------------------------------------------------------
        // a) Es werden entweder Iteratoren oder Container an die Funktionen übergeben
        // b) Beim sogenannten "Pipe-Lining", also verschachteltetem Aufrufen der jeweiligen Funktionen
        //    ist man bei der zweiten Variante etwas flexibler

        // -------------------------------------------------------------------------------------
        // Teilaufgabe 2:
        // -------------------------------------------------------------------------------------
        // Zu Beispiel wie folgt:
        // Der übersetzungsfähige Quellcode stammt aus der Datei 'FunctionalProgramming01.cpp':
        // Hier sind alle 'include'-Dateien und Definitionen der 'map'-Funktion vorhanden.

        //void test_functional_map_02e() {

        //    std::vector<std::string> words = {
        //        std::string("one"),
        //        std::string("two"),
        //        std::string("three")
        //    };

        //    std::for_each(std::begin(words), std::end(words), [](const std::string& word) {
        //        std::cout << word << ' ';
        //        });
        //    std::cout << std::endl;

        //    auto result = map(
        //        std::begin(words),
        //        std::end(words),
        //        [](std::string word) {
        //            // convert std::string to upper case
        //            std::transform(std::begin(word), std::end(word), std::begin(word), std::toupper);
        //            return word;
        //        }
        //    );

        //    std::for_each(std::begin(result), std::end(result), [](std::string s) {
        //        std::cout << s << ' ';
        //        }
        //    );
        //    std::cout << std::endl;
        //}
    }

    namespace Exercise_02 {

        template <typename TReturn, typename InputIterator, typename TFunctor>
        auto fold(InputIterator begin, InputIterator end, TFunctor&& lambda)
            // not needed, just for demonstration purposes
            -> TReturn
        {
            TReturn init{};

            return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
        }

        template <typename InputIterator, typename TFunctor>
        auto foldEx(InputIterator begin, InputIterator end, TFunctor&& lambda)
            // REQUIRED
            -> decltype(lambda(
                std::declval<typename std::iterator_traits<InputIterator>::value_type >(),
                std::declval<typename std::iterator_traits<InputIterator>::value_type >()))
        {
            using TReturn = 
                decltype(lambda(
                    std::declval<typename std::iterator_traits<InputIterator>::value_type >(),
                    std::declval<typename std::iterator_traits<InputIterator>::value_type >())
                    );

            TReturn init{};

            return std::accumulate(begin, end, init, std::forward<TFunctor>(lambda));
        }

        static void test_fold_01()
        {
            std::vector<int> numbers { 1, 2, 3, 4, 5, 6, 7, 8 };

            std::string concatenated = fold<std::string>(
                std::begin(numbers),
                std::end(numbers),
                [](std::string s, int n) -> std::string {
                    return s + std::to_string(n); 
                }

                // oder 
                // [](auto n, auto m) -> std::string {
                //    return n + std::to_string(m);
                // }
            );

            std::cout << concatenated << std::endl;
        }

        static void test_fold_02()
        {
            std::vector<int> numbers{ 8, 7, 6, 5, 4, 3, 2, 1 };

            std::string concatenated = foldEx(
                std::begin(numbers),
                std::end(numbers),
                [](auto n, int m) -> std::string {
                    return n + std::to_string(m);
                }
            );

            std::cout << concatenated << std::endl;
        }

        static void testExercise_02() {
            test_fold_01();
            test_fold_02();
        }
    }

}

void test_exercises_functional_programming()
{
    using namespace Exercises_FunctionalProgramming;
    Exercise_02::testExercise_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
