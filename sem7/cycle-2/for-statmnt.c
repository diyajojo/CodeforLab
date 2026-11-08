
%{
    #include "y.tab.h"
%}

%%
"for"                  { return FOR; }
[a-zA-Z][a-zA-Z0-9]*   { return ID; }
[0-9]+                 { return NUMBER; }
"<="                   { return LE; }
">="                   { return GE; }
"=="                   { return EQ; }
"!="                   { return NE; }
"++"                   { return INC; }
"--"                   { return DEC; }
[\t\n]                 ;
.                      { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}



%{
    #include <stdio.h>
%}

%token FOR ID NUMBER LE GE EQ NE INC DEC

%%
start : FOR '(' init ';' cond ';' updte ')'
        { printf("Valid FOR syntax\n"); }
      ;

init : ID '=' expr
     ;

cond : expr relop expr
     ;

relop : '<' | '>' | GE | LE | EQ | NE
      ;

updte : ID INC
      | ID DEC
      | ID '=' expr
      ;

expr : term '+' term
     | term '-' term
     | term
     ;

term : ID | NUMBER
     ;
%%

int main()
{
    printf("Enter the statement:\n");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid FOR syntax\n");
    return 0;
}
