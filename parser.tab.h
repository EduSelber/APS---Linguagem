/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EQ = 258,                      /* EQ  */
    LT = 259,                      /* LT  */
    GT = 260,                      /* GT  */
    LE = 261,                      /* LE  */
    GE = 262,                      /* GE  */
    NE = 263,                      /* NE  */
    IDENTIFIER = 264,              /* IDENTIFIER  */
    STRING = 265,                  /* STRING  */
    NUMBER = 266,                  /* NUMBER  */
    CIRCULO = 267,                 /* CIRCULO  */
    RETANGULO = 268,               /* RETANGULO  */
    LINHA = 269,                   /* LINHA  */
    COR = 270,                     /* COR  */
    GRUPO = 271,                   /* GRUPO  */
    MOVER = 272,                   /* MOVER  */
    SE = 273,                      /* SE  */
    REPETIR = 274,                 /* REPETIR  */
    VEZES = 275,                   /* VEZES  */
    X = 276,                       /* X  */
    Y = 277,                       /* Y  */
    RAIO = 278,                    /* RAIO  */
    LARGURA = 279,                 /* LARGURA  */
    ALTURA = 280,                  /* ALTURA  */
    X1 = 281,                      /* X1  */
    Y1 = 282,                      /* Y1  */
    X2 = 283,                      /* X2  */
    Y2 = 284,                      /* Y2  */
    COR_ATUAL = 285,               /* COR_ATUAL  */
    ASSIGN = 286,                  /* ASSIGN  */
    ADD_ASSIGN = 287,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 288,              /* SUB_ASSIGN  */
    SENAO = 289,                   /* SENAO  */
    UMINUS = 290                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 287 "parser.y"

    double num;
    char *str;
    ASTNode *ast;

#line 105 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
