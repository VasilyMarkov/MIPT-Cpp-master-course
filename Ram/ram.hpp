#ifndef RAM_H
#define RAM_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <numeric>
#include "token.hpp"

namespace my_impl {

template <typename T, typename U>
inline void print(const std::unordered_map<T, U>& map) {
    for(auto&& [key, value] : map) {
        std::cout << "key: " << key 
        << " with value :" << value <<  ' ';
    }
}

inline std::unordered_map<std::string, int> var_store_;
inline std::vector<int> global_memory_;

class RamParser final {
public:
    RamParser()
    {
        global_memory_.resize(1000);
        std::iota(std::begin(global_memory_), std::end(global_memory_), 0);
    }

    void pushToken(std::unique_ptr<iToken> token) 
    {
        tokens_.emplace_back(std::move(token));
    }

    void parse() {
        // for(auto&& token : tokens_) {
        //     std::cout << token->toString() << std::endl;
        // }
        c_it_ = std::cbegin(tokens_);
        statement();
    }

    friend std::ostream& operator<<(std::ostream& os, const RamParser& parser) 
    {
        for(auto&& token : parser.tokens_) {
            os << token->toString() << ' ';
        }
        return os;
    }
private:
    using tokens_t =  std::vector<std::unique_ptr<iToken>>;
    using tokens_cit = tokens_t::const_iterator;
    tokens_t tokens_;
    tokens_cit c_it_;

    bool tokenEq(tokens_cit c_it, token_type rhs) const
        {return (*c_it)->type() == rhs;};

    bool tokenNotEq(tokens_cit c_it, token_type rhs) const
        {return (*c_it)->type() != rhs;};

    void nextToken() {++c_it_;};

    int statement() {

        if(c_it_ == std::cend(tokens_)) return 0;

        switch ((*c_it_)->type())
        {
        case token_type::INPUT:
            input();
            break;
        case token_type::OUTPUT:
            output();
            break;
        case token_type::ID:
            assign();
            break;
        default:
            break;
        }
        return 1;
    }

    int input() {
        nextToken();
        if(tokenEq(c_it_, token_type::ID)) {

            auto id = static_cast<IdToken&>(**c_it_).id();

            if(tokenEq(c_it_, token_type::SCOLON)) {
                int tmp = 0;
                std::cout << "input: " << std::endl;
                std::cin >> tmp;
                var_store_.emplace(id, tmp);
            }
        }
        nextToken();
        return statement();
    }

    int output() {
        nextToken();
        if(tokenEq(c_it_, token_type::ID)) {

            auto var = var_store_.at(static_cast<IdToken&>(**c_it_).id());

            nextToken();
            
            if(tokenEq(c_it_, token_type::SCOLON)) {
                std::cout << var << std::endl;
            }
        }
        nextToken();
        return statement();
    }

    int assign() {
        auto id = static_cast<IdToken&>(**c_it_).id();
        nextToken();

        if(tokenEq(c_it_, token_type::ASSIGN)) {
            if(var_store_.find(id) != std::end(var_store_)) {
                nextToken();
                var_store_.at(id) = expr();
            }
            else {
                nextToken();
                var_store_.emplace(id, expr());
            }
        }
        return statement();
    }

    int expr() {
        auto res = factor();
        while(tokenNotEq(c_it_, token_type::SCOLON))
        {
            switch ((*c_it_)->type())
            {
            case token_type::ADD:
                nextToken();
                res += factor();
                break;
            case token_type::SUB:
                nextToken();
                res -= factor();
                break;
            default:
                break;
            }
        }
        nextToken();

        return res;
    }

    int factor() {
        auto res = 0;
        switch ((*c_it_)->type())
        {
        case token_type::VALUE:
            res = static_cast<ValueToken&>(**c_it_).value();
            break;
        case token_type::ID:
            res = var_store_.at(static_cast<IdToken&>(**c_it_).id());
            break;
        default:
            break;
        }
        nextToken();
        return res;
    }

};

inline std::unique_ptr<iToken> newAdd()                     {return std::make_unique<AddToken>();}
inline std::unique_ptr<iToken> newSub()                     {return std::make_unique<SubToken>();}
inline std::unique_ptr<iToken> newOBracket()                {return std::make_unique<ObracketToken>();}
inline std::unique_ptr<iToken> newCBracket()                {return std::make_unique<CbracketToken>();}
inline std::unique_ptr<iToken> newAssign()                  {return std::make_unique<AssignToken>();}
inline std::unique_ptr<iToken> newScolon()                  {return std::make_unique<ScolonToken>();}
inline std::unique_ptr<iToken> newInput()                   {return std::make_unique<InputToken>();}
inline std::unique_ptr<iToken> newOutput()                  {return std::make_unique<OutputToken>();}
inline std::unique_ptr<iToken> newVal(const char* value)    {return std::make_unique<ValueToken>(value);}
inline std::unique_ptr<iToken> newId(const char* id)        {return std::make_unique<IdToken>(id);}



} //namespace my_impl

#endif //RAM_H
