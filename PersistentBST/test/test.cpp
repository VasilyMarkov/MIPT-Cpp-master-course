#include <gtest/gtest.h>
#include "persistent_bst.hpp"
#include "utility.hpp"

TEST(Pbst, insertTest) {
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);

    auto flatten = pbst.flatten();
    std::vector<int> result = {1,2,3};
    EXPECT_EQ(flatten, result);
}

TEST(Pbst, initializer_listTest) {
    my_impl::PersistentBST<int> pbst = {3,1,2};

    auto flatten = pbst.flatten();
    std::vector<int> result = {1,2,3};
    EXPECT_EQ(flatten, result);
}

TEST(Pbst, equalTest) {
    my_impl::PersistentBST<int> pbst1 = {3,1,2};
    my_impl::PersistentBST<int> pbst2 = {3,1,2};
    EXPECT_TRUE(pbst1 == pbst2);

    my_impl::PersistentBST<int> pbst3 = {1,2,3};
    EXPECT_FALSE(pbst1 == pbst3);
    
    my_impl::PersistentBST<int> pbst4;
    my_impl::PersistentBST<int> pbst5;
    EXPECT_FALSE(pbst1 == pbst4);
    EXPECT_TRUE(pbst4 == pbst5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

