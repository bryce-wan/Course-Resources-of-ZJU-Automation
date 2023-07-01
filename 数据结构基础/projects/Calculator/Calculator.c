#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef struct
{
    int top;
    double *data;
} DataStack;

typedef struct
{
    int top;
    char *data;
} OpStack;

int IsFull_data(DataStack *S)
{
    if (S->top == MAXSIZE - 1)
    {
        return 1;
    }
    return 0;
}

int IsFull_op(OpStack *S)
{
    if (S->top == MAXSIZE - 1)
    {
        return 1;
    }
    return 0;
}

DataStack *InitStack_data()
{
    DataStack *S;

    S = (DataStack *)malloc(sizeof(DataStack));

    S->data = (double *)malloc(sizeof(double) * MAXSIZE);

    S->top = -1;

    return S;
}

OpStack *InitStack_op()
{
    OpStack *S;

    S = (OpStack *)malloc(sizeof(OpStack));

    S->data = (char *)malloc(sizeof(char) * MAXSIZE);

    S->top = -1;

    return S;
}

double Calculate(DataStack *S1, OpStack *S2, char *str)
{
}

int main()
{
    DataStack *S1 = InitStack_data();

    OpStack *S2 = InitStack_op();

    char temp[MAXSIZE];

    scanf("%s", temp);

    printf("res: %lf\n", Calculate(S1, S2, temp));
}