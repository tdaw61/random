%option yylineno
%pointer

%{
#include <stdlib.h>
#include <string.h>
#include "ast.hpp"
#include "parser.hpp"

extern YYSTYPE yylval;

void yyerror(const char *);

%}

/* Insert your lexer here. Please don't just overwrite the file because of the enhanced header section. */

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

while			return WHILE;	
div 			return DIVIDE;

[ \t\n]  		; /* skip whitespace */
[1-9][0-9]*		{int value = (int)strtol(yytext, 0, 10);
			yylval.u_base_int = value;
			return NUM;}
[0][xX][0-9A-F]*	return HEX;
[0][1234567][01234567]*		return OCT;
[0][0]*			 return ZERO;
[01][01]*[b]		 return BIN;
[a-zA-Z][0-9_a-zA-Z]*	{yylval.u_base_charptr = new char[strlen(yytext + 1)];
			strcpy(yylval.u_base_charptr, yytext);
			yylval.u_base_charptr[strlen(yytext)] = '\0';
			return LITERAL;}
[(][%][\40-\176]*[%][)]  

%%

int yywrap(void) {
	return 1;
}

