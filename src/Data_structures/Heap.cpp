#pragma once

#ifndef HEAP_CPP

#include <cstddef>

inline size_t left_child(size_t child) {
    return 2 * child + 1;
}

inline size_t right_child(size_t child) {
    return 2 * child + 2;
}

inline size_t parent(size_t child) {
    return (child - 1) / 2;
}

template<class T>
class Heap {
public:
    Heap(std::vector<T>& arr): arr(arr) {
        heapify();
    }

    std::vector<T> get_sorted() {
        std::vector<T> ans(arr.size());
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            ans[i] = extract_min();
        }

        return ans;
    }

private:
    void sift_down(size_t index) {
        while (index < arr.size()) {
            size_t left = left_child(index);
            size_t right = right_child(index);

            size_t min_ind = index;
            if (right < arr.size() && arr[right] < arr[min_ind]) {
                min_ind = right;
            }
            if (left < arr.size() && arr[left] < arr[min_ind]) {
                min_ind = left;
            }

            if (min_ind != index) {
                std::swap(arr[index], arr[min_ind]);
                index = min_ind;
            }
            else {
                break;
            }
        }
    }

    void heapify() {
        for (int i = arr.size() / 2 - 1; i >= 0; i--) {
            sift_down(i);
        }
    }

    T extract_min () {
        T min_value = arr.front();
        std::swap(arr.front(), arr.back());
        arr.pop_back();
        sift_down(0);

        return min_value;
    }

    std::vector<T> arr;
};

#endif