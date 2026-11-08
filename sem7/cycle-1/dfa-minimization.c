#include <stdio.h>

int main()
{
    int n, m, i, j, k, a, x, y;
    int trans[10][10], final[10], mark[10][10] = {0};
    int changed;

    printf("Enter number of states:\n");
    scanf("%d", &n);

    printf("Enter number of symbols:\n");
    scanf("%d", &m);

    printf("Enter transition table:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);

    printf("Enter final states (1 for final, 0 for non-final):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &final[i]);

    // Initial marking
    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(final[i] != final[j])
                mark[i][j] = 1;

    // Check transitions repeatedly
    do
    {
        changed = 0;

        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                for(a = 0; a < m; a++)
                {
                    x = trans[i][a];
                    y = trans[j][a];

                    if(x > y)
                    {
                        k = x;
                        x = y;
                        y = k;
                    }

                    if(mark[x][y] == 1 && mark[i][j] == 0)
                    {
                        mark[i][j] = 1;
                        changed = 1;
                    }
                }
            }
        }

    } while(changed);

    printf("Equivalent states:\n");

    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(mark[i][j] == 0)
                printf("%d and %d\n", i, j);

    return 0;
}