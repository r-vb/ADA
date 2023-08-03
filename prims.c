#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Representation of the graph
typedef struct Graph {
    int numVertices;
    int graph[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to create a new graph
Graph createGraph(int numVertices) {
    Graph graph;
    graph.numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph.graph[i][j] = 0; // Initialize all edges to 0 (no edge)
        }
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->graph[src][dest] = weight;
    graph->graph[dest][src] = weight;
}

// Function to find the vertex with the minimum key value, from the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[], int numVertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the MST
void printMST(int parent[], Graph graph, int numVertices) {
    printf("Minimum Spanning Tree Edges:\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d -- %d  Weight: %d\n", parent[i], i, graph.graph[i][parent[i]]);
    }
}

// Prim's algorithm function
void primMST(Graph graph, int numVertices) {
    int parent[MAX_VERTICES]; // Array to store the MST
    int key[MAX_VERTICES]; // Key values used to pick minimum weight edge in cut
    bool mstSet[MAX_VERTICES]; // Array to keep track of vertices included in MST

    // Initialize key values as infinite and mstSet as false
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Start with the first vertex
    key[0] = 0;
    parent[0] = -1; // First node is always the root of MST

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = true;

        // Update key value and parent index of adjacent vertices
        for (int v = 0; v < numVertices; v++) {
            if (graph.graph[u][v] && !mstSet[v] && graph.graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph.graph[u][v];
            }
        }
    }

    printMST(parent, graph, numVertices);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    Graph graph = createGraph(numVertices);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    primMST(graph, numVertices);

    return 0;
}
