//All states that can be reached from that state using zero or more epsilon transitions, including the starting state itself.
// prgm to find epsilon closure of a given state (start state)

#include <stdio.h>
#define MAX 100
int n,s,eps[MAX][MAX],visited[MAX];

void closure(int s)
{
    visited[s]=1;
    for(int i=0;i<n;i++)
        {
            if(eps[s][i]==1 && visited[i]==0)
            {
                closure(i);
            }
        }
}

int main()
{
    printf("enter number of states:\n");
    scanf("%d",&n);
    
    printf("enter the epsilon transition matrix:\n");
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                {
                    scanf("%d",&eps[i][j]);
                }
        }

    printf("enter the starting state:\n");
    scanf("%d",&s);

    for(int i=0;i<n;i++)
        {
            visited[i]=0;
        }
    printf("epsilon closure of %d is :{",s);
    closure(s);
    for(int i=0;i<n;i++)
        {
            if(visited[i]==1)
            {
                printf("%d\t\t",i);
            }
        }
    printf("}\n");
    return 0;
}