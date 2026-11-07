#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

char table[8][8] = {
    {'>','>','<','<','<','>','<','>'},
    {'>','>','<','<','<','>','<','>'},
    {'>','>','>','>','<','>','<','>'},
    {'>','>','>','>','<','>','<','>'},
    {'<','<','<','<','<','=','<',' '},
    {'>','>','>','>',' ','>',' ','>'},
    {'>','>','>','>',' ','>',' ','>'},
    {'<','<','<','<','<',' ','<',' '}
};

int findex(char s)
{
    switch(s)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case 'i': return 6;
        case '$': return 7;
    }
    return -1;
}

int reduce()
{
    if(stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    else if(top >= 2 && stack[top] == ')' &&
            stack[top-1] == 'E' && stack[top-2] == '(')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    else if(top >= 2 && stack[top] == 'E' &&
            stack[top-2] == 'E' &&
            (stack[top-1] == '+' || stack[top-1] == '-' ||
             stack[top-1] == '*' || stack[top-1] == '/'))
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    char a, b;
    int j, x, y;

    printf("Enter expression using i only: ");
    scanf("%s", input);

    strcat(input, "$");
    stack[++top] = '$';

    while(1)
    {
        j = top;

        while(j >= 0 && stack[j] == 'E')
            j--;

        a = stack[j];
        b = input[ip];

        if(top == 1 && stack[0] == '$' &&
           stack[1] == 'E' && b == '$')
        {
            printf("Accepted\n");
            break;
        }

        x = findex(a);
        y = findex(b);

        if(x == -1 || y == -1)
        {
            printf("Rejected\n");
            break;
        }

        else if(table[x][y] == '<' || table[x][y] == '=')
        {
            stack[++top] = b;
            ip++;
        }

        else if(table[x][y] == '>')
        {
            if(!reduce())
            {
                printf("Rejected\n");
                break;
            }
        }

        else
        {
            printf("Rejected\n");
            break;
        }
    }

    return 0;
}