%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *msg);
int yylex();

%}

%union {
    double num;
    char* str;
}

%token <num> NUMBER
%token <str> STRING IDENTIFIER
%token CIRCULO RETANGULO LINHA COR GRUPO MOVER SE REPETIR VEZES
%token X Y X1 Y1 X2 Y2 RAIO LARGURA ALTURA
%token EQ GE LE NE GT LT
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN
%token LBRACE RBRACE LPAREN RPAREN

%left '+' '-'
%left '*' '/'

%%

program:
    /* vazio */
    | program statement
;

statement:
    shape
    | color
    | group
    | conditional
    | loop
    | assignment
;

shape:
    CIRCULO X expr Y expr RAIO expr
    | RETANGULO X expr Y expr LARGURA expr ALTURA expr
    | LINHA X1 expr Y1 expr X2 expr Y2 expr
;

color:
    COR expr
;

group:
    GRUPO LBRACE program RBRACE transform_opt
;

transform_opt:
    /* vazio */
    | MOVER X expr Y expr
;

conditional:
    SE condition LBRACE program RBRACE
;

loop:
    REPETIR expr VEZES LBRACE program RBRACE
;

assignment:
    IDENTIFIER ASSIGN expr
    | IDENTIFIER PLUS_ASSIGN expr
    | IDENTIFIER MINUS_ASSIGN expr
;

condition:
    expr comparator expr
;

comparator:
    EQ | GE | LE | NE | GT | LT
;

expr:
    expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | NUMBER
    | STRING
    | IDENTIFIER
    | LPAREN expr RPAREN
;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro de sintaxe: %s\n", msg);
}
