#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

#include "src/Sorters.hpp"
#include "Benchmark.cpp"

#include <iostream>

using custom_type = int;

int main() {
    std::vector<Sorter<custom_type>*> sorters = {
        new Insertion_sorter<custom_type>, 
        new Merge_sorter<custom_type>,
        new Quick_sorter<custom_type>,
        new Heap_sorter<custom_type>,
        new G_quick_sorter<custom_type>,
    };
    for (auto& it : sorters) {;
        Benchmark<custom_type> bench(it);
    
        bench.test();
    }
    
    return 0;
}