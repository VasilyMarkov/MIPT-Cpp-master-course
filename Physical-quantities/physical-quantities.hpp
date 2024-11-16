#ifndef PHYSICAL_QUANTITIES_H
#define PHYSICAL_QUANTITIES_H

#include <iostream>
#include <type_traits>
#include <array>
#include <utility>

template<int... Args>
struct Unit {
    static constexpr auto dims = std::make_tuple(Args...);
};

template<typename Tuple1, typename Tuple2, std::size_t... Is>
constexpr auto tuple_sum_impl(Tuple1 t1, Tuple2 t2, std::index_sequence<Is...>) {
    return std::make_tuple((std::get<Is>(t1) + std::get<Is>(t2))...);
}

template<typename UnitT>
struct Value {
    using Unit = UnitT;
    double value = 0.0;
    explicit Value(double d): value(d) {}
};


template<typename Tuple1, typename Tuple2>
constexpr auto tuple_sum(Tuple1 t1, Tuple2 t2) {
    return tuple_sum_impl(t1, t2, std::make_index_sequence<std::tuple_size<Tuple1>::value>{});
}

template<int... Args1, int... Args2>
constexpr auto sumDims(Value<Unit<Args1...>>, Value<Unit<Args2...>>) {
    constexpr auto t1 = std::make_tuple(Args1...);
    constexpr auto t2 = std::make_tuple(Args2...);
    constexpr auto result_tuple = tuple_sum(t1, t2);
    constexpr auto max_dimension = std::max(std::tuple_size_v<decltype(t1)>, std::tuple_size_v<decltype(t2)>);

    constexpr auto to_unit_impl = [=]<std::size_t... Is>(std::index_sequence<Is...>) {
        return Unit<std::get<Is>(result_tuple)...>{};
    };

    return to_unit_impl(std::make_index_sequence<std::tuple_size_v<decltype(result_tuple)>>{});
}

template<int... Args1, int... Args2>
constexpr auto operator*(Value<Unit<Args1...>> val1, Value<Unit<Args2...>> val2) {
    return Value<decltype(sumDims(val1, val2))>(val1.value * val2.value);
}

using Meter = Unit<1,0,0>;
// using Speed = Value<Unit<1,0,-1>>;
// using Acceleration = Value<Unit<1,0,-2>>;
using Force = Value<Unit<1,1,-2>>;





#endif //PHYSICAL_QUANTITIES_H