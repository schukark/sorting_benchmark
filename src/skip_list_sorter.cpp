#pragma once

#ifndef SKIP_LIST_SORTER_CPP

#include "Sorter.cpp"
#include "Data_structures/skip_list.cpp"
#include <vector>

template<class T>
class SkipListSorter : public Sorter<T> {
public:
    SkipListSorter() : Sorter<T>(3e5, "Skip list sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        SkipList<T> list = list_from_vector<T>(data);
        data = vector_from_skip_list<T>(list);
    }

private:

};

#endif