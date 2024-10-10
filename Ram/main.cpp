#include <iostream>
#include "lexer.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong arguments!" << std::endl;
        return 1;
    }
    std::ifstream file (argv[1]);
    
    try {
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return 0;
        }

        auto driver = std::make_unique<my_impl::Driver>(file);
        driver->parse();
        std::cout << driver->output();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    file.close();
}