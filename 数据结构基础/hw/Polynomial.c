#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node
{
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read();        /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Add(Polynomial a, Polynomial b);

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Your function will be put here */
Polynomial Add(Polynomial a, Polynomial b)
{
    PtrToNode p1, p2, head = NULL, p = NULL, tail = NULL;

    if (!a)
        return b;
    else if (!b)
        return a;
    else
    {
        p1 = a->Next;
        p2 = b->Next;
    }

    head = (PtrToNode)malloc(sizeof(struct Node));
    head->Next = NULL;
    tail = head;

    while (p1 && p2)
    {
        if (p1->Exponent > p2->Exponent)
        {
            p = p1;
            p1 = p1->Next;
            tail->Next = p;
            tail = tail->Next;
        }
        else if (p1->Exponent < p2->Exponent)
        {
            p = p2;
            p2 = p2->Next;
            tail->Next = p;
            tail = tail->Next;
        }
        else if (p1->Exponent == p2->Exponent)
        {

            if (p1->Coefficient + p2->Coefficient != 0)
            {
                p = p1;
                p->Coefficient = p1->Coefficient + p2->Coefficient;
                tail->Next = p;
                tail = tail->Next;
            }
            p1 = p1->Next;
            p2 = p2->Next;
        }
    }

    if (p1 == NULL)
        tail->Next = p2;
    if (p2 == NULL)
        tail->Next = p1;
    return head;
}