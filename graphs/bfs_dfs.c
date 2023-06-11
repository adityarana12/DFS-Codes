#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Graph {
    int vertices;
    int adjMatrix[MAX_SIZE][MAX_SIZE];
    int visited[MAX_SIZE];
};

struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->rear == MAX_SIZE - 1) {
        printf("Queue is full.\n");
    } else {
        if (queue->front == -1) {
            queue->front = 0;
        }
        queue->rear++;
        queue->items[queue->rear] = item;
    }
}

int dequeue(struct Queue* queue) {
    int item;
    if (queue->front == -1) {
        printf("Queue is empty.\n");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

int isEmpty(struct Queue* queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

void BFS(struct Graph* graph, int startVertex) {
    struct Queue* queue = createQueue();

    graph->visited[startVertex] = 1;
    printf("BFS traversal: ");
    printf("%d ", startVertex);

    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && graph->visited[i] == 0) {
                graph->visited[i] = 1;
                printf("%d ", i);
                enqueue(queue, i);
            }
        }
    }

    printf("\n");
}

void DFS(struct Graph* graph, int startVertex) {
    printf("%d ", startVertex);

    graph->visited[startVertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[startVertex][i] == 1 && graph->visited[i] == 0) {
            DFS(graph, i);
        }
    }
}

int main() {
    struct Graph* graph = createGraph(7);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 2, 6);

    int startVertex;

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    BFS(graph, startVertex);

    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    printf("Dfs traversal is:");
    DFS(graph, startVertex);

    printf("\n");

    return 0;
}