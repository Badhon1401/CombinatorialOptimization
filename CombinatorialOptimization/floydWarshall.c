#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 4

// Function to perform the Floyd-Warshall algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize the distance matrix same as the input graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Update distance matrix by considering all vertices as intermediates
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distances between every pair of vertices
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 3, INT_MAX, 5},
        {2, 0, INT_MAX, 4},
        {INT_MAX, 1, 0, INT_MAX},
        {INT_MAX, INT_MAX, 2, 0}
    };

    floydWarshall(graph);

    return 0;
}