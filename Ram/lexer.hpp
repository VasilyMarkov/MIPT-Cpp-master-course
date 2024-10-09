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

#endif //LEXER_H