#pragma once

#ifndef MERGE_SORTER_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class Merge_sorter : public Sorter<T> {
public:
    Merge_sorter() : Sorter<T>(1e6, "Merge sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        if (l == r) return;

        int i = 0, j = 0, mid = (l + r) >> 1;

        std::vector<T> left(data.begin(), data.begin() + mid + 1);
        std::vector<T> right(data.begin() + mid + 1, data.end());

        sort(left, 0, mid);
        sort(right, 0, r - mid - 1);

        for (int k = 0; k <= r; k++) {
            if (i > mid) {
                data[k] = right[j++];
            }
            else if (j > r - mid - 1) {
                data[k] = left[i++];
            }
            else if (left[i] > right[j]) {
                data[k] = right[j++];
            }
            else {
                data[k] = left[i++];
            }
        }
    }

private:

};

#endif