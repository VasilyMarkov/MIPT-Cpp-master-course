%option c++

%option noyywrap

%{

#include <iostream>
#include "lexer.hpp"

static my_impl::Ram ram;
auto parser = ram.parser();

%}

WS              [ \t\n\v]+
DIGIT           [0-9]
DIGIT1          [1-9]
ID              [a-zA-Z_][a-zA-Z0-9_]*
INPUT           "input"
OUTPUT          "print"
%%

{WS}              /* skip blanks and tabs */
"+"               parser->pushToken(my_impl::token_type::ADD);
"-"               parser->pushToken(my_impl::token_type::SUB);
"["               parser->pushToken(my_impl::token_type::OBRAC);
"]"               parser->pushToken(my_impl::token_type::CBRAC);
"="               parser->pushToken(my_impl::token_type::ASSIGN);
";"               parser->pushToken(my_impl::token_type::SCOLON);

{INPUT}           parser->pushToken(my_impl::token_type::INPUT);
{OUTPUT}          parser->pushToken(my_impl::token_type::OUTPUT);
{DIGIT1}{DIGIT}*  parser->pushValue(yytext);         
{ID}              parser->pushId(yytext);         
.			      

%%

int main() {
    while (ram.lexer()->yylex() != 0) {}

    std::cout << *parser << std::endl;

    parser->parse();

}