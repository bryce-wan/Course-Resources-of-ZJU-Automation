import numpy as np
from queue import PriorityQueue


class Graph:
    def __init__(self, n):
        self.v = n
        self.edges = [[-1 for i in range(n)] for j in range(n)]
        self.visited = []

    # add edge to a unidirected graph
    def add_edge(self, u, v, weight):
        self.edges[u][v] = weight


def dijkstra(graph, s):
    distance = [np.inf for i in range(graph.v)]
    distance[s] = 0

    to_visit = PriorityQueue()
    to_visit.put((0, s))

    while not to_visit.empty():
        (dist, current_v) = to_visit.get()
        graph.visited.append(current_v)
        for neighbor in range(graph.v):
            if graph.edges[current_v][neighbor] != -1 and neighbor not in graph.visited:
                d = graph.edges[current_v][neighbor]
                old_dis = distance[neighbor]
                new_dis = distance[current_v] + d
                if new_dis < old_dis:
                    to_visit.put((new_dis, neighbor))
                    distance[neighbor] = new_dis
    return distance


if __name__ == '__main__':
    # initialize graph
    start_v = 1
    n = 16
    G = Graph(n+1)
    G.add_edge(1, 2, -18)
    G.add_edge(2, 3, -15.5)
    G.add_edge(2, 4, -14)
    G.add_edge(3, 5, -13.5)
    G.add_edge(3, 6, -13.5)
    G.add_edge(4, 7, -15.5)
    G.add_edge(4, 8, -14)
    G.add_edge(5, 9, -9)
    G.add_edge(5, 10, -14)
    G.add_edge(6, 11, -15.5)
    G.add_edge(6, 12, -14)
    G.add_edge(7, 13, -13.5)
    G.add_edge(7, 14, -13.5)
    G.add_edge(8, 15, -15.5)
    G.add_edge(8, 16, -14)

    # get distance to all other vertices
    distance = dijkstra(G, start_v)[1:]
    print("")
    print(distance)
    print("min distance ", min(distance))
    print("dist vertice of the path with the minimum distance: ",
          distance.index(min(distance))+1)
    print("")
