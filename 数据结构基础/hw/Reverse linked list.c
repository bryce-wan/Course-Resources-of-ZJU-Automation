#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node
{
    ElementType Element;
    Position Next;
};

List Read();        /* details omitted */
void Print(List L); /* details omitted */
List Reverse(List L);

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */
List Reverse(List L)
{
    PtrToNode p1, p2, temp;

    if (L && (L->Next))
    {
        p1 = L->Next;

        p2 = p1->Next;
        while (p2 != NULL)
        {
            temp = p2->Next;
            p2->Next = p1;
            p1 = p2;
            p2 = temp;
        }
        L->Next->Next = NULL;
        L->Next = p1;
        return L;
    }
    return L;
}