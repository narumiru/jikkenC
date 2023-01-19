%{
#define YYSTYPE double
#include "arithr.tab.h"
//extern double yylval;
%}
%%
([0-9]+)|([0-9]*\.[0-9]+) {yylval = atof(yytext); return NUMBER; }
[\t ] ; /* ignore whitespace */
\n  return 0;
. return yytext[0];
%%
