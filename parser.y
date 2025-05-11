%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void yyerror(const char *msg);
int yylex();

FILE *svg_file;
char current_color[64] = "black";

// Tabela de símbolos
struct Var {
    char name[64];
    enum { NUM, STR } type;
    union {
        double num;
        char str[128];
    } value;
};

struct Var vars[100];
int var_count = 0;

void executar_loop(int vezes, void (*bloco)(void)) {
    for (int i = 0; i < vezes; i++) {
        bloco();
    }
}

void temp_loop_block();

void (*loop_fn)(void) = NULL;

// Gerenciamento de variáveis

double get_var(char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0 && vars[i].type == NUM) {
            return vars[i].value.num;
        }
    }
    return 0;
}

void set_var_num(char* name, double value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].type = NUM;
            vars[i].value.num = value;
            return;
        }
    }
    strcpy(vars[var_count].name, name);
    vars[var_count].type = NUM;
    vars[var_count++].value.num = value;
}

void set_var_str(char* name, char* value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].type = STR;
            strcpy(vars[i].value.str, value);
            return;
        }
    }
    strcpy(vars[var_count].name, name);
    vars[var_count].type = STR;
    strcpy(vars[var_count++].value.str, value);
}
%}

%union {
    double num;
    char* str;
    int op;
}

%token <num> NUMBER
%token <str> STRING IDENTIFIER
%token CIRCULO RETANGULO LINHA COR GRUPO MOVER SE REPETIR VEZES
%token X Y X1 Y1 X2 Y2 RAIO LARGURA ALTURA
%token EQ GE LE NE GT LT
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN
%token LBRACE RBRACE LPAREN RPAREN

%type <num> expr condition
%type <op> comparator

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

statements:
    statement
    | statements statement
;

shape:
    CIRCULO X expr Y expr RAIO expr
    {
        fprintf(svg_file, "<circle cx='%.2lf' cy='%.2lf' r='%.2lf' stroke='%s' fill='none'/>", $3, $5, $7, current_color);
        fprintf(svg_file, "\n");
    }
    | RETANGULO X expr Y expr LARGURA expr ALTURA expr
    {
        fprintf(svg_file, "<rect x='%.2lf' y='%.2lf' width='%.2lf' height='%.2lf' stroke='%s' fill='none'/>", $3, $5, $7, $9, current_color);
        fprintf(svg_file, "\n");
    }
    | LINHA X1 expr Y1 expr X2 expr Y2 expr
    {
        fprintf(svg_file, "<line x1='%.2lf' y1='%.2lf' x2='%.2lf' y2='%.2lf' stroke='%s'/>", $3, $5, $7, $9, current_color);
        fprintf(svg_file, "\n");
    }
;

color:
    COR STRING
    {
        strncpy(current_color, $2, sizeof(current_color));
        free($2);
    }
;

group:
    GRUPO LBRACE statements RBRACE transform_opt
;

transform_opt:
    /* vazio */
    | MOVER X expr Y expr
    {
        fprintf(svg_file, "<g transform='translate(%.2lf,%.2lf)'>\n", $3, $5);
        fprintf(svg_file, "</g>\n");
    }
;

conditional:
    SE condition LBRACE statements RBRACE
    {
        if (!$2) fseek(svg_file, 0, SEEK_END);
    }
;

loop:
    REPETIR expr VEZES LBRACE
    {
        // Abrimos a função temporária
        fprintf(svg_file, "<!-- Loop iniciado -->\n");
        fprintf(svg_file, "<g>\n");
    }
    statements
    RBRACE
    {
        fprintf(svg_file, "</g>\n");
        executar_loop((int)$2, temp_loop_block);
    }
;

assignment:
    IDENTIFIER ASSIGN expr
    {
        set_var_num($1, $3);
    }
    | IDENTIFIER PLUS_ASSIGN expr
    {
        set_var_num($1, get_var($1) + $3);
    }
    | IDENTIFIER MINUS_ASSIGN expr
    {
        set_var_num($1, get_var($1) - $3);
    }
;

condition:
    expr comparator expr
    {
        switch ($2) {
            case EQ: $$ = ($1 == $3); break;
            case NE: $$ = ($1 != $3); break;
            case GE: $$ = ($1 >= $3); break;
            case LE: $$ = ($1 <= $3); break;
            case GT: $$ = ($1 > $3); break;
            case LT: $$ = ($1 < $3); break;
            default: $$ = 0;
        }
    }
;

comparator:
    EQ { $$ = EQ; }
    | NE { $$ = NE; }
    | GE { $$ = GE; }
    | LE { $$ = LE; }
    | GT { $$ = GT; }
    | LT { $$ = LT; }
;

expr:
    expr '+' expr     { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { $$ = $1 / $3; }
    | NUMBER          { $$ = $1; }
    | IDENTIFIER      { $$ = get_var($1); }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void temp_loop_block() {
    // Este é um placeholder. O corpo real é executado em tempo de parsing
}

void yyerror(const char *msg) {
    fprintf(stderr, "Erro: %s\n", msg);
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