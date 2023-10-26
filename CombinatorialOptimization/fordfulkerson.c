#include <stdio.h>
#include <stdbool.h>
#include<limits.h>

// Number of vertices in the graph
#define V 6

// Function to find the minimum of two integers
int min(int a, int b) {
    return a < b ? a : b;
}

// Depth-first search to find an augmenting path
bool dfs(int graph[V][V], int source, int sink, int parent[]) {
    bool visited[V];
    for (int i = 0; i < V; ++i) {
        visited[i] = false;
    }

    int stack[V];
    int top = -1;
    stack[++top] = source;
    visited[source] = true;
    parent[source] = -1;

    while (top >= 0) {
        int u = stack[top--];
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] > 0) {
                stack[++top] = v;
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

// Ford-Fulkerson algorithm
int fordFulkerson(int graph[V][V], int source, int sink) {
    int u, v;

    // Create a residual graph and initialize it with the original capacities
    int rGraph[V][V];
    for (u = 0; u < V; ++u) {
        for (v = 0; v < V; ++v) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V]; // This array is filled by BFS and to store path

    int maxFlow = 0; // There is no flow initially

    // Augment the flow while tere is path from source to sink
    while (dfs(rGraph, source, sink, parent)) {
        // Find minimum residual capacity of the edhes along the path filled by BFS
        int pathFlow = INT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges along the path
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
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

    int maxFlow = fordFulkerson(graph, source, sink);
    printf("Maximum flow in the graph: %d\n", maxFlow);

    return 0;
}
