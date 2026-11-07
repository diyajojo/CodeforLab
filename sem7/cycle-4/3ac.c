
#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    char tac[10][50];
    char r[10], a[10], op[5], b[10], lbl[10];

    printf("Enter the number of instructions:\n");
    scanf("%d", &n);

    printf("Enter the instructions:\n");

    for(int i = 0; i < n; i++)
    {
        scanf(" %[^\n]", tac[i]);
    }

    printf("8086 assembly code is:\n");

    for(int i = 0; i < n; i++)
    {
        if(sscanf(tac[i], "%s = %s %s %s", r, a, op, b) == 4)
        {
            printf("MOV AX, %s\n", a);

            if(op[0] == '+')
                printf("ADD AX, %s\n", b);

            else if(op[0] == '-')
                printf("SUB AX, %s\n", b);

            else if(op[0] == '*')
            {
                printf("MOV BX, %s\n", b);
                printf("MUL BX\n");
            }

            else if(op[0] == '/')
            {
                printf("MOV BX, %s\n", b);
                printf("MOV DX, 0\n");
                printf("DIV BX\n");
            }

            printf("MOV %s, AX\n", r);
        }

        else if(sscanf(tac[i], "%s = %s", r, a) == 2)
        {
            printf("MOV AX, %s\n", a);
            printf("MOV %s, AX\n", r);
        }

        else if(sscanf(tac[i], "goto %s", lbl) == 1)
        {
            printf("JMP %s\n", lbl);
        }

        else if(sscanf(tac[i], "%[^:]:", lbl) == 1)
        {
            printf("%s:\n", lbl);
        }
    }

    return 0;
}
