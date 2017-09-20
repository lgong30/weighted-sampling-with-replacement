//
// Created by Long Gong on 9/20/17.
//

#include <iostream>
#include <random>
#include <chrono>
#include "../src/sample.hpp"

void print_stars(size_t n){
    while (n > 0) {
        std::cout << "*";
        -- n;
    }
}

void test_vose_algorithm_sample(){
    std::vector<double> p={0.2, 0.2, 0.2, 0.4};
    size_t n = p.size();
    std::vector<size_t> counter(n, 0);
    size_t m = 1000000;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, n);
    auto rng = std::bind(distribution, generator);
    auto rns = saber::sample(m, p.begin(), p.end(), rng);
    for (auto r: rns) {
        ++ counter[r];
    }
    for (size_t i = 0;i < n;++ i) {
        std::cout << i << ": " << counter[i] << std::endl;
    }
    std::cout << "\n\nHistogram:\n";
    size_t one_star = 10000;
    for (size_t i = 0;i < n;++ i) {
        std::cout << i << ": ";
        print_stars(counter[i] / one_star);
        std::cout << std::endl;
    }
}

void test_roulette_wheel_selection(){
    std::vector<double> p={0.1, 0.2, 0.3, 0.4};
    size_t n = p.size();
    std::vector<size_t> counter(n, 0);
    size_t m = 1000000;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::default_random_engine generator1;
    std::uniform_int_distribution<int> distribution1(0, n);

    auto rg = std::bind(distribution, generator);
    auto ug = std::bind(distribution1, generator1);



    auto rns = saber::roulette_wheel_selection(m, p.begin(), p.end(), ug, rg);

    for (auto r: rns) {
        ++ counter[r];
    }
    for (size_t i = 0;i < n;++ i) {
        std::cout << i << ": " << counter[i] << std::endl;
    }
    std::cout << "\n\nHistogram:\n";
    size_t one_star = 10000;
    for (size_t i = 0;i < n;++ i) {
        std::cout << i << ": ";
        print_stars(counter[i] / one_star);
        std::cout << std::endl;
    }

}

int main()
{
    std::cout << "Test 1:\n";
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    test_vose_algorithm_sample();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "\nElapsed time = "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "s"
              << std::endl;
    std::cout << "\n+++++++++++++++++++++++++++++++++++++\nTest 2:\n";
    start = std::chrono::steady_clock::now();
    test_roulette_wheel_selection();
    end = std::chrono::steady_clock::now();
    std::cout << "\nElapsed time = "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "s"
              << std::endl;
    return 0;
}