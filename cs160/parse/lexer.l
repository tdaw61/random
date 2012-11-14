
%option yylineno
%pointer

%{
#include <stdlib.h>
#include <string.h>
#include "parser.hpp"

extern YYSTYPE yylval;
void yyerror(const char *);
%}

/* 
  WRITE ME: put any definitions you need here.  Add your own regular expressions
            below for ALL tokens defined in the manual. You can choose not to use
	    definitions here.

*/

/*
  The example below is very simple, but it shows almost everything you will need
  to do for this first part.

  The syntax is as follows:

  regular_expression      {  c code  }

  The lexer will try to match each regular expression.  When it does it will execute
  the c code.
*/

%%

=			return EQ;
==			return DEQ;
!= 			return NE;
\!			return NOT;
\<			return LT;
\<= 			return LE;
\> 			return GT;
\>= 			return GE;
\+ 			return PLUS;
\- 			return MINUS;
\*			return MULT;
\&& 			return AND;
\|			return ABS;
\;			return SEMI;
\, 			return COMMA;
\{			return OFUNC;
\} 			return CFUNC;
\(			return OPAREN;
\)			return CPAREN;
\[			return OARRAY;
\]			return CARRAY;
\: 			return COLON;
boolean		return BOOLEAN;
if			return IF;
else			return ELSE;
for 			return FOR;
var			return VAR;
function		return FUNCTION;
intarray		return INTARRAY;
return 		return RETURN;
true			return TRUE;
false			return FALSE;
integer		return INT;
<<EOF>> 		return END;
while			return WHILE;	
div 			return DIVIDE;

[ \t\n]  		; /* skip whitespace */
[1-9][0-9]*		yylval = atoi (yytext); return NUM;
[0][xX][0-9A-F]*	return HEX;
[0][1234567][01234567]*		return OCT;
[0][0]*			 return ZERO;
[01][01]*[b]		 return BIN;
[a-zA-Z][0-9_a-zA-Z]*	return LITERAL;
[(][%][\40-\176]*[%][)]  



%%


/* You shouldn't need to edit any part of this*/

int yywrap(void) {
	return 1;
}
 
