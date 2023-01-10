#include <stdio.h>
#ifndef _H_AST1_
#define _H_AST1_

typedef enum
{
ENUM_program,
ENUM_declarations,
ENUM_decl_statement,
ENUM_statements,
ENUM_statement,
ENUM_assignment_stmt,
ENUM_expression,
ENUM_term,
ENUM_factor,
ENUM_add_op,
ENUM_mul_op,
ENUM_var,
ENUM_loop_stmt,
ENUM_cond_stmt,
ENUM_condition,
ENUM_cond_op,
ENUM_DEFINE,
ENUM_ARRAY,
ENUM_WHILE,
ENUM_IF,
ENUM_ELSE,
ENUM_EQ,
ENUM_LT,
ENUM_GT,
ENUM_ASSIGN,
ENUM_ADD,
ENUM_SUB,
ENUM_MUL,
ENUM_DIV,
ENUM_NUMBER,
ENUM_IDENT,
}NodeType;

typedef struct abstract_node{
	NodeType nType;
	struct abstract_node *first_node;
	struct abstract_node *second_node;
	struct abstract_node *third_node;
}Node;

extern Node *top;

Node* build_node3(NodeType nType, Node* first_node, Node* second_node, Node* third_node);
Node* build_node_token(NodeType nType);

void printTree(Node *top_node);

#endif	// _H_HEAD1_

