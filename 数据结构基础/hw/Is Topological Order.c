#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;
#define MaxVertexNum 10 /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq(LGraph Graph, Vertex Seq[]);

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < G->Nv; j++)
            scanf("%d", &Seq[j]);
        if (IsTopSeq(G, Seq) == true)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}

/* Your function will be put here */
bool IsTopSeq(LGraph Graph, Vertex Seq[])
{
    Vertex tmp[MaxVertexNum];

    PtrToAdjVNode p;

    for (int i = 0; i < Graph->Nv; i++)
    {
        tmp[i] = 0;
    }

    for (int i = 0; i < Graph->Nv; i++)
    {
        p = Graph->G[i].FirstEdge;

        while (p != NULL)
        {
            tmp[p->AdjV]++;

            p = p->Next;
        }
    }

    for (int i = 0; i < Graph->Nv; i++)
    {
        if (tmp[Seq[i] - 1] == 0)
        {
            p = Graph->G[Seq[i] - 1].FirstEdge;

            while (p)
            {
                tmp[p->AdjV]--;

                p = p->Next;
            }
        }
        else
            return false;
    }

    return true;
}