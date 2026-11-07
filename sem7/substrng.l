//to check if subtring has amit in it(case insensitive), if present reject string else accept string



%{
#include <stdio.h>
%}

%%
.*[Aa][Mm][Ii][Tt].*    { printf("Rejected\n"); }
.*                       { printf("Accepted\n"); }
%%

int main()
{
    printf("Enter the string:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
