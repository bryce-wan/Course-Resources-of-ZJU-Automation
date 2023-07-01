//优先队列可以通过数组、链表或者有序数组、链表实现

typedef struct HeapStruct *MaxHeap;
struct HeapStruct // 数组实现最大堆
{
    ElementType *elements;
    int size;
    int capcity;
};

MaxHeap Create(int MaxSize)
{
    MaxHeap H = malloc(struct HeapStruct);
    H->elements = malloc(sizeof(ElementType) * (MAxSize + 1)); //我们在0位置存放哨兵，在1位置开始存放元素，所以是maxsize+1
    H->size = 0;
    H->capcity = MaxSize;

    H->elements[0] = MaxData;
}

void Insert(MaxHeap H, ElementType item)
{
    int i;
    if (IsFull(H))
    {
        printf("the maxheap is full");
        return;
    }
    i = ++H->size;
    for (; H->elements[i / 2] < item; i /= 2)
    {
        H->elements[i] = H->elements[i / 2];
    }
    H->elements[i] = item;
}

ElementType DeleteMAx(MaxHeap H)
{
    int parent, child;
    ElementType MaxItem, temp;

    if (IsEmpty(H))
    {
        printf("the maxheap is empty");
        return;
    }

    MaxHeap = H->elements[1]; //最大值，即树的根

    temp = H->elements[H->size--]; //最末端的值赋给temp，删除其位置，size-=1

    for (parent = 1; parent * 2 <= H->size; parent = child) //从根开始从上向下过滤，给temp找位置
    {
        child = parent * 2;
        if ((child != H->size) && (H->elements[child] < H->elements[child + 1])) //使得child指向左右子结点的较大者
        {
            child++;
        }
        if (temp >= H->elements[child]) //为temp找一个位置
            break;
        else
            H->elements[parent] = H->elements[child];
    }
    H->elements[parent] = temp;
    return MaxItem;
}