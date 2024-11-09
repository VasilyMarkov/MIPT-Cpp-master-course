%option c++

%option noyywrap

%{

#include <iostream>
#include "ram.hpp"
#include "token.hpp"
%}

WS              [ \t\n\v]+
DIGIT           [0-9]
DIGIT1          [1-9]
ID              [a-zA-Z_][a-zA-Z0-9_]*
INPUT           "input"
OUTPUT          "print"
%%

{WS}              /* skip blanks and tabs */
"+"               return static_cast<int>(my_impl::token_type::ADD);
"-"               return static_cast<int>(my_impl::token_type::SUB);
"["               return static_cast<int>(my_impl::token_type::OBRAC);
"]"               return static_cast<int>(my_impl::token_type::CBRAC);
"="               return static_cast<int>(my_impl::token_type::ASSIGN);
";"               return static_cast<int>(my_impl::token_type::SCOLON);

{INPUT}           return static_cast<int>(my_impl::token_type::INPUT);
{OUTPUT}          return static_cast<int>(my_impl::token_type::OUTPUT);
{DIGIT1}{DIGIT}*  return static_cast<int>(my_impl::token_type::VALUE);   
{DIGIT}          return static_cast<int>(my_impl::token_type::VALUE);   
{ID}              return static_cast<int>(my_impl::token_type::ID);
.			      

%%

