#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

#define size 1000
#define inf 0x3f3f3f3f
#define ll unsigned long long

ll res[size] = {0};
ll pre[size] = {0};
ll flow[size][size] = {0};
ll edge[size][size] = {0};
int cnt = 1;

map<string, int> M;

int Ne;

ll maxflow(ll src, ll dest)
{
    ll sum = 0;

    queue<int> Q;

    while (true)
    {
        memset(res, 0, sizeof(res));

        res[src] = inf;

        Q.push(src);

        // find a augmenting path with BFS
        while (!Q.empty())
        {
            ll u = Q.front();

            Q.pop();

            for (ll v = 1; v <= Ne; v++)

                if (!res[v] && edge[u][v] > flow[u][v])
                {
                    res[v] = min(res[u], edge[u][v] - flow[u][v]);

                    Q.push(v);

                    pre[v] = u;
                }
        }

        // there is no augmenting path anymore
        if (res[dest] == 0)
            return sum;

        // else do the increasing work
        else
        {
            for (ll v = dest; v != src; v = pre[v])
            {
                flow[pre[v]][v] += res[dest];

                flow[v][pre[v]] -= res[dest];
            }
            sum += res[dest];
        }
    }
    return sum;
}

int main()
{

    string source, destination, src, dest;

    ll cap;

    cin >> source >> destination >> Ne;

    if (M[source] == 0)
        M[source] = cnt++;

    if (M[destination] == 0)
        M[destination] = cnt++;

    for (ll i = 1; i <= Ne; i++)
    {
        cin >> src >> dest >> cap;

        if (M[src] == 0)
            M[src] = cnt++;

        if (M[dest] == 0)
            M[dest] = cnt++;

        edge[M[src]][M[dest]] += cap;
    }

    cout << maxflow(1, 2) << endl;

    return 0;
}