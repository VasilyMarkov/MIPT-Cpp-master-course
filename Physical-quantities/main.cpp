#include "physical-quantities.hpp"

int main() {
    Time t(10.0);
    Current I(0.1);
    Resistance R(150.0);

    auto Q = I*I*R*t;
    std::cout << std::boolalpha << std::is_same_v<decltype(Q), Energy> << std::endl;
    Q.print();



    Value<Unit<1,1>> value1(2.0);
    Value<Unit<1,1,0,2>> value2(3.0);
    auto pr = value1/value2;
    pr.print();
}