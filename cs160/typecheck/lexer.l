%option yylineno
%pointer

%{
#include <stdlib.h>
#include <string.h>
#include "ast.hpp"
#include "parser.hpp"

void yyerror(const char *);
bool comm = false;

%}



%%



\(% 				{comm = true;}
%\)				{comm = false;}
==				{if (!comm) return EQUAL;}
=				{if (!comm) return SET;}
\>=				{if (!comm) return GTE;}
\>				{if (!comm) return GT;}
\<=				{if (!comm) return LTE;}
\<				{if (!comm) return LT;}
\;				{if (!comm) return SEMICOLON;}
\,				{if (!comm) return COMMA;}
\:				{if (!comm) return COLON;}
\|				{if (!comm) return ABS;}
\{				{if (!comm) return OFUNC;}
\}				{if (!comm) return CFUNC;}
\[				{if (!comm) return OARRAY;}
\]				{if (!comm) return CARRAY;}
\(				{if (!comm) return OPAREN;}
\)				{if (!comm) return CPAREN;}
\-				{if (!comm) return MINUS;}
!=				{if (!comm) return NOTEQUAL;}
!				{if (!comm) return NOT;}
&&				{if (!comm) return AND;}
[|][|]				{if (!comm) return OR;}
\+				{if (!comm) return	PLUS;}
\*				{if (!comm) return TIMES;}
boolean				{if (!comm) return BOOLEAN;}
else				{if (!comm) return ELSE;}
if				{if (!comm) return IF;}
integer				{if (!comm) return INTEGER;}
for 				{if (!comm) return FOR;}
var				{if (!comm) return VAR;}
function			{if (!comm) return FUNCTION;}
intarray			{if (!comm) return INTARRAY;}
return				{if (!comm) return RETURN;}
while				{if (!comm) return WHILE;}
div				{if (!comm) return DIVIDE;}
true				{if (!comm) { yylval.u_base_int = 1; return TRUE;}}
false				{if (!comm) { yylval.u_base_int = 0; return FALSE;}}
[ \t\n]  			        {}
[1-9][0-9]*			{if (!comm) { int value = (int)strtol(yytext, 0, 10);		yylval.u_base_int = value; return NUMBER;}}
0				{if (!comm) { int value = (int)strtol(yytext, 0, 10); yylval.u_base_int = value; return ZERO;}}
0[xX][0-9ABCDEF]+		{if (!comm) { int value = (int)strtol(yytext, 0, 16); yylval.u_base_int = value; return HEX;}}
0[0-7]+			{if (!comm) { int value = (int)strtol(yytext, 0, 8); yylval.u_base_int = value; return OCT;}}
[01]+b				{if (!comm){ char* p = strstr(yytext, "b"); p='\0'; int value = (int)strtol(yytext, 0, 2); yylval.u_base_int = value; return BIN;}}
[a-zA-Z][a-zA-Z0-9_]*	{if (!comm) {  yylval.u_base_charptr = strdup(yytext); return IDENTIFIER;}}


%%

/***************************************************************************
	Stop Replacing Code Here
***************************************************************************/

int yywrap(void) {
	return 1;
}


