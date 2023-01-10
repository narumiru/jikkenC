#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

Node* build_node3(NodeType nType, Node* first_node, Node* second_node, Node* third_node){

	Node *new_node;
	
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		return NULL;
	}
	
	new_node->nType = nType;
	new_node->first_node = first_node;
	new_node->second_node = second_node;
	new_node->third_node = third_node;

	return new_node;
}


Node* build_node_token(NodeType nType){

	Node *new_node;
	
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL){
		return NULL;
	}
	
	new_node->nType = nType;
	new_node->first_node = NULL;
	new_node->second_node = NULL;
	new_node->third_node = NULL;

	return new_node;
}




void printTree(Node* top_node){

	//枝複数判定
	if(top_node->second_node != NULL){
		printf("(");
	}

	if(top_node->first_node != NULL){
		printTree(top_node->first_node);
	}
	if(top_node->second_node != NULL){
		printTree(top_node->second_node);
	}
	if(top_node->third_node != NULL){
		printTree(top_node->third_node);
	}
	printf(" %d ",top_node->nType);

	//枝複数判定
	if(top_node->second_node != NULL){
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
/*

int main(void){

	Node *top, *p1, *p2, *p3, *p4;

	p1 = build_node3(ENUM_ADD,
			build_node_token(ENUM_NUMBER),
			build_node_token(ENUM_NUMBER),
			NULL);
	p2 = build_node3(ENUM_SUB,
			build_node_token(ENUM_NUMBER),
			build_node_token(ENUM_NUMBER),
			NULL);
	p3 = build_node3(ENUM_MUL,
			build_node3(ENUM_NUMBER, NULL, NULL, NULL),
			build_node3(ENUM_NUMBER, NULL, NULL, NULL),
			NULL);
	p4 = build_node3(ENUM_factor,p1,p2,p3);

	top = build_node3(ENUM_ASSIGN,
			build_node3(ENUM_IDENT, NULL, NULL, NULL),
			p4,
			NULL);

	printTree(top);
	fprintf(stdout,"\n");
	return 0;
}
*/
//( 30 (( 29  29  25 )( 29  29  26 )( 29  29  27 ) 8 ) 24 )

