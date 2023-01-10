%{
#include <stdio.h>
#include "arithrv.tab.h"
extern int yylex();
extern int yyerror();
double vbltable[26];
%}
%union{
	double dval;
	int vblno;
}
%token <vblno> NAME
%token <dval> NUMBER
%type <dval> expression mulexp primary
%%
statement_list : statement '\n'
| statement_list statement '\n'
;
statement : expression {printf("= %g\n", $1);}
| NAME '=' expression {vbltable[$1] = $3; printf("%C= %g\n",$1+'a', $3);}
;
expression : expression '+' mulexp {$$ = $1 + $3;}
| expression '-' mulexp {$$ = $1 - $3;}
| mulexp {$$ = $1;}
;
mulexp : mulexp '*' primary {$$ = $1 * $3;}
| mulexp '/' primary {
	if($3 == 0.0){
		yyerror("divede by zero");
		return 0;
	}else $$ = $1 / $3;}
| primary {$$ = $1;}
;
primary : NUMBER {$$ = $1;}
|  '(' expression ')' {$$ = $2 ;}
|  NAME {$$ = vbltable[$1];}
;
%%
int main(void)
{
	if(yyparse()) {
		fprintf(stderr, "Error\n");
		return 1;
	}
}
