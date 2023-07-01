typedef struct
{
    int front;
    int rear;
    int capacity;
    int *elements;
} MyCircularQueue;

MyCircularQueue *myCircularQueueCreate(int k)
{
    MyCircularQueue *obj = (MyCircularQueue *)malloc(sizeof(MyCircularQueue));
    obj->capacity = k + 1;
    obj->rear = obj->front = 0;
    obj->elements = (int *)malloc(sizeof(int) * obj->capacity);
    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue *obj, int value)
{
    if ((obj->rear + 1) % obj->capacity == obj->front)
    {
        return false;
    }
    obj->elements[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->capacity;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj)
{
    if (obj->rear == obj->front)
    {
        return false;
    }
    obj->front = (obj->front + 1) % obj->capacity;
    return true;
}

int myCircularQueueFront(MyCircularQueue *obj)
{
    if (obj->rear == obj->front)
    {
        return -1;
    }
    return obj->elements[obj->front];
}

int myCircularQueueRear(MyCircularQueue *obj)
{
    if (obj->rear == obj->front)
    {
        return -1;
    }
    return obj->elements[(obj->rear - 1 + obj->capacity) % obj->capacity];
}

bool myCircularQueueIsEmpty(MyCircularQueue *obj)
{
    return obj->rear == obj->front;
}

bool myCircularQueueIsFull(MyCircularQueue *obj)
{
    return (obj->rear + 1) % obj->capacity == obj->front;
}

void myCircularQueueFree(MyCircularQueue *obj)
{
    free(obj->elements);
    free(obj);
}