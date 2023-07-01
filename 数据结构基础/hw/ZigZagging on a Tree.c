#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct TreeNode *Tree;
struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
};

typedef struct StackNode *Stack;
struct StackNode
{
    Tree Data[100];
    int top;
};

Stack CreateStack();

Tree Pop(Stack S);

void Push(Stack S, Tree T);

char IsEmpty(Stack S);

Tree BuildTree(int *in, int *post, int n);

void ZigzagTraversal(Tree T);

int main()
{
    int n;

    scanf("%d", &n);

    int in[1000], post[1000];

    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &post[i]);

    Tree T = BuildTree(in, post, n);

    ZigzagTraversal(T);

    return 0;
}

Tree BuildTree(int *in, int *post, int n)
{
    if (n == 0)

        return NULL;

    Tree root = (Tree)malloc(sizeof(struct TreeNode));

    int len = 0;

    root->Element = post[n - 1];

    for (int i = 0; i < n; i++)
    {
        if (in[i] == post[n - 1])
        {
            len = i;
            break;
        }
    }

    root->Left = BuildTree(in, post, len);

    root->Right = BuildTree(in + len + 1, post + len, n - len - 1);

    return root;
}

Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct StackNode));

    S->top = -1;

    return S;
}

Tree Pop(Stack S)
{
    if (S->top == -1)

        return NULL;

    else
    {
        return S->Data[S->top--];
    }
}

void Push(Stack S, Tree T)
{
    S->Data[++(S->top)] = T;
}

char IsEmpty(Stack S)
{
    return S->top == -1 ? 1 : 0;
}

void ZigzagTraversal(Tree T)
{
    Stack S1 = CreateStack();

    Stack S2 = CreateStack();

    Tree tempT;

    if (T == NULL)
        return;
    else
        Push(S1, T);

    while ((!IsEmpty(S1)) || (!IsEmpty(S2)))
    {
        if (IsEmpty(S2))

            while (!IsEmpty(S1))
            {
                tempT = Pop(S1);

                if (tempT->Right != NULL)
                    Push(S2, tempT->Right);

                if (tempT->Left != NULL)
                    Push(S2, tempT->Left);

                if (IsEmpty(S1) && IsEmpty(S2))
                    printf("%d", tempT->Element);
                else
                    printf("%d ", tempT->Element);
            }

        if (IsEmpty(S1))

            while (!IsEmpty(S2))
            {
                tempT = Pop(S2);

                if (tempT->Left != NULL)
                    Push(S1, tempT->Left);

                if (tempT->Right != NULL)
                    Push(S1, tempT->Right);

                if (IsEmpty(S1) && IsEmpty(S2))
                    printf("%d", tempT->Element);
                else
                    printf("%d ", tempT->Element);
            }
    }
    return;
}