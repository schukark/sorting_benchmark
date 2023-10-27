#pragma once

#ifndef G_QUICK_SORTER_CPP

#include "Sorter.cpp"
#include <vector>
#include <random>
#include <algorithm>

template<class T>
class G_quick_sorter : public Sorter<T> {
public:
    G_quick_sorter() : Sorter<T>(1e6, "Guaranteed quick sort"), gen(rd()) {}

    void sort(std::vector<T>& data, int l, int r) override {
        if (l >= r) {
            return;
        }

        if (r - l + 1 <= 5) {
            sort_5(data, l, r);
            return;
        }

        int part = partition(data, l, r);

        sort(data, l, part - 1);
        sort(data, part + 1, r);
    }

private:
    int partition(std::vector<T>& data, int left, int right) {
        T pivot = choose_index(data, left, right);
        size_t pivot_ind = std::find(data.begin() + left, data.begin() + right + 1, pivot) - data.begin();

        std::swap(data[right], data[pivot_ind]);

        int i = left;

        for (int j = left; j < right; j++) {
            if (data[j] <= pivot) {
                std::swap(data[i], data[j]);
                i++;
            }
        }

        std::swap(data[i], data[right]);

        return i;
    }

    T choose_index(std::vector<T>& data, size_t left, size_t right) {
        if (right - left + 1 <= 5) {
            sort_5(data, left, right);
            return data[left + (right - left) / 2];
        }

        std::vector<T> medians;

        for (int i = left; i <= right; i += 5) {
            int sub_right = i + 4;
            if (sub_right > right) {
                sub_right = right;
            }
            sort_5(data, i, sub_right);
            medians.push_back(data[i + (sub_right - i) / 2]);
        }

        return choose_index(medians, 0, medians.size() - 1);
    }

    void sort_5(std::vector<T>& data, size_t left, size_t right) const {
        if (right - left == 4) {
            for (const auto& [x, y]: changes) {
                if (data[left + x] > data[left + y]) {
                    std::swap(data[left + x], data[left + y]);
                }
            }
        }
        else {
            std::sort(data.begin() + left, data.begin() + right + 1);
        }
    }


    std::vector<std::pair<size_t, size_t>> changes = {{0, 1}, {3, 4}, {1, 2}, {0, 3}, {2, 4}, {1, 3}, {1, 2}};
    std::random_device rd;
    std::mt19937 gen;
};

#endif