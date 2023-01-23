#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "codegen.h"

Node *top;
Symbol_T symbol_table[MAX_NODE_NUM];
int Symbol_Table_Num=0;
int Label_Id=0;

int setOffset(Node* p){
    int i = Symbol_Table_Num;
    symbol_table[i].varName = p->varName;
    symbol_table[i].offset = i*4;  //int型なので4バイト
    //個数が増える
    Symbol_Table_Num++;
    return i*4;
}

int getOffset(Node* p){
    int mem_position;
    char *varname;
    varname = p->varName;
    //既存の確認
    for(int i=0;i<Symbol_Table_Num;i++){
        if(*varname == *symbol_table[i].varName){
            mem_position = symbol_table[i].offset;
            return mem_position;
        }
    }
    //既存にない
    printf("offset error type=%s",p->nType);
    return -1;
}


//宣言文
//arrayは未実装
int codegen_decl_statement(Node* p){
    int offset;
    char* varname;
    //構文チェック
    if(p->nType != ENUM_decl_statement){
        printf("error type=%s",p->nType);
        return -1;
    }
    //codegen_DEFINE(p->first_node);
    //codegen_ARRAY(p->first_node);
    //記号表と対応
    offset = setOffset(p->second_node);
    //offset =  getOffset(p->second_node);
    return 0;
}

//変数宣言部
int codegen_declarations(Node* p){
    //宣言文
    codegen_decl_statement(p->first_node);
    //変数宣言部
    if(p->second_node != NULL){
        codegen_declarations(p->second_node);
    }
    return 0;
}

//識別子
//$v0に答えをいれていく
int codegen_ident(Node* p){
    int offset;
    offset = getOffset(p);
    //printf("\tlw\t$v0, %d($t0)\n",offset);
    //printf("\tnop\n");
    return offset;
}
//数
int codegen_number(Node* p){
    printf("\taddi\t$v0, $zero, %d\n", p->value);
    return 0;
}


//変数
int codegen_var(Node* p){
    //識別子
    if(p->first_node->nType == ENUM_IDENT){
        int offset;
        offset = codegen_ident(p->first_node);
        printf("\tlw\t$v0, %d($t0)\n",offset);
        printf("\tnop\n");
        return 0;
    }
    //数
    if(p->first_node->nType == ENUM_NUMBER){

        codegen_number(p->first_node);
        return 0;
    }
    return -1;
}

//因子
int codegen_factor(Node* p){
    //変数のパターン
    if(p->first_node->nType == ENUM_var){
        codegen_var(p->first_node);
        return 0;
    }
    //(算術式)の場合
    if(p->second_node->nType == ENUM_expression){
        codegen_expression(p->second_node);
        return 0;
    }
    return 0;
}


int codegen_mul_op(Node* p){
    switch (p->first_node->nType){
        case ENUM_MUL:
            printf("\tmult\t$v0, $t1\n");
            printf("\tmflo\t$v0\n");
            break;
        case ENUM_DIV:
            printf("\tdiv\t$v0, $t1\n");
            printf("\tmflo\t$v0\n");
            break;
        default:
            printf("error_term:\n");
    }
}

//項
//$v0に答えを格納するコード
int codegen_term(Node* p){
    //因子のパターン
    if(p->first_node->nType == ENUM_factor){
        codegen_factor(p->first_node);
        return 0;
    }
    //項 乗除演算子 因子のパターン
    if(p->first_node->nType == ENUM_term){
        codegen_term(p->first_node);    //項
        printf("\taddi\t$sp, $sp, -4 \n");  //スタックポインタの調整
        printf("\tsw\t$v0, 0($sp)\n");     //プッシュ
        codegen_factor(p->third_node);  //因子
        printf("\tadd\t$t1, $v0, $zero\n");  //因子の数値を$t1に
        printf("\tlw\t$v0, 0($sp)\n");     //ポップ
        printf("\tnop\n");
        printf("\taddi\t$sp, $sp, 4\n");  //spの調整

        codegen_mul_op(p->second_node);
        return 0;
    }
    return -1;
}

//加減演算子
int codegen_add_op(Node* p){
    switch (p->first_node->nType){
        case ENUM_ADD:
        printf("\tadd\t$v0, $v0, $t1\n");
        return 0;
        case ENUM_SUB:
        printf("\tsub\t$v0, $v0, $t1\n");
        return 0;
        default:
        printf("error_exp\n");
    }
    return -1;
}
//$v0に答えを格納するコード
int codegen_expression(Node* p){
    //項のパターン
    if(p->first_node->nType == ENUM_term){
        codegen_term(p->first_node);
        return 0;
    }else{
        //算術式 加減演算子 項のパターン
        codegen_expression(p->first_node);
        printf("\taddi\t$sp, $sp, -4 \n");  //スタックポインタの調整
        printf("\tsw\t$v0, 0($sp)\n");     //プッシュ
        codegen_term(p->third_node);
        printf("\tadd\t$t1, $v0, $zero\n");  //項の数値を$t1に
        printf("\tlw\t$v0, 0($sp)\n");     //ポップ
        printf("\tnop\n");
        printf("\taddi\t$sp, $sp, 4 \n");  //spの調整
        //加減演算子
        codegen_add_op(p->second_node);

        return 0;
    }
}

//比較演算子
int codegen_cond_op(Node* p){
    switch(p->first_node->nType){
        case ENUM_EQ:
            printf("\tslt\t$v0, $t2, $t3\n");
            printf("\tslt\t$v1, $t3, $t2\n");
            printf("\tadd\t$v0, $v0, $v1\n");  //真なら0、偽なら1
            return 0;
        case ENUM_LT:
            printf("\tslt\t$v0, $t2, $t3\n");  //真なら1、偽なら0
            printf("\txori\t$v0, $v0, 1\n");   //排他的論理和でひっくり返す
            return 0;
        case ENUM_GT:
            printf("\tslt\t$v0, $t3, $t2\n");  //真なら1、偽なら0
            printf("\txori\t$v0, $v0, 1\n");   //排他的論理和でひっくり返す
            return 0;
        default:
            printf("error\n");
    }
    return -1;
}

//条件式
int codegen_condition(Node* p){
    //算術式
    codegen_expression(p->first_node);
    printf("\taddi\t$sp, $sp, -4 \n");  //スタックポインタの調整
    printf("\tsw\t$v0, 0($sp)\n");     //プッシュ
    codegen_expression(p->third_node);
    printf("\tadd\t$t3, $v0, $zero\n");  //項の数値を$t3に
    printf("\tlw\t$v0, 0($sp)\n");     //ポップ
    printf("\tnop\n");
    printf("\tadd\t$t2, $v0, $zero\n");  //項の数値を$t2に
    printf("\taddi\t$sp, $sp, 4 \n");  //spの調整
    //比較演算子
    codegen_cond_op(p->second_node);
    return 0;
}

//代入文
//算術式の答えは$v0に入っているはず
int codegen_assignment_stmt(Node* p){
    //識別子（名前）
    int offset;
    offset = codegen_ident(p->first_node);
    //算術式
    codegen_expression(p->third_node);
    printf("\tsw\t$v0, %d($t0)\n",offset);
    return 0;
}
//ループ文
int codegen_loop_stmt(Node* p){
    int l_id;
    l_id = Label_Id;
    Label_Id++;
    //jump命令＋whileで戻ってくるラベル
    printf("\tj\t$WHILE_INIT%d\n",l_id);
    printf("$WHILE_TRUE%d:\n",l_id);
    //文集合
    codegen_statements(p->third_node);
    //条件付きジャンプ
    printf("$WHILE_INIT%d:\n",l_id);
    //条件文
    codegen_condition(p->second_node);
    printf("\tbeq\t$v0, $zero, $WHILE_TRUE%d\n",l_id);
    printf("\tnop\t\n");
    return 0;
}

//条件分岐文
//if 条件式 文集合 or if 条件文 文集合 else 文集合
int codegen_cond_stmt(Node* p){
    int l_id;
    l_id = Label_Id;
    Label_Id++;
    //条件式
    codegen_condition(p->first_node);
    //if文
    if(p->third_node == NULL){
        //偽のときジャンプする
        printf("\tbne\t$v0, $zero, $IF_FAUSE%d\n",l_id);
        printf("\tnop\t\n");
        //真の時の文集合
        codegen_statements(p->second_node);
        printf("$IF_FAUSE%d:\n",l_id);
        return 0;
    }

    //if-else文
    if(p->third_node->nType == ENUM_statements){
        //偽のときジャンプする
        printf("\tbne\t$v0, $zero, $IF_FALSE%d\n",l_id);
        printf("\tnop\t\n");
        //真の時の文集合
        codegen_statements(p->second_node);
        //if-else文終了までジャンプ
        printf("\tj\t$IF_FINISH%d\n",l_id);
        printf("$IF_FALSE%d:\n",l_id);
        //偽のときの文集合
        codegen_statements(p->third_node);
        printf("$IF_FINISH%d:\n",l_id);
        return 0;
    }
    return -1;
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
    return 0;
}

void cogeden_init(){
    printf("\tINITIAL_GP = 0x10008000\n");
    printf("\tINITIAL_SP = 0x7ffffffc\n");
    printf("\t# system call service number\n");
    printf("\tstop_service = 99\n");
    printf("\t.text\n");
    printf("init:\n");
    printf("\t# initialize $gp (global pointer) and $sp (stack pointer)\n");
    printf("\tla\t$gp, INITIAL_GP \n");
    printf("\tla\t$sp, INITIAL_SP\n");
    printf("\tjal main\n");
    printf("\tnop\t\n");
    printf("\tli\t$v0, stop_service\n");
    printf("\tsyscall\n");
    printf("\tnop\n");
    printf("stop:\n");
    printf("\tj\tstop\n");
    printf("\tnop\n");
    printf("\n");
    printf("\t.text\t 0x00001000\n");
    printf("main:\n");
}

int codegen(Node* p){
    if(p == NULL) return -1;
    cogeden_init();
    //変数宣言部
    codegen_declarations(p->first_node);
    //文集合
    codegen_statements(p->second_node);
    printf("\tjr\t$ra\n");
    printf("\tnop\t\n");
    return 0;
}



int main()
{
    int result;
    result = yyparse();
	printTree(top);
    printf("\n");
	if (result == 0){
		result = codegen(top);
	}
	fprintf(stdout,"\n");
	return result;
}
