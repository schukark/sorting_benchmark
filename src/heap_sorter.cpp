#pragma once

#ifndef HEAP_SORTER_CPP

#include "Sorter.cpp"
#include "Data_structures/heap.cpp"
#include <vector>

template<class T>
class HeapSorter : public Sorter<T> {
public:
    HeapSorter() : Sorter<T>(1e6, "Heap sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        Heap heap(data);
        data = std::move(heap.get_sorted());
    }

private:

};

#endif