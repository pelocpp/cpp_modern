// =====================================================================================
// Random.cpp // Random Numbers
// =====================================================================================

module;

#include <print>    // module implementation too unstable

module modern_cpp:random;

import std;

namespace {

    constexpr std::size_t TotalNumbers = 6 * 100'000;

    void printNumbers(const std::vector<int>& numbers)
    {
        std::for_each(
            numbers.begin(),
            numbers.end(),
            [](int n) { std::println("{} ", n); }
        );
        std::println();
    }

    void printHistogram(const std::vector<int>& numbers, int scale, int startIndex)
    {
        std::for_each(
            numbers.begin(),
            numbers.end(),
            [=, index = startIndex] (int count) mutable {
                std::string bar(count / scale, '*');
                std::println("{:10}: {:6} | {}", index++, count, bar);
            }
        );
        std::println();
    }

    void random_01()
    {
        std::default_random_engine engine;
        // or
        // std::default_random_engine engine{ std::random_device{}() };

        std::uniform_int_distribution<int> distribution{ 0, 5 };

        std::vector<int> numbers;
        numbers.reserve(TotalNumbers);

        // 1. generate random numbers using a classic STL algorithm 'std::generate_n'
        std::generate_n(
            std::back_inserter(numbers),
            TotalNumbers,
            [&]() { return distribution(engine); }
        );

        // 2. count frequencies using 'std::for_each'
        std::vector<int> frequencies(6, 0);
        std::for_each(
            numbers.begin(),
            numbers.end(), 
            [&](int random) { ++frequencies[random]; }
        );

        // 3. output as a table
        printNumbers(frequencies);
    }

    void random_02()
    {
        // 1. hardware source for the initial value (seed) only
        std::random_device device;

        // 2. fast pseudo-random number generator (Mersenne Twister)
        std::mt19937 generator{ device() };

        // 3. uniform distribution
        std::uniform_int_distribution<int> distribution{ 0, 5 };

        // 4. generating random numbers via an STL algorithm -  passing generator
        std::vector<int> numbers;
        numbers.reserve(TotalNumbers);
        std::generate_n(
            std::back_inserter(numbers),
            TotalNumbers, 
            [&] () { return distribution(generator); }
        );

        // 5. counting frequencies using std::for_each
        std::vector<int> frequencies(6, 0);
        std::for_each(
            numbers.begin(),
            numbers.end(), 
            [&](int random) { ++frequencies[random]; }
        );

        // 6. output as ASCII bar chart
        printHistogram(frequencies, 2'500, 1);
    }

    constexpr std::size_t NumberOfCoins = 10;
    constexpr std::size_t TotalTrials = 10 * 100'000;

    void random_03()
    {
        // 1. engine & binomial distribution (10 coins, standard probability p = 0.5)
        std::mt19937 engine{ std::random_device{}() };
        std::binomial_distribution<int> distribution{ NumberOfCoins };

        // 2. generate all 1,000,000 attempts using std::generate_n
        std::vector<int> results;
        results.reserve(TotalTrials);

        std::generate_n(
            std::back_inserter(results),
            TotalTrials,
            [&]() { return distribution(engine); }
        );

        // 3. count frequencies (0 to 10 heads) using std::for_each
        std::vector<int> coins(NumberOfCoins + 1, 0);
        std::for_each(
            results.begin(),
            results.end(),
            [&](int heads) { ++coins[heads]; }
        );

        // 4. output as ASCII bar chart
        printHistogram(coins, 5'000, 0);
    }
}

void main_random()
{
    random_01();
    random_02();
    random_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
