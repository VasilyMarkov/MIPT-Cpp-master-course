#include <iostream>
#include <vector>
#include "persistent_bst.hpp"
#include "utility.hpp"

int main() {
    my_impl::PersistentBST pbst = {4,5};
    // pbst.printOldTree();
    pbst.printNewTree();
}
