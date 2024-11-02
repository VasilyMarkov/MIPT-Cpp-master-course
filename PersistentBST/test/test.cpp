#include <gtest/gtest.h>
#include <random>
#include <set>
#include "persistent_bst.hpp"
#include "utility.hpp"


class OrderedType final 
{
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

struct PodType final
{
    int x{}, y{}, z{};
    auto operator<=>(const PodType&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const PodType& pod_type) 
    {
        os << "x: " << pod_type.x  << " y: " << pod_type.y  << " z: " << pod_type.z; 
        return os;
    }
};

struct NonePodType
{
    int x{}, y{}, z{};
    virtual ~NonePodType(){}

    auto operator<=>(const NonePodType&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const NonePodType& none_pod_type) 
    {
        os << "x: " << none_pod_type.x  << " y: " << none_pod_type.y  << " z: " << none_pod_type.z; 
        return os;
    }
};

TEST(Pbst, insertTest) {
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);
    
    std::vector result = {1,2,3};
    EXPECT_EQ(pbst.flatten(), result);
}

TEST(Pbst, initializer_listTest) {
    my_impl::PersistentBST pbst = {3,1,2};

    std::vector result = {1,2,3};
    EXPECT_EQ(pbst.flatten(), result);
}

TEST(Pbst, removeTest) {
    my_impl::PersistentBST<int> pbst = {3,1,2};
    pbst.insert(4);

    pbst.remove(4);
    pbst.remove(1);
    
    std::vector result = {2,3};
    EXPECT_EQ(pbst.flatten(), result);
}

TEST(Pbst, searchTest) {
    my_impl::PersistentBST<int> pbst = {3,1,2};
    
    EXPECT_EQ(*pbst.search(3), 3);
}

TEST(Pbst, equalTest) {
    my_impl::PersistentBST pbst1 = {3,1,2};
    my_impl::PersistentBST pbst2 = {3,1,2};
    EXPECT_TRUE(pbst1 == pbst2);

    my_impl::PersistentBST pbst3 = {1,2,3};
    EXPECT_TRUE(pbst1 == pbst3);
    
    my_impl::PersistentBST<int> pbst4;
    my_impl::PersistentBST<int> pbst5;
    EXPECT_FALSE(pbst1 == pbst4);
    EXPECT_TRUE(pbst4 == pbst5);
}

TEST(Pbst, bigDataTest) {

    const size_t SIZE = 1e3;

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

TEST(Pbst, undoInsertTest) {
    my_impl::PersistentBST pbst = {3,1,2};
    my_impl::PersistentBST pbst_new = {3,1,2,4};
    my_impl::PersistentBST pbst_old = {3,1};
    pbst.undo();
    pbst.undo();

    EXPECT_TRUE(pbst == pbst_old);
}

TEST(Pbst, undoRemoveTest) {
    my_impl::PersistentBST pbst = {3,1,2,4};
    my_impl::PersistentBST pbst_new = {3,1,2,4};

    pbst.remove(4);
    pbst.undo();

    EXPECT_TRUE(pbst == pbst_new);
}

TEST(Pbst, undoRedoTest1) {
    my_impl::PersistentBST pbst = {3,1,2,4};
    my_impl::PersistentBST pbst_old = {3,1,2,4};
    my_impl::PersistentBST pbst_old1 = {1,2};
    
    pbst.undo();
    pbst.redo();
    EXPECT_TRUE(pbst == pbst_old);
    
    pbst.undo();
    pbst.remove(3);

    EXPECT_TRUE(pbst == pbst_old1);
}

TEST(Pbst, undoRedoTest2) {
    my_impl::PersistentBST pbst = {3,1,2,4};
    my_impl::PersistentBST pbst_old = {3,1,2,4};
    my_impl::PersistentBST pbst_old1 = {1,2};
    
    pbst.undo();
    pbst.redo();
    pbst.undo();
    pbst.redo();
    EXPECT_TRUE(pbst == pbst_old);

    pbst.redo();
    pbst.redo();
    EXPECT_TRUE(pbst == pbst_old);
}

TEST(Pbst, NonIntTest) {
    
    std::vector<PodType> data(10);
    std::generate(std::begin(data), std::end(data), 
        [n = 0]() mutable {return PodType{n++, n++, n++};});

    std::random_shuffle(std::begin(data), std::end(data));

    my_impl::PersistentBST<PodType> pbst{data};

    std::sort(std::begin(data), std::end(data));

    EXPECT_EQ(pbst.flatten(), data);
}

TEST(Pbst, NonIntTest1) {
    
    std::vector<PodType> data(10);
    std::generate(std::begin(data), std::end(data), 
        [n = 0]() mutable {return PodType{n++, n++, n++};});

    std::random_shuffle(std::begin(data), std::end(data));

    my_impl::PersistentBST<PodType> pbst{data};

    std::sort(std::begin(data), std::end(data));

    EXPECT_EQ(pbst.flatten(), data);
}

TEST(Pbst, NonIntergalTypeRemove) {
    
    std::vector<PodType> data(10);
    
    std::generate(std::begin(data), std::end(data), 
        [n = 0]() mutable {return PodType{n++, n++, n++};});

    std::vector<PodType> ref_data(std::begin(data), std::end(data)-1);

    my_impl::PersistentBST<PodType> pbst{data};

    pbst.remove(*(std::end(data)-1));

    EXPECT_EQ(pbst.flatten(), ref_data);
}

TEST(Pbst, NonIntergalTypeUndoRedo) {
    
    std::vector<PodType> data(10);
    
    std::generate(std::begin(data), std::end(data), 
        [n = 0]() mutable {return PodType{n++, n++, n++};});

    my_impl::PersistentBST<PodType> pbst{data};
 

    auto value1 = PodType{50, 50, 50}; 
    auto value2 = PodType{52, 52, 52}; 

    pbst.insert(value1);
    pbst.undo();
    EXPECT_EQ(pbst.flatten(), data);

    pbst.redo();
    pbst.remove(value1);
    EXPECT_EQ(pbst.flatten(), data);

    pbst.undo();
    pbst.insert(value2);
    data.push_back(value2);
    EXPECT_EQ(pbst.flatten(), data);

}


// TEST(Pbst, NonIntergalTypeRemove) {
    
//     std::vector<PodType> data(10);
    
//     std::generate(std::begin(data), std::end(data), 
//         [n = 0]() mutable {return PodType{n++, n++, n++};});

//     std::vector<PodType> ref_data(std::begin(data), std::end(data)-1);

//     my_impl::PersistentBST<PodType> pbst{data};

//     pbst.remove(*(std::end(data)-1));

//     EXPECT_EQ(pbst.flatten(), ref_data);
// }

// TEST(Pbst, NonIntergalTypeTest) {
//     my_impl::PersistentBST<OrderedType> pbst;
    
//     OrderedType foo{1};

//     pbst.insert(foo);

// }

// TEST(Pbst, moveNonIntergalTypeTest) {
//     my_impl::PersistentBST<OrderedType> pbst;

//     pbst.insert(OrderedType{1});

// }

// TEST(Pbst, moveNonIntergalTypeTest) {
//     my_impl::Test<int> pod;
//     my_impl::Test<std::vector<int>> not_pod;
// }

TEST(Pbst_flat, insert) 
{
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);

    std::vector<int> data = {1,2,3};

    EXPECT_EQ(pbst.flatten(), data);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

