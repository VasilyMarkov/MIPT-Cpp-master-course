#include "physical-quantities.hpp"

int main() {
    Force unit1(2.0);
    Force unit2(3.0);
    auto product = unit1*unit2;
    std::cout << typeid(product).name() << std::endl;
    std::cout << product.value << std::endl;
}