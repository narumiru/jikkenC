%{
#include <stdio.h>
#include "arithr.tab.h"
extern int yylex();
extern int yyerror();
#define YYSTYPE double
%}
%token NUMBER
%%
statement : expression { printf("= %f\n", $1);}
;
expression : expression '+' term {$$ = $1 + $3;}
| expression '-' term {$$ = $1 - $3;}
| term {$$ = $1;}
;
term : term '*' factor {$$ = $1 * $3;}
| term '/' factor {
	if($3 == 0.0){
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
