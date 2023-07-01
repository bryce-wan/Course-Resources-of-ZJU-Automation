//用邻接矩阵表示图
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100

typedef int WeightType;
typedef int DataType;
typedef int Vertex;

typedef struct GNode *MGraph;
struct GNode
{
    int ne;
    int nv;
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType D[MaxVertexNum];
};

typedef struct ENode *Edge;
struct ENode
{
    Vertex v1, v2;
    WeightType value;
};

MGraph CreateGraph(int VertexNum) //建立并返回一个空图,有所有的顶点但是没有边
{
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(GNode));
    Graph->nv = VertexNum;
    Graph->ne = 0;

    for (int V = 0; V < Graph->nv; V++)
    {
        for (int W = 0; W < Graph->nv; W++)
        {
            Graph->G[V][W] = 0; //或者infinity
        }
    }
}

void InsertEdge(MGraph G, Edge E) //插入边
{
    Graph->G[E->v1][E->v2] = E->value;
    Graph->G[E->v2][E->v1] = E->value;
}

MGraph BuildGraph()
{
    MGraph Graph;
    int n;
    Edge E;

    sancf("%d", &n);
    Graph = CreateGraph(n);
    scanf("%d", &(Graph->ne));
    if (Graph->ne)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < Graph->ne; i++)
        {
            scanf("%d %d %d", &(E->v1), &(E->v2), &(E->value));
            InsertEdge(Graph, E);
        }
    }

    return Graph;
}