#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

#include "src/sorters_list.hpp"
#include "Benchmark.cpp"

#include <iostream>

int main() {
    std::vector<Sorter<int>*> int_sorters = {
        new InsertionSorter<int>,
        new MergeSorter<int>,
        new QuickSorter<int>,
        new HeapSorter<int>,
        new GQuickSorter<int>,
        new SkipListSorter<int>
    };
    for (auto& it : int_sorters) {
        Benchmark<int> bench(it);

        bench.test();
    }

    std::vector<Sorter<std::string>*> string_sorters = {
        new InsertionSorter<std::string>,
        new InsertionBinSorter<std::string>
    };

    for (auto& it : string_sorters) {
        Benchmark<std::string> bench(it);

        bench.test();
    }
    return 0;
}