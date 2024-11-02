#include "radix_sort.hpp"

namespace my_impl
{

static int getMax(const std::vector<int>& arr) 
{
    return *std::max_element(arr.begin(), arr.end());
}


static void countingSort(std::vector<int>& arr, int exp) 
{
    std::vector<int> output(arr.size());
    std::vector<int> count(10, 0);

    for(auto&& el : arr) {
        int index = (el / exp) % 10;
        count[index]++;
    }

    std::transform(std::cbegin(count)+1, std::cend(count), std::cbegin(count), std::begin(count)+1, std::plus<>{});

    for(auto it = std::crbegin(arr); it != std::crend(arr); ++it) {
        int index = (*it / exp) % 10;
        output[count[index] - 1] = *it;
        count[index]--;
    }

    arr = std::move(output);
}


void radixSort(std::vector<int>& arr) 
{
    int max = getMax(arr);

    for (int exp = 1; max / exp > 0; exp *= 10) 
    {
        countingSort(arr, exp);
    }
}


} //namespace my_impl

