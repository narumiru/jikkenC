%{
#include <stdio.h>
#include "test_arith.tab.h"
//extern int yylex();
//extern int yyerror();
%}
%token NUMBER
%token	ADD
%token	SUB
%token	MUL
%token	DIV
%token	L_PARAN
%token	R_PARAN
%%
statement : expression 
;
expression : expression ADD term 
| expression SUB term 
| term 
;
term : term MUL factor 
| term DIV factor 
| factor 
;
factor : NUMBER 
|  L_PARAN expression R_PARAN 
;
%%
int main(void)
{
if(yyparse()) {
	fprintf(stderr, "Error\n");
	return 1;
	}
return 0;
}
