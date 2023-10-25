#include "src/Sorters.hpp"
#include "Benchmark.cpp"

#include <iostream>

using custom_type = std::string;
using sorter_engine = Insertion_sorter<custom_type>;

int main() {
    Sorter<custom_type> *tester = new sorter_engine();
    Benchmark<custom_type> bench(tester);
    
    bench.test();
    return 0;
}