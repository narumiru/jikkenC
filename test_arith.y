%{
#include <stdio.h>
#include "test_ast.h"
#include "test_arith.tab.h"
//extern int yyerror();
%}
%union
{
Node* np;
int ival;
}

%token  NUMBER
%token  ADD
%token  SUB
%token  MUL
%token  DIV
%token  L_PARAN
%token  R_PARAN

%type <np> statement expression term factor

%%
statement : expression 
{top = build_node2(ENUM_statement,$1,NULL);}
;
expression : expression ADD term 
{$$ = build_node2(ENUM_ADD,$1,$3);}
| expression SUB term 
{$$ = build_node2(ENUM_SUB,$1,$3);}
| term 
{$$ = $1;}
;
term : term MUL factor 
{$$ = build_node2(ENUM_MUL,$1,$3);}
| term DIV factor 
{$$ = build_node2(ENUM_DIV,$1,$3);}
| factor 
{$$ = $1;}
;
factor : NUMBER 
{$$ = build_node_token(ENUM_NUMBER);}
|  L_PARAN expression R_PARAN 
{$$ = build_node_token(ENUM_NUMBER);}
;
%%

Node *top;
int main(void)
{
	if(yyparse()) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	printTree(top);
	return 0;
}
