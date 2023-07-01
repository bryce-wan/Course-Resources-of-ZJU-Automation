#include <stdio.h>

int N;

int src[1000], sorted[1000], heap[1000], insert[1000], *ans;

void swap(int *a, int *b)
{
    int c = *a;

    *a = *b;

    *b = c;
}

int is_same(int *a, int *b)
{
    for (int i = 0; i < N; i++)
    {
        if (a[i] != b[i])

            return 0;
    }

    return 1;
}
void adjust_heap(int start, int last)
{
    int parent, child;

    int max = heap[start];

    for (parent = start; last > parent * 2 + 1; parent = child)
    {
        child = parent * 2 + 1;

        if (child + 1 < last && heap[child + 1] > heap[child])
        {
            child += 1;
        }

        if (heap[child] > max)
        {
            heap[parent] = heap[child];
        }
        else
            break;
    }
    heap[parent] = max;
}

void heap_sort(int step)
{
    if (N <= step)
        return;

    swap(heap, heap + N - step);

    adjust_heap(0, N - step);
}

void insertion_sort(int step)
{
    int i;

    int tmp = insert[step];

    for (i = step; i > 0 && tmp < insert[i - 1]; i--)
    {
        insert[i] = insert[i - 1];
    }
    insert[i] = tmp;
}

int main()
{
    int is_insert_sorted = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &src[i]);

        heap[i] = insert[i] = src[i];
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &sorted[i]);
    }

    for (int i = (N - 1) / 2; i >= 0; i--)
    {
        adjust_heap(i, N);
    }

    for (int step = 1; step < N; step++)
    {
        insertion_sort(step);

        if (is_same(insert, sorted))
        {
            is_insert_sorted = 1;
            insertion_sort(step + 1);
            ans = insert;
            break;
        }

        heap_sort(step);

        if (is_same(heap, sorted))
        {
            heap_sort(step + 1);
            ans = heap;
            break;
        }
    }

    if (is_insert_sorted == 1)
    
        printf("Insertion Sort\n");
    

    else
        printf("Heap Sort\n");

    for (int i = 0; i < N; i++)
    {
        if (i != N - 1)
            printf("%d ", ans[i]);
        else
            printf("%d", ans[i]);
    }
}
