#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"

Node *top;
Symbol_T symbol_table[MAX_NODE_NUM];


int getOffset(Node* p){
    //int mem_position
    //mem_position= symbol_t->offset + init_position;
    //return mem_position;
    return 0;
}


//宣言文
//arrayは未実装
int codegen_declaration(Node* p){
    char* varname;
    //構文チェック
    if(p->nType != ENUM_declarations){
        return -1;
    }
    //codegen_DEFINE(p->first_node);
    //codegen_ARRAY(p->first_node);
    
    varname = p->second_node->varName;
    //メモリ確保の処理
    //printf("sw $v0, %d($t0)\n",x);
    //
    return 0;
}

//変数宣言部
int codegen_declarations(Node* p){
    //正当性チェック
    if(p->nType != ENUM_declarations){
        printf("error");
        return -1;
    }
    //宣言文
    codegen_declaration(p->first_node);
    //変数宣言部
    if(p->second_node != NULL){
        codegen_declarations(p->second_node);
    }
}


//算術式
int codegen_expression(Node* p){
    return 0;
}

//条件式
int codegen_condition(Node* p){
    return 0;
}

//代入文
int codegen_assignment_stmt(Node* p){
    int x = getOffset(p->first_node);
    //算術式
    codegen_expression(p->second_node);
    printf("sw $v0, %d($t0)\n",x);
    return 0;
}
//ループ文
int codegen_loop_stmt(Node* p){


    return 0;
}
//条件分岐文
int codegen_cond_stmt(Node* p){
    return 0;
}


//文
int codegen_statement(Node* p){
    switch (p->first_node->nType){
        //代入文
        case ENUM_assignment_stmt :
            codegen_assignment_stmt(p->first_node);
            break;

        //ループ文
        case ENUM_loop_stmt :
            codegen_loop_stmt(p->first_node);
            break;

        //条件分岐文
        case ENUM_cond_stmt :
            codegen_cond_stmt(p->first_node);
            break;
        default:
            return -1;
    }
    return 0;
}

//文集合
int codegen_statements(Node* p){
    //文
    codegen_statement(p->first_node);
    //文集合
    if(p->second_node != NULL){
        codegen_statements(p->second_node);
    }
}

int codegen(Node* p){
    //変数宣言部
    codegen_declarations(p->first_node);
    //文集合
    codegen_statements(p->second_node);

    return 0;
}



int main(void)
{
    int result;
    result = yyparse();
	if (result == 0){
		//result = codegen(top);
	}
	printTree(top);
	fprintf(stdout,"\n");
	return result;
}
