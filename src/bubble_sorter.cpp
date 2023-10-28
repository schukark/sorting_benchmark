#pragma once

#ifndef BUBBLE_SORTER_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class BubbleSorter: public Sorter<T> {
public:
    BubbleSorter(): Sorter<T>(1e4, "Bubble sort") {}

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