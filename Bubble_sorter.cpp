#pragma once

#ifndef BUBBLE_SORT_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class Bubble_sorter: public Sorter<T> {
public:
    Bubble_sorter(): Sorter<T>(1e4, "Bubble sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        for (int i = 0; i < data.size(); i++) {
            for (int j = i + 1; j < data.size(); j++) {
                if (data[i] > data[j]) {
                    std::swap(data[i], data[j]);
                }
            }
        }
    }

private:

};

#endif