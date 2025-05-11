%{
#include "parser.tab.h"
#include <cstdlib>
#include <cstring>
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
"x"                 { return X; }
"y"                 { return Y; }
"x1"                { return X1; }
"y1"                { return Y1; }
"x2"                { return X2; }
"y2"                { return Y2; }
"raio"              { return RAIO; }
"largura"           { return LARGURA; }
"altura"            { return ALTURA; }
"=="                { return IGUAL; }
"!="                { return DIFERENTE; }
">="                { return MAIORIGUAL; }
"<="                { return MENORIGUAL; }
">"                 { return MAIOR; }
"<"                 { return MENOR; }
"="                 { return ATRIB; }
"+="                { return MAISIGUAL; }
"-="                { return MENOSIGUAL; }
"+"                 { return MAIS; }
"-"                 { return MENOS; }
"*"                 { return VEZES_OP; }
"/"                 { return DIV; }

\"([^\\\"]|\\.)*\"  {
    yylval.str = strdup(yytext + 1);  // remove aspas
    yylval.str[strlen(yylval.str) - 1] = '\0';
    return STRING;
}

{identifier} {
    yylval.str = strdup(yytext);
    return ID;
}

{digit}+(\.{digit}+)? {
    yylval.fval = atof(yytext);
    return NUM;
}

"{"                 { return ABRECHAVE; }
"}"                 { return FECHACHAVE; }
"("                 { return ABREPAR; }
")"                 { return FECHAPAR; }

[ \t\r\n]+          { /* ignora espaços e quebras de linha */ }

.                   { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
