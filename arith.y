%{
#include <stdio.h>
#include "arith.tab.h"
extern int yylex();
extern int yyerror();
%}
%token NUMBER
%%
statement : expression { printf("= %d\n", $1);}
;
expression : expression '+' term {$$ = $1 + $3;}
| expression '-' term {$$ = $1 - $3;}
| term {$$ = $1;}
;
term : term '*' factor {$$ = $1 * $3;}
| term '/' factor {
	if($3 == 0){
		yyerror("divede by zero");
		return 0;
	}else $$ = $1 / $3;}
| factor {$$ = $1;}
;
factor : NUMBER {$$ = $1;}
|  '(' expression ')' {$$ = ( $2 );}
;
%%
int main(void)
{
if(yyparse()) {
fprintf(stderr, "Error\n");
return 1;
}
return 0;
}
