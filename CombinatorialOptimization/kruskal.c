#include <stdio.h>
#include<stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

// Compare function for sorting edges based on weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Find operation of union-find
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union operation of union-find
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Kruskal's algorithm to find Minimum Spanning Tree
void kruskalMST(struct Edge edges[], int V, int E) {
    // Allocate memory for subsets
    struct Subset subsets[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Sort the edges in ascending order of weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    int mstWeight = 0; // Weight of the minimum spanning tree
    for (int e = 0; e < E; ++e) {
        int x = find(subsets, edges[e].src);
        int y = find(subsets, edges[e].dest);

        // If adding this edge does not form a cycle, include it in the MST
        if (x != y) {
            printf("Edge %d-%d with weight %d included in MST\n", edges[e].src, edges[e].dest, edges[e].weight);
            mstWeight += edges[e].weight;
            unionSets(subsets, x, y);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
}

int main() {
    int V = 4; // Number of vertices in the graph
    int E = 5; // Number of edges in the graph

    // Example edges and their weights
    struct Edge edges[] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    kruskalMST(edges, V, E);

    return 0;
}
