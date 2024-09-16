#ifndef COW_STRING_H
#define COW_STRING_H

#include <iostream>
#include <type_traits>
#include <concepts>
#include <cstring>
#include <cstddef>  
#include <memory>
#include <vector>
#include <boost/tokenizer.hpp>

namespace my_impl {

template<typename CharT, typename Traits = std::char_traits<CharT>> 
requires std::is_same_v<CharT, char>     || 
         std::is_same_v<CharT, char8_t>  ||
         std::is_same_v<CharT, char16_t> ||
         std::is_same_v<CharT, char32_t> ||
         std::is_same_v<CharT, wchar_t>
struct basicCowString final
{
    basicCowString() = default;

    explicit basicCowString(const CharT* str):
        ptr_data_(std::make_shared<buffer>(Traits::length(str))), 
        size_(ptr_data_->size())
    {
        std::copy(str, str + Traits::length(str), std::begin(*ptr_data_));
    }

    explicit basicCowString(const std::basic_string<CharT>& str):
        ptr_data_(std::make_shared<buffer>(str.size())), 
        size_(ptr_data_->size())
    {
        std::copy(std::begin(str), std::end(str), std::begin(*ptr_data_));
    }

    template <std::contiguous_iterator Iter>
    basicCowString(Iter begin, Iter end):
        ptr_data_(std::make_shared<buffer>(std::distance(begin, end))),
        size_(ptr_data_->size())
    { 
        std::copy(begin, end, std::begin(*ptr_data_));
    }

    basicCowString(const basicCowString& rhs) noexcept = default;
    basicCowString& operator=(const basicCowString& rhs) noexcept = default;

    basicCowString(basicCowString&& rhs) noexcept
    {
        std::swap(ptr_data_, rhs.ptr_data_);
        std::swap(size_, rhs.size_);
    }

    basicCowString& operator=(basicCowString&& rhs) noexcept 
    {
        std::swap(ptr_data_, rhs.ptr_data_);
        std::swap(size_, rhs.size_);
        return *this;
    }

    ~basicCowString() = default;

    size_t size() const noexcept {return size_;}

    bool unique() const noexcept {return ptr_data_.unique();}

    basicCowString substr(size_t begin, size_t end) const {
        if(begin == end) return basicCowString{};

        if(end < begin) throw std::length_error("invalid iterator range");

        basicCowString tmp(std::begin(*ptr_data_)+begin, std::begin(*ptr_data_)+end);
        tmp.detach();
        return tmp;
    }

    std::vector<basicCowString<CharT>> tokens(const CharT* seps) const {
        
        boost::tokenizer<boost::char_separator<CharT>> tokenizer
        (
            std::string_view(std::begin(*ptr_data_), std::end(*ptr_data_)), 
            boost::char_separator<CharT>(seps)
        );

        return std::vector<basicCowString<char>>(std::begin(tokenizer), std::end(tokenizer));
    }

    friend constexpr bool operator==(const basicCowString& lhs, const basicCowString& rhs) 
    {
        return lhs.size() == rhs.size() && !Traits::compare(lhs.ptr_data_->data(), rhs.ptr_data_->data(), lhs.size());
    }

    friend constexpr bool operator==(const basicCowString& lhs, const CharT* rhs) 
    {
        return lhs.size() == Traits::length(rhs) && !Traits::compare(lhs.ptr_data_->data(), rhs, lhs.size());
    }

    friend std::ostream& operator<<(std::ostream& os, const basicCowString& string) 
    {
        if constexpr (std::is_same_v<CharT, char>) {
            for(auto&& el : *string.ptr_data_) os << el;
        }
        return os;
    }
private:

    void detach() {
        if(!ptr_data_.unique()) {
            auto new_ptr_data_ = std::make_unique<buffer>(ptr_data_->size());
            std::copy(std::begin(*ptr_data_), std::end(*ptr_data_), std::begin(*new_ptr_data_));
            ptr_data_ = std::move(new_ptr_data_);
        }
    }

    using buffer = std::vector<CharT>;
    std::shared_ptr<buffer> ptr_data_ = nullptr;
    size_t size_ = 0;
};

using cowString     = basicCowString<char>; 
using u8CowString   = basicCowString<char8_t>; 
using u16CowString  = basicCowString<char16_t>; 
using u32CowString  = basicCowString<char32_t>; 
using wCowString    = basicCowString<wchar_t>; 

} //namespace my_impl




#endif //COW_STRING_H