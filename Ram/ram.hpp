#ifndef RAM_H
#define RAM_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

namespace my_impl {

enum class token_type {
    ADD,
    SUB,
    NUM,
    OBRAC,
    CBRAC,
    ASSIGN,
    INPUT,
    OUTPUT,
    SCOLON
};

class iToken {
protected:
public:
    iToken() = default;
    virtual ~iToken() = default;
    virtual std::string toString() const = 0;
};

class AddToken: public iToken {
public:
    AddToken(): iToken() {}
    std::string toString() const override {
        return "+";
    }
};

class SubToken: public iToken {
public:
    SubToken(): iToken() {}
    std::string toString() const override {
        return "-";
    }
};

class ValueToken: public iToken {
public:
    explicit ValueToken(int value) noexcept:iToken(), value_(value) {}
    std::string toString() const override {
        return std::to_string(value_);
    }
private:
    int value_;
};

class IdToken: public iToken {
public:
    IdToken(std::string id): iToken(), id_(id) {}
    std::string toString() const override {
        return id_;
    }
private:
    std::string id_;
};


class RamParser final {
public:
    RamParser(){}

    void pushToken(token_type token) 
    {
        switch (token)
        {
        case token_type::ADD:
            tokens_.emplace_back(std::make_unique<AddToken>());
            break;
        case token_type::SUB:
            tokens_.emplace_back(std::make_unique<SubToken>());
            break;
        case token_type::OBRAC:
            
            break;
        case token_type::CBRAC:
            
            break;
        case token_type::ASSIGN:
            
            break;
        case token_type::SCOLON:
            
            break;
        case token_type::INPUT:
            
            break;
        case token_type::OUTPUT:
            
            break;
        default:
            break;
        }
    }

    void pushValue(const char* value) 
    {
        tokens_.emplace_back(std::make_unique<ValueToken>(std::stoi(std::string(value))));
    }

    void pushId(const char* id) 
    {
        tokens_.emplace_back(std::make_unique<IdToken>(id));
    }

    void parse() {
        parseToken(**std::begin(tokens_));
    }

    friend std::ostream& operator<<(std::ostream& os, const RamParser& parser) 
    {
        // std::cout << "parser" << std::endl;
        for(auto&& token : parser.tokens_) {
            os << token->toString() << ' ';
        }
        return os;
    }
private:
    void parseToken(const iToken& token) {

    }
    std::vector<std::unique_ptr<iToken>> tokens_;
};





} //namespace my_impl

#endif //RAM_H