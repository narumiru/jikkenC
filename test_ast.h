#include <stdio.h>

typedef enum
{
ENUM_NUMBER,
ENUM_ADD,
ENUM_SUB,
ENUM_MUL,
ENUM_DIV,
ENUM_L_PARAN,
ENUM_R_PARAN,
ENUM_statement
}NodeType;

typedef struct abstract_node{
	NodeType nType;
	struct abstract_node *front_node;
	struct abstract_node *back_node;
}Node;

Node* build_node2(NodeType nType, Node* front_node, Node* back_node);
Node* build_node_token(NodeType nType);

void printTree(Node *top_node);


