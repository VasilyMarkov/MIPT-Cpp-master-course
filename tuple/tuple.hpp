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
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace mpl = boost::mpl;

template <typename T>
struct sizeofType : mpl::size_t<sizeof(typename boost::remove_reference<T>::type)> {};

template <typename... Ts>
struct Tuple {
    using Vec = mpl::vector<Ts...>;
    using sorted = typename mpl::sort<Vec, mpl::less<sizeofType<mpl::_1>, sizeofType<mpl::_2>>>::type;
};

template <typename T>
void printType() {
    std::cout << boost::typeindex::type_id<T>().pretty_name() << std::endl;
}

template <typename Tuple>
void printSortedTypes() {
    using SortedTypes = typename Tuple::sorted;
    boost::mpl::for_each<SortedTypes, boost::add_pointer<mpl::_1>>
    (
        []<typename T>(T)
        {
            printType<T>();
        }
    );
}


#endif //TUPLE_H