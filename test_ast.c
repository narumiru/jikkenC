#include <stdio.h>
#include <stdlib.h>
#include "test_ast.h"
//extern Node *top;

Node* build_node2(NodeType nType, Node* front_node, Node* back_node){

	Node *new_node;
	
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		return NULL;
	}
	
	new_node->nType = nType;
	new_node->front_node = front_node;
	new_node->back_node = back_node;

	return new_node;
}


Node* build_node_token(NodeType nType){

	Node *new_node;
	
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		return NULL;
	}
	
	new_node->nType = nType;
	new_node->front_node = NULL;
	new_node->back_node = NULL;

	return new_node;
}




void printTree(Node* top_node){

	//枝複数判定
	if(top_node->back_node != NULL){
		printf("(");
	}

	if(top_node->front_node != NULL){
		printTree(top_node->front_node);
	}
	if(top_node->back_node != NULL){
		printTree(top_node->back_node);
	}
	switch (top_node->nType){
		case 0:
			printf("N ");
			break;
		case 1:
			printf("+");
			break;
		case 2:
			printf("-");
			break;
		case 3:
			printf("*");
			break;
		case 4:
			printf("/");
			break;
		case 5:
			printf("( ");
			break;
		case 6:
			printf(" )");
			break;
	}

	//枝複数判定
	if(top_node->back_node != NULL){
		printf(")");
	}

}
/*
int main(void){
	Node *top;
	printTree(top);
	fprintf(stdout,"\n");
	return 0;
}

int main(void){

	Node *top, *p1, *p2, *p3, *p4;

	p1 = build_node2(ENUM_ADD,
			build_node_token(ENUM_NUMBER),
			build_node_token(ENUM_NUMBER));
	p2 = build_node2(ENUM_SUB,
			build_node_token(ENUM_NUMBER),
			build_node_token(ENUM_NUMBER));
	p3 = build_node2(ENUM_MUL,
			build_node_token(ENUM_NUMBER),
			build_node_token(ENUM_NUMBER));
	p4 = build_node2(ENUM_ADD,p1,p2);

	top = build_node2(ENUM_statement,p4,p3);

	printTree(top);
	fprintf(stdout,"\n");
	return 0;
}
*/
//( 30 (( 29  29  25 )( 29  29  26 )( 29  29  27 ) 8 ) 24 )

