#ifndef LEXER_H
#define LEXER_H
#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif
#include <fstream>
#include "ram.hpp"

namespace yy {

class RamLexer final : public yyFlexLexer {
public:
    RamLexer(): 
        yyFlexLexer() {}

    int yylex() override {
        int token = yyFlexLexer::yylex();
        return token;
    };
};
} //namespace yy

namespace my_impl
{

class Driver final {
public:
    explicit Driver(std::stringstream& file):
        lexer_(std::make_unique<yy::RamLexer>()), 
        parser_(std::make_unique<RamParser>()) 
    {
        lexer_->switch_streams(file, std::cout);
    }

    int yylex() {
        auto tt = static_cast<token_type>(lexer_->yylex());

        switch (tt)
        {
        case token_type::ADD:
            parser_->pushToken(newAdd());
            break;
        case token_type::SUB:
            parser_->pushToken(newSub());
            break;
        case token_type::OBRAC:
            parser_->pushToken(newOBracket());
            break;
        case token_type::CBRAC:
            parser_->pushToken(newCBracket());
            break;
        case token_type::ASSIGN:
            parser_->pushToken(newAssign());
            break;
        case token_type::VALUE:
            parser_->pushToken(newVal(lexer_->YYText()));
            break;
        case token_type::ID:
            parser_->pushToken(newId(lexer_->YYText()));
            break;
        case token_type::INPUT:
            parser_->pushToken(newInput());
            break;
        case token_type::OUTPUT:
            parser_->pushToken(newOutput());
            break;
        case token_type::SCOLON:
            parser_->pushToken(newScolon());
            break;
        
        default:
            break;
        }
        return static_cast<int>(tt);
    }

    void parse() {
        while (yylex() != 0) {}
        parser_->parse();
    }
    std::string output() {
        return (*parser_->getStream()).str(); 
    }
private:
    std::unique_ptr<yy::RamLexer> lexer_;
    std::unique_ptr<RamParser> parser_;
};
 
} // namespace my_impl




#endif //LEXER_H