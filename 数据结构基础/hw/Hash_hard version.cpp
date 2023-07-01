#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int size = 0;

int cnt = 0;

struct node
{
    int value;
    int pos;
    int mod;
};

bool operator<(const node &a, const node &b)
{
    return a.value > b.value;
}

int main()
{
    int n;

    scanf("%d", &n);

    vector<node> data;

    for (int i = 0; i < n; i++)
    {
        int temp;

        scanf("%d", &temp);

        if (temp != -1)
        {
            data.push_back({temp, i, temp % n});
            ::size++;
        }
    }

    int indegree[100000];

    priority_queue<node> q;

    for (int i = 0; i < ::size; i++)
    {
        indegree[i] = (data[i].pos - data[i].mod + n) % n;
    }

    for (int i = 0; i < ::size; i++)
    {
        if (!indegree[i])
            q.push(data[i]);
    }

    int flag = 0;

    while (!q.empty())
    {
        node k = q.top();
        q.pop();

        if (flag)
            printf(" ");

        flag = 1;

        printf("%d", k.value);

        ::cnt++;

        for (int i = 0; i < ::size; i++)
        {
            if ((k.pos - data[i].mod + n) % n < (data[i].pos - data[i].mod + n) % n)
                if (--indegree[i] == 0)
                    q.push(data[i]);
        }
    }
}