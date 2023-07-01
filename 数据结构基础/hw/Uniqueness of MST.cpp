#include <bits/stdc++.h>
using namespace std;

#define Mv 50000
#define Me 100000
typedef long long ll;

int father[Mv];

int nv, ne;

bool flag = true;

int ranks[Mv];

struct Edge
{
    int u, v;
    ll w;

} E[Me];

bool cmp(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}

int find(int x)
{
    if (father[x] == -1)
        return x;
    else
        return father[x] = find(father[x]);
}

void unite(int x, int y)
{
    x = find(x);

    y = find(y);

    if (x == y)

        return;

    if (ranks[x] < ranks[y])
    {
        father[x] = y;

        if (ranks[x] == ranks[y])

            ranks[y]++;
    }
    else
    {
        father[y] = x;

        if (ranks[x] == ranks[y])

            ranks[x]++;
    }
}

ll kr()
{
    ll res = 0;

    sort(E, E + ne, cmp);

    for (int i = 1; i <= nv; i++)

        father[i] = -1;

    for (int i = 0; i < ne; i++)
    {
        if (find(E[i].u) != find(E[i].v))
        {

            for (int j = i + 1; j < ne; j++)
            {
                if (E[i].w == E[j].w)
                {
                    if (((find(E[j].u) == find(E[i].u)) && (find(E[j].v) == find(E[i].v))) || ((find(E[j].v) == find(E[i].u)) && (find(E[j].u) == find(E[i].v))))
                    {
                        flag = false;
                    }
                }
                else
                    break;
            }

            unite(E[i].u, E[i].v);

            res += E[i].w;
        }
    }

    return res;
}

int main()
{

    scanf("%d %d", &nv, &ne);

    for (int i = 0; i < ne; i++)
    {
        int v1, v2;
        ll weight;

        scanf("%d %d %lld", &v1, &v2, &weight);

        E[i].w = weight;
        E[i].u = v1;
        E[i].v = v2;

        // if (find(v1) != find(v2))
        //     father[v1] = v2;
    }

    int count = 0;

    ll res = kr();

    for (int i = 1; i <= nv; i++)
    {
        if (father[i] == -1)
            count++;
    }

    if (count > 1)
    {
        printf("No MST\n");
        printf("%d\n", count);
        return 0;
    }

    else
    {

        if (flag == true && res != -1)
        {
            printf("%lld\n", res);
            printf("Yes\n");
            return 0;
        }
        else if (flag == false && res != -1)
        {
            printf("%lld\n", res);
            printf("No\n");
            return 0;
        }
    }
}
