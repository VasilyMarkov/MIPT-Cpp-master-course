#include <iostream>
#include "lexer.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong arguments!" << std::endl;
        return 1;
    }
    try {
        fs::path filePath = argv[1];
        auto file = my_impl::utility::readFile(filePath);
        auto driver = std::make_unique<my_impl::Driver>(file);
        driver->parse();
        std::cout << driver->output();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}