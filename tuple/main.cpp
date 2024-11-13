#include "tuple.hpp"

int main() {
    using SortingTuple = Tuple<int, double, float, short>;

    SortingTuple tuple;
    print_sorted_types<SortingTuple>();
}