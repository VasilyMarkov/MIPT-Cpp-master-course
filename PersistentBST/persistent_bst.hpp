#ifndef PERSISTENT_BST_H
#define PERSISTENT_BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

namespace my_impl
{

template <std::totally_ordered T>
class PersistentBST {
public:
    class Node;
    using Node_ptr = std::shared_ptr<Node>;

    class Node {
    public:
        Node(T value) noexcept: value_(value) {}
        Node(T value, Node_ptr left, Node_ptr right):
            value_(value), 
            left_(left),
            right_(right) {}
        T value_;
        Node_ptr left_;
        Node_ptr right_;
    };

    PersistentBST(){}

    void insert(T value) {
        if(empty()) 
            head_ = std::make_shared<Node>(value);
        else 
            insertRecursive(head_, value);
    }

    void print() {
        inorder(head_);
        std::cout << std::endl;
    }

    std::vector<T> flatten() {
        std::vector<T> result;
        inorder(head_, result);
        return result;
    }

    bool empty() const noexcept {
        return head_ == nullptr;
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

    void inorder(Node_ptr root, std::vector<T>& vec) {
        if (root == nullptr) return;
        inorder(root->left_, vec);
        vec.push_back(root->value_);
        inorder(root->right_, vec);
    } 
    
    void inorder(Node_ptr root) {
        if (root == nullptr) return;
        inorder(root->left_);
        std::cout << root->value_ << ' ';
        inorder(root->right_);
    } 

    Node_ptr head_;
};

} // namespace my_impl

#endif //PERSISTENT_BST_H
