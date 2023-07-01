#include <stdio.h>
#include <stdlib.h>

int find(int *S, int c)
{
    if (S[c] < 0)
        return c;

    else
        return S[c] = find(S, S[c]);
}

void connect(int *S, int c1, int c2)
{
    int root1 = find(S, c1);

    int root2 = find(S, c2);

    if (S[root1] < S[root2])
        S[root2] = root1;
    else if (S[root1] > S[root2])
        S[root1] = root2;
    else
    {
        S[root1] = root2;
        S[root2] -= 1;
    }
}

void check_connection(int *S, int c1, int c2)
{
    if (find(S, c1) == find(S, c2))
        printf("yes\n");
    else
        printf("no\n");
}

void check_network(int *S, int n)
{
    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (S[i] < 0)
            count++;
    }

     if (count == 1)
        printf("The network is connected.");

    else
        printf("There are %d components.", count);

    return;
}

int main()
{
    int n;

    scanf("%d", &n);

    int *a = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i <= n; i++)
        a[i] = -1;

    char c;

    int c1, c2;

    while (1)
    {
        scanf("%c", &c);

        if (c == 'I')
        {
            scanf("%d %d", &c1, &c2);
            connect(a, c1, c2);
        }
        if (c == 'C')
        {
            scanf("%d %d", &c1, &c2);
            check_connection(a, c1, c2);
        }
        if (c == 'S')
        {
            check_network(a, n);

            break;
        }
    }

    return 0;
}