#include "physical-quantities.hpp"

int main() {
    Time t(10.0);
    Current I(0.1);
    Resistance R(150.0);

    auto Q = I*I*R*t;
    std::cout << std::boolalpha << std::is_same_v<decltype(Q), Joule> << std::endl;
    Q.print();
}