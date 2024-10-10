#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>


namespace my_impl
{

enum class token_type {
    ADD = 1,
    SUB,
    VALUE,
    OBRAC,
    CBRAC,
    ASSIGN,
    INPUT,
    OUTPUT,
    SCOLON,
    ID
};

class iToken {
public:
    virtual token_type type() const noexcept = 0;
    virtual ~iToken() = default;
    virtual std::string toString() const = 0;
    bool operator==(token_type token_type) const noexcept {
        return type() == token_type;
    }
    bool operator!=(token_type token_type) const noexcept {
        return type() != token_type;
    }
};

class AddToken: public iToken {
public:
    AddToken() {}

    token_type type() const noexcept override 
    {return token_type::ADD;}

    std::string toString() const override {
        return "+";
    }
};

class SubToken: public iToken {
public:
    SubToken() {}

    token_type type() const noexcept override 
    {return token_type::SUB;}

    std::string toString() const override {
        return "-";
    }
};

class ObracketToken: public iToken {
public:
    ObracketToken() {}

    token_type type() const noexcept override 
    {return token_type::OBRAC;}

    std::string toString() const override {
        return "[";
    }
};

class CbracketToken: public iToken {
public:
    CbracketToken() {}

    token_type type() const noexcept override 
    {return token_type::CBRAC;}

    std::string toString() const override {
        return "]";
    }
};

class AssignToken: public iToken {
public:
    AssignToken() {}

    token_type type() const noexcept override 
    {return token_type::ASSIGN;}

    std::string toString() const override {
        return "=";
    }
};

class ValueToken: public iToken {
public:
    explicit ValueToken(const char* value) noexcept:
        value_(std::stoi(std::string(value))) {}

    int value() const noexcept {return value_;}

    token_type type() const noexcept override 
    {return token_type::VALUE;}

    std::string toString() const override {
        return std::to_string(value_);
    }
private:
    int value_;
};

class IdToken: public iToken {
public:
    IdToken(std::string id):id_(id) {}

    token_type type() const noexcept override 
    {return token_type::ID;}

    std::string id() const noexcept {return id_;}

    std::string toString() const override {
        return id_;
    }
private:
    std::string id_;
};

class InputToken: public iToken {
public:
    InputToken() {}

    token_type type() const noexcept override 
    {return token_type::INPUT;}

    std::string toString() const override {
        return "input";
    }
};

class OutputToken: public iToken {
public:
    OutputToken() {}

    token_type type() const noexcept override 
    {return token_type::OUTPUT;}

    std::string toString() const override {
        return "print";
    }
};

class ScolonToken: public iToken {
public:
    ScolonToken() {}

    token_type type() const noexcept override 
    {return token_type::SCOLON;}

    std::string toString() const override {
        return ";";
    }
};

} // namespace my_impl

#endif //TOKEN_H