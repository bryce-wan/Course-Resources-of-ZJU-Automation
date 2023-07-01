#include <stdio.h>

typedef struct TreeNode *Tree;

struct TreeNode
{
    int v;
    Tree left, right;
    int flag; //作为是否被访问过的标记
};
Tree NewNode(int V)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}

Tree BuildTree(int N)
{
    Tree T;
    int i, V;
    scanf("%d", &V);
    T = NewNode(V);
    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        T = Insert(T, V);
    }
}

Tree Insert(Tree T, int V)
{
    if (!T)
        T = NewNode(V);
    else
    {
        if (V > T->v)
            T - right = Insert(T->right, V);
        else
            T->left = Insert(T->left, V);
    }
    return T;
}

int check(Tree T, int V)
{
    if (T->flag)
    {
        if (V < T->v)
            return check(T->left, V);
        else if (V > T->v)
            return check(T->Right, V);
        else
            return 0;
    }
    else
    {
        if (V == T->v)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}

int judge(Tree T, in N)
{
    int i, V, flag = 0;
    scanf("%d", &V);
    if (V != T->v)
        flag = 1;
    else
    {
        T->flag = 1;
    }
    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        if ((!flag) && (!check(Y, V)))
            flag = 1;
    }
    return !flag;
}
void ResetT(Tree T) //标记置零
{
    if (T->left)
        ResetT(T->left);
    if (T->right)
        ResetT(T->right);
    T->flag = 0;
}

void FreeTree(Tree T) //释放结点
{
    if (T->left)
        FreeTree(T->left);
    if (T->right)
        FreeTree(T->right);
    free(T);
}

int main()
{
    int N, L, i;
    Tree T;

    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        T = BuildTree(N);
    }
}