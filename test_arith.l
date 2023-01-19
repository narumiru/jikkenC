%{
#include "test_ast.h"
#include "test_arith.tab.h"
%}
%%
[0-9]+ 		return NUMBER;
"+" 		return ADD;
"-" 		return SUB;
"*" 		return MUL;
"/" 		return DIV;
"(" 		return L_PARAN;
")" 		return R_PARAN;
[\t ] ; /* ignore whitespace */
\n return 0;
%%
