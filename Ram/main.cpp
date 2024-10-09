#include <iostream>
#include "ram.hpp"
#include "lexer.hpp"

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Wrong arguments!" << std::endl;
            return 1;
        }
        std::ifstream file (argv[1]);

        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return 0;
        }

        auto lexer = std::make_unique<yy::RamLexer>();
        lexer->switch_streams(file, std::cout);

        while (lexer->yylex() != 0) {}
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}