
%option noyywrap 
%option never-interactive

%{
 #include <string.h>
 #include <iostream>
 #include "syntaxer.hpp"
%}

DIGIT [0-9]
LETTER [a-zA-Z_]
OPERATOR_ARITHMETIC [+-//*%]

%%

{DIGIT}+        {
    strcpy_s(yylval.buffer, 128, yytext);
    // std::cout << "\nGot " << yylval.buffer;
    return NUMBER_LITERAL;   
}

<<EOF>>          {
    return END_OF_FILE;
}

 /*
 [#]             {
     return END_OF_FILE;
 }
 */
(#(.*))\n ;

{LETTER}+({DIGIT}|{LETTER})*   {
	strcpy_s(yylval.buffer, 128, yytext);
    // std::cout << "\nGot " << yylval.buffer;
    return IDENTIFIER;   
}

"\"".*"\""   {
    strcpy_s(yylval.buffer, 128, yytext);
    // std::cout << "\nGot " << yylval.buffer;
    return STRING_LITERAL;   
}

[';"{}()\[\]]   {
    strcpy_s(yylval.buffer, 128, yytext);
    // std::cout << "\nGot " << yylval.buffer;
    return yytext[0];
}

"=" {
    return yytext[0];
}

{OPERATOR_ARITHMETIC} return yytext[0]; 

.|\n                          ; /* ignore all the rest */

%%
