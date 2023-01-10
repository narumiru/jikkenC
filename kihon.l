%{
#include "kihon.tab.h"
#include "ast.h"
%}
%%
"define"	return DEFINE;
"array" 	return ARRAY;
"while" 	return WHILE;
"if"		return IF;
"else"		return ELSE;
";"			return SEMIC;
"["			return L_BRACKET;
"]" 		return R_BRACKET;
"(" 		return L_PARAN;
")" 		return R_PARAN;
"{" 		return L_BRACE;
"}" 		return R_BRACE;
"=="		return EQ;
"<" 		return LT;
">" 		return GT;
"=" 		return ASSIGN;
"+" 		return ADD;
"-" 		return SUB;
"*" 		return MUL;
"/" 		return DIV;
[0-9]+		return NUMBER;
[a-z|A-Z]|[a-z|A-Z][a-z|A-Z|0-9]+ {return IDENT;}
[ \t\n]     ;
%%
