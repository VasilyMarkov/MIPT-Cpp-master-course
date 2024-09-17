#ifndef STRING_TWINE_H
#define STRING_TWINE_H
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>


namespace my_impl {

class StringTwine final 
{
public:
    StringTwine(): root(std::make_unique<Node>("")) {}
    explicit StringTwine(std::string_view sv): root(std::make_unique<Node>(sv)) {}

    void concat(std::string_view sv) {
        root = std::make_unique<Node>(std::move(root), std::make_unique<Node>(sv));
    }

    std::string to_string() const {
        return root->to_string();
    }
private:
    struct Node {
        std::string_view sv;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(std::string_view sv) : sv(sv), left(nullptr), right(nullptr) {}
        Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : sv(""), left(std::move(left)), right(std::move(right)) {}

        std::string to_string() const {
            if (left && right) {
                return left->to_string() + right->to_string();
            }
            return std::string(sv);
        }
    };
private:
    std::unique_ptr<Node> root;
};

} //namespace my_impl

#endif //STRING_TWINE_H