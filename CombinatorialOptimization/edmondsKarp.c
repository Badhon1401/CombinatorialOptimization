#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 6 // Number of vertices in the graph

bool bfs(int rGraph[V][V], int source, int sink, int parent[]) {
    bool visited[V];
    for (int i = 0; i < V; ++i) {
        visited[i] = false;
    }

    int queue[V];
    int front = 0, rear = 0;
    queue[rear++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
                if (v == sink) {
                    return true;
                }
            }
        }
    }
    return false;
}

int edmondsKarp(int graph[V][V], int source, int sink) {
    int rGraph[V][V]; // Residual graph
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V]; // Store augmenting path
    int maxFlow = 0; // Initialize the maximum flow

    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, source, sink, parent)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = pathFlow < rGraph[u][v] ? pathFlow : rGraph[u][v];
        }

        // update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Example graph represented as an adjacency matrix with capacities
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0; // Source vertex
    int sink = 5;   // Sink vertex

    int maxFlow = edmondsKarp(graph, source, sink);
    printf("Maximum flow in the graph: %d\n", maxFlow);

    return 0;
}
