#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <type_traits>

namespace my_impl
{

struct typeLess {
    template<typename T, typename U>
    struct compare: std::integral_constant<bool, 
        !std::is_same_v<T, U> && (sizeof(T) < sizeof(U))> {};
};

template<typename T, typename U>
void compareTypes() 
{
    if constexpr(typeLess::compare<T, U>::value) {
        std::cout << "T is less than U" << std::endl;
    }
    else {
        std::cout << "U is less than T" << std::endl;
    }
}

template<typename... Args>
class Tuple
{
public:
    Tuple(){}
private:

};

} // namespace my_impl

#endif //TUPLE_H