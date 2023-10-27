#pragma once

#ifndef BENCHMARK_CPP

#include "src/Sorter.cpp"

#include <concepts>
#include <random>
#include <algorithm>
#include <assert.h>

#include <limits>
#include <chrono>

#include <iostream>
#include <iomanip>
#include <fstream>

template<class T>
class Benchmark {
public:
    Benchmark(Sorter<T>* sorting_engine): sorting_engine(sorting_engine), gen(rd()) {
        std::string file_name = sorting_engine->get_sort_name() + ".txt";
        
        if constexpr(std::is_integral_v<T>) {
            test_sizes = {10, 30, 100, 300, 1000, 3000, 10000, 30000, 100000, 300000, 1000000};
            fout = std::ofstream("benchmark_results/Int_" + file_name);
        }
        else if constexpr(std::is_same_v<T, std::string>) {
            test_sizes = {10, 30, 100, 300, 1000, 3000, 10000};
            lengths = {1, 10, 100, 1000, 10000};
            fout = std::ofstream("benchmark_results/String_" + file_name);
        }
    }

    void test() {
        if constexpr (std::is_integral_v<T>) {
            std::cout << std::setw(23) << sorting_engine->get_sort_name() << std::endl;
            std::cout << "|" << std::setw(7) << "N" << "|" << std::setw(15) << "Time taken" << "|" << std::endl;

            for (const auto& test_size : test_sizes) {
                std::cout << "|" << std::setw(7) << test_size << "|";

                if (sorting_engine->get_max_test_size() >= test_size) {
                    auto result = test_one_size(test_size);
                    std::cout << std::setw(15) << convert_time(result) << "|" << std::endl;
                    fout << "N:" << test_size << " " << result << std::endl;
                }
                else {
                    std::cout << std::setw(15) << ">5s" << "|" << std::endl;
                    fout << "N:" << test_size << " " << ">5s" << std::endl;
                }

                assert(std::is_sorted(test_data.begin(), test_data.end()) && "Array was sorted incorrectly");
            }
        }

        else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << std::setw(23) << sorting_engine->get_sort_name() << std::endl;

            std::cout << "|" << std::setw(7) << "M \\ N" << "|";
            for (auto& test_size : test_sizes) {
                std::cout << std::setw(15) << test_size << "|";
            }
            std::cout << std::endl;

            for (auto& string_size : lengths) {
                std::cout << "|" << std::setw(7) << string_size << "|";
                
                for (auto& test_size : test_sizes) {
                    if (sorting_engine->get_max_test_size() >= test_size) {
                        auto result = test_one_size(test_size, string_size);
                        std::cout << std::setw(15) << convert_time(result) << "|";
                        fout << "(N: " << test_size << " M: " << string_size << ") " << result << std::endl;
                    }
                    else {
                        std::cout << std::setw(15) << ">5s" << "|";
                        fout << "(N: " << test_size << " M: " << string_size << ") " << ">5s" << std::endl;
                    }
                    assert(std::is_sorted(test_data.begin(), test_data.end()) && "Array was sorted incorrectly");
                }
                std::cout << std::endl;
            }
        }
    }

private:
    int64_t test_one_size(size_t test_size, size_t string_size = 0, int runs = 10) {
        int64_t result = 0;

        for (int i = 0; i < runs; i++) {
            result += time_test(test_size, string_size);
            
        }

        return result / runs;
    }

    int64_t time_test(size_t test_size, size_t string_size = 0) {
        test_data = generate_test(test_size, string_size);

        auto start = std::chrono::high_resolution_clock::now();
        sorting_engine->sort(test_data, 0, test_size - 1);
        auto end = std::chrono::high_resolution_clock::now();

        int64_t result = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        //std::cout << result << std::endl;

        return result;
    }

    std::vector<T> generate_test(size_t test_size, size_t string_size = 0) {
        if constexpr(std::is_integral_v<T>) {
            T min_value = std::numeric_limits<T>::min();
            T max_value = std::numeric_limits<T>::max();

            std::uniform_int_distribution dis(min_value, max_value);

            std::vector<T> arr(test_size);
            for (auto& it : arr) {
                it = dis(gen);
            }

            return arr;
        }
        else if constexpr(std::is_same_v<T, std::string>) {
            std::vector<T> arr(test_size);
            std::uniform_int_distribution<int> dis(0, 25);

            for (auto &it : arr) {
                T current = std::string(string_size, 'a');
                for (auto& ch : current) {
                    ch += dis(gen);
                }
                it = current;
            }

            return arr;
        }
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
    std::vector<size_t> test_sizes;
    std::vector<size_t> lengths;
    std::ofstream fout;
};

#endif