#include <stdio.h>

int G[1000][1000];

int judge(int *path, int Nv)
{
    int visit[Nv + 2];

    memset(visit, 0, sizeof(int) * (Nv + 2));

    int i = 1;

    while (i != Nv + 1)
    {
        int v1 = path[i], v2 = path[i + 1];

        if (G[v1][v2] == 1 && visit[v1] == 0)
        {
            visit[v1] = 1;
            i++;
            continue;
        }
        else
            return 0;
    }
    return 1;
}

int main()
{
    int Nv, Ne;

    scanf("%d %d", &Nv, &Ne);

    int v1, v2;

    for (int i = 1; i <= Ne; i++)
    {
        scanf("%d %d", &v1, &v2);

        G[v1][v2] = G[v2][v1] = 1;
    }

    int K;

    scanf("%d", &K);

    for (int i = 0; i < K; i++)
    {
        int length = 0;

        scanf("%d", &length);

        int path[length + 1];

        for (int j = 1; j <= length; j++)
        {
            scanf("%d", &path[j]);
        }

        if (length != Nv + 1)
        {
            puts("NO");
        }
        else if (path[1] != path[length])
        {
            puts("NO");
        }
        else
        {
            if (judge(path, Nv) == 1)
            {
                puts("YES");
            }
            else
            {
                puts("NO");
            }
        }
    }
}