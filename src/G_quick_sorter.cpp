#pragma once

#ifndef G_QUICK_SORTER_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class G_Quick_sorter : public Sorter<T> {
public:
    G_Quick_sorter() : Sorter<T>(1e6, "Heap sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        Heap heap(data);
        data = std::move(heap.get_sorted());
    }

private:

};

#endif