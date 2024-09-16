#ifndef CUSTOM_CHAR_TRAITS_H
#define CUSTOM_CHAR_TRAITS_H
#include <array>

namespace my_impl {

template <typename CharT>
struct TestCharTraits;

template<>
struct TestCharTraits<char> {
    static constexpr std::array<char, 6> value1 = {'a', 'b', 'c', 'd', 'e', '\0'};
    static constexpr std::array<char, 6> value2 = {'v', 'w', 'x', 'y', 'z', '\0'};
    static constexpr std::array<char, 3> substr_value = {'b', 'c', 'd'};
};

template<>
struct TestCharTraits<char16_t> {
    static constexpr std::array<char16_t, 6> value1 = {u'a', u'b', u'c', u'd', u'e', '\0'};
    static constexpr std::array<char16_t, 6> value2 = {u'v', u'w', u'x', u'y', u'z', '\0'};
    static constexpr std::array<char16_t, 3> substr_value = {u'b', u'c', u'd'};
};

template<>
struct TestCharTraits<char32_t> {
    static constexpr std::array<char32_t, 6> value1 = {U'a', U'b', U'c', U'd', U'e', '\0'};
    static constexpr std::array<char32_t, 6> value2 = {U'v', U'w', U'x', U'y', U'z', '\0'};
    static constexpr std::array<char32_t, 3> substr_value = {U'b', U'c', U'd'};
};

template<>
struct TestCharTraits<wchar_t> {
    static constexpr std::array<wchar_t, 6> value1 = {L'a', L'b', L'c', L'd', L'e', '\0'};
    static constexpr std::array<wchar_t, 6> value2 = {L'v', L'w', L'x', L'y', L'z', '\0'};
    static constexpr std::array<wchar_t, 3> substr_value = {L'b', L'c', L'd'};
};

} //namespace my_impl

#endif //CUSTOM_CHAR_TRAITS_H