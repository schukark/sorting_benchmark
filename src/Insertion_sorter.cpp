#pragma once

#ifndef INSERTION_SORT_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class Insertion_sorter : public Sorter<T> {
public:
    Insertion_sorter() : Sorter<T>(1e5, "Insertion sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        for (int i = 1; i < data.size(); ++i) {
            int index = i - 1;
            T value = data[i];

            for (; index >= 0 && data[index] > value; index--) {
                data[index + 1] = data[index];
            }

            data[index + 1] = value;
        }
    }

private:

};

#endif