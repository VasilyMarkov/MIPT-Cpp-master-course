#include <gtest/gtest.h>
#include "cowString.hpp"
#include "customCharTraits.hpp"

template <typename T>
class TypedCowStringTest : public testing::Test {
public:
    const T* value1 = my_impl::TestCharTraits<T>::value1.data();
    const T* value2 = my_impl::TestCharTraits<T>::value2.data();
    const T* substr_value = my_impl::TestCharTraits<T>::substr_value.data();
};

using charTypes = ::testing::Types<char, char16_t, char32_t, wchar_t>;

TYPED_TEST_SUITE(TypedCowStringTest, charTypes);


TEST(cowStringTest, literalCompare) {
    my_impl::cowString str{"abcde"};

    EXPECT_EQ(str, "abcde");    
}

TYPED_TEST(TypedCowStringTest, equalCompare) {
    my_impl::basicCowString str1{this->value1};
    my_impl::basicCowString str2{this->value1};

    EXPECT_EQ(str1, str2);   
}   

TYPED_TEST(TypedCowStringTest, size) {
    my_impl::basicCowString str{this->value1};

    EXPECT_EQ(str.size(), 5);
}

TYPED_TEST(TypedCowStringTest, copyCtr) {
    my_impl::basicCowString str1{this->value1};
    my_impl::basicCowString str2{str1};

    EXPECT_EQ(str1, str2);
    EXPECT_EQ(str1.unique(), false);
    EXPECT_EQ(str2.unique(), false);
}

TYPED_TEST(TypedCowStringTest, moveCtr) {
    my_impl::basicCowString str1{this->value1};
    auto str2 = std::move(str1);

    EXPECT_EQ(str2, this->value1);
    EXPECT_EQ(str2.unique(), true);
}

TYPED_TEST(TypedCowStringTest, copyAssign) {
    my_impl::basicCowString str1{this->value1};
    EXPECT_EQ(str1.unique(), true);

    my_impl::basicCowString str2{this->value2};
    str1 = str2;

    EXPECT_EQ(str1, this->value2);
    EXPECT_EQ(str1.unique(), false);
    EXPECT_EQ(str2.unique(), false);
}

TYPED_TEST(TypedCowStringTest, moveAssign) {
    my_impl::basicCowString str1{this->value1};
    EXPECT_EQ(str1.unique(), true);

    auto str2 = std::move(str1);

    EXPECT_EQ(str2, this->value1);
    EXPECT_EQ(str2.unique(), true);
}

TEST(cowStringTest, emptyString) {
    my_impl::cowString str{};
    EXPECT_EQ(str.size(), 0);
}

TEST(cowStringTest, IteratorRangeTest) {
    std::string str = "abcde";
    std::vector<char> vecStr(std::begin(str), std::end(str));

    my_impl::cowString cowStr1(std::begin(str), std::end(str));
    my_impl::cowString cowStr2(std::begin(vecStr), std::end(vecStr));

    EXPECT_EQ(cowStr1, "abcde");
    EXPECT_EQ(cowStr2, "abcde");
}

TYPED_TEST(TypedCowStringTest, substrTest1) {
    my_impl::basicCowString str1{this->value1};
    auto str2 = str1.substr(1, 4);
    EXPECT_EQ(str2, this->substr_value);
}

TYPED_TEST(TypedCowStringTest, substrTest2) {
    my_impl::basicCowString str1{this->value1};
    auto str2 = str1.substr(1, 1);
    EXPECT_EQ(str2.size(), 0);
}

TYPED_TEST(TypedCowStringTest, substrTest3) {
    my_impl::basicCowString str1{this->value1};
    ASSERT_THROW(str1.substr(2, 1), std::length_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

