
#include <stdio.h>

int top = -1, ip = 0;
char stack[50], input[50];

int reduce()
{
    if(top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    else if(top >= 2 && stack[top] == 'E' &&
            stack[top-2] == 'E' &&
            (stack[top-1] == '+' || stack[top-1] == '*'))
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    else if(top >= 2 && stack[top] == ')' &&
            stack[top-2] == '(' && stack[top-1] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    printf("Grammar: E->E+E | E->E*E | E->(E) | E->i\n");
    printf("Enter input using i: ");
    scanf("%49s", input);

    while(input[ip] != '\0')
    {
        stack[++top] = input[ip++];
        printf("SHIFT\n");

        while(reduce())
            printf("REDUCE\n");

        stack[top+1] = '\0';
        printf("STACK: %s\n", stack);
    }

    if(top == 0 && stack[top] == 'E')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
