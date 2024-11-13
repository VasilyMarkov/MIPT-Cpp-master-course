#include "tuple.hpp"

int main() {
    using SortingTuple = Tuple<int, double, float, short>;

    SortingTuple tuple;
    printSortedTypes<SortingTuple>();
}