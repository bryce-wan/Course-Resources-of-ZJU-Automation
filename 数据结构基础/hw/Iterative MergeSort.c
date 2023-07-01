#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass(ElementType list[], ElementType sorted[], int N, int length);

void output(ElementType list[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void merge_sort(ElementType list[], int N)
{
    ElementType extra[MAXN]; /* the extra space required */
    int length = 1;          /* current length of sublist being merged */
    while (length < N)
    {
        merge_pass(list, extra, N, length); /* merge list into extra */
        output(extra, N);
        length *= 2;
        merge_pass(extra, list, N, length); /* merge extra back to list */
        output(list, N);
        length *= 2;
    }
}

int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */

int min(int a, int b)
{
    return a <= b ? a : b;
}

void merge_pass(ElementType list[], ElementType sorted[], int N, int length)
{
    for (int i = 0; i < N; i += 2 * length)
    {
        int lpos = i, rpos = i + length;

        int k = i;

        int end = min(i + 2 * length, N);

        while (lpos < i + length && rpos < end && lpos < N)
        {
            if (list[lpos] < list[rpos])
                sorted[k++] = list[lpos++];
            else
                sorted[k++] = list[rpos++];
        }

        while (lpos < i + length)
            sorted[k++] = list[lpos++];

        while (rpos < end)
            sorted[k++] = list[rpos++];
    }
}