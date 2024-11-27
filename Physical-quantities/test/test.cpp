#include <gtest/gtest.h>
#include "physical-quantities.hpp"

TEST(Physical_quantities, test1) {
    Distance d(2.0);
    Mass m(3.0);
    Time t(4.0);
    auto U = d*m*t;
    
    EXPECT_DOUBLE_EQ(U.value, 24.0);
    ASSERT_TRUE((std::is_same_v<decltype(U), Value<Unit<1,1,1>>>));
}

TEST(Physical_quantities, test2) {
    Value<Unit<>> value1(2.0);
    Value<Unit<1,0,1>> value2(3.0);
    auto U = value1*value2;
    
    EXPECT_DOUBLE_EQ(U.value, 6.0);
    ASSERT_TRUE((std::is_same_v<decltype(U), Value<Unit<1,0,1>>>));
}

TEST(Physical_quantities, test3) {
    Current current(0.1);
    Resistance resistance(150.0);
    auto voltage = current * resistance;
    
    EXPECT_DOUBLE_EQ(voltage.value, 15.0);
    ASSERT_TRUE((std::is_same_v<decltype(voltage), Value<Unit<2,1,-2,-1>>>));
}

TEST(Physical_quantities, test4) {
    Value<Unit<1,0,2>> value1(2.0);
    Value<Unit<1,0,0,1,1>> value2(3.0);
    auto U = value1 * value2;
    
    EXPECT_DOUBLE_EQ(U.value, 6.0);
    ASSERT_TRUE((std::is_same_v<decltype(U), Value<Unit<2,0,2,1,1>>>));
}

TEST(Physical_quantities, test5) {
    Time t(10.0);
    Current I(0.1);
    Resistance R(150.0);
    auto Q = I*I*R*t;
    
    EXPECT_DOUBLE_EQ(Q.value, 15.0);
    ASSERT_TRUE((std::is_same_v<decltype(Q), Energy>));
}

TEST(Physical_quantities, test6) {
    Force F(10.0);
    Mass m(2.0);

    auto a = F / m;
    
    EXPECT_DOUBLE_EQ(a.value, 5.0);
    ASSERT_TRUE((std::is_same_v<decltype(a), Acceleration>));
}

TEST(Physical_quantities, test7) {
    Value<Unit<>> value1(2.0);
    Value<Unit<>> value2(3.0);
    auto U = value1*value2;
    
    EXPECT_DOUBLE_EQ(U.value, 6.0);
    ASSERT_TRUE((std::is_same_v<decltype(U), Value<Unit<>>>));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

