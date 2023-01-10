%token DEFINE ARRAY WHILE IF ELSE
%{
#include <stdio.h>
#include "arithrv.tab.h"
#include "ast.h"
extern int yylex();
extern int yyerror();
%}
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

%token NUMBER
%token IDENT

%%
program : declarations statements 
	{top = build_node3(ENUM_program, $1, $2, NULL)}
;
declarations : decl_statement declarations 
	{top = build_node3(ENUM_declarations, $1, $2, NULL)}
| decl_statement
	{top = build_node3(ENUM_declarations, $1, NULL, NULL)}
;
decl_statement : DEFINE IDENT SEMIC 
	{top = build_node3(ENUM_decl_statement, $1, $2, NULL)}
| ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC
	{top = build_node3(ENUM_decl_statement, $1, $2, $3)}
;
statements :  statement statements
	{top = build_node3(ENUM_statements, $1, $2, NULL)}
| statement
	{top = build_node3(ENUM_statements, $1, NULL, NULL)}
;
statement : assignment_stmt 
	{top = build_node3(ENUM_statement, $1, NULL, NULL)}
| loop_stmt 
	{top = build_node3(ENUM_statement, $1, NULL, NULL)}
| cond_stmt
	{top = build_node3(ENUM_statement, $1, NULL, NULL)}
;
assignment_stmt : IDENT ASSIGN expression SEMIC 
	{top = build_node3(ENUM_assignment_stmt, $1, $2, $3)}
| IDENT  L_BRACKET  NUMBER  R_BRACKET  ASSIGN  expression SEMIC
	{top = build_node3(ENUM_assignment_stmt, $1, $2, $3)}
;
expression : expression add_op term 
| term
;
term : term mul_op factor 
| factor
;
factor : var 
|  L_PARAN expression R_PARAN 
;
add_op : ADD 
| SUB
;
mul_op : MUL 
| DIV
;
var : IDENT 
| NUMBER 
| IDENT L_BRACKET NUMBER R_BRACKET 
;
loop_stmt : WHILE  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE
;
cond_stmt : IF  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE 
| IF  L_PARAN condition R_PARAN  L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE
;
condition : expression cond_op expression
;
cond_op : EQ 
| LT 
| GT
;


%%
int main(void)
{
if (yyparse()){
fprintf(stderr, "Error\n");
return 1;
}
return 0;
}
