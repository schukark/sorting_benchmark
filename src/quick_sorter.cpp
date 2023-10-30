#pragma once

#ifndef QUICK_SORTER_CPP

#include "Sorter.cpp"
#include <vector>
#include <random>

template<class T>
class QuickSorter : public Sorter<T> {
public:
    QuickSorter() : Sorter<T>(1e6, "Quick sort"), gen(rd()) {}

    void sort(std::vector<T>& data, int l, int r) override {
        if (l >= r) {
            return;
        }

        int part = partition(data, l, r);

        sort(data, l, part - 1);
        sort(data, part + 1, r);
    }

private:
    /// @brief Function needed by quick sort to partition an array based on the pivoting element
    /// @param data full vector to be sorted
    /// @param left left boundary of the "to be sorted" subarray
    /// @param right right boundary
    /// @return the index of the pivoting element after partitioning
    int partition(std::vector<T>& data, int left, int right) {
        T pivot = 0LL + data[left] + data[right] + data[(right + left) / 2] - 
            std::max(data[left], std::max(data[right], data[(right + left) / 2])) - std::min(data[left], std::min(data[right], data[(right + left) / 2]));
        
        int pivot_ind = left;
        //T pivot = data[pivot_ind];

        if (pivot == data[right]) {
            pivot_ind = right;
        }
        else if (pivot == data[(right + left) / 2]) {
            pivot_ind = (right + left) / 2;
        }

        std::swap(data[right], data[pivot_ind]);

        int i = left;

        for (int j = left; j < right; j++) {
            if (data[j] <= pivot) {
                std::swap(data[i], data[j]);
                i++;
            }
        }

        std::swap(data[i], data[right]);

        return i;
    }


    std::random_device rd;
    std::mt19937 gen;
};

#endif