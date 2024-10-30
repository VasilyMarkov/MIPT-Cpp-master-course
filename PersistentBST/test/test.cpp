#include <gtest/gtest.h>
#include <random>
#include <set>
#include "persistent_bst.hpp"
#include "utility.hpp"

TEST(Pbst, insertTest) {
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);

    auto flatten = pbst.flatten();
    std::vector result = {1,2,3};
    EXPECT_EQ(flatten, result);
}

TEST(Pbst, initializer_listTest) {
    my_impl::PersistentBST pbst = {3,1,2};

    auto flatten = pbst.flatten();
    std::vector result = {1,2,3};
    EXPECT_EQ(flatten, result);
}

TEST(Pbst, equalTest) {
    my_impl::PersistentBST pbst1 = {3,1,2};
    my_impl::PersistentBST pbst2 = {3,1,2};
    EXPECT_TRUE(pbst1 == pbst2);

    my_impl::PersistentBST pbst3 = {1,2,3};
    EXPECT_FALSE(pbst1 == pbst3);
    
    my_impl::PersistentBST<int> pbst4;
    my_impl::PersistentBST<int> pbst5;
    EXPECT_FALSE(pbst1 == pbst4);
    EXPECT_TRUE(pbst4 == pbst5);
}

TEST(Pbst, bigDataTest) {

    const size_t SIZE = 10;

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(1, SIZE);

    std::vector<int> data(SIZE);
    std::generate(std::begin(data), std::end(data), 
        [&distrib, &gen](){ return distrib(gen); });

    std::set sort_data(std::begin(data), std::end(data));
    my_impl::PersistentBST pbst = data;

    std::vector out_data(std::begin(sort_data), std::end(sort_data));

    EXPECT_EQ(pbst.flatten(), out_data);
}

TEST(Pbst, undoRedoTest) {
    my_impl::PersistentBST pbst = {4,2,6,1,3,5,7,8};
    my_impl::PersistentBST pbst_old = {4,2,6,1,3,5,7};
    my_impl::PersistentBST pbst_new = {4,2,6,1,3,5,7,8};
    
    pbst.undo();
    EXPECT_TRUE(pbst == pbst_old);

    pbst.redo();
    EXPECT_TRUE(pbst == pbst_new);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

