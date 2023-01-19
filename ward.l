%{
int num_lines = 0, num_chars = 0, wordCount = 0;
%} 
%%
[^ \s\n]+ wordCount++; num_chars+=yyleng;
\n ++num_lines; ++num_chars;
. ++num_chars;
%%
int main(void) {
	yylex();
	printf("# of lines = %d\n# of word = %d\n# of chars = %d\n", num_lines, wordCount, num_chars);
	return 0;
}

