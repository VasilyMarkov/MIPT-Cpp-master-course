#include <iostream>
#include <vector>
#include "persistent_bst.hpp"
#include "utility.hpp"

int main() {
    my_impl::PersistentBST<int> pbst;
    pbst.insert(3);
    pbst.insert(1);
    pbst.insert(2);

     auto flatten = pbst.flatten();
     std::vector<int> result = {1,2,3};
     pbst.print();
    
}
