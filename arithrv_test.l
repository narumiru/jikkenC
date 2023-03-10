%{
#include "arithrv_test.tab.h"
%}
%%
[0-9]+|[0-9]*\.[0-9]+ {yylval.dval = atof(yytext) ; return NUMBER; }
[\t ] ; /* ignore whitespace */
[a-z] {yylval.vblno = yytext[0] - 'a'; return NAME; }
"$" {return 0; /* end of input */}
\n |
. return yytext[0];
%%
