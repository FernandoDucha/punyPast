/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_TESTE_TAB_H_INCLUDED
# define YY_YY_TESTE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    SPACE = 259,
    MOD = 260,
    RIGHTSHIFT = 261,
    LEFTSHIFT = 262,
    SEMICOLON = 263,
    SIN = 264,
    EOLN = 265,
    PIVAL = 266,
    PLUS = 267,
    MINUS = 268,
    DIV = 269,
    MUL = 270,
    POW = 271,
    OPENBRACKET = 272,
    CLOSEBRACKET = 273,
    UNARYMINUS = 274,
    COS = 275,
    TAN = 276,
    ASIN = 277,
    ACOS = 278,
    ATAN = 279,
    FACT = 280,
    INC = 281,
    DEC = 282,
    LAND = 283,
    OR = 284,
    COMPLEMENT = 285,
    NOT = 286,
    XOR = 287,
    ASSIGN = 288,
    IOR = 289,
    AND = 290,
    OPENREG = 291,
    CLOSEREG = 292,
    REGA = 293,
    ANS = 294,
    FIX = 295,
    SCI = 296,
    ENG = 297,
    CONST = 298,
    LOG = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TESTE_TAB_H_INCLUDED  */
