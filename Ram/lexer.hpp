#ifndef LEXER_H
#define LEXER_H
#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif
#include <fstream>
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
    Ram(size_t size):lexer_(std::make_unique<yy::RamLexer>()), parser_(std::make_unique<RamParser>(size)){}

    std::unique_ptr<yy::RamLexer> lexer() noexcept {return std::move(lexer_);}
    std::unique_ptr<RamParser> parser() noexcept {return std::move(parser_);}

    void setStream(std::ifstream& file) {
        lexer_->switch_streams(file, std::cout);
    }
private:
    std::unique_ptr<yy::RamLexer> lexer_;
    std::unique_ptr<RamParser> parser_;
};

} //namespace my_impl

#endif //LEXER_H