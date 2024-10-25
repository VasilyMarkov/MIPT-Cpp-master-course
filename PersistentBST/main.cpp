#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "string_twine.hpp"

int main(int argc, char* argv[]) {
    std::string line;
    my_impl::StringTwine twine("");

    while (std::getline(std::cin, line)) {
        twine.concat(line);
    }
    std::cout << twine.to_string() << std::endl;
    return 0;
}