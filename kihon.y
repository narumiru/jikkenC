%{
#include <stdio.h>
#include "ast.h"
#include "kihon.tab.h"
Node *top;
%}

%union{
Node* np; //木
int ival; //数
char* sp; //変数名
}

%token	DEFINE
%token	ARRAY
%token	WHILE
%token	IF
%token	ELSE
%token	SEMIC
%token	L_BRACKET
%token	R_BRACKET
%token	L_PARAN
%token	R_PARAN
%token	L_BRACE
%token	R_BRACE
%token	ASSIGN
%token	ADD
%token	SUB
%token	MUL
%token	DIV
%token	EQ
%token	LT
%token	GT

%token <sp> IDENT
%token <ival> NUMBER

%type <np> program declarations decl_statement statements statement assignment_stmt expression term factor add_op mul_op var loop_stmt cond_stmt condition cond_op

%%
program : declarations statements 
	{top = build_node3(ENUM_program, $1, $2, NULL);}
;
declarations : decl_statement declarations 
	{$$ = build_node3(ENUM_declarations, $1, $2, NULL);}
| decl_statement
	{$$ = build_node3(ENUM_declarations, $1, NULL, NULL);}
;
decl_statement : DEFINE IDENT SEMIC 
	{$$ = build_node3(ENUM_decl_statement, build_node_token(ENUM_DEFINE), build_node_var(ENUM_IDENT,$2), NULL);}
| ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC
	{$$ = build_node3(ENUM_decl_statement, build_node_token(ENUM_ARRAY), build_node_var(ENUM_IDENT,$2), build_node_num(ENUM_NUMBER, $4));}
;
statements :  statement statements
	{$$ = build_node3(ENUM_statements, $1, $2, NULL);}
| statement
	{$$ = build_node3(ENUM_statements, $1, NULL, NULL);}
;
statement : assignment_stmt 
	{$$ = build_node3(ENUM_statement, $1, NULL, NULL);}
| loop_stmt 
	{$$ = build_node3(ENUM_statement, $1, NULL, NULL);}
| cond_stmt
	{$$ = build_node3(ENUM_statement, $1, NULL, NULL);}
;
assignment_stmt : IDENT ASSIGN expression SEMIC 
	{$$ = build_node3(ENUM_assignment_stmt, build_node_var(ENUM_IDENT,$1), build_node_token(ENUM_ASSIGN), $3);}
| IDENT  L_BRACKET  NUMBER  R_BRACKET  ASSIGN  expression SEMIC
	{$$ = build_node3(ENUM_assignment_stmt, build_node_var(ENUM_IDENT,$1), build_node_num(ENUM_NUMBER,$3), build_node_token(ENUM_ASSIGN));}
;
expression : expression add_op term 
	{$$ = build_node3(ENUM_expression, $1, $2, $3);}
| term
	{$$ = build_node3(ENUM_expression, $1, NULL, NULL);}
;
term : term mul_op factor 
	{$$ = build_node3(ENUM_term, $1, $2, $3);}
| factor
	{$$ = build_node3(ENUM_term, $1, NULL, NULL);}
;
factor : var 
	{$$ = build_node3(ENUM_factor, $1, NULL, NULL);}
|  L_PARAN expression R_PARAN 
	{$$ = build_node3(ENUM_factor, $2, NULL, NULL);}
;
add_op : ADD 
	{$$ = build_node3(ENUM_add_op, build_node_token(ENUM_ADD), NULL, NULL);}
| SUB
	{$$ = build_node3(ENUM_add_op, build_node_token(ENUM_SUB), NULL, NULL);}
;
mul_op : MUL 
	{$$ = build_node3(ENUM_mul_op, build_node_token(ENUM_MUL), NULL, NULL);}
| DIV
	{$$ = build_node3(ENUM_mul_op, build_node_token(ENUM_DIV), NULL, NULL);}
;
var : IDENT 
	{$$ = build_node3(ENUM_var,build_node_var(ENUM_IDENT,$1) , NULL, NULL);}
| NUMBER 
	{$$ = build_node3(ENUM_var, build_node_num(ENUM_NUMBER,$1), NULL, NULL);}
| IDENT L_BRACKET NUMBER R_BRACKET 
	{$$ = build_node3(ENUM_var, build_node_var(ENUM_IDENT,$1), build_node_num(ENUM_NUMBER,$3), NULL);}
;
loop_stmt : WHILE  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE
	{$$ = build_node3(ENUM_loop_stmt, build_node_token(ENUM_WHILE), $3, $6);}
;
cond_stmt : IF  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE 
	{$$ = build_node3(ENUM_cond_stmt, build_node_token(ENUM_IF), $3, $6);}
| IF  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE
	{$$ = build_node3(ENUM_cond_stmt, build_node_token(ENUM_IF), build_node_token(ENUM_ELSE), $3);}
;
condition : expression cond_op expression
	{$$ = build_node3(ENUM_condition, $1, $2, $3);}
;
cond_op : EQ 
	{$$ = build_node3(ENUM_cond_op, build_node_token(ENUM_EQ), NULL, NULL);}
| LT 
	{$$ = build_node3(ENUM_cond_op, build_node_token(ENUM_LT), NULL, NULL);}
| GT
	{$$ = build_node3(ENUM_cond_op, build_node_token(ENUM_GT), NULL, NULL);}
;


%%
int main(void)
{
	if (yyparse()){
		fprintf(stderr, "Error\n");
		return 1;
	}
	printTree(top);
	fprintf(stdout,"\n");
	return 0;
return 0;
}
