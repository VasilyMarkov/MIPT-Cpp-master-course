#include "physical-quantities.hpp"

int main() {
    Time t(10.0);
    Current I(0.1);
    Resistance R(150.0);

    auto Q = I*I*R*t;

    Q.print();
}