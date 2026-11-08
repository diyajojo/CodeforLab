%{
#include "ast.tab.h"
#include <string.h>
%}

%%

[a-zA-Z][a-zA-Z0-9]* {
    yylval.str = strdup(yytext);
    return ID;
}

[-+*/()]  { return yytext[0]; }
[ \t\n]+  ;
.         { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}



%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *left, *right;
} Node;

Node *root;

Node *createNode(char *v, Node *l, Node *r)
{
    Node *n = malloc(sizeof(Node));
    n->value = strdup(v);
    n->left = l;
    n->right = r;
    return n;
}

void printAST(Node *n, int level)
{
    if(n == NULL) return;

    for(int i=0; i<level; i++)
        printf("  ");

    printf("%s\n", n->value);

    printAST(n->left, level+1);
    printAST(n->right, level+1);
}

int yylex();
int yyerror(char *s);
%}

%union {
    char *str;
    Node *node;
}

%token <str> ID
%type <node> E T F

%left '+' '-'
%left '*' '/'

%%

input : E { root = $1; };

E : E '+' T { $$ = createNode("+", $1, $3); }
  | E '-' T { $$ = createNode("-", $1, $3); }
  | T       { $$ = $1; };

T : T '*' F { $$ = createNode("*", $1, $3); }
  | T '/' F { $$ = createNode("/", $1, $3); }
  | F       { $$ = $1; };

F : '(' E ')' { $$ = $2; }
  | ID        { $$ = createNode($1, NULL, NULL); };

%%

int main()
{
    printf("Enter expression: ");
    yyparse();

    printf("\nAbstract Syntax Tree:\n");
    printAST(root, 0);
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid expression\n");
    return 0;
}
