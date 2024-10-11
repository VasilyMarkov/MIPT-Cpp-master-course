#ifndef RAM_H
#define RAM_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <numeric>
#include <exception>
#include <sstream>
#include "token.hpp"

namespace my_impl {

class ram_error final: std::exception 
{
public:
    ram_error(const std::string& what_arg):what_(what_arg) {}

    const char* what() const noexcept override {
        return what_.c_str();
    }

private:
    std::string what_;
};

enum class varType {
    X,
    C,
    OTHER
};

constexpr size_t MEM_SIZE = 1000;

inline std::unordered_map<std::string, int> var_store_;
inline std::vector<int> global_memory_(MEM_SIZE);

class RamParser final 
{
public:
    RamParser():out_stream_(std::make_unique<std::stringstream>())
    {
        std::iota(std::begin(global_memory_), std::end(global_memory_), 0);
    }

    void pushToken(std::unique_ptr<iToken> token) 
    {
        tokens_.emplace_back(std::move(token));
    }

    void parse() 
    {
        iter = std::cbegin(tokens_);

        try {
            statement();
        }
        catch(const ram_error& ram_excep) {
            *out_stream_ << ram_excep.what() << std::endl;
        }
        catch(const std::exception& excep) {
            throw;
        }  
    }
    
    std::unique_ptr<std::stringstream> getStream() noexcept 
    {
        return std::move(out_stream_);
    }

    friend std::ostream& operator<<(std::ostream& os, const RamParser& parser) 
    {
        for(auto&& token : parser.tokens_) {
            os << token->toString() << ' ';
        }
        return os;
    }
private:
    std::unique_ptr<std::stringstream> out_stream_;
    using tokens_t =  std::vector<std::unique_ptr<iToken>>;
    using tokens_cit = tokens_t::const_iterator;
    tokens_t tokens_;
    tokens_cit iter;

    void nextToken() noexcept {++iter;};

    int statement() 
    {
        if(iter == std::cend(tokens_)) return 0;
        //input expr;
        else if(**iter == token_type::INPUT)
        {
            input();
        }
        //print expr;
        else if(**iter == token_type::OUTPUT)
        {
            output();
        }
        //var = expr;
        else if(**iter == token_type::ID)
        {
            varAssign(varType::OTHER);
        }
        // [ = expr;
        else if(**iter == token_type::OBRAC &&
                **std::next(iter) == token_type::ASSIGN)
        {
            varAssign(varType::C);
        }
        // ][ = expr;
        else if(**iter == token_type::CBRAC &&
                **std::next(iter) == token_type::OBRAC &&
                **std::next(iter, 2) == token_type::ASSIGN)
        {
            nextToken();
            varAssign(varType::X);
        }
        // expr = expr
        else 
        {
            exprAssign();
        }
        if(**iter == token_type::SCOLON) 
        {
            nextToken();
            return statement();
        }
        else
            throw ram_error("Syntax error: expected ;");
    }

    int input() 
    {
        nextToken();
        
        int input = 0;
        std::cin >> input;
        if(**iter == token_type::ID) {
            auto id = static_cast<IdToken&>(**iter).id();
            var_store_.emplace(id, input);
        }
        else 
        {
            auto res = expr();
            global_memory_[res] = input;
        }
        return 0;
    }

    int output() 
    {
        nextToken();
        *out_stream_ << expr() << std::endl;
        return 0;
    }

    void exprAssign() {
        auto lhs = expr();

        if (lhs < 0 || lhs > global_memory_.size()) throw ram_error("Out of memory");

        if(**iter == token_type::ASSIGN) {
            nextToken();
            auto rhs = expr();
            if(lhs)
            global_memory_[lhs] = rhs;
        }
    }

    void varAssign(varType var_type) {
        switch (var_type)
        {
        case varType::X:
            assign("x");
            break;
        case varType::C:
            assign("c");
            break;
        case varType::OTHER:
            assign(static_cast<IdToken&>(**iter).id());
            break;
        default:
            break;
        }
    }

    int assign(std::string id) 
    {
        nextToken();

        if(**iter == token_type::ASSIGN) {
            if(var_store_.find(id) != std::end(var_store_)) {
                nextToken();

                int res = expr();
                if(res < 0) throw ram_error("Out of memory");
                
                var_store_.at(id) = global_memory_.at(res);
            }
            else {
                nextToken();

                int res = expr();
                if(res < 0) throw ram_error("Out of memory");
                var_store_.emplace(id, global_memory_.at(res));
            }
        }
        return 0;
    }

    int expr() 
    {
        int res{};
        int tmp = factor();
        while(**iter == token_type::ADD ||
              **iter == token_type::SUB)
        {
            switch ((*iter)->type())
            {
            case token_type::ADD:
                nextToken();
                tmp += expr();
                break;
            case token_type::SUB:
                nextToken();
                tmp -= expr();
                break;
            default:
                break;
            }
        }
        res = tmp;

        return res;
    }

    int factor() 
    {
        auto res = 0;

        if(**iter == token_type::ID)
        {
            auto id = static_cast<IdToken&>(**iter).id();
            nextToken();
            if(**iter == token_type::OBRAC) {
                return var_store_.at(id) + expr();
            }
            return var_store_.at(id);
        }
        else if(**iter == token_type::OBRAC) {
            nextToken();
            if(**iter == token_type::ADD || **iter == token_type::SUB) {
                return var_store_.at("c");
            }
            if(**iter == token_type::CBRAC && **std::next(iter) != token_type::CBRAC) {
                return var_store_.at("c");
            }
            int res = expr();
            if(**iter == token_type::CBRAC) {
                nextToken();
                return res;
            }
        }
        else if(**iter == token_type::VALUE) {
            res = static_cast<ValueToken&>(**iter).value();
        }
        else if(**iter == token_type::ID) {
            res = var_store_.at(static_cast<IdToken&>(**iter).id());
        }
        else
            throw ram_error("Syntax error");

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
