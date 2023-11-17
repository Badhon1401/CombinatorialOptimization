#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 5

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to print the solution including paths
void printSolution(int dist[], int parent[]) {
    printf("Vertex \t Distance from Source \t Path\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d \t\t\t ", i, dist[i]);

        // Print the path from the source to vertex i
        int j = i;
        while (j != -1) {
            printf("%d ", j);
            j = parent[j];
        }

        printf("\n");
    }
}

// Bellman-Ford algorithm to find shortest paths from source to all vertices
void bellmanFord(struct Edge edges[], int E, int src) {
    int dist[V];
    int parent[V];

    // Initialize distances from source to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1; // Initialize parent array
    }
    dist[src] = 0; // Distance from source to itself is always 0

    // Relax all edges V-1 times to find shortest distances
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Update the parent for vertex v
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative-weight cycle\n");
            return;
        }
    }

    // Print the shortest distances and paths
    printSolution(dist, parent);
}

int main() {
    int E = 8; // Number of edges in the graph
    struct Edge edges[] = {
        {0, 1, -1}, {0, 2, 4},
        {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5},
        {3, 1, 1}, {4, 3, -3}
    };

    int src = 0; // Source vertex

    bellmanFord(edges, E, src);

    return 0;
}
