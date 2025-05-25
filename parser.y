%{
#include "symbol_table.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern SymbolTable *symbol_table;

ASTNode *root = NULL;
static const char *current_color = "#000000"; 

const char* color_name_to_hex(const char *name) {
    if (strcmp(name, "azul") == 0) return "#0000FF";
    else if (strcmp(name, "vermelho") == 0) return "#FF0000";
    else if (strcmp(name, "verde") == 0) return "#00FF00";
    else if (strcmp(name, "amarelo") == 0) return "#FFFF00";
    else if (strcmp(name, "preto") == 0) return "#000000";
    else if (strcmp(name, "branco") == 0) return "#FFFFFF";
    else if (strcmp(name, "roxo") == 0) return "#800080";
    else if (strcmp(name, "laranja") == 0) return "#FFA500";
    else if (strcmp(name, "cinza") == 0) return "#808080";
    else {
        fprintf(stderr, "Unknown color: %s. Using black.\n", name);
        return "#000000";
    }
}

/* AST Node Creation Functions */
ASTNode* create_assign_node(char *id, ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.id = strdup(id);
    node->data.assign.expr = expr;
    return node;
}
ASTNode* create_line_node(ASTNode *x1, ASTNode *y1, ASTNode *x2, ASTNode *y2) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_LINE;
    node->data.line.x1 = x1;
    node->data.line.y1 = y1;
    node->data.line.x2 = x2;
    node->data.line.y2 = y2;
    return node;
}

ASTNode* create_circle_node(ASTNode *x, ASTNode *y, ASTNode *radius) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_CIRCLE;
    node->data.circle.x = x;
    node->data.circle.y = y;
    node->data.circle.radius = radius;
    return node;
}

ASTNode* create_rect_node(ASTNode *x, ASTNode *y, ASTNode *width, ASTNode *height) {
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

ASTNode* create_expr_ident_node(char *ident) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_IDENT;
    node->data.expr_ident.ident = strdup(ident);
    return node;
}

ASTNode* create_expr_num_node(double num) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_NUM;
    node->data.expr_num.num = num;
    return node;
}

ASTNode* create_expr_binop_node(char op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_EXPR_BINOP;
    node->data.expr_binop.op = op;
    node->data.expr_binop.left = left;
    node->data.expr_binop.right = right;
    return node;
}
ASTNode* create_if_node(ASTNode *cond, ASTNode *if_body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->data.if_stmt.cond = cond;
    node->data.if_stmt.if_body = if_body;
    return node;
}

ASTNode* create_if_else_node(ASTNode *cond, ASTNode *if_body, ASTNode *else_body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IF_ELSE;
    node->data.if_else_stmt.cond = cond;
    node->data.if_else_stmt.if_body = if_body;
    node->data.if_else_stmt.else_body = else_body;
    return node;
}

double eval_expr(ASTNode *node, SymbolTable *symbol_table) {
    if (!node) return 0.0;
    switch (node->type) {
        case NODE_EXPR_NUM:
            return node->data.expr_num.num;
        case NODE_EXPR_IDENT:
            return symbol_table_get(symbol_table, node->data.expr_ident.ident);
        case NODE_EXPR_BINOP: {
            double left = eval_expr(node->data.expr_binop.left, symbol_table);
            double right = eval_expr(node->data.expr_binop.right, symbol_table);
            switch (node->data.expr_binop.op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/':
                    if (right == 0) yyerror("Division by zero");
                    return left / right;
                case '=': return left == right;
                case '!': return left != right;
                case '<': return left < right;
                case '>': return left > right;
                case 'l': return left <= right;
                case 'g': return left >= right;
                default: return 0.0;
            }
        }
        default:
            return 0.0;
    }
}

void execute_node(ASTNode *node, SymbolTable *symbol_table, FILE *svg_file) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_ASSIGN: {
            double value = eval_expr(node->data.assign.expr, symbol_table);
            symbol_table_set(symbol_table, node->data.assign.id, value);
            break;
        }
        case NODE_CIRCLE: {
            double x = eval_expr(node->data.circle.x, symbol_table);
            double y = eval_expr(node->data.circle.y, symbol_table);
            double radius = eval_expr(node->data.circle.radius, symbol_table);
            fprintf(svg_file, "<circle cx=\"%g\" cy=\"%g\" r=\"%g\" stroke=\"%s\" fill=\"none\"/>\n",
                    x, y, radius, current_color);
            break;
        }
        case NODE_RECT: {
            double x = eval_expr(node->data.rect.x, symbol_table);
            double y = eval_expr(node->data.rect.y, symbol_table);
            double width = eval_expr(node->data.rect.width, symbol_table);
            double height = eval_expr(node->data.rect.height, symbol_table);
            fprintf(svg_file, "<rect x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\" stroke=\"%s\" fill=\"none\"/>\n",
                    x, y, width, height, current_color);
            break;
        }
        case NODE_IF:
            if (eval_expr(node->data.if_stmt.cond, symbol_table)) {
                execute_node(node->data.if_stmt.if_body, symbol_table,svg_file);
            }
            break;
        case NODE_IF_ELSE:
            if (eval_expr(node->data.if_else_stmt.cond, symbol_table)) {
                execute_node(node->data.if_else_stmt.if_body, symbol_table,svg_file);
            } else {
                execute_node(node->data.if_else_stmt.else_body, symbol_table,svg_file);
            }
            break;
        case NODE_LINE: {
            double x1 = eval_expr(node->data.line.x1, symbol_table);
            double y1 = eval_expr(node->data.line.y1, symbol_table);
            double x2 = eval_expr(node->data.line.x2, symbol_table);
            double y2 = eval_expr(node->data.line.y2, symbol_table);
            fprintf(svg_file, "<line x1=\"%g\" y1=\"%g\" x2=\"%g\" y2=\"%g\" stroke=\"%s\"/>\n",
                    x1, y1, x2, y2, current_color);
            break;
        }
        case NODE_COLOR:
            current_color = color_name_to_hex(node->data.color.color);
            break;
        case NODE_LOOP:
            for (int i = 0; i < node->data.loop.iterations; i++) {
                execute_node(node->data.loop.body, symbol_table, svg_file);
            }
            break;
        case NODE_PROGRAM:
            for (int i = 0; i < node->data.program.count; i++) {
                execute_node(node->data.program.stmts[i], symbol_table, svg_file);
            }
            break;
        default:
            break;
    }
}

void free_node(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case NODE_ASSIGN:
            free(node->data.assign.id);
            free_node(node->data.assign.expr);
            break;
        case NODE_CIRCLE:
            free_node(node->data.circle.x);
            free_node(node->data.circle.y);
            free_node(node->data.circle.radius);
            break;
        case NODE_RECT:
            free_node(node->data.rect.x);
            free_node(node->data.rect.y);
            free_node(node->data.rect.width);
            free_node(node->data.rect.height);
            break;
        case NODE_COLOR:
            free(node->data.color.color);
            break;
        case NODE_LOOP:
            free_node(node->data.loop.body);
            break;
        case NODE_IF:
            free_node(node->data.if_stmt.cond);
            free_node(node->data.if_stmt.if_body);
            break;
        case NODE_IF_ELSE:
            free_node(node->data.if_else_stmt.cond);
            free_node(node->data.if_else_stmt.if_body);
            free_node(node->data.if_else_stmt.else_body);
            break;
        case NODE_PROGRAM:
            for (int i = 0; i < node->data.program.count; i++) {
                free_node(node->data.program.stmts[i]);
            }
            free(node->data.program.stmts);
            break;
        case NODE_EXPR_IDENT:
            free(node->data.expr_ident.ident);
            break;
        case NODE_EXPR_BINOP:
            free_node(node->data.expr_binop.left);
            free_node(node->data.expr_binop.right);
            break;
        case NODE_LINE:
            free_node(node->data.line.x1);
            free_node(node->data.line.y1);
            free_node(node->data.line.x2);
            free_node(node->data.line.y2);
            break;
        default:
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
%token SENAO

%left EQ NE LT LE GT GE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <ast> program stmt shape_stmt color_stmt loop assignment expr if_stmt
%type <num> expr_value

%%

program:
    /* empty */ { $$ = create_program_node(NULL, 0); root = $$; }
    | program stmt {
        ASTNode **new_stmts = realloc($1->data.program.stmts, ($1->data.program.count + 1) * sizeof(ASTNode*));
        new_stmts[$1->data.program.count] = $2;
        $$ = create_program_node(new_stmts, $1->data.program.count + 1);
        root = $$;
    }
    ;

stmt:
    shape_stmt ';' { $$ = $1; }
    | color_stmt ';' { $$ = $1; }
    | assignment ';' { $$ = $1; }
    | loop { $$ = $1; }
    | if_stmt
    ;

assignment:
    IDENTIFIER ASSIGN expr { $$ = create_assign_node($1, $3); }
    | IDENTIFIER ADD_ASSIGN expr {
        ASTNode *ident = create_expr_ident_node($1);
        ASTNode *add = create_expr_binop_node('+', ident, $3);
        $$ = create_assign_node($1, add);
        free($1);
    }
    ;

if_stmt:
    SE '(' expr ')' '{' program '}' SENAO '{' program '}' {
        $$ = create_if_else_node($3, $6, $10);
    }
    | SE '(' expr ')' '{' program '}' {
        $$ = create_if_node($3, $6);
    }
    ;

shape_stmt:
    CIRCULO X expr Y expr RAIO expr { $$ = create_circle_node($3, $5, $7); }
    | RETANGULO X expr Y expr LARGURA expr ALTURA expr { $$ = create_rect_node($3, $5, $7, $9); }
    | LINHA X expr Y expr X expr Y expr { $$ = create_line_node($3, $5, $7, $9); }
    ;

color_stmt:
    COR STRING { $$ = create_color_node($2); free($2); }
    ;

loop:
    REPETIR expr_value VEZES '{' program '}' {
        $$ = create_loop_node((int)$2, $5);
    }
    ;

expr:
    NUMBER { $$ = create_expr_num_node($1); }
    | IDENTIFIER { $$ = create_expr_ident_node($1); free($1); }
    | expr '+' expr { $$ = create_expr_binop_node('+', $1, $3); }
    | expr '-' expr { $$ = create_expr_binop_node('-', $1, $3); }
    | expr '*' expr { $$ = create_expr_binop_node('*', $1, $3); }
    | expr '/' expr { $$ = create_expr_binop_node('/', $1, $3); }
    | expr EQ expr { $$ = create_expr_binop_node('=', $1, $3); }
    | expr NE expr { $$ = create_expr_binop_node('!', $1, $3); }
    | expr LT expr { $$ = create_expr_binop_node('<', $1, $3); }
    | expr LE expr { $$ = create_expr_binop_node('l', $1, $3); }
    | expr GT expr { $$ = create_expr_binop_node('>', $1, $3); }
    | expr GE expr { $$ = create_expr_binop_node('g', $1, $3); }
    | '(' expr ')' { $$ = $2; }
    ;

expr_value:
    expr { $$ = eval_expr($1, symbol_table); free_node($1); }
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

    FILE *svg_file = fopen("output.svg", "w");
    if (!svg_file) {
        perror("Error creating SVG file");
        fclose(yyin);
        return 1;
    }
    fprintf(svg_file, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\" version=\"1.1\">\n");

    symbol_table_init(&symbol_table);
    
    if (yyparse() == 0) {
        execute_node(root, symbol_table,svg_file);
    }
    fprintf(svg_file, "</svg>\n");
    free_node(root);
    symbol_table_destroy(symbol_table);
    fclose(yyin);
    fclose(svg_file);
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
