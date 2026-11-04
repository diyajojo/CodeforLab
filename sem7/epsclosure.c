#include <stdio.h>
#define MAX 100

int n, s, eps[MAX][MAX], visited[MAX];

void closure(int s)
{
    visited[s] = 1;

    for (int i = 0; i < n; i++)
    {
        if (eps[s][i] == 1 && !visited[i])
        {
            closure(i);
        }
    }
}

int main()
{
    printf("Enter number of states:\n");
    scanf("%d", &n);

    printf("Enter the epsilon transition matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &eps[i][j]);
        }
    }

    printf("Enter the starting state:\n");
    scanf("%d", &s);

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    closure(s);

    printf("Epsilon closure: { ");

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            printf("%d ", i);
    }

    printf("}");

    return 0;
}