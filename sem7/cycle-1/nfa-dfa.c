
#include <stdio.h>

int n, m, total = 1;
int nfa[20][20][20], count[20][20];
int states[100][20], dfa[100][20];

// Check if DFA state already exists
int find(int a[])
{
    for(int i = 0; i < total; i++)
    {
        int same = 1;

        for(int j = 0; j < n; j++)
            if(states[i][j] != a[j])
                same = 0;

        if(same) return i;
    }
    return -1;
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    // Read NFA transitions
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("Number of transitions from q%d on symbol %d: ", i, j);
            scanf("%d", &count[i][j]);

            printf("Enter destination states: ");
            for(int k = 0; k < count[i][j]; k++)
                scanf("%d", &nfa[i][j][k]);
        }
    }

    // Initial DFA state = {q0}
    states[0][0] = 1;

    // NFA to DFA conversion
    for(int i = 0; i < total; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int next[20] = {0};

            // Find next states
            for(int s = 0; s < n; s++)
                if(states[i][s])
                    for(int k = 0; k < count[s][j]; k++)
                        next[nfa[s][j][k]] = 1;

            // Check existing state
            int f = find(next);

            // Add new state if not found
            if(f == -1)
            {
                f = total++;

                for(int s = 0; s < n; s++)
                    states[f][s] = next[s];
            }

            dfa[i][j] = f;
        }
    }

    // Print DFA transition table
    printf("\nDFA Transition Table\n");

    for(int i = 0; i < total; i++)
    {
        printf("{");
        for(int s = 0; s < n; s++)
            if(states[i][s])
                printf("q%d ", s);

        printf("}\t");

        for(int j = 0; j < m; j++)
            printf("%d\t", dfa[i][j]);

        printf("\n");
    }

    return 0;
}
