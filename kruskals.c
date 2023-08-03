#include <stdio.h>
#include <stdlib.h>

// Representation of an edge in the graph
typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

// Representation of the graph
typedef struct Graph {
    int numVertices;
    int numEdges;
    Edge* edges;
} Graph;

// Function to create a new graph
Graph* createGraph(int numVertices, int numEdges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    graph->edges = (Edge*)malloc(numEdges * sizeof(Edge));
    return graph;
}

// Compare function used for sorting the edges based on weight
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Find function for Union-Find
int find(int parent[], int vertex) {
    if (parent[vertex] == vertex)
        return vertex;
    return find(parent, parent[vertex]);
}

// Union function for Union-Find
void unionSet(int parent[], int rank[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);

    if (rank[xRoot] < rank[yRoot])
        parent[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

// Kruskal's algorithm function
void kruskalMST(Graph* graph) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;
    Edge* edges = graph->edges;

    // Sort edges in ascending order based on weight
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    // Allocate memory for parent and rank arrays used in Union-Find
    int* parent = (int*)malloc(numVertices * sizeof(int));
    int* rank = (int*)malloc(numVertices * sizeof(int));

    // Initialize parent array to have each vertex as its own parent
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstEdges = 0;
    printf("Minimum Spanning Tree Edges:\n");

    for (int i = 0; i < numEdges && mstEdges < numVertices - 1; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        // Check if adding this edge will form a cycle
        if (find(parent, src) != find(parent, dest)) {
            printf("%d -- %d  Weight: %d\n", src, dest, edges[i].weight);
            unionSet(parent, rank, src, dest);
            mstEdges++;
        }
    }

    // Free allocated memory
    free(parent);
    free(rank);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    Graph* graph = createGraph(numVertices, numEdges);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }

    kruskalMST(graph);

    return 0;
}
