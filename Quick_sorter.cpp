#pragma once

#ifndef QUICK_SORTER_CPP

#include "Sorter.cpp"
#include <vector>
#include <random>

template<class T>
class Quick_sorter : public Sorter<T> {
public:
    Quick_sorter() : Sorter<T>(1e6, "Quick sort"), gen(rd()) {}

    void sort(std::vector<T>& data, int l, int r) override {
        if (l >= r) {
            return;
        }

        int part = partition(data, l, r);

        sort(data, l, part - 1);
        sort(data, part + 1, r);
    }

private:
    int partition(std::vector<T>& data, int left, int right) {
        //std::uniform_int_distribution<int> dis(left, right);
        //int pivot_ind = dis(gen);
        int pivot_ind = left;
        int pivot = data[pivot_ind];

        int count = 0;
        for (int i = left; i <= right; i++) {
            count += (data[i] <= pivot && i != pivot_ind);
        }

        std::swap(data[pivot_ind + count], data[pivot_ind]);

        int i = left, j = right;

        while (i < pivot_ind + count && j > pivot_ind + count) {
            while (data[i] <= pivot) {
                i++;
            }
            while (data[j] > pivot) {
                j--;
            }

            if (i < pivot_ind + count && j > pivot_ind + count) {
                std::swap(data[i++], data[j--]);
            }
        }

        return pivot_ind + count;
    }


    std::random_device rd;
    std::mt19937 gen;
};

#endif