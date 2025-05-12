%{
#include "ast.h"
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
%}

digit       [0-9]
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit}|_)*
number      {digit}+(\.{digit}+)?([eE][+-]?{digit}+)?
whitespace  [ \t]+
newline     \n

%%

"circulo"         { return CIRCULO; }
"retangulo"       { return RETANGULO; }
"linha"           { return LINHA; }
"cor"             { return COR; }
"grupo"           { return GRUPO; }
"mover"           { return MOVER; }
"se"              { return SE; }
"repetir"         { return REPETIR; }
"vezes"           { return VEZES; }
"x"               { return X; }
"y"               { return Y; }
"raio"            { return RAIO; }
"largura"         { return LARGURA; }
"altura"          { return ALTURA; }
"="               { return ASSIGN; }
"+="              { return ADD_ASSIGN; }
"-="              { return SUB_ASSIGN; }
"=="              { return EQ; }
"<"               { return LT; }
">"               { return GT; }
"<="              { return LE; }
">="              { return GE; }
"!="              { return NE; }
"+"               { return '+'; }
"-"               { return '-'; }
"*"               { return '*'; }
"/"               { return '/'; }
"("               { return '('; }
")"               { return ')'; }
"{"               { return '{'; }
"}"               { return '}'; }
";"               { return ';'; }

{identifier}      { yylval.str = strdup(yytext); return IDENTIFIER; }
{number}          { yylval.num = atof(yytext); return NUMBER; }
\"[^\"]*\"        { 
                    char *s = yytext;
                    s[strlen(s)-1] = '\0';
                    yylval.str = strdup(s+1); 
                    return STRING; 
                  }
{whitespace}      { /* Ignore whitespace */ }
{newline}         { /* Return newline as statement separator */ }
.                 { yyerror("Invalid character"); }

%%

int yywrap(void) {
    return 1;
}