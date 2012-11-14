/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BOOLEAN = 258,
     ELSE = 259,
     IF = 260,
     WHILE = 261,
     INTEGER = 262,
     FOR = 263,
     VAR = 264,
     FUNCTION = 265,
     INTARRAY = 266,
     RETURN = 267,
     AND = 268,
     DIVIDE = 269,
     EQUAL = 270,
     SET = 271,
     GTE = 272,
     GT = 273,
     LTE = 274,
     LT = 275,
     MINUS = 276,
     NOTEQUAL = 277,
     NOT = 278,
     OR = 279,
     PLUS = 280,
     TIMES = 281,
     TRUE = 282,
     FALSE = 283,
     NUMBER = 284,
     SEMICOLON = 285,
     COMMA = 286,
     COLON = 287,
     ABS = 288,
     CURLYOPEN = 289,
     CURLYCLOSE = 290,
     SQUAREOPEN = 291,
     SQUARECLOSE = 292,
     PARENOPEN = 293,
     PARENCLOSE = 294,
     IDENTIFIER = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


