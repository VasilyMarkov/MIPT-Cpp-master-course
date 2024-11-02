#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>
#include <utility>
#include <iomanip>
#include <algorithm>
#include "utility.hpp"

namespace my_impl
{
namespace {

template <typename Iter>
int getMax(Iter begin, Iter end) 
{
    return *std::max_element(begin, end);
}

template <typename Iter>
static void countingSort(Iter begin, Iter end, int exp) 
{
    std::vector<int> output(std::distance(begin, end));
    std::vector<int> count(10, 0);
    std::vector<int> arr(begin, end);

    for(auto it = begin; it != end; ++it) {
        int index = (*it / exp) % 10;
        count[index]++;
    }

    std::transform(std::cbegin(count)+1, std::cend(count), std::cbegin(count), std::begin(count)+1, std::plus<>{});

    for(auto it = std::crbegin(arr); it != std::crend(arr); ++it) {
        int index = (*it / exp) % 10;
        output[count[index] - 1] = *it;
        count[index]--;
    }

    std::move(std::begin(output), std::end(output), begin);
}

}

template<std::contiguous_iterator Iter>
void radixSort(Iter begin, Iter end) 
{
    int max = getMax(begin, end);

    for (int exp = 1; max / exp > 0; exp *= 10) 
    {
        countingSort(begin, end, exp);
    }
}


} //namespace my_impl

#endif //RADIX_SORT_H