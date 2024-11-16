#ifndef PHYSICAL_QUANTITIES_H
#define PHYSICAL_QUANTITIES_H

#include <iostream>
#include <type_traits>
#include <array>
#include <utility>
#include <unordered_map>

namespace 
{

// std::unordered_map<size_t, std::string> dimension_names = 
// {
//     {0, "m"},
//     {1, "kg"},
//     {2, "s"},
//     {3, "С"}
// }

template<typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
    ((std::cout << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template<typename Tuple>
void print_tuple(const Tuple& t) {
    print_tuple_impl(t, std::make_index_sequence<std::tuple_size<Tuple>::value>{});
}

template<int... Args>
struct Unit {
    static constexpr auto dims = std::make_tuple(Args...);
};

template<typename UnitT>
struct Value {
    using Unit = UnitT;
    double value = 0.0;
    explicit Value(double d): value(d) {}

    void print() {
        print_tuple(Unit::dims);
    }
};

template<typename Tuple1, typename Tuple2, std::size_t... Is>
constexpr auto tuple_sum_impl(Tuple1 t1, Tuple2 t2, std::index_sequence<Is...>) {
    return std::make_tuple((std::get<Is>(t1) + std::get<Is>(t2))...);
}

template<typename Tuple1, typename Tuple2>
constexpr auto tuple_sum(Tuple1 t1, Tuple2 t2) {
    return tuple_sum_impl(t1, t2, std::make_index_sequence<std::tuple_size_v<Tuple1>>{});
}

template<typename Tuple, std::size_t N>
constexpr auto pad_tuple(Tuple t) {
    if constexpr (N == 0) {
        return t;
    } else {
        return pad_tuple<decltype(std::tuple_cat(t, std::make_tuple(0))), N - 1>(std::tuple_cat(t, std::make_tuple(0)));
    }
}

template<int... Args1, int... Args2>
constexpr auto sum_dims(Value<Unit<Args1...>>, Value<Unit<Args2...>>) {
    constexpr auto t1 = std::make_tuple(Args1...);
    constexpr auto t2 = std::make_tuple(Args2...);

    constexpr std::size_t size1 = sizeof...(Args1);
    constexpr std::size_t size2 = sizeof...(Args2);
    constexpr std::size_t max_size = (size1 > size2) ? size1 : size2;

    constexpr auto padded_t1 = pad_tuple<decltype(t1), max_size - size1>(t1);
    constexpr auto padded_t2 = pad_tuple<decltype(t2), max_size - size2>(t2);

    constexpr auto result_tuple = tuple_sum(padded_t1, padded_t2);
   
    constexpr auto to_unit_impl = [=]<std::size_t... Is>(std::index_sequence<Is...>) {
        return Unit<std::get<Is>(result_tuple)...>{};
    };

    return to_unit_impl(std::make_index_sequence<std::tuple_size_v<decltype(result_tuple)>>{});
}

} // namespace 

template<int... Args1, int... Args2>
constexpr auto operator*(Value<Unit<Args1...>> val1, Value<Unit<Args2...>> val2) {
    return Value<decltype(sum_dims(val1, val2))>(val1.value * val2.value);
}

using Meter = Unit<1,0,0>;
using Square = Unit<2,0,0>;
using Mass = Unit<0,1,0>;
using Second = Unit<0,0,1>;
using Second2 = Unit<0,0,2>;
using Charge = Unit<0,0,0,1>;

using Speed = Value<Unit<1,0,-1>>;
using Acceleration = Value<Unit<1,0,-2>>;
using Force = Value<Unit<1,1,-2>>;
using Pressure = Value<Unit<-1,1,-2>>;
using Current = Value<Unit<0,0,-1,1>>;




#endif //PHYSICAL_QUANTITIES_H