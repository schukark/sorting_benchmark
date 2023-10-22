#pragma once

#ifndef BENCHMARK_CPP

#include "Sorters/Sorter.cpp"

#include <concepts>
#include <random>
#include <algorithm>

#include <limits>
#include <chrono>

#include <iostream>
#include <iomanip>

template<class T>
class Benchmark {
public:
    Benchmark(Sorter<T>* sorting_engine): sorting_engine(sorting_engine), gen(rd()) {}

    void test() {
        std::cout << std::setw(23) << sorting_engine->get_sort_name() << std::endl;
        std::cout << "|" << std::setw(7) << "N" << "|" << std::setw(15) << "Time taken" << "|" << std::endl;

        for (const auto& test_size : test_sizes) {
            std::cout << "|" << std::setw(7) << test_size << "|";

            if (sorting_engine->get_max_test_size() >= test_size) {
                std::cout << std::setw(15) << convert_time(test_one_size(test_size)) << "|" << std::endl;
            }
            else {
                std::cout << std::setw(15) << ">5s" << "|" << std::endl;
            }
        }
    }

    void test_correctness () {
        std::cout << std::setw(23) << sorting_engine->get_sort_name() << std::endl;
        std::cout << "|" << std::setw(7) << "N" << "|" << std::setw(15) << "Time taken" << "|" << std::endl;

        for (const auto& test_size : test_sizes) {
            std::cout << "|" << std::setw(7) << test_size << "|";

            if (sorting_engine->get_max_test_size() >= test_size) {
                test_one_size(test_size);
                bool sorted = std::is_sorted(test_data.begin(), test_data.end());
                std::cout << std::setw(15) << sorted << "|" << std::endl;
            }
            else {
                std::cout << std::setw(15) << "not tested" << "|" << std::endl;
            }
        }
    }

private:
    auto test_one_size(size_t test_size, int runs = 10) {
        int64_t result = 0;

        for (int i = 0; i < runs; i++) {
            result += time_test(test_size);
        }

        return result / runs;
    }

    auto time_test(size_t test_size) {
        generate_test(test_size);

        auto start = std::chrono::high_resolution_clock::now();
        sorting_engine->sort(test_data, 0, test_size - 1);
        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    void generate_test(size_t test_size) {
        T min_value = std::numeric_limits<T>::min();
        T max_value = std::numeric_limits<T>::max();

        std::uniform_int_distribution dis(min_value, max_value);

        std::vector<T> arr(test_size);
        for (auto& it : arr) {
            it = dis(gen);
        }

        test_data = std::move(arr);
    }

    std::string convert_time(int64_t time) const {
        if (time < 1000) {
            return std::to_string(time) + " ns";
        }
        else if (time < 1e6) {
            return std::to_string(std::round(time / 1e3 * 1e3) / 1000) + " mcs";
        }
        else if (time < 1e9) {
            return std::to_string(std::round(time / 1e6 * 1e6) / 1000000) + " ms";
        }
        return std::to_string(std::round(time / 1e9 * 1e9) / 1000000000) + " s";
    }

    std::random_device rd;
    std::mt19937 gen;

    Sorter<T>* sorting_engine;
    std::vector<T> test_data;
    std::vector<size_t> test_sizes = {20, 100, 500, 1000, 2000, 10000, 50000, 200000, 1000000};
};

#endif