
#include <stdio.h>
#define MAX 100

int n, m, state;
int visited[MAX], final[MAX], nfinal[MAX];
int eps[MAX][MAX], closure[MAX][MAX];
int trans[MAX][MAX][MAX], ntrans[MAX][MAX][MAX];
char symb[MAX];

void dfs(int s, int visited[])
{
    visited[s] = 1;

    for(int i = 0; i < n; i++)
    {
        if(eps[s][i] == 1 && visited[i] == 0)
            dfs(i, visited);
    }
}

int main()
{
    printf("Enter number of states:\n");
    scanf("%d", &n);

    printf("Enter number of symbols:\n");
    scanf("%d", &m);

    printf("Enter symbols:\n");
    for(int i = 0; i < m; i++)
        scanf(" %c", &symb[i]);

    printf("Enter epsilon matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

    printf("Enter symbol transition matrices:\n");
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                scanf("%d", &trans[j][k][i]);

    printf("Enter final states (-1 to stop):\n");
    while(1)
    {
        scanf("%d", &state);
        if(state == -1)
            break;
        final[state] = 1;
    }

    // Step 1: Find epsilon closure
    for(int i = 0; i < n; i++)
    {
        int visited[MAX] = {0};
        dfs(i, visited);

        for(int j = 0; j < n; j++)
            closure[i][j] = visited[j];
    }

    // Step 2: Find new transitions
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            for(int k = 0; k < n; k++)
                if(closure[i][k])
                    for(int l = 0; l < n; l++)
                        if(trans[k][l][j])
                            for(int p = 0; p < n; p++)
                                if(closure[l][p])
                                    ntrans[i][p][j] = 1;

    // Step 3: Find new final states
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(closure[i][j] && final[j])
                nfinal[i] = 1;

    // Step 4: Print transitions
    printf("\nNew NFA transitions:\n");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            printf("q%d --%c--> ", i, symb[j]);

            for(int k = 0; k < n; k++)
                if(ntrans[i][k][j])
                    printf("q%d ", k);

            printf("\n");
        }

    printf("New final states:\n");

    for(int i = 0; i < n; i++)
        if(nfinal[i])
            printf("q%d ", i);

    return 0;
}
