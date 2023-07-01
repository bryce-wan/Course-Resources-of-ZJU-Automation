#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <stdlib.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MaxVertexNum 1100
#define MaxEdgeNum 5100
#define MaxPathLength 50000

typedef unsigned long long ll;

typedef struct EdgeStruct
{
    int from; // The start of an edge

    int to; // The end of an edge

    int next; // The next edge in the Chained Forward Star

    double cost; // The weight of the edge

} E;

int Nv, Ne; // The number of vertices and edges in the graph

void Init(int *head, ll *dist, ll *dist2, int *path, int *path2, int *from); // Initialize the arrays that store the graph

void ReadGraph(E *Edge, int *head, ll *dist, ll *dist2, int *path, int *path2, int *from); // Read the input graph

void AddEdge(E *Edge, int *head, int u, int v, int w, int cnt); // Add an edge to the graph

void Dijkstra(E *Edge, int *head, ll *dist, ll *dist2, int *path, int *path2, int *from); // Use Dijkstra to find the second-shortest path

void PrintAns(ll *dist, ll *dist2, int *path, int *path2, int *from); // Print the answer

int main()
{
    scanf("%d %d", &Nv, &Ne); // Read the numbers of vertices and edges

    E Edge[MaxEdgeNum]; // An array of edge structs to store the graph

    int head[MaxVertexNum];

    int path[MaxVertexNum]; // To store the index of the previous vertex in a certain vertex's shortest path

    int path2[MaxVertexNum]; // To store the index of the previous vertex in a certain vertex's second-shortest path

    int from[MaxVertexNum]; // To mark if a vertex's second-shortest path is updated from another vertex's second-shortest path

    ll dist[MaxVertexNum]; // To store the shortest distance

    ll dist2[MaxVertexNum]; // To store the second-shortest distance

    ReadGraph(Edge, head, dist, dist2, path, path2, from);

    Dijkstra(Edge, head, dist, dist2, path, path2, from);

    PrintAns(dist, dist2, path, path2, from);

    // system("pause"); // pause it if you want to see the result in the .exe
}

void ReadGraph(E *Edge, int *head, ll *dist, ll *dist2, int *path, int *path2, int *from)
{
    int cnt = 1;

    Init(head, dist, dist2, path, path2, from); // Initialize the arrays that store the graph

    for (int i = 1; i <= Ne; i++) // Read edges
    {
        int v1, v2, w;

        scanf("%d %d %d", &v1, &v2, &w); // Read an edge

        AddEdge(Edge, head, v1, v2, w, cnt++);

        // AddEdge(Edge, head, v2, v1, w, cnt++);
    }
}

void Init(int *head, ll *dist, ll *dist2, int *path, int *path2, int *from) // Initialize the arrays that store the graph
{
    fill(dist, dist + MaxVertexNum, INF); // Initialize the shortest distance from all the vertices to the source to be INF

    fill(dist2, dist2 + MaxVertexNum, INF); // Initialize the second-shortest distance from all the vertices to the source to be INF

    fill(path, path + MaxVertexNum, -1); // Initialize the index of the previous node of a vertex in its shortest path to be -1

    fill(path2, path2 + MaxVertexNum, -1); // Initialize the index of the previous node of a vertex in its second-shortest path to be -1

    fill(from, from + MaxVertexNum, -1);

    memset(head, -1, sizeof(int) * (MaxVertexNum));
}

void AddEdge(E *Edge, int *head, int u, int v, int w, int cnt) // Add an edge to the Chained Forward Star
{
    // Add the edge

    Edge[cnt].from = u;

    Edge[cnt].to = v;

    Edge[cnt].cost = w;

    // Build the Chain Forward Star

    Edge[cnt].next = head[u];

    head[u] = cnt;
}

void PrintAns(ll *dist, ll *dist2, int *path, int *path2, int *from)
{
    int ans_path[MaxPathLength] = {0}; // An array to store the answer path

    int ans_path_length = 1; // To record the final length of the path

    ans_path[1] = Nv; // The destination of the path is vertex Nv

    ll ans; // The answer length of the second-shortest path

    int *PATH; // A pointer to change the array where we do the  iteration

    if (dist2[Nv] != INF) // The second-shortest path from the source to the destination exists
    {
        ans = dist2[Nv]; // The total length of the second-shortest path is in dist2[]

        PATH = path2; // Start from the the second-shortest path array

        int i = Nv;

        bool change = 1; // Mark the change of the PATH array

        while (PATH[i] != -1)
        {

            ans_path[++ans_path_length] = PATH[i];

            if (change == 1 && from[i] != 1)
            {
                PATH = path; // Turn to the shortest path

                change = 0; // Stop the change

                i = path2[i];

                continue;
            }

            i = PATH[i]; // Iterate
        }
    }

    else // The second-shortest path from the source to the destination does not exist
    {
        printf("There is no 2nd-shortest path! "); // Error msg

        return;
    }

    printf("%llu ", ans); // Print the answer length

    for (int i = ans_path_length; i >= 1; i--) // Print the answer path
    {
        if (i != 1)

            printf("%d ", ans_path[i]);

        else

            printf("%d", ans_path[i]);
    }
}

void Dijkstra(E *Edge, int *head, ll *dist, ll *dist2, int *path, int *path2, int *from)
{
    priority_queue<int> Q; // Initialize a priority queue

    dist[1] = 0; // The shortest distance from source to itself is 0

    Q.push(1); // Push the source into the priority queue

    while (!Q.empty()) // While the priority queue is not empty
    {

        int u = Q.top(); // Get the top element

        Q.pop(); // Pop the top element

        for (int i = head[u]; i != -1; i = Edge[i].next) // Visit all the connected vertices and update the distances
        {
            int v = Edge[i].to; // v is the object vertex

            if ((dist[v] > dist[u] + Edge[i].cost) && (u != Nv)) // Update the shortest path to the new road and then update the second-shortest path to the previous shortest path
            {
                dist2[v] = dist[v]; // Update the second-shortest distance from source to v to the shortest distance
                path2[v] = path[v]; // Update the previous node in the second-shortest path
                from[v] = 0;        // The second-shortest path is not updated from the second-shortest path of from source to u

                dist[v] = dist[u] + Edge[i].cost; // Update the shortest distance from source to v to the new distance
                path[v] = u;                      // Update the previous node in the shortest path

                Q.push(v); // Push v into the priority queue
            }

            if ((dist[u] + Edge[i].cost > dist[v]) && (dist[u] + Edge[i].cost < dist2[v]) && (u != Nv)) // Only update the second-shortest path to the new road
            {
                dist2[v] = dist[u] + Edge[i].cost; // Update the second-shortest distance from source to v to the new distance
                path2[v] = u;                      // Update the previous node in the second-shortest path
                from[v] = 0;                       // The second-shortest path is not updated from the second-shortest path from source to u

                Q.push(v); // Push v into the priority queue
            }

            if ((dist2[u] + Edge[i].cost < dist2[v]) && (u != Nv)) // Only update the second-shortest path
            {
                dist2[v] = dist2[u] + Edge[i].cost; // Update the second-shortest distance from source to v to the new second-shortest distance
                path2[v] = u;                       // Update the previous node in the second-shortest path
                from[v] = 1;                        // The second-shortest path is updated from the second-shortest path from source to u

                Q.push(v); // Push v into the priority queue
            }
        }
    }
}