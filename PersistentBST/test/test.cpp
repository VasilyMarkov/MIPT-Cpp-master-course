#include <gtest/gtest.h>
#include "persistent_bst.hpp"
#include "utility.hpp"

TEST(Pbst, test) {
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);

    auto flatten = pbst.flatten();
    std::vector<int> result = {1,2,3};
    EXPECT_EQ(flatten, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

