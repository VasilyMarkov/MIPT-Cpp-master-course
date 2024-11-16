#include "physical-quantities.hpp"

int main() {
    Speed unit1(2.0);
    Current unit2(3.0);
    auto product = unit1*unit2;
    std::cout << typeid(product).name() << std::endl;
    std::cout << product.value << std::endl;
    product.print();
}