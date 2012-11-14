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
     COMMENT = 258,
     EQ = 259,
     DEQ = 260,
     NE = 261,
     LT = 262,
     LE = 263,
     GT = 264,
     GE = 265,
     PLUS = 266,
     MINUS = 267,
     DIVIDE = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     SEMI = 272,
     COMMA = 273,
     ABS = 274,
     OFUNC = 275,
     CFUNC = 276,
     OPAREN = 277,
     CPAREN = 278,
     OARRAY = 279,
     CARRAY = 280,
     BOOLEAN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     FOR = 285,
     FUNCTION = 286,
     INTARRAY = 287,
     RETURN = 288,
     TRUE = 289,
     FALSE = 290,
     INT = 291,
     DECIMAL = 292,
     HEX = 293,
     OCT = 294,
     BIN = 295,
     ZERO = 296,
     VAR = 297,
     MULT = 298,
     LITERAL = 299,
     NUM = 300,
     IDENT = 301,
     COLON = 302,
     UN_MINUS = 303
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


