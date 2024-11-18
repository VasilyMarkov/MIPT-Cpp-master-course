#include "tuple.hpp"

struct Base {};
struct Derived: Base {};
struct Payload: Base {int foo;};

int main() {
    using Tuple1 = Tuple<int, double, float, short>;
    using Tuple2 = Tuple<int, int, short>;
    using Tuple3 = Tuple<int, int&, int&&>;
    using Tuple4 = Tuple<>;
    using Tuple5 = Tuple<Payload, Base, Derived>;
    using Tuple6 = Tuple<const int, const volatile int>;
    using Tuple7 = Tuple<const volatile int, const int, const int&>;


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
    std::cout << std::endl;
    printSortedTypes<Tuple7>();
    std::cout << std::endl;

}