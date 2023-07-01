//并查集：仅针对求并和查找的集合，不相交！特点思想是用集合中的一个元素来代表集合
//查找：看两个元素是否属于一个集合，只要向上走看他们的根节点是否相同
#define ElementType int
#define MaxSize 100
typedef struct
{
    ElementType data;
    int parent;

} SetType;

//集合的查找运算
int Find(SetType *S, ElementType X) //按值查找集合中的元素位置
{
    int i;
    for (i = 0; (i < MaxSize) && (S[i].data != X); i++)
        ;

    if (i >= MaxSize)
        return -1;

    for (; S[i].parent >= 0; i = S[i].parent)
        ;

    return i;
}

//集合的并运算：
// 1. 分别找到X1和X2的所在集合树的根节点
// 2. 如果他们不同根，则将其中一个根结点的父节点指针设置成另一个根结点的数组下标（不必是二叉树）

void Union(SetType *S, ElementType X1, ElementType X2) //并集操作
{
    int root1, root2;
    root1 = Find(X1);
    root2 = Find(X2);

    if (root1 != root2)
        S[root2].parent = root1;
}

//为了改善合并以后的查找性能，可以将相对小的集合合并到相对大的集合中去
//优化Union()
//充分利用结构中的，原来根结点parent=-1，现在是负数，绝对值表示这棵树/集合的元素个数
