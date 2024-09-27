#include <gtest/gtest.h>
#include "ram.hpp"
#include <regex>

TEST(Ram, tokenizer) {
    std::string expr = "2 +   5   - 4";
    my_impl::Tokenizer tokenizer(expr, " ");
    std::vector<std::string> ref = {"2", "+", "5", "-", "4"};
    EXPECT_EQ(tokenizer.tokens(), ref);
}

TEST(Ram, tokenizer_print) {
    std::string expr = "input a; [ = a[5]; ][ = [[ + a -2];";
    my_impl::Tokenizer tokenizer(expr, " ");
    // std::cout << tokenizer << std::endl;

    for(auto&& token:tokenizer.tokens()) {
        std::cout << token << std::endl;
    }

}

TEST(Lexer, lex) {
    my_impl::Lexer lex(std::string_view("+"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

