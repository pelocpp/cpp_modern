// =====================================================================================
// Random.cpp // Random Numbers
// =====================================================================================

module modern_cpp:random;

namespace Random {

    void main_random_01()
    {
        // pseudo-random numbers engine
        std::default_random_engine engine{};
        // or
        // std::default_random_engine engine{ static_cast<unsigned int> (time(0)) };

        // random integer numbers from a given input range with uniform probabilty
        std::uniform_int_distribution<int> distribution{ 0, 5 };

        // need vector of length 6 zero-initialized
        std::vector<int> numbers(6, 0);

        // generate random numbers
        for (int i = 0; i < 6 * 100000; i++) {
            int random = distribution(engine);
            numbers[random]++;
        }

        // print numbers 
        for (int n : numbers)
            std::cout << n << " ";
        std::cout << std::endl;
    }

    void main_random_02()
    {
        // pseudo-random numbers engine
        std::random_device engine{};
        std::mt19937 generator(engine());

        // random integer numbers from a given input range with uniform probabilty
        std::uniform_int_distribution<int> distribution{ 0, 5 };

        // need vector of length 6 zero-initialized
        std::vector<int> numbers(6, 0);

        // generate random numbers
        for (int i = 0; i < 6 * 100000; i++) {
            int random = distribution(engine);
            numbers[random]++;
        }

        // print numbers 
        for (int n : numbers)
            std::cout << n << " ";
        std::cout << std::endl;
    }   

    void main_random_03()
    {
        static const size_t numCoins = 10;

        // pseudo-random numbers engine
        std::default_random_engine engine{};

        // throw 10 coins, 0..10-time 'Kopf' / binomial probabilty
        std::binomial_distribution<int> distribution{ numCoins };

        // need vector of length 10 zero-initialized (10 coins)
        std::vector<int> coins(numCoins + 1, 0);

        // generate random numbers
        for (int i = 0; i < 10 * 100000; i++) {
            int random = distribution(engine);
            coins[random]++;
        }

        // print numbers 
        for (int n : coins)
            std::cout << n << " ";
        std::cout << std::endl;
    }
}

void main_random()
{
    using namespace Random;
    main_random_01();
    main_random_02();
    main_random_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
