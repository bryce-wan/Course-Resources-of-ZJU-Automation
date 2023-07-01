## 最短路径问题

1. 无权图

2. 有权图

有权图的单源最短路径算法：

```C
//Dijkstra算法 无法解决负权图

void Dijkstra(Vertex s)
{
    while(1)
    {
        V = 未收录顶点中dist最小者；
        if(这样的V不存在) break；

        collected[V]=true;

        for(V的每个邻接点)
        {
            if(collected[V]==false)
            {
                if(dist[V]+E<V,W> < dist[w])
                {
                    dist[W]=dist[V]+E<V,W>;
                    path[W]=V;
                }
            }
        }

    }
}
```

有权图的多源最短路径

```C
//Floyd算法 无法解决负权图
void Floyd(Graph G)
{   
    int i,j;
    for()
}
```
