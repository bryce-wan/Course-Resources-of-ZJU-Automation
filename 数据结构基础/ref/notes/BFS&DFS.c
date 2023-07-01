void DFS(Vertex V)
{
    visited[V] = true;

    for (each W in G)
    {
        if (!visited[W] && Connected(W, V))
            DFS(W);
    }
}

void BFS(Vertex V)
{
    visited[V] = true;

    Enqueue(V, Q);

    while (!IsEmpty(Q))
    {
        V = Dequeue(Q);
        for (each W in G)
        {
            if (!visited[W] && Connected(W, V))

                visited[W] = true;
            Enqueue(W, Q);
        }
    }
}