#pragma once
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#ifndef SORTER_CPP

#include <vector>
#include <cstddef>
#include <string>
#include <limits>

template<class T>
class Sorter {
public:
    Sorter<T>(size_t value, std::string name): max_test_size(value), sort_name(name) {}
    virtual void sort(std::vector<T>& data, int l, int r) = 0;

    size_t get_max_test_size() const {
        return max_test_size;
    }

    std::string get_sort_name() const {
        return sort_name;
    }

private:
    size_t max_test_size;
    std::string sort_name;
};

#endif