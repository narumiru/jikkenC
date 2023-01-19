%{
int num_lines = 0, num_chars = 0, wordCount = 0; 
int Countc = 0, Count1 = 0;
%} 
%%
\n ++num_lines; ++num_chars;
[a-z]|[A-Z] ++num_chars; ++Countc;
[0-9] ++num_chars; ++Count1;
. ++num_chars;
%%
int main(void) {
	yylex();
	printf("# of lines = %d\n# of chars = %d\n", num_lines, num_chars);
	printf("# of char = %d\n# of int = %d\n", Countc, Count1);
	return 0;
}

