#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#define MAX_NODE_NUM 1024

typedef struct symbol_token{
	char *varName; //変数名
	//int arraySize; //（配列の場合）
    int offset; //メモリのオフセットを記録
}Symbol_T;

//プロトタイプ宣言
int getOffset(Node* p);
int codegen_declaration(Node* p);
int codegen_declarations(Node* p);
int codegen_expression(Node* p);
int codegen_condition(Node* p);
int codegen_assignment_stmt(Node* p);
int codegen_loop_stmt(Node* p);
int codegen_cond_stmt(Node* p);
int codegen_statement(Node* p);
int codegen_statements(Node* p);
int codegen(Node* p);
