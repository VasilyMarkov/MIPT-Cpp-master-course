%option c++

%option noyywrap

%{

#include <iostream>
#include "lexer.hpp"

static my_impl::Ram ram(1000);
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
"+"               parser->pushToken(my_impl::newAdd());
"-"               parser->pushToken(my_impl::newSub());
"["               parser->pushToken(my_impl::newOBracket());
"]"               parser->pushToken(my_impl::newCBracket());
"="               parser->pushToken(my_impl::newAssign());
";"               parser->pushToken(my_impl::newScolon());

{INPUT}           parser->pushToken(my_impl::newInput());
{OUTPUT}          parser->pushToken(my_impl::newOutput());
{DIGIT1}{DIGIT}*  parser->pushToken(my_impl::newVal(yytext));       
{ID}              parser->pushToken(my_impl::newId(yytext));         

.			      

%%

int main() {
    int tmp = 0;
    std::cin >> tmp;
    while (ram.lexer()->yylex() != 0) {}

    parser->parse();

}