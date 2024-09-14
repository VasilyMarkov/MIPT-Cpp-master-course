#include <gtest/gtest.h>
#include "cowString.hpp"

TEST(cowString, defCtr) {
    my_impl::CowString cStr("abcde");
    EXPECT_EQ("abcde", cStr);
}

TEST(cowString, size) {
    my_impl::CowString cStr("hello");
    EXPECT_EQ(cStr.size(), 5);
}

TEST(Iterator, begin) {
    my_impl::CowString cStr("abcde");
    EXPECT_EQ(*cStr.begin(), 'a');
    EXPECT_EQ(*cStr.cbegin(), *cStr.begin());
    EXPECT_EQ(cStr.cbegin(), cStr.begin());
}

TEST(Iterator, end) {
    my_impl::CowString cStr("abcde");
    auto it = cStr.begin();
    for(size_t i = 0; i < cStr.size(); ++i) {
        ++it;
    } 
    EXPECT_EQ(it, cStr.end());
}

TEST(Iterator, it_prefix_increment) {
    my_impl::CowString cStr("abcde");
    EXPECT_EQ(*++cStr.begin(), 'b');
}

TEST(Iterator, it_postfix_increment) {
    my_impl::CowString cStr("abcde");
    EXPECT_EQ(*cStr.begin()++, 'a');
}

TEST(Iterator, it_prefix_decrement) {
    my_impl::CowString cStr("abcde");
    EXPECT_EQ(*--cStr.end(), 'e');
}

TEST(Iterator, it_postfix_decrement) {
    my_impl::CowString cStr("abcde");
    auto it = --cStr.end();
    EXPECT_EQ(*it--, 'e');
}

TEST(cowString, compare) {
    my_impl::CowString cStr1("hello");
    my_impl::CowString cStr2("hello");
    EXPECT_EQ(cStr1, cStr2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

