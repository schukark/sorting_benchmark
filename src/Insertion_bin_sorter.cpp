#pragma once

#ifndef INSERTION_SORT_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class InsertionBinSorter : public Sorter<T> {
public:
    InsertionBinSorter() : Sorter<T>(1e5, "Binary insertion sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        for (int i = 1; i < data.size(); ++i) {
            T value = data[i];
            int index = std::upper_bound(data.begin(), data.begin() + i, value) - data.begin();

            for (int j = i; j > index; j--) {
                std::swap(data[j], data[j - 1]);
            }
        }
    }

private:

};

#endif