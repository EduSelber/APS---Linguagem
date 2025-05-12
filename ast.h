#ifndef AST_H
#define AST_H

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

ASTNode* create_assign_node(char *id, double value);
ASTNode* create_circle_node(double x, double y, double radius);
ASTNode* create_rect_node(double x, double y, double width, double height);
ASTNode* create_color_node(char *color);
ASTNode* create_loop_node(int iterations, ASTNode *body);
ASTNode* create_program_node(ASTNode **stmts, int count);
void execute_node(ASTNode *node);
void free_node(ASTNode *node);

#endif