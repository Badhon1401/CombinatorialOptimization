#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 6

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < V; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the final solution
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Dijkstra's algorithm to find the shortest paths from source to all vertices
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // Array to store the shortest distance from source to i
    int visited[V];   // Array to keep track of visited vertices

    // Initialize distances as INFINITE and visited array as 0
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        // Update dist value of the adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 1, 4, 0, 0, 0},
        {1, 0, 4, 2, 7, 0},
        {4, 4, 0, 3, 5, 0},
        {0, 2, 3, 0, 4, 6},
        {0, 7, 5, 4, 0, 7},
        {0, 0, 0, 6, 7, 0}
    };

    int source = 0; // Source vertex

    dijkstra(graph, source);

    return 0;
}
