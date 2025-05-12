%{
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern SymbolTable *symbol_table;

/* AST Node Definitions */
typedef struct ASTNode ASTNode;

typedef enum {
    NODE_ASSIGN,
    NODE_CIRCLE,
    NODE_RECT,
    NODE_COLOR,
    NODE_LOOP,
    NODE_PROGRAM
} NodeType;

struct ASTNode {
    NodeType type;
    union {
        struct { char *id; double value; } assign;
        struct { double x, y, radius; } circle;
        struct { double x, y, width, height; } rect;
        struct { char *color; } color;
        struct { int iterations; ASTNode *body; } loop;
        struct { ASTNode **stmts; int count; } program;
    } data;
};

ASTNode *root = NULL;

/* AST Node Creation Functions */
ASTNode* create_assign_node(char *id, double value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.id = strdup(id);
    node->data.assign.value = value;
    return node;
}

ASTNode* create_circle_node(double x, double y, double radius) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_CIRCLE;
    node->data.circle.x = x;
    node->data.circle.y = y;
    node->data.circle.radius = radius;
    return node;
}

ASTNode* create_rect_node(double x, double y, double width, double height) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_RECT;
    node->data.rect.x = x;
    node->data.rect.y = y;
    node->data.rect.width = width;
    node->data.rect.height = height;
    return node;
}

ASTNode* create_color_node(char *color) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_COLOR;
    node->data.color.color = strdup(color);
    return node;
}

ASTNode* create_loop_node(int iterations, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_LOOP;
    node->data.loop.iterations = iterations;
    node->data.loop.body = body;
    return node;
}

ASTNode* create_program_node(ASTNode **stmts, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->data.program.stmts = stmts;
    node->data.program.count = count;
    return node;
}

/* AST Execution Functions */
void execute_node(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_ASSIGN:
            printf("ASSIGN: %s = %.2f\n", node->data.assign.id, node->data.assign.value);
            symbol_table_set(symbol_table, node->data.assign.id, node->data.assign.value);
            break;
        case NODE_CIRCLE:
            printf("DRAW CIRCLE: x=%.2f y=%.2f radius=%.2f\n", 
                   node->data.circle.x, node->data.circle.y, node->data.circle.radius);
            break;
        case NODE_RECT:
            printf("DRAW RECT: x=%.2f y=%.2f width=%.2f height=%.2f\n",
                   node->data.rect.x, node->data.rect.y, 
                   node->data.rect.width, node->data.rect.height);
            break;
        case NODE_COLOR:
            printf("SET COLOR: %s\n", node->data.color.color);
            break;
        case NODE_LOOP:
            printf("START LOOP: %d iterations\n", node->data.loop.iterations);
            for (int i = 0; i < node->data.loop.iterations; i++) {
                printf("LOOP ITERATION %d:\n", i+1);
                execute_node(node->data.loop.body);
            }
            printf("END LOOP\n");
            break;
        case NODE_PROGRAM:
            for (int i = 0; i < node->data.program.count; i++) {
                execute_node(node->data.program.stmts[i]);
            }
            break;
    }
}

void free_node(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_ASSIGN:
            free(node->data.assign.id);
            break;
        case NODE_COLOR:
            free(node->data.color.color);
            break;
        case NODE_LOOP:
            free_node(node->data.loop.body);
            break;
        case NODE_PROGRAM:
            for (int i = 0; i < node->data.program.count; i++) {
                free_node(node->data.program.stmts[i]);
            }
            free(node->data.program.stmts);
            break;
    }
    free(node);
}
%}

%union {
    double num;
    char *str;
    ASTNode *ast;
}

%token EQ LT GT LE GE NE
%token <str> IDENTIFIER STRING
%token <num> NUMBER
%token CIRCULO RETANGULO LINHA COR GRUPO MOVER SE REPETIR VEZES
%token X Y RAIO LARGURA ALTURA X1 Y1 X2 Y2 COR_ATUAL
%token ASSIGN ADD_ASSIGN SUB_ASSIGN
%token '(' ')' '{' '}' ';'

%type <num> expr
%type <ast> program stmt shape_stmt color_stmt loop assignment

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

program:
    /* empty */ { 
        $$ = create_program_node(NULL, 0); 
        root = $$;  // Assign the initial empty program to root
    }
    | program stmt { 
        ASTNode **new_stmts = realloc($1->data.program.stmts, 
                                    ($1->data.program.count + 1) * sizeof(ASTNode*));
        new_stmts[$1->data.program.count] = $2;
        $$ = create_program_node(new_stmts, $1->data.program.count + 1);
        root = $$;  // Update root to the latest program node
    }
    ;

stmt:
    shape_stmt ';' { $$ = $1; }
    | color_stmt ';' { $$ = $1; }
    | assignment ';' { $$ = $1; }
    | loop { $$ = $1; }
    ;

assignment:
    IDENTIFIER ASSIGN expr { $$ = create_assign_node($1, $3); free($1); }
    | IDENTIFIER ADD_ASSIGN expr { 
        double val = symbol_table_get(symbol_table, $1) + $3;
        $$ = create_assign_node($1, val); 
        free($1);
    }
    ;

shape_stmt:
    CIRCULO X expr Y expr RAIO expr { $$ = create_circle_node($3, $5, $7); }
    | RETANGULO X expr Y expr LARGURA expr ALTURA expr { $$ = create_rect_node($3, $5, $7, $9); }
    ;

color_stmt:
    COR STRING { $$ = create_color_node($2); free($2); }
    ;

loop:
    REPETIR expr VEZES '{' program '}' { 
        $$ = create_loop_node((int)$2, $5); 
    }
    ;

expr:
    NUMBER { $$ = $1; }
    | IDENTIFIER { $$ = symbol_table_get(symbol_table, $1); free($1); }
    | expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if ($3 == 0) yyerror("Division by zero");
        $$ = $1 / $3; 
    }
    | '(' expr ')' { $$ = $2; }
    ;

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    symbol_table_init(&symbol_table);
    
    if (yyparse() == 0) {
        execute_node(root);  // root is now set by the parser
    }
    
    free_node(root);
    symbol_table_destroy(symbol_table);
    fclose(yyin);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}