
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *p;
int tcount = 0, n = 0;

struct {
    char op[10], a1[20], a2[20], res[20];
} q[50];

void emit(char op[], char a[], char b[], char r[])
{
    strcpy(q[n].op, op);
    strcpy(q[n].a1, a);
    strcpy(q[n].a2, b);
    strcpy(q[n].res, r);
    n++;
}

void temp(char t[])
{
    sprintf(t, "t%d", ++tcount);
}

void skip()
{
    while (*p == ' ') p++;
}

void expr(char r[]);

void factor(char r[])
{
    char a[20];

    skip();

    if (*p == '(')
    {
        p++;
        expr(r);
        p++;
    }
    else if (*p == '-')
    {
        p++;
        factor(a);
        temp(r);
        emit("uminus", a, "", r);
    }
    else
    {
        int i = 0;
        while (isalnum(*p) || *p == '_')
            r[i++] = *p++;
        r[i] = '\0';
    }
}

void term(char r[])
{
    char b[20], t[20], op[2];

    factor(r);

    while (*p == '*' || *p == '/')
    {
        op[0] = *p++;
        op[1] = '\0';

        factor(b);
        temp(t);
        emit(op, r, b, t);
        strcpy(r, t);
        skip();
    }
}

void expr(char r[])
{
    char b[20], t[20], op[2];

    term(r);

    while (*p == '+' || *p == '-')
    {
        op[0] = *p++;
        op[1] = '\0';

        term(b);
        temp(t);
        emit(op, r, b, t);
        strcpy(r, t);
        skip();
    }
}

int main()
{
    char s[100], lhs[20] = "", res[20];
    char *eq;

    printf("Enter expression: ");
    fgets(s, 100, stdin);

    s[strcspn(s, "\n")] = '\0';

    eq = strchr(s, '=');

    if (eq)
    {
        sscanf(s, "%19s", lhs);
        p = eq + 1;
    }
    else
        p = s;

    expr(res);

    if (eq)
        emit("=", res, "", lhs);

    printf("\nThree Address Code:\n");

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(q[i].op, "="))
            printf("%s = %s\n", q[i].res, q[i].a1);

        else if (!strcmp(q[i].op, "uminus"))
            printf("%s = -%s\n", q[i].res, q[i].a1);

        else
            printf("%s = %s %s %s\n",
                q[i].res, q[i].a1, q[i].op, q[i].a2);
    }

    printf("\nQuadruples:\n");
    printf("No.\tOp\tArg1\tArg2\tResult\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%s\t%s\t%s\n",
            i, q[i].op, q[i].a1, q[i].a2, q[i].res);

    return 0;
}
