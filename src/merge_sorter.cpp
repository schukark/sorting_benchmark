#pragma once

#ifndef MERGE_SORTER_CPP

#include "Sorter.cpp"
#include <vector>

template<class T>
class MergeSorter : public Sorter<T> {
public:
    MergeSorter() : Sorter<T>(1e6, "Merge sort") {}

    void sort(std::vector<T>& data, int l, int r) override {
        int n = data.size();

        for (int curr_size = 1; curr_size < n; curr_size *= 2) {
            for (int l = 0; l < n - 1; l += 2 * curr_size) {
                int mid = std::min(l + curr_size - 1, n - 1);
                int r = std::min(l + 2 * curr_size - 1, n - 1);
                merge(data, l, mid, r);
            }
        }
    }

private:
    void merge(std::vector<T>& data, int l, int mid, int r) {
        int left_size = mid - l + 1;
        int right_size = r - mid;

        std::vector<T> left(data.begin() + l, data.begin() + mid + 1);
        std::vector<T> right(data.begin() + mid + 1, data.begin() + r + 1);

        int i = 0, j = 0, k = l;

        while (i < left_size && j < right_size) {
            if (left[i] <= right[j]) {
                data[k++] = left[i++];
            } else {
                data[k++] = right[j++];
            }
        }

        while (i < left_size) {
            data[k++] = left[i++];
        }

        while (j < right_size) {
            data[k++] = right[j++];
        }
    }
};

#endif