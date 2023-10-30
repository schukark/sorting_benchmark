#pragma once

#ifndef G_QUICK_SORTER_CPP

#include "Sorter.cpp"
#include <vector>
#include <random>
#include <algorithm>
#include <assert.h>

template<class T>
class GQuickSorter : public Sorter<T> {
public:
    GQuickSorter() : Sorter<T>(1e6, "Guaranteed quick sort"), gen(rd()) {}

    void sort(std::vector<T>& data, int l, int r) override {
        if (l >= r) {
            return;
        }

        int part = partition(data, l, r);

        sort(data, l, part - 1);
        sort(data, part + 1, r);
    }

private:
    /// @brief Function needed by quick sort to partition an array based on the pivoting element
    /// @param data full vector to be sorted
    /// @param left left boundary of the "to be sorted" subarray
    /// @param right right boundary
    /// @return the index of the pivoting element after partitioning
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

    /// @brief Chooses a pivoting element based on the median of medians algorithm
    /// @param data vector of elements
    /// @param left left boundary of subarray
    /// @param right right boundary
    /// @return pivoting element
    T choose_index(std::vector<T>& data, size_t left, size_t right) const {
        if (right - left + 1 <= 5) {
            return data[left + (right - left) / 2];
        }

        std::vector<T> medians;

        for (int i = left; i + 4 <= right; i += 5) {
            sort_5(data, i, i + 4);
            medians.push_back(data[i + 2]);
        }

        return choose_index(medians, 0, medians.size() - 1);
    }

    /// @brief A sorting network algorithm that sorts a 5 element array in 7 comparisons
    /// @param data full vector to be sorted
    /// @param left left boundary of the group of 5 elements
    /// @param right right boundary
    void sort_5(std::vector<T>& data, size_t left, size_t right) const {
        assert(right - left == 4);
        std::vector<T> result(data.begin() + left, data.begin() + right + 1);
        if (result[0] > result[1]) {
            std::swap(result[0], result[1]);
        }
        if (result[2] > result[3]) {
            std::swap(result[2], result[3]);
        }
        if (result[0] > result[2]) {
            std::swap(result[0], result[2]);
            std::swap(result[1], result[3]);
        }

        if (result[4] > result[2]) {
            if (result[4] > result[3]) {// case 1: A C D E
                if (result[1] > result[3]) {
                    if (result[1] > result[4]) {
                        result = { result[0], result[2], result[3], result[4], result[1] };
                    }
                    else {
                        result = { result[0], result[2], result[3], result[1], result[4] };
                    }
                }
                else if (result[1] < result[2]) {
                    result = { result[0], result[1], result[2], result[3], result[4] };
                }
                else {
                    result = { result[0], result[2], result[1], result[3], result[4] };
                }
            }
            else { // case 2 A C E D
                if (result[1] > result[4]) {
                    if (result[1] > result[3]) {
                        result = { result[0], result[2], result[4], result[3], result[1] };
                    }
                    else {
                        result = { result[0], result[2], result[4], result[1], result[3] };
                    }
                }
                else if (result[1] < result[2]) {
                    result = { result[0], result[1], result[2], result[4], result[3] };
                }
                else {
                    result = { result[0], result[2], result[1], result[4], result[3] };
                }
            }
        }
        else if (result[4] < result[0]) { // subcase 1 E A C D
            if (result[1] > result[2]) {
                if (result[1] > result[3]) {
                    result = { result[4], result[0], result[2], result[3], result[1] };
                }
                else {
                    result = { result[4], result[0], result[2], result[1], result[3] };
                }
            }
            else {
                result = { result[4], result[0], result[1], result[2], result[3] };
            }
        }
        else { // subcase 2 A E C D
            if (result[1] > result[2]) {
                if (result[1] > result[3]) {
                    result = { result[0], result[4], result[2], result[3], result[1] };
                }
                else {
                    result = { result[0], result[4], result[2], result[1], result[3] };
                }
            }
            else if (result[1] < result[4]) {
                result = { result[0], result[1], result[4], result[2], result[3] };
            }
            else {
                result = { result[0], result[4], result[1], result[2], result[3] };
            }
        }

        for (int i = left; i <= right; i++) {
            data[i] = result[i - left];
        }
    }


    std::random_device rd;
    std::mt19937 gen;
};

#endif