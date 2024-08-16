// =====================================================================================
// Accumulate.cpp // std::accumulate
// =====================================================================================

module modern_cpp:accumulate;

namespace AlgorithmAccumulate {

    static std::string toString(std::vector<std::string> const& vec) {

        std::string s{ 
            std::accumulate(
                vec.begin(),
                vec.end(),
                std::string{}, // first element
                [counter = 0](const std::string& first, const auto& next) mutable {
                    counter++;
                    std::ostringstream ss;
                    ss << std::setfill('0') << std::setw(2) << counter
                        << ": " << std::setfill(' ') << std::setw(10)
                        << std::right << next << std::endl;

                    return first + ss.str();
                }
            ) 
        };

        return s;
    }

    template <typename T>
    static std::string toString(std::vector<T> const& vec) {

        std::string s{ 
            std::accumulate(
                vec.begin(),
                vec.end(),
                std::string{}, // first element
                [counter = 0](const std::string& first, const T& next) mutable {
                    counter++;
                    std::ostringstream ss;
                    ss << std::setfill('0') << std::setw(2) << counter
                        << ": " << std::setfill(' ') << std::setw(10)
                        << std::right << next << std::endl;

                    return first + ss.str();
                }
            ) 
        };

        return s;
    }

    static void test_01() {
        std::vector<std::string> names {"Hans", "Sepp", "Georg"};
        std::string s{ toString(names) };
        std::cout << s << std::endl;
    }

    static void test_02() {
        std::vector<float> digits { 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f };
        std::string s{ toString(digits) };
        std::cout << s << std::endl;
    }

    static void test_03() {
        // using template version of toString
        std::vector<std::string> names { "Hans", "Sepp", "Georg" };
        std::string s{ toString<std::string>(names) };
        std::cout << s << std::endl;
    }
}

void main_accumulate()
{
    using namespace AlgorithmAccumulate;
    test_01();
    test_02();
    test_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
