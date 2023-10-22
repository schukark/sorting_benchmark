#include "src/Sorters.hpp"
#include "Benchmark.cpp"

#include <iostream>

using custom_type = std::string;

int main() {
    Sorter<custom_type> *tester = new Quick_sorter<custom_type>();
    Benchmark<custom_type> bench(tester);
    
    bench.test();
    //bench.test_correctness();

    return 0;
}