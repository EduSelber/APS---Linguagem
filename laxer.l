%{
#include "parser.tab.h"
#include <string.h>
%}

digit      [0-9]
letter     [a-zA-Z]
identifier {letter}({letter}|{digit}|_)*

%%

"circulo"           { return CIRCULO; }
"retangulo"         { return RETANGULO; }
"linha"             { return LINHA; }
"cor"               { return COR; }
"grupo"             { return GRUPO; }
"mover"             { return MOVER; }
"se"                { return SE; }
"repetir"           { return REPETIR; }
"vezes"             { return VEZES; }

"x"                { return X; }
"y"                { return Y; }
"x1"               { return X1; }
"y1"               { return Y1; }
"x2"               { return X2; }
"y2"               { return Y2; }
"raio"             { return RAIO; }
"largura"          { return LARGURA; }
"altura"           { return ALTURA; }

"=="               { return EQ; }
">="               { return GE; }
"<="               { return LE; }
"!="               { return NE; }
">"                { return GT; }
"<"                { return LT; }

"="                { return ASSIGN; }
"+="               { return PLUS_ASSIGN; }
"-="               { return MINUS_ASSIGN; }

\"[^"]*\"          { yylval.str = strdup(yytext); return STRING; }
{identifier}       { yylval.str = strdup(yytext); return IDENTIFIER; }
{digit}+(\.{digit}+)?  { yylval.num = atof(yytext); return NUMBER; }

"{"                { return LBRACE; }
"}"                { return RBRACE; }
"("                { return LPAREN; }
")"                { return RPAREN; }

[ \t\r\n]+         ; // Ignora espaços

.                  { return *yytext; }

%%
