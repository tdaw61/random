%option yylineno
%pointer

%{
#include <stdlib.h>
#include <string.h>
#include "ast.hpp"
#include "parser.hpp"

void yyerror(const char *);
int nest=0;
int line=1;
int space=1;
%}

/***************************************************************************
	Replace With your code from this point on
***************************************************************************/

%%


[ \t]  			        {}
[\n]					{}
\(% 			{nest=1;}

%\)				{nest=0;}

boolean		{if (nest==0) return BOOLEAN;}
else			{if (nest==0) return ELSE;}
if				{if (nest==0) return IF;}
integer			{if (nest==0) return INTEGER;}
for 			{if (nest==0) return FOR;}
var				{if (nest==0) return VAR;}
function		{if (nest==0) return FUNCTION;}
intarray		{if (nest==0) return INTARRAY;}
return			{if (nest==0) return RETURN;}
&&				{if (nest==0) return AND;}
\/				{if (nest==0) return DIVIDE;}
==				{if (nest==0) return EQUAL;}
=				{if (nest==0) return SET;}
>=				{if (nest==0) return GTE;}
>				{if (nest==0) return GT;}
[<][=]			{if (nest==0) return LTE;}
[<]				{if (nest==0) return LT;}
\-				{if (nest==0) return MINUS;}
!=				{if (nest==0) return NOTEQUAL;}
!				{if (nest==0) return NOT;}
[|][|]			{if (nest==0) return OR;}
[+]				{if (nest==0) return	PLUS;}
[*]				{if (nest==0) return TIMES;}
true			{if (nest==0) { yylval.u_base_int = 1; return TRUE;}}
false		{if (nest==0) { yylval.u_base_int = 0; return FALSE;}}
[1-9][0-9]*		{if (nest==0) { int value = (int)strtol(yytext, 0, 10); yylval.u_base_int = value; return NUMBER;}}
0				{if (nest==0) { int value = (int)strtol(yytext, 0, 10); yylval.u_base_int = value; return NUMBER;}}
0[xX][0-9ABCDEF]+	{if (nest==0) { int value = (int)strtol(yytext, 0, 16); yylval.u_base_int = value; return NUMBER;}}
0[0-7]+			{if (nest==0) { int value = (int)strtol(yytext, 0, 8); yylval.u_base_int = value; return NUMBER;}}
[01]+b			{if (nest==0){ char* p = strstr(yytext, "b"); p='\0'; int value = (int)strtol(yytext, 0, 2); yylval.u_base_int = value; return NUMBER;}}
;				{if (nest==0) return SEMICOLON;}
,				{if (nest==0) return COMMA;}
[|]				{if (nest==0) return ABS;}
[{]				{if (nest==0) return CURLYOPEN;}
[}]				{if (nest==0) return CURLYCLOSE;}
\[				{if (nest==0) return SQUAREOPEN;}
\]				{if (nest==0) return SQUARECLOSE;}
\(				{if (nest==0) return	PARENOPEN;}
\)				{if (nest==0) return PARENCLOSE;}
[a-zA-Z][a-zA-Z0-9_]*	{if (nest==0) {  yylval.u_base_charptr = strdup(yytext); return IDENTIFIER;}}

.				{if (nest==0) yyerror((char *) "invalid character");}

%%

/***************************************************************************
	Stop Replacing Code Here
***************************************************************************/

int yywrap(void) {
	return 1;
}
