
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m;
char a[10][10], f[10];

void add(char c)
{
    int i;
    for(i=0;i<m;i++)
        if(f[i]==c) return;
    f[m++]=c;
}

void first(char c)
{
    int i,j;

    for(i=0;i<n;i++)
        if(a[i][0]==c)
        {
            if(a[i][2]=='$') add('$');
            else
                for(j=2;a[i][j];j++)
                {
                    if(!isupper(a[i][j]))
                    {
                        add(a[i][j]);
                        break;
                    }
                    first(a[i][j]);
                    break;
                }
        }
}

void follow(char c)
{
    int i,j;

    if(a[0][0]==c) add('$');

    for(i=0;i<n;i++)
        for(j=2;a[i][j];j++)
            if(a[i][j]==c)
            {
                if(a[i][j+1])
                    first(a[i][j+1]);
                else if(c!=a[i][0])
                    follow(a[i][0]);
            }
}

int main()
{
    char c;
    int i;

    printf("Enter number of productions: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%s",a[i]);

    printf("Enter non-terminal: ");
    scanf(" %c",&c);

    m=0;
    first(c);
    printf("FIRST = {");
    for(i=0;i<m;i++) printf("%c",f[i]);
    printf("}\n");

    m=0;
    follow(c);
    printf("FOLLOW = {");
    for(i=0;i<m;i++) printf("%c",f[i]);
    printf("}\n");

    return 0;
}


































