#ifndef PERSISTENT_BST_H
#define PERSISTENT_BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>
#include <utility>
#include <iomanip>
#include <algorithm>
#include "utility.hpp"
#include "radix_sort.hpp"

namespace my_impl
{

template <std::totally_ordered T>
class PersistentBST final 
{
    class Node;
    using Node_ptr = std::shared_ptr<Node>;

    class Node final 
    {
    public:
        explicit Node(T value) noexcept: value_(value) {}
        
        Node(T value, Node_ptr left, Node_ptr right) noexcept:
            value_(value), 
            left_(left), 
            right_(right) {}
        
        void swap(Node& other) noexcept 
        {
            std::swap(value_, other);
            std::swap(left_, other.left_);
            
        }
    private:
        T value_;
        Node_ptr left_;
        Node_ptr right_;

        friend class PersistentBST;
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

    Node_ptr search(const T& value) noexcept
    {
        return searchRecursive(root_, value);
    }

    void remove(const T& value) 
    {
        if(!empty()) {
            temp_root_ = removeRecursive(root_, value);
            std::swap(temp_root_, root_);
            active_root_ = root_;
            --size_;
        }
    }

    void undo() noexcept
    {
        if(size_ > 1 && !undo_cnt_) 
        {   
            active_root_ = temp_root_;
            ++undo_cnt_;
        } 
    }

    void redo() noexcept { active_root_ = root_; --undo_cnt_;}

    void print() 
    {
        dump(active_root_);
        std::cout << "-----" << std::endl;
    }

    std::vector<T> flatten() 
    {
        std::vector<T> result;
        traversalFlat(active_root_, result);
        return result;
    }

    bool empty() const noexcept { return size_ == 0; }

    bool operator==(const PersistentBST& rhs) const noexcept 
    {
        return inorderEqual(active_root_, rhs.active_root_);
    }
    
private:
    Node_ptr insertRecursive(Node_ptr node, const T& value) 
    {
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

    Node_ptr searchRecursive(Node_ptr node, const T& value) 
    {
        if(!node || value == node->value_) return node;

        if(value < node->value_) 
        {
            return searchRecursive(node->left_, value);
        }
        else 
        {
            return searchRecursive(node->right_, value);
        }
    }

    Node_ptr removeRecursive(Node_ptr node, const T& value) 
    {
        if (!node) {
            return nullptr;
        }

        if (value < node->value_) 
        {
            auto newLeft = removeRecursive(node->left_, value);
            return std::make_shared<Node>(node->value_, newLeft, node->right_);
        } 
        else if (value > node->value_) 
        {
            auto newRight = removeRecursive(node->right_, value);
            return std::make_shared<Node>(node->value_, node->left_, newRight);
        } 
        else {
            if (!node->left_) 
            {
                return node->right_;
            } 
            else if (!node->right_) 
            {
                return node->left_;
            } 
            else 
            {
                auto minNode = findMin(node->right_);
                return std::make_shared<Node>(minNode->value_, node->left_, removeRecursive(node->right_, minNode->value_));
            }
        }
    }

    Node_ptr findMin(Node_ptr node) const 
    {
        while (node->left_) {
            node = node->left_;
        }
        return node;
    }

    void traversalFlat(Node_ptr root, std::vector<T>& vec) 
    {
        if (!root) return;

        traversalFlat(root->left_, vec);
        vec.push_back(root->value_);
        traversalFlat(root->right_, vec);
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

    bool inorderEqual(Node_ptr lhs, Node_ptr rhs) const noexcept
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

template<>
class PersistentBST<int> 
{
    enum class lastOperation_t {INSERT, REMOVE};
public:
    PersistentBST() {}

    template <HasBeginEnd Cont>
    PersistentBST(const Cont& cont)
    {
        main_data_.reserve(cont.size());

        for(auto&& el:cont) 
        {
            insert(el);
        }
    }

    PersistentBST(const std::initializer_list<int>& list)
    {
        main_data_.reserve(list.size());

        for(auto&& el:list) 
        {
            insert(el);
        }
    }
    
    void insert(int value)
    {
        lastOperation = lastOperation_t::INSERT;

        insertValue(value);
    }

    void remove(int value) 
    {
        if(!main_data_.empty()) 
        {
            lastOperation = lastOperation_t::REMOVE;

            if(std::binary_search(std::begin(main_data_), std::end(main_data_), value)) 
            {
                current_value_ = value;
                removeValue(value);
                radixSort(std::begin(main_data_), std::end(main_data_));
            }
        }
    }

    std::vector<int>::const_iterator search(int value) const  
    {
        if(std::binary_search(std::begin(main_data_), std::end(main_data_), value)) 
        {
            return std::lower_bound(std::begin(main_data_), std::end(main_data_), value);
        }
    }

    void undo() 
    {
        if(!main_data_.empty() && !undo_cnt_) 
        { 
            if(lastOperation == lastOperation_t::INSERT) 
            {
                removeValue(current_value_);
            }
            else 
            {
                insertValue(current_value_);
            }
            ++undo_cnt_;
        }
    }

    void redo() 
    {
        if(lastOperation == lastOperation_t::INSERT) 
        {
            insertValue(current_value_);
        }
        else 
        {
            removeValue(current_value_);
        }
        --undo_cnt_;
    }

    std::vector<int> flatten() const { return main_data_; }

    void print() const {my_impl::print(main_data_);}

    bool operator==(const PersistentBST& rhs) const noexcept 
    {
        return main_data_ == rhs.main_data_;
    }

private:
    void insertValue(int value) 
    {
        if(main_data_.empty()) 
        {
            main_data_.push_back(value);
            current_value_ = value;
            return;
        }

        prev_value_ = current_value_;

        if(std::find(std::begin(main_data_), std::end(main_data_), value) == std::end(main_data_))
        {
            main_data_.push_back(value);
            radixSort(std::begin(main_data_), std::end(main_data_));
            current_value_ = value;
        }
    }
    void removeValue(int value) 
    {
        auto current_value_it = std::lower_bound(std::begin(main_data_), std::end(main_data_), value);
        std::swap(*current_value_it, main_data_.back());
        main_data_.pop_back();
    }

    std::vector<int> main_data_;
    int prev_value_{};
    int current_value_{};
    lastOperation_t lastOperation;
    size_t undo_cnt_{};
};

} // namespace my_impl

#endif //PERSISTENT_BST_H
