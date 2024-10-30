#include <gtest/gtest.h>
#include <random>
#include <set>
#include "persistent_bst.hpp"
#include "utility.hpp"

class OrderedType final {
public:
    explicit OrderedType(int value):value_(value) {std::cout << "def ctr" << std::endl;}
    
    OrderedType(const OrderedType& other): value_(other.value_) 
    {std::cout << "copy ctr" << std::endl;}
    
    OrderedType(OrderedType&& other): value_(other.value_) 
    {std::cout << "move ctr" << std::endl;}
    
    OrderedType& operator=(const OrderedType& other) 
    {value_ = other.value_; std::cout << "copy operator" << std::endl; return *this;}
    
    OrderedType& operator=(OrderedType&& other) 
    {value_ = other.value_; std::cout << "move operator" << std::endl; return *this;}
    
    ~OrderedType() {std::cout << "dtr" << std::endl;}

    auto operator<=>(const OrderedType&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const OrderedType& ordered_type) 
    {
        os << "OrderedType: " << ordered_type.value_;
        return os;
    }

private:
    int value_{};
};

struct NotOrderType {
    int x;
    int y;
};

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

// TEST(Pbst, NonIntergalTypeTest) {
//     my_impl::PersistentBST<OrderedType> pbst;
    
//     OrderedType foo{1};
//     OrderedType bar{2};
//     OrderedType foo_bar{3};

//     pbst.insert(foo_bar);
//     pbst.insert(foo);
//     pbst.insert(bar);

//     std::vector<OrderedType> data = {OrderedType(1), OrderedType(2), OrderedType(3)};

//     EXPECT_EQ(pbst.flatten(), data);
// }

TEST(Pbst, NonIntergalTypeTest) {
    my_impl::PersistentBST<OrderedType> pbst;
    
    OrderedType foo{1};

    pbst.insert(foo);

}

TEST(Pbst, moveNonIntergalTypeTest) {
    my_impl::PersistentBST<OrderedType> pbst;

    pbst.insert(OrderedType{1});

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

