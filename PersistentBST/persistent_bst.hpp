#ifndef PERSISTENT_BST_H
#define PERSISTENT_BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>
#include <utility>
#include <iomanip>

namespace my_impl
{

template<typename Cont>
concept HasBeginEnd = requires (Cont container) 
{
    { container.begin() } -> std::input_iterator;
    { container.end() } -> std::input_iterator;
};

template <std::totally_ordered T>
class PersistentBST final {
    class Node;
    using Node_ptr = std::shared_ptr<Node>;

    class Node final {
    public:
        explicit Node(T value) noexcept: value_(value) {}
        
        Node(T value, Node_ptr left, Node_ptr right) noexcept:
            value_(value), 
            left_(left), 
            right_(right) {}

        Node(const Node& other): 
            value_(other.value_), 
            left_(other.left_), 
            right_(other.right_) {}
        
        Node& operator=(const Node& other) {
            Node(other) temp;
        }
        
        void swap(Node& other) noexcept {
            std::swap(value_, other);
            std::swap(left_, other.left_);
            
        }

        friend PersistentBST;
    private:
        T value_;
        Node_ptr left_;
        Node_ptr right_;
    };
public:
    PersistentBST() {}
    explicit PersistentBST(Node_ptr new_root) noexcept: root_(new_root) {}

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

    void swap(PersistentBST& other) noexcept
    {
        std::swap(root_, other->root_);
        std::swap(size_, other->size_);
    }
    
    void insert(const T& value) 
    {
        std::cout << "const T&" << std::endl;
        if(empty()) {
            root_ = std::make_shared<Node>(value);
            ++size_;
            return;
        }

        temp_root_ = insertRecursive(root_, value);
        std::swap(temp_root_, root_);
        active_root_ = root_;

        ++size_;
    }

    void insert(T&& value) 
    {
        std::cout << "T&&" << std::endl;
        if(empty()) {
            root_ = std::make_shared<Node>(std::move(value));
            ++size_;
            return;
        }

        temp_root_ = insertRecursive(root_, std::move(value));
        std::swap(temp_root_, root_);
        active_root_ = root_;

        ++size_;
    }

    void undo() noexcept
    {
        if(size_ > 1 && !undo_cnt_) 
        {   
            active_root_ = temp_root_;
            ++undo_cnt_;
        } 
    }

    void redo() noexcept { if(size_ >= 2) active_root_ = root_; }

    void print() 
    {
        dump(active_root_);
        std::cout << "-----" << std::endl;
    }

    std::vector<T> flatten() 
    {
        std::vector<T> result;
        inorderFlat(active_root_, result);
        return result;
    }

    bool empty() const noexcept { return size_ == 0; }

    friend bool operator==(const PersistentBST& lhs, const PersistentBST& rhs) noexcept {
        return inorderEqual(lhs.active_root_, rhs.active_root_);
    }
    
private:
    Node_ptr insertRecursive(Node_ptr node, const T& value) 
    {
        std::cout << "const insert&" << std::endl;

        if(!node) return std::make_shared<Node>(value);   

        if(value < node->value_) 
        {
            auto new_left = insertRecursive(node->left_,value);
            return std::make_shared<Node>(node->value_, new_left, node->right_);
        }
        else if(value > node->value_) 
        {
            auto new_right = insertRecursive(node->right_,value);
            return std::make_shared<Node>(node->value_, node->left_, new_right);
        }
        else return node;
    }

    Node_ptr insertRecursive(Node_ptr node, T&& value) 
    {
        std::cout << "insert&&" << std::endl;
        if(!node) return std::make_shared<Node>(std::move(value));   

        if(value < node->value_) 
        {
            auto new_left = insertRecursive(node->left_, std::move(value));
            return std::make_shared<Node>(node->value_, new_left, node->right_);
        }
        else if(value > node->value_) 
        {
            auto new_right = insertRecursive(node->right_, std::move(value));
            return std::make_shared<Node>(node->value_, node->left_, new_right);
        }
        else return node;
    }

    void inorderFlat(Node_ptr root, std::vector<T>& vec) 
    {
        if (!root) return;

        inorderFlat(root->left_, vec);
        vec.push_back(root->value_);
        inorderFlat(root->right_, vec);
    } 

    void dump(Node_ptr root, const std::string& prefix = "", bool isTail = true) 
    {
        if (!root) {
            std::cout << prefix << (isTail ? "└──" : "├──") << "n" << std::endl;
            return;
        }

        std::cout << prefix << (isTail ? "└──" : "├──") << root->value_ << std::endl;

        std::string newPrefix = prefix + (isTail ? "    " : "│   ");

        dump(root->right_, newPrefix, !root->left_);
        dump(root->left_, newPrefix, true);
    }

    friend bool inorderEqual(Node_ptr lhs, Node_ptr rhs) noexcept
    {
        if (!lhs && !rhs) return true;
        if (!lhs || !rhs) return false;

        if (lhs->value_ != rhs->value_) return false;

        return inorderEqual(lhs->left_, rhs->left_) && inorderEqual(lhs->right_, rhs->right_);
    }

    Node_ptr root_;
    Node_ptr temp_root_;
    Node_ptr active_root_;
    size_t size_{};
    size_t undo_cnt_{};
};

template<template <typename> typename Cont, typename T>
PersistentBST(const Cont<T>&) -> PersistentBST<T>;



} // namespace my_impl

#endif //PERSISTENT_BST_H
