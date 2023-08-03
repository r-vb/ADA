#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NODES 100

// Queue implementation for BFS
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

bool isQueueFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// BFS function
void BFS(int adjMatrix[MAX_NODES][MAX_NODES], int numNodes, int startNode) {
    bool visited[MAX_NODES] = { false };
    Queue* queue = createQueue(numNodes);

    visited[startNode] = true;
    enqueue(queue, startNode);

    printf("Breadth-First Traversal: ");

    while (!isQueueEmpty(queue)) {
        int currentNode = dequeue(queue);
        printf("%d ", currentNode);

        for (int i = 0; i < numNodes; i++) {
            if (adjMatrix[currentNode][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }

    free(queue);
}

int main() {
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    int adjMatrix[MAX_NODES][MAX_NODES];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    int startNode;
    printf("Enter the starting node for BFS: ");
    scanf("%d", &startNode);

    BFS(adjMatrix, numNodes, startNode);
    
    printf("\n");

    return 0;
}
