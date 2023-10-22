#pragma once

#ifndef HEAP_SORTER_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class Heap_sorter : public Sorter<T> {
public:
    Heap_sorter() : Sorter<T>(1e6, "Heap sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        
    }

private:

};

#endif