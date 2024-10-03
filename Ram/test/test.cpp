#include <gtest/gtest.h>
#include <regex>
#include "lexer.hpp"

TEST(Lexer, lex) {

    my_impl::Ram ram(1000);

    while (ram.lexer()->yylex() != 0) {}

    ram.parser()->parse();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

