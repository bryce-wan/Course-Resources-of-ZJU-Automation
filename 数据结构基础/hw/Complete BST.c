#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int calculate(int n)
{
    int k = (int)log2(n + 1);

    int left = (int)pow(2, k - 1) - 1;

    int remain = n + 1 - (int)pow(2, k);

    if (remain >= (int)pow(2, k - 1))

        left += (int)pow(2, k - 1);
    else
        left += remain;

    return (int)left;
}

void solve(int left, int right, int root, int *tree, int *temp)
{
    int n = right - left + 1;

    if (n == 0)

        return;

    int ltree = calculate(n);

    tree[root] = temp[left + ltree];

    int leftroot = root * 2 + 1;

    int rightroot = leftroot + 1;

    solve(left, left + ltree - 1, leftroot, tree, temp);

    solve(left + ltree + 1, right, rightroot, tree, temp);
}

int main()
{
    int tree[1000] = {0};

    int temp[1000] = {0};

    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &temp[i]);

    qsort(temp, n, sizeof(int), cmp);

    solve(0, n - 1, 0, tree, temp);

    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            printf("%d ", tree[i]);
        }
        else
            printf("%d", tree[i]);
    }
}