
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

=			printf("lexer: assign\n"); return EQ;
==			printf("lexer: ==\n"); return DEQ;
!= 			printf("lexer: !=\n"); return NE;
\!			printf("lexer: ! \n"); return NOT;
\<			printf("lexer: <\n"); return LT;
\<= 			printf("lexer: <=\n"); return LE;
\> 			printf("lexer: >\n"); return GT;
\>= 			printf("lexer: >=\n"); return GE;
\+ 			printf("lexer: +\n"); return PLUS;
\- 			printf("lexer: -\n"); return MINUS;
\*			printf("lexer: *\n"); return MULT;
\&& 			printf("lexer: &&\n"); return AND;
\|			printf("lexer: ||\n"); return ABS;
\;			printf("lexer: ;\n"); return SEMI;
\, 			printf("lexer: ,\n"); return COMMA;
\{			printf("lexer: {\n"); return OFUNC;
\} 			printf("lexer: } \n"); return CFUNC;
\(			printf("lexer: (\n"); return OPAREN;
\)			printf("lexer: )\n"); return CPAREN;
\[			printf("lexer: [\n"); return OARRAY;
\]			printf("lexer: ]\n"); return CARRAY;
\: 			printf("lexer: :\n"); return COLON;
boolean			printf("lexer: boolean\n"); return BOOLEAN;
if			printf("lexer: if\n"); return IF;
else			printf("lexer: else\n"); return ELSE;
for 			printf("lexer: for\n"); return FOR;
var			printf("lexer: var\n"); return VAR;
function		printf("lexer: function\n"); return FUNCTION;
intarray		printf("lexer: intarray\n"); return INTARRAY;
return 			printf("lexer: return\n"); return RETURN;
true			printf("lexer: true\n"); return TRUE;
false			printf("lexer: false\n"); return FALSE;
integer			printf("lexer: integer\n"); return INT;
<<EOF>> 		return END;
while			printf("lexer: while \n"); return WHILE;	
div 			printf("lexer: divide \n"); return DIVIDE

[ \t\n]  		; /* skip whitespace */
[1-9][0-9]*		printf("lexer: decimal\n"); yylval = atoi (yytext); return NUM;
[0][xX][0-9A-F]*	printf("lexer: hex\n"); return HEX;
[0][1234567][01234567]*		printf("lexer: oct\n"); return OCT;
[0][0]*			printf("lexer: zero \n"); return ZERO;
[01][01]*[b]		printf("lexer: binary\n"); return BIN;
[a-zA-Z][0-9_a-zA-Z]*	printf("lexer: literal\n"); return LITERAL;
[(][%][\40-\176]*[%][)] printf("lexer: comment \n"); 



%%


/* You shouldn't need to edit any part of this*/

int yywrap(void) {
	return 1;
}
 
