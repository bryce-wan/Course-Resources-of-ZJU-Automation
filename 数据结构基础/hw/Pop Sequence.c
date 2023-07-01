#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

struct Stack
{
    int *data;
    int top;
    int maxsize;
};

typedef struct Stack *pStack;

int main()
{
    int max, len, k;
    int i, j;

    scanf("%d %d %d", &max, &len, &k);

    int *store = (int *)malloc(sizeof(int) * len);

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < len; j++)
        {
            scanf("%d", &store[j]);
        }

        int num = 1;
        int tmp = 0;
        int error = 0;

        pStack S = (pStack)malloc(sizeof(struct Stack));

        S->data = (int *)malloc(sizeof(int) * max);
        S->maxsize = max;
        S->top = 0;
        S->data[S->top] = num;
        num++;

        while ((tmp < len) && (S->top < S->maxsize))
        {
            if (S->top == -1)
            {
                S->top++;
                if ((S->top) < (S->maxsize))
                    S->data[S->top] = num;
                num++;
            }

            if (store[tmp] > S->data[S->top])
            {
                S->top++;
                S->data[S->top] = num;
                if ((S->top) > (S->maxsize - 1))
                {
                    error = 1;
                    break;
                }
                num++;
            }
            else if (store[tmp] == S->data[S->top])
            {
                S->top--;
                tmp++;
            }
            else if (store[tmp] < S->data[S->top])
            {
                error = 1;
                break;
            }
        }
        if (error)
            printf("NO");
        else
            printf("YES");
        if (i != k - 1)
            printf("\n");
    }

    return 0;
}