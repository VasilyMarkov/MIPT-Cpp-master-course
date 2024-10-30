#ifndef PERSISTENT_BST_H
#define PERSISTENT_BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>
#include <utility>

namespace my_impl
{

template<typename Cont>
concept HasBeginEnd = requires (Cont container) 
{
    { container.begin() } -> std::input_iterator;
    { container.end() } -> std::input_iterator;
};

template<typename T>
class BstIterator {
public:
    explicit BstIterator(T* ptr) noexcept: ptr_(ptr) {}

    T& operator*() { return *ptr_; }

    bool operator!=(const BstIterator& other) 
    const noexcept { return ptr_ != other.ptr; }

    BstIterator& operator++() {
        ptr_++;
        return *this;
    }
private:
    T* ptr_;
};

template <std::totally_ordered T>
class PersistentBST {
    class Node;
    using Node_ptr = std::shared_ptr<Node>;

    class Node {
    public:
        explicit Node(T value) noexcept: value_(value) {}
        
        Node(T value, Node_ptr left, Node_ptr right) noexcept:
            value_(value), 
            left_(left), 
            right_(right) {}

        T value_;
        Node_ptr left_;
        Node_ptr right_;
    };
public:
    PersistentBST() {}
    explicit PersistentBST(Node_ptr new_head) noexcept: head_(new_head) {}

    template <HasBeginEnd Cont>
    PersistentBST(const Cont& cont)
    {
        for(auto&& el:cont) {
            insert(el);
        }
    }

    PersistentBST(const std::initializer_list<T>& list)
    {
        for(auto&& el:list) {
            insert(el);
        }
    }

    void insert(T value) 
    { 
        if(empty()) head_ = std::make_shared<Node>(value); 

        else 
        {
            temp_head_ = std::make_shared<Node>(*head_); 
            insertRecursive(head_, value);
        }
        size_++;
    }
    
    void testInsert(T value) {
        temp_bst_ = std::make_unique<PersistentBST>(testInsertRecursive(head_, value));
    }

    void print() 
    {
        dump(head_);
    }

    std::vector<T> flatten() {
        std::vector<T> result;
        inorderFlat(head_, result);
        return result;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    void printTemp() {
        // inorderDump(temp_->head_);
        // std::cout << std::endl;
    }

    friend bool operator==(const PersistentBST& lhs, const PersistentBST& rhs) noexcept {
        return inorderEqual(lhs.head_, rhs.head_);
    }
    
    
private:
    void insertRecursive(Node_ptr node, T value) {
        if(value < node->value_) {
            if(node->left_ == nullptr) {
                

                node->left_ = std::make_shared<Node>(value);
            }
            else {
                insertRecursive(node->left_, value);
            }   
        }
        else {
            if(node->right_ == nullptr) {
                node->right_ = std::make_shared<Node>(value);
            }
            else {
                insertRecursive(node->right_, value);
            } 
        }
    }

    void inorderFlat(Node_ptr root, std::vector<T>& vec) 
    {
        if (root == nullptr) return;

        inorderFlat(root->left_, vec);
        vec.push_back(root->value_);
        inorderFlat(root->right_, vec);
    } 
    
    void dump(Node_ptr root, const std::string& prefix = "", bool isTail = true) {
        if (!root) {
            std::cout << prefix << (isTail ? "└──" : "├──") << "n" << std::endl;
            return;
        }

        std::cout << prefix << (isTail ? "└──" : "├──") << root->value_ << std::endl;

        std::string newPrefix = prefix + (isTail ? "    " : "│   ");

        dump(root->left_, newPrefix, root->right_ == nullptr);
        dump(root->right_, newPrefix, true);
    } 

    friend bool inorderEqual(Node_ptr lhs, Node_ptr rhs) noexcept
    {
        if (lhs == nullptr && rhs == nullptr) return true;
        if (lhs == nullptr || rhs == nullptr) return false;

        if (lhs->value_ != rhs->value_) return false;

        return inorderEqual(lhs->left_, rhs->left_) && inorderEqual(lhs->right_, rhs->right_);
    }

    Node_ptr head_;
    Node_ptr temp_head_;
    size_t size_{0};
};

template<template <typename> typename Cont, typename T>
PersistentBST(const Cont<T>&) -> PersistentBST<T>;

} // namespace my_impl

#endif //PERSISTENT_BST_H