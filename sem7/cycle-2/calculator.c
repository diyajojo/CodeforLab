variable.l
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ;
\n          { return '\n'; }
.           { return yytext[0]; }
%%
int yywrap()
{
    return 1;
}




variable.y
%{
#include <stdio.h>
int yylex();
int yyerror(char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
input:
    expression '\n' {printf("result =%d\n",$1);}
    ;

expression:
      expression '+' expression {$$=$1+$3;}
    | expression '-' expression {$$=$1-$3;}
    | expression '*' expression {$$=$1*$3;}
    | expression '/' expression {$$=$1/$3;}
    | '(' expression ')'    {$$=$2;}   
    | NUMBER                 {$$=$1;}         
    ;
%%

int main()
{
    printf("enter expression\n");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("invalid expression\n");
    return 0;
}

