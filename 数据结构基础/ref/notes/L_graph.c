//用邻接表表示图
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100

typedef int WeightType;
typedef int DataType;
typedef int Vertex;

typedef struct GNode *LGraph;
struct GNode
{
    int ne;
    int nv;
    ADJlist G;
};

typedef struct VNode
{
    PtrtoAdjVNode firstedge;
    DataType data;
} ADJlist[MaxVertexNum];

typedef struct AdjVNode *PtrtoAdjVNode;
struct AdjVNode
{
    WeightType weight;
    PtrtoAdjVNode next;
    Vertex v;
};
