#include <gtest/gtest.h>
#include "cowString.hpp"
#include "testCharTraits.hpp"

template <typename T>
class CowStringTest : public testing::Test {
public:
    my_impl::basicCowString<T> cowString1 = my_impl::makeString(my_impl::TestCharTraits<T>::value1);
    my_impl::basicCowString<T> cowString2 = my_impl::makeString(my_impl::TestCharTraits<T>::value1);
};

using MyTypes = ::testing::Types<char, char16_t, char32_t>;
TYPED_TEST_SUITE(CowStringTest, MyTypes);

TYPED_TEST(CowStringTest, typedCtr) {
    EXPECT_EQ(this->cowString1, this->cowString2);
}

// TEST(cowString, defCtr) {
//     my_impl::cowString cStr("abcde");
//     EXPECT_EQ(cStr, "abcde");
// }

// TEST(cowString, size) {
//     my_impl::cowString cStr("abcde");
//     EXPECT_EQ(cStr.size(), 5);
// }

// TEST(cowString, compare) {
//     my_impl::cowString cStr1("abcde");
//     my_impl::cowString cStr2("abcde");
//     EXPECT_EQ(cStr1, cStr2);
// }

// TEST(cowString, copyCtr) {
//     my_impl::cowString cStr1("abcde");
//     my_impl::cowString cStr2(cStr1);
//     EXPECT_EQ(cStr1, cStr2);
// }

// TEST(cowString, moveCtr) {
//     my_impl::cowString cStr1("abcde");
//     my_impl::cowString cStr2(std::move(cStr1));
//     EXPECT_EQ(cStr2, "abcde");
// }

// TEST(cowString, copyAssign) {
//     my_impl::cowString cStr1("abcde");
//     my_impl::cowString cStr2("vwxyz");
//     cStr1 = cStr2;
//     EXPECT_EQ(cStr1, "vwxyz");
// }

// TEST(cowString, moveAssign) {
//     my_impl::cowString cStr1("abcde");
//     my_impl::cowString cStr2("vwxyz");
//     cStr1 = std::move(cStr2);
//     EXPECT_EQ(cStr1, "vwxyz");
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

