#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

// Depth-First Search recursive function
void DFS(int graph[MAX_NODES][MAX_NODES], int numNodes, bool visited[MAX_NODES], int vertex) {
    printf("%d ", vertex);
    visited[vertex] = true;

    for (int i = 0; i < numNodes; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            DFS(graph, numNodes, visited, i);
        }
    }
}

int main() {
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    int graph[MAX_NODES][MAX_NODES];
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    bool visited[MAX_NODES] = {false};

    int sourceVertex;
    printf("Enter the source vertex for DFS: ");
    scanf("%d", &sourceVertex);

    printf("DFS traversal starting from vertex %d: ", sourceVertex);
    DFS(graph, numNodes, visited, sourceVertex);

    return 0;
}
