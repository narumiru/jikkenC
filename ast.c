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


	write_node_type(top_node->nType);
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

	//枝複数判定
	if(top_node->second_node != NULL){
		printf(")");
	}

}

void write_node_type(NodeType type){
	switch(type){
		case 0:
			printf("program");
			break;
		case 1:
			printf("declarations");
			break;
		case 2:
			printf("decl_statement");
			break;
		case 3:
			printf("statements");
			break;
		case 4:
			printf("statement");
			break;
		case 5:
			printf("assignment_stmt");
			break;
		case 6:
			printf("expression");
			break;
		case 7:
			printf("term");
			break;
		case 8:
			printf("factor");
			break;
		case 9:
			printf("add_op");
			break;
		case 10:
			printf("mul_op");
			break;
		case 11:
			printf("var");
			break;
		case 12:
			printf("loop_stmt");
			break;
		case 13:
			printf("cond_stmt");
			break;
		case 14:
			printf("condition");
			break;
		case 15:
			printf("cond_op");
			break;
		case 16:
			printf("DEFINE");
			break;
		case 17:
			printf("ARRAY");
			break;
		case 18:
			printf("WHILE");
			break;
		case 19:
			printf("IF");
			break;
		case 20:
			printf("ELSE");
			break;
		case 21:
			printf("EQ");
			break;
		case 22:
			printf("LT");
			break;
		case 23:
			printf("GT");
			break;
		case 24:
			printf("ASSIGN");
			break;
		case 25:
			printf("ADD");
			break;
		case 26:
			printf("SUB");
			break;
		case 27:
			printf("MUL");
			break;
		case 28:
			printf("DIV");
			break;
		case 29:
			printf("NUMBER");
			break;
		case 30:
			printf("IDENT");
			break;
		default:
			printf("%d",type);
	}
	printf(" ");
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

