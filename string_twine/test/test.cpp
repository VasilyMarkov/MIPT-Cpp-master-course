#include <gtest/gtest.h>
#include "string_twine.hpp"

TEST(StringTwine, test) {
    my_impl::StringTwine twine("Hello");
    twine.concat(", ");
    twine.concat("world!");

    EXPECT_EQ(twine.to_string(), "Hello, world!");
}

TEST(StringTwine, test2) {
    my_impl::StringTwine twine("");
    twine.concat(std::string_view("36SKnTSqOA\n"));
    twine.concat(std::string_view("Ob9DGN0tEY\n"));
    std::cout << twine.to_string() << std::endl;
    // EXPECT_EQ(twine.to_string(), "Hello, world!");
}

TEST(StringTwine, empty) {
    my_impl::StringTwine twine("");
    twine.concat(", ");
    twine.concat("world!");

    EXPECT_EQ(twine.to_string(), ", world!");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

