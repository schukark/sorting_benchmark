#include "Sorters.hpp"
#include "Benchmark.cpp"

#include <iostream>

int main() {
    Sorter<int> *tester = new Merge_sorter<int>();
    Benchmark<int> bench(tester);
    
    bench.test();
    bench.test_correctness();

    return 0;
}