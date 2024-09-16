#ifndef TESTCHARTRAITS_H
#define TESTCHARTRAITS_H
#include <array>

namespace my_impl {
    
template <typename CharT>
struct TestCharTraits;

template<>
struct TestCharTraits<char> {
    static constexpr std::array<char, 6> value1 = {'a', 'b', 'c', 'd', 'e', '\n'};
    static constexpr std::array<char, 6> value2 = {'y', 'w', 'x', 'y', 'z', '\n'};
};

template<>
struct TestCharTraits<char16_t> {
    static constexpr std::array<char16_t, 6> value1 = {u'a', u'b', u'c', u'd', u'e', '\n'};
    static constexpr std::array<char16_t, 6> value2 = {u'y', u'w', u'x', u'y', u'z', '\n'};
};

template<>
struct TestCharTraits<char32_t> {
    static constexpr std::array<char32_t, 6> value1 = {U'a', U'b', U'c', U'd', U'e', '\n'};
    static constexpr std::array<char32_t, 6> value2 = {U'y', U'w', U'x', U'y', U'z', '\n'};
};

template<>
struct TestCharTraits<wchar_t> {
    static constexpr std::array<wchar_t, 6> value1 = {L'a', L'b', L'c', L'd', L'e', '\n'};
    static constexpr std::array<wchar_t, 6> value2 = {L'y', L'w', L'x', L'y', L'z', '\n'};
};

} //namespace my_impl

#endif //TESTCHARTRAITS_H