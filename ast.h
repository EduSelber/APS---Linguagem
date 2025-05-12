#ifndef AST_H
#define AST_H

// Forward declaration to avoid circular dependency
typedef struct SymbolTable SymbolTable;

typedef struct ASTNode ASTNode;

typedef enum {
    NODE_ASSIGN,
    NODE_CIRCLE,
    NODE_RECT,
    NODE_COLOR,
    NODE_LOOP,
    NODE_PROGRAM,
    NODE_EXPR_IDENT,
    NODE_EXPR_NUM,
    NODE_EXPR_BINOP
} NodeType;

struct ASTNode {
    NodeType type;
    union {
        struct { char *id; ASTNode *expr; } assign;
        struct { ASTNode *x; ASTNode *y; ASTNode *radius; } circle;
        struct { ASTNode *x; ASTNode *y; ASTNode *width; ASTNode *height; } rect;
        struct { char *color; } color;
        struct { int iterations; ASTNode *body; } loop;
        struct { ASTNode **stmts; int count; } program;
        struct { char *ident; } expr_ident;
        struct { double num; } expr_num;
        struct { char op; ASTNode *left; ASTNode *right; } expr_binop;
    } data;
};

// AST Node Creation
ASTNode* create_assign_node(char *id, ASTNode *expr);
ASTNode* create_circle_node(ASTNode *x, ASTNode *y, ASTNode *radius);
ASTNode* create_rect_node(ASTNode *x, ASTNode *y, ASTNode *width, ASTNode *height);
ASTNode* create_color_node(char *color);
ASTNode* create_loop_node(int iterations, ASTNode *body);
ASTNode* create_program_node(ASTNode **stmts, int count);

// Expression Nodes
ASTNode* create_expr_ident_node(char *ident);
ASTNode* create_expr_num_node(double num);
ASTNode* create_expr_binop_node(char op, ASTNode *left, ASTNode *right);

// Execution Functions
double eval_expr(ASTNode *node, SymbolTable *symbol_table);
void execute_node(ASTNode *node, SymbolTable *symbol_table);
void free_node(ASTNode *node);

#endif