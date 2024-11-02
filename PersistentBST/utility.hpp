#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <iostream>
#include <unordered_map>

namespace my_impl {

template<typename Cont>
concept HasBeginEnd = requires (Cont container) 
{
    { container.begin() } -> std::input_iterator;
    { container.end() } -> std::input_iterator;
};

template <typename T>
void print(const std::vector<T>& vector) {
    for(auto&& el:vector) {
        std::cout << el << std::endl;
    }
    // std::cout << std::endl;
}

template <typename T, typename U>
void print(const std::unordered_map<T, U>& map) {
    for(auto&& el:map) {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}


}//namespace app

#endif //UTILITY_H