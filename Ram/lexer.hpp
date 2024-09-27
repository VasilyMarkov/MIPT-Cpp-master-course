#ifndef LEXER_H
#define LEXER_H
#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif
#include "ram.hpp"

namespace yy {

class RamLexer : public yyFlexLexer {
public:
    RamLexer(): yyFlexLexer() {}

    int yylex() override {
        int token = yyFlexLexer::yylex();
        return token;
    };
};

} //namespace yy


namespace my_impl {

class Ram final {
public:
    Ram():lexer_(std::make_unique<yy::RamLexer>()), parser_(std::make_unique<RamParser>()){}

    std::unique_ptr<yy::RamLexer> lexer() noexcept {return std::move(lexer_);}

    std::unique_ptr<RamParser> parser() noexcept {return std::move(parser_);}
private:
    std::unique_ptr<yy::RamLexer> lexer_;
    std::unique_ptr<RamParser> parser_;
};

}

#endif //LEXER_H