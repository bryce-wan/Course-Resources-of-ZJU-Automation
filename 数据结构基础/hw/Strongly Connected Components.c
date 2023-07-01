#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10 /* maximum number of vertices */
typedef int Vertex;    /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode
{
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode
{
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV(Vertex V)
{
    printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V));

int main()
{
    Graph G = ReadG();

    G->NumOfEdges = 5;
    G->NumOfVertices = 4;
    G->Array = (PtrToVNode *)malloc(sizeof(struct VNode) * 4);
    G->Array[0] = (PtrToVNode)malloc(sizeof(struct VNode));
    G->Array[0]->Vert = 1;
    G->Array[0]->Next = NULL;
    G->Array[1] = (PtrToVNode)malloc(sizeof(struct VNode));
    G->Array[1]->Vert = 2;
    G->Array[1]->Next = NULL;
    G->Array[2] = (PtrToVNode)malloc(sizeof(struct VNode));
    G->Array[2]->Vert = 0;
    G->Array[2]->Next = NULL;
    G->Array[3] = (PtrToVNode)malloc(sizeof(struct VNode));
    G->Array[3]->Vert = 2;
    G->Array[3]->Next = NULL;
    G->Array[3]->Next = (PtrToVNode)malloc(sizeof(struct VNode));
    G->Array[3]->Next->Vert = 1;
    G->Array[3]->Next->Next = NULL;

    StronglyConnectedComponents(G, PrintV);
    return 0;
}

/* Your function will be put here */

#define min(a, b) (((a) < (b)) ? (a) : (b))

int vis[100] = {0};

int num[100] = {0}, low[100] = {0};

int S[100], top = 0, count = 0;

int is_instack(int V)
{
    for (int i = 1; i <= top; i++)
        if (S[i] == V)
            return 1;

    return 0;
}

void pop(void (*visit)(Vertex V))
{
    visit(S[top]);

    top--;
}

void DFS(Graph G, Vertex V, void (*visit)(Vertex V))
{
    vis[V] = 1;

    num[V] = low[V] = count;

    S[++top] = V;

    for (PtrToVNode p = G->Array[V]; p; p = p->Next)
    {
        if (!vis[p->Vert])
        {
            DFS(G, p->Vert, visit);

            low[V] = min(low[V], low[p->Vert]);
        }
        else if (is_instack(p->Vert))
        {
            low[V] = min(low[V], num[p->Vert]);
        }
    }

    if (num[V] == low[V])
    {
        while (S[top] != V)
            pop(visit);

        pop(visit);
        printf("\n");
    }

    count += 1;
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{

    for (int v = 0; v < G->NumOfVertices; v++)
    {
        if (vis[v] == 0)
        {
            DFS(G, v, visit);
        }
    }
}
