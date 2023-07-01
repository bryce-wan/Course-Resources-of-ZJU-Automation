//只允许在一端进行删除，在另一端进行添加，FIFO
#include <stdio.h>
#define ElementType int
#define MAXSIZE 100

struct QNode
{
    ElementType data[MAXSIZE];
    int rear;
    int front;
};

typedef struct QNode *queue;

//顺环队列:避免队列中存在空位置浪费，首尾相连。但这种情况无法区分队列空满（front==rear）
//解决方案：使用额外标记 或者 仅使用n-1个数组空间

void AddQ(queue pq, ElementType item) //顺环队列的入环操作
{
    if ((pq->rear + 1) % MAXSIZE == pq->front)
    {
        printf("full!");

        return;
    }
    pq->rear = (pq->rear + 1) % MAXSIZE;

    pq->data[pq->rear] = item;
}

ElementType DeleteQ(queue pq)
{
    if (pq->front == pq->rear)
    {
        return ERROR;
    }

    else
    {
        pq->front = (pq->front + 1) % MAXSIZE;

        return pq->data[pq->front];
    }
}