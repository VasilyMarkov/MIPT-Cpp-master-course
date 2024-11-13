#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size_t.hpp>

namespace mpl = boost::mpl;

template <typename T>
struct sizeofType : mpl::size_t<sizeof(T)> {};

template <typename... Ts>
struct Tuple {
    using Vec = mpl::vector<Ts...>;
    using sorted = typename mpl::sort<Vec, mpl::less<sizeofType<mpl::_1>, sizeofType<mpl::_2>>>::type;
};

struct printType {
    template <typename T>
    void operator()(T) const {
        std::cout << typeid(T).name() << std::endl;
    }
};

template <typename Tuple>
void printSortedTypes() {
    using SortedTypes = typename Tuple::sorted;
    boost::mpl::for_each<SortedTypes>(printType());
}

#endif //TUPLE_H