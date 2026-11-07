#include <stdio.h>
#include <ctype.h>

void E();
void EP();
void T();
void TP();
void F();

char s[50];
int i=0,error=0;

 void E()
{
    T();
    EP();
}

void EP()
{
    if(s[i]=='+')
    {
        i++;
        T();
        EP();
    }
}
void T()
{
    F();
    TP();
}
void TP()
{
    if(s[i]=='*')
    {
        i++;
        F();
        TP();
    }
}
void F()
{
    if(s[i]=='(')
    {
        i++;
        E();
        if(s[i]==')')
            i++;
        else
            error=1;
    }
    else if(isalnum(s[i]))
    {
        i++;
    }
    else
    {
        error=1;
    }
}



int main()
{
    printf("enter the expression:\n");
    scanf("%c",s);
     E();
    if(s[i]='$' && error==0)
    {
        printf("string accepted\n");
    }
    else
    {
        printf("string rejected\n");
    }
    return 0;
}