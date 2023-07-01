//使用单链表实现队列，链表头可以进行插入和删除，而链表尾只能进行插入。所以，front==head， rear==tail
#include <stdio.h>
#define ElementType int
#define MAXSIZE 100

struct Node
{
    ElementType data;
    struct Node *next;
};
struct QNode
{
    struct Node *rear;
    struct Node *front;
}

struct QNode *queue;

queue ptrQ;
//实际上可以理解为 生成一个链表之后，将指向其头尾的指针保存在一个结构里面

void AddQ(queue ptrQ, ElementType item)
{
    struct Node *newnode;
    newnode = (struct Node *)malloc(sizeof(struct Node));

    newnode->next = NULL;
    newnode->data = item;

    queue->rear = newnode;
}