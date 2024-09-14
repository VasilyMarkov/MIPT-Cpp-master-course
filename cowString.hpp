#ifndef COW_STRING_H
#define COW_STRING_H

#include <iostream>
#include <type_traits>
#include <concepts>
#include <cstring>
#include <iterator> 
#include <cstddef>  

namespace my_impl {

template <typename T, typename U>
requires(std::same_as<T, std::decay_t<U>>)
void construct(T* ptr, U&& rhs) noexcept(noexcept(U{})) 
{new (ptr) T(std::forward<U>(rhs));}

template<typename T> void destroy(T* ptr) {ptr->~T();}

template<std::random_access_iterator It> void destroy(It begin, It end) noexcept {
    while(begin != end) {
        destroy(&*begin++);
    }
}

template <class T>
struct Iterator final {
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;  
    using reference         = T&;  

    constexpr Iterator() noexcept {};
    constexpr explicit Iterator(pointer ptr) noexcept: ptr_(ptr) {}
    constexpr Iterator(const Iterator& itr) noexcept: ptr_(itr.ptr_) {}
    constexpr Iterator& operator=(const Iterator& itr) noexcept {ptr_ = itr.ptr_;}
    ~Iterator(){}

    constexpr const reference operator*() const {return *ptr_;}
    constexpr reference operator*() {return *ptr_;}
    constexpr pointer operator->() const {return ptr_;}

    constexpr Iterator& operator++() {ptr_++; return *this;}
    constexpr Iterator operator++(int) {Iterator tmp = *this; ++(*this); return tmp;}
    constexpr Iterator& operator--() {ptr_--; return *this;}
    constexpr Iterator operator--(int) {Iterator tmp = *this; --(*this); return tmp;}

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {return lhs.ptr_ == rhs.ptr_;}
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {return lhs.ptr_ != rhs.ptr_;}
    
private:
    pointer ptr_;
};


template <class T>
struct bufCowString 
{
protected:
    size_t size_, used_ = 0;
    T* data_ = nullptr;
protected:
    bufCowString(size_t n = 0):
        data_(n == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(char)*n))), 
        size_(n) {}

    bufCowString(const bufCowString& buf) = delete;
    bufCowString& operator=(const bufCowString& buf) = delete;

    bufCowString (bufCowString&& buf) noexcept: 
        size_(buf.size_), used_(buf.used_), data_(buf.data_) 
    {
        buf.size_ = 0;
        buf.used_ = 0;
        buf.data_ = nullptr; 
    };
    
    bufCowString& operator=(bufCowString&& buf) noexcept 
    {
        std::swap(data_, buf.data_); 
        std::swap(size_, buf.size_);
        std::swap(used_, buf.used_);
        return *this;
    };

    ~bufCowString() 
    {
        destroy(data_, data_ + used_);
        ::operator delete(data_);
    };
};

template<class CharT, class Traits = std::char_traits<CharT>> 
struct CowString final: private bufCowString<CharT> 
{
    using bufCowString<CharT>::used_;
    using bufCowString<CharT>::size_;
    using bufCowString<CharT>::data_;

    using iterator = Iterator<CharT>;
    using const_iterator = const Iterator<CharT>;

    inline iterator begin() noexcept { return iterator(&data_[0]); }
    inline const_iterator cbegin() noexcept { return const_iterator(&data_[0]); }
    inline iterator end() noexcept { return iterator(&data_[size_]); }
    inline const_iterator cend() noexcept { return const_iterator(&data_[size_]); }

    explicit CowString(size_t n = 0): bufCowString<CharT>(n) {}

    CowString(const CharT* str): bufCowString<CharT>(Traits::length(str))    
    {
        while(used_ < Traits::length(str)) {
            construct(data_ + used_, str[used_]);
            ++used_;
        }
    }

    // template<typename It> CowString(It begin, It end): 
    //     bufCowString<T>(std::distance(begin, end)) 
    // {
    //     while(begin != end) {
    //         auto it = *begin++;
    //         construct(data_ + used_++, std::move(it));
    //     }
    // }

    CowString(const CowString& rhs): bufCowString<CharT>(rhs.used_)
    {
        while(used_ < rhs.used_) {
            construct(data_+used_, std::move(rhs.data_[used_]));
            used_++;
        }
    }

    ~CowString() 
    {

    }
    
    constexpr size_t size() const noexcept {
        return size_;
    }

    constexpr auto operator==(const CowString& rhs) const {
        return Traits::compare(data_, rhs.data_, std::min(size_, rhs.size_)) == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const CowString& string) {
        for(size_t i = 0; i < string.size_; ++i) os << string.data_[i];
        return os;
    }
};

}

#endif //COW_STRING_H