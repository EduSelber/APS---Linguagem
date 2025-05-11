%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *msg);
int yylex();

FILE *svg_file;
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
    {
        svg_file = fopen("saida.svg", "w");
        fprintf(svg_file, "<svg xmlns='http://www.w3.org/2000/svg' width='800' height='600'>\n");
    }
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
    {
        fprintf(svg_file, "<circle cx='%lf' cy='%lf' r='%lf' stroke='black' fill='none'/>\n", $3, $5, $7);
    }
    | RETANGULO X expr Y expr LARGURA expr ALTURA expr
    {
        fprintf(svg_file, "<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='black' fill='none'/>\n", $3, $5, $7, $9);
    }
    | LINHA X1 expr Y1 expr X2 expr Y2 expr
    {
        fprintf(svg_file, "<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' stroke='black'/>\n", $3, $5, $7, $9);
    }
;

color:
    COR expr
    {
        // Aqui poderia modificar uma variável global `current_color` (não implementado ainda)
    }
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
    expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr     { $$ = $1 - $3; }
    | expr '*' expr     { $$ = $1 * $3; }
    | expr '/' expr     { $$ = $1 / $3; }
    | NUMBER            { $$ = $1; }
    | STRING            { $$ = 0; /* Ignora string nas expressões por enquanto */ }
    | IDENTIFIER        { $$ = 0; /* Variáveis ainda não implementadas */ }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro de sintaxe: %s\n", msg);
    if (svg_file) fclose(svg_file);
}

int main() {
    yyparse();
    if (svg_file) {
        fprintf(svg_file, "</svg>\n");
        fclose(svg_file);
    }
    return 0;
}
