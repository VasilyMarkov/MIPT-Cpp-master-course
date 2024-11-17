#include "tuple.hpp"

struct Base {};
struct Derived: Base {};
struct Payload: Base {int foo;};

int main() {
    using Tuple1 = Tuple<int, double, float, short>;
    using Tuple2 = Tuple<int, int, short>;
    using Tuple3 = Tuple<int, int&, int&&>;
    using Tuple4 = Tuple<>;
    using Tuple5 = Tuple<Base, Derived, Payload>;
    using Tuple6 = Tuple<decltype([](){}), void, char>;

    printSortedTypes<Tuple1>();
    std::cout << std::endl;
    printSortedTypes<Tuple2>();
    std::cout << std::endl;
    printSortedTypes<Tuple3>();
    std::cout << std::endl;
    printSortedTypes<Tuple4>();
    std::cout << std::endl;
    printSortedTypes<Tuple5>();
    std::cout << std::endl;
    printSortedTypes<Tuple6>();

}