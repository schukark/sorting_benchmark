//#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

#include "src/Sorters.hpp"
#include "Benchmark.cpp"

#include <iostream>

int main() {
    std::vector<Sorter<int>*> int_sorters = {
        new Insertion_sorter<int>,
        new Merge_sorter<int>,
        new Quick_sorter<int>,
        new Heap_sorter<int>,
        new G_quick_sorter<int>,
    };
    for (auto& it : int_sorters) {
        ;
        Benchmark<int> bench(it);

        bench.test();
    }

    std::vector<Sorter<std::string>*> string_sorters = {
        new Insertion_sorter<std::string>,
        new Insertion_bin_sorter<std::string>
    };

    for (auto& it : string_sorters) {
        Benchmark<std::string> bench(it);

        bench.test();
    }
finalle:
    return 0;
}