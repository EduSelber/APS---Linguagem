/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 357 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_EQ = 3,                         /* EQ  */
  YYSYMBOL_LT = 4,                         /* LT  */
  YYSYMBOL_GT = 5,                         /* GT  */
  YYSYMBOL_LE = 6,                         /* LE  */
  YYSYMBOL_GE = 7,                         /* GE  */
  YYSYMBOL_NE = 8,                         /* NE  */
  YYSYMBOL_IDENTIFIER = 9,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_NUMBER = 11,                    /* NUMBER  */
  YYSYMBOL_CIRCULO = 12,                   /* CIRCULO  */
  YYSYMBOL_RETANGULO = 13,                 /* RETANGULO  */
  YYSYMBOL_LINHA = 14,                     /* LINHA  */
  YYSYMBOL_COR = 15,                       /* COR  */
  YYSYMBOL_GRUPO = 16,                     /* GRUPO  */
  YYSYMBOL_MOVER = 17,                     /* MOVER  */
  YYSYMBOL_SE = 18,                        /* SE  */
  YYSYMBOL_REPETIR = 19,                   /* REPETIR  */
  YYSYMBOL_VEZES = 20,                     /* VEZES  */
  YYSYMBOL_X = 21,                         /* X  */
  YYSYMBOL_Y = 22,                         /* Y  */
  YYSYMBOL_RAIO = 23,                      /* RAIO  */
  YYSYMBOL_LARGURA = 24,                   /* LARGURA  */
  YYSYMBOL_ALTURA = 25,                    /* ALTURA  */
  YYSYMBOL_X1 = 26,                        /* X1  */
  YYSYMBOL_Y1 = 27,                        /* Y1  */
  YYSYMBOL_X2 = 28,                        /* X2  */
  YYSYMBOL_Y2 = 29,                        /* Y2  */
  YYSYMBOL_COR_ATUAL = 30,                 /* COR_ATUAL  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 32,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 33,                /* SUB_ASSIGN  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_36_ = 36,                       /* '{'  */
  YYSYMBOL_37_ = 37,                       /* '}'  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_SENAO = 39,                     /* SENAO  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_UMINUS = 44,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_stmt = 47,                      /* stmt  */
  YYSYMBOL_assignment = 48,                /* assignment  */
  YYSYMBOL_if_stmt = 49,                   /* if_stmt  */
  YYSYMBOL_shape_stmt = 50,                /* shape_stmt  */
  YYSYMBOL_color_stmt = 51,                /* color_stmt  */
  YYSYMBOL_loop = 52,                      /* loop  */
  YYSYMBOL_expr = 53,                      /* expr  */
  YYSYMBOL_expr_value = 54                 /* expr_value  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  31
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  87

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,    42,    40,     2,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    39,
      44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   313,   313,   314,   323,   324,   325,   326,   327,   331,
     332,   341,   344,   350,   351,   352,   356,   360,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   382
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "EQ", "LT", "GT", "LE",
  "GE", "NE", "IDENTIFIER", "STRING", "NUMBER", "CIRCULO", "RETANGULO",
  "LINHA", "COR", "GRUPO", "MOVER", "SE", "REPETIR", "VEZES", "X", "Y",
  "RAIO", "LARGURA", "ALTURA", "X1", "Y1", "X2", "Y2", "COR_ATUAL",
  "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "'('", "')'", "'{'", "'}'", "';'",
  "SENAO", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "program",
  "stmt", "assignment", "if_stmt", "shape_stmt", "color_stmt", "loop",
  "expr", "expr_value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -33,   252,   -33,   -24,    -9,    -2,    -1,    -5,   -13,    37,
     -33,     6,   -33,     7,     9,   -33,    37,    37,    37,    37,
      37,   -33,    37,   -33,   -33,    37,   201,    16,   -33,   -33,
     -33,   201,   201,    10,    35,    62,    82,    91,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,     1,    37,
      37,    37,    13,   -33,    18,    18,    18,    18,    18,    18,
     -32,   -32,   -33,   -33,   -33,   104,   132,   145,   -33,   209,
      37,    37,    37,   236,   -33,   201,   154,   195,    23,    37,
      37,    36,   201,   201,   -33,   244,   -33
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       3,     0,     8,     0,     0,     7,     0,     0,     0,     0,
       0,    16,     0,    19,    18,     0,    31,     0,     6,     4,
       5,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    24,    26,    28,    27,    29,    25,
      20,    21,    22,    23,     2,     0,     0,     0,     2,     0,
       0,     0,     0,     0,    17,    13,     0,     0,    12,     0,
       0,     0,    14,    15,     2,     0,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,    99,   -33,   -33,   -33,   -33,   -33,   -33,   -16,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    10,    11,    12,    13,    14,    15,    26,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    32,    33,    34,    35,    21,    36,    16,    17,    37,
      46,    47,    18,    38,    39,    40,    41,    42,    43,    19,
      20,    22,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    49,    65,    66,    67,    48,    64,    38,    39,
      40,    41,    42,    43,    28,    29,    23,    30,    24,    68,
      44,    45,    46,    47,    75,    76,    77,    50,    44,    45,
      46,    47,    81,    82,    83,    38,    39,    40,    41,    42,
      43,    25,    84,     0,     0,    44,    45,    46,    47,     0,
       0,     0,     0,     0,    51,    38,    39,    40,    41,    42,
      43,     0,     0,     0,    38,    39,    40,    41,    42,    43,
       0,     0,    44,    45,    46,    47,     0,    38,    39,    40,
      41,    42,    43,     0,     0,     0,     0,    52,     0,     0,
       0,     0,    44,    45,    46,    47,    53,    70,     0,     0,
       0,    44,    45,    46,    47,    38,    39,    40,    41,    42,
      43,     0,     0,     0,    44,    45,    46,    47,    38,    39,
      40,    41,    42,    43,     0,     0,    71,    38,    39,    40,
      41,    42,    43,    69,     0,     0,    72,    73,     0,     0,
       0,     0,    44,    45,    46,    47,     0,     0,     0,    79,
       0,     0,     0,    85,     0,    44,    45,    46,    47,     0,
       0,     0,     0,     0,    44,    45,    46,    47,    38,    39,
      40,    41,    42,    43,    38,    39,    40,    41,    42,    43,
       0,     0,     0,     0,     0,     0,     0,    80,     3,     0,
       0,     4,     5,     6,     7,     0,     0,     8,     9,     0,
       0,     0,     0,     0,     0,    44,    45,    46,    47,     0,
       0,    44,    45,    46,    47,     3,    74,     0,     4,     5,
       6,     7,     2,     3,     8,     9,     4,     5,     6,     7,
       0,     3,     8,     9,     4,     5,     6,     7,     0,     0,
       8,     9,     0,    78,     0,     0,     0,     0,     0,     0,
       0,    86
};

static const yytype_int8 yycheck[] =
{
      16,    17,    18,    19,    20,    10,    22,    31,    32,    25,
      42,    43,    21,     3,     4,     5,     6,     7,     8,    21,
      21,    34,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    22,    49,    50,    51,    20,    36,     3,     4,
       5,     6,     7,     8,    38,    38,     9,    38,    11,    36,
      40,    41,    42,    43,    70,    71,    72,    22,    40,    41,
      42,    43,    39,    79,    80,     3,     4,     5,     6,     7,
       8,    34,    36,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    22,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    40,    41,    42,    43,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    35,    23,    -1,    -1,
      -1,    40,    41,    42,    43,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    40,    41,    42,    43,     3,     4,
       5,     6,     7,     8,    -1,    -1,    24,     3,     4,     5,
       6,     7,     8,    64,    -1,    -1,    21,    68,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    84,    -1,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,     9,    -1,
      -1,    12,    13,    14,    15,    -1,    -1,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    -1,
      -1,    40,    41,    42,    43,     9,    37,    -1,    12,    13,
      14,    15,     0,     9,    18,    19,    12,    13,    14,    15,
      -1,     9,    18,    19,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    46,     0,     9,    12,    13,    14,    15,    18,    19,
      47,    48,    49,    50,    51,    52,    31,    32,    21,    21,
      21,    10,    34,     9,    11,    34,    53,    54,    38,    38,
      38,    53,    53,    53,    53,    53,    53,    53,     3,     4,
       5,     6,     7,     8,    40,    41,    42,    43,    20,    22,
      22,    22,    35,    35,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    36,    53,    53,    53,    36,    46,
      23,    24,    21,    46,    37,    53,    53,    53,    37,    25,
      22,    39,    53,    53,    36,    46,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    46,    47,    47,    47,    47,    47,    48,
      48,    49,    49,    50,    50,    50,    51,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     1,     3,
       3,    11,     7,     7,     9,     9,     2,     6,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 313 "parser.y"
                { (yyval.ast) = create_program_node(NULL, 0); root = (yyval.ast); }
#line 1483 "parser.tab.c"
    break;

  case 3: /* program: program stmt  */
#line 314 "parser.y"
                   {
        ASTNode **new_stmts = realloc((yyvsp[-1].ast)->data.program.stmts, ((yyvsp[-1].ast)->data.program.count + 1) * sizeof(ASTNode*));
        new_stmts[(yyvsp[-1].ast)->data.program.count] = (yyvsp[0].ast);
        (yyval.ast) = create_program_node(new_stmts, (yyvsp[-1].ast)->data.program.count + 1);
        root = (yyval.ast);
    }
#line 1494 "parser.tab.c"
    break;

  case 4: /* stmt: shape_stmt ';'  */
#line 323 "parser.y"
                   { (yyval.ast) = (yyvsp[-1].ast); }
#line 1500 "parser.tab.c"
    break;

  case 5: /* stmt: color_stmt ';'  */
#line 324 "parser.y"
                     { (yyval.ast) = (yyvsp[-1].ast); }
#line 1506 "parser.tab.c"
    break;

  case 6: /* stmt: assignment ';'  */
#line 325 "parser.y"
                     { (yyval.ast) = (yyvsp[-1].ast); }
#line 1512 "parser.tab.c"
    break;

  case 7: /* stmt: loop  */
#line 326 "parser.y"
           { (yyval.ast) = (yyvsp[0].ast); }
#line 1518 "parser.tab.c"
    break;

  case 9: /* assignment: IDENTIFIER ASSIGN expr  */
#line 331 "parser.y"
                           { (yyval.ast) = create_assign_node((yyvsp[-2].str), (yyvsp[0].ast)); }
#line 1524 "parser.tab.c"
    break;

  case 10: /* assignment: IDENTIFIER ADD_ASSIGN expr  */
#line 332 "parser.y"
                                 {
        ASTNode *ident = create_expr_ident_node((yyvsp[-2].str));
        ASTNode *add = create_expr_binop_node('+', ident, (yyvsp[0].ast));
        (yyval.ast) = create_assign_node((yyvsp[-2].str), add);
        free((yyvsp[-2].str));
    }
#line 1535 "parser.tab.c"
    break;

  case 11: /* if_stmt: SE '(' expr ')' '{' program '}' SENAO '{' program '}'  */
#line 341 "parser.y"
                                                          {
        (yyval.ast) = create_if_else_node((yyvsp[-8].ast), (yyvsp[-5].ast), (yyvsp[-1].ast));
    }
#line 1543 "parser.tab.c"
    break;

  case 12: /* if_stmt: SE '(' expr ')' '{' program '}'  */
#line 344 "parser.y"
                                      {
        (yyval.ast) = create_if_node((yyvsp[-4].ast), (yyvsp[-1].ast));
    }
#line 1551 "parser.tab.c"
    break;

  case 13: /* shape_stmt: CIRCULO X expr Y expr RAIO expr  */
#line 350 "parser.y"
                                    { (yyval.ast) = create_circle_node((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1557 "parser.tab.c"
    break;

  case 14: /* shape_stmt: RETANGULO X expr Y expr LARGURA expr ALTURA expr  */
#line 351 "parser.y"
                                                       { (yyval.ast) = create_rect_node((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1563 "parser.tab.c"
    break;

  case 15: /* shape_stmt: LINHA X expr Y expr X expr Y expr  */
#line 352 "parser.y"
                                        { (yyval.ast) = create_line_node((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1569 "parser.tab.c"
    break;

  case 16: /* color_stmt: COR STRING  */
#line 356 "parser.y"
               { (yyval.ast) = create_color_node((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1575 "parser.tab.c"
    break;

  case 17: /* loop: REPETIR expr_value VEZES '{' program '}'  */
#line 360 "parser.y"
                                             {
        (yyval.ast) = create_loop_node((int)(yyvsp[-4].num), (yyvsp[-1].ast));
    }
#line 1583 "parser.tab.c"
    break;

  case 18: /* expr: NUMBER  */
#line 366 "parser.y"
           { (yyval.ast) = create_expr_num_node((yyvsp[0].num)); }
#line 1589 "parser.tab.c"
    break;

  case 19: /* expr: IDENTIFIER  */
#line 367 "parser.y"
                 { (yyval.ast) = create_expr_ident_node((yyvsp[0].str)); free((yyvsp[0].str)); }
#line 1595 "parser.tab.c"
    break;

  case 20: /* expr: expr '+' expr  */
#line 368 "parser.y"
                    { (yyval.ast) = create_expr_binop_node('+', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1601 "parser.tab.c"
    break;

  case 21: /* expr: expr '-' expr  */
#line 369 "parser.y"
                    { (yyval.ast) = create_expr_binop_node('-', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1607 "parser.tab.c"
    break;

  case 22: /* expr: expr '*' expr  */
#line 370 "parser.y"
                    { (yyval.ast) = create_expr_binop_node('*', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1613 "parser.tab.c"
    break;

  case 23: /* expr: expr '/' expr  */
#line 371 "parser.y"
                    { (yyval.ast) = create_expr_binop_node('/', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1619 "parser.tab.c"
    break;

  case 24: /* expr: expr EQ expr  */
#line 372 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('=', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1625 "parser.tab.c"
    break;

  case 25: /* expr: expr NE expr  */
#line 373 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('!', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1631 "parser.tab.c"
    break;

  case 26: /* expr: expr LT expr  */
#line 374 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('<', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1637 "parser.tab.c"
    break;

  case 27: /* expr: expr LE expr  */
#line 375 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('l', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1643 "parser.tab.c"
    break;

  case 28: /* expr: expr GT expr  */
#line 376 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('>', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1649 "parser.tab.c"
    break;

  case 29: /* expr: expr GE expr  */
#line 377 "parser.y"
                   { (yyval.ast) = create_expr_binop_node('g', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1655 "parser.tab.c"
    break;

  case 30: /* expr: '(' expr ')'  */
#line 378 "parser.y"
                   { (yyval.ast) = (yyvsp[-1].ast); }
#line 1661 "parser.tab.c"
    break;

  case 31: /* expr_value: expr  */
#line 382 "parser.y"
         { (yyval.num) = eval_expr((yyvsp[0].ast), symbol_table); free_node((yyvsp[0].ast)); }
#line 1667 "parser.tab.c"
    break;


#line 1671 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 385 "parser.y"


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
