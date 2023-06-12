#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 6

struct Graph {
    int vertices;
    int adjacencyMatrix[MAX_SIZE][MAX_SIZE];
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->adjacencyMatrix[src][dest] = weight;
    graph->adjacencyMatrix[dest][src] = weight;
}

int findMinDistance(int distance[], int visited[], int vertices) {
    int minDistance = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < vertices; i++) {
        if (visited[i] == 0 && distance[i] <= minDistance) {
            minDistance = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%c ", vertex + 'a');
        return;
    }

    printPath(parent, parent[vertex]);
    printf("%c ", vertex + 'a');
}

void printShortestPath(int distance[], int parent[], int startVertex, int endVertex) {
    printf("Shortest path from %c to %c: ", startVertex + 'a', endVertex + 'a');
    printPath(parent, endVertex);
    printf("\n");
    printf("Shortest distance: %d\n", distance[endVertex]);
}

void dijkstra(struct Graph* graph, int startVertex, int endVertex) {
    int distance[MAX_SIZE];
    int parent[MAX_SIZE];
    int visited[MAX_SIZE];

    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    distance[startVertex] = 0;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int currentVertex = findMinDistance(distance, visited, graph->vertices);
        visited[currentVertex] = 1;

        for (int i = 0; i < graph->vertices; i++) {
            if (!visited[i] && graph->adjacencyMatrix[currentVertex][i] != 0 &&
                distance[currentVertex] != INT_MAX &&
                distance[currentVertex] + graph->adjacencyMatrix[currentVertex][i] < distance[i]) {
                distance[i] = distance[currentVertex] + graph->adjacencyMatrix[currentVertex][i];
                parent[i] = currentVertex;
            }
        }
    }

    printShortestPath(distance, parent, startVertex, endVertex);
}

int main() {
    struct Graph* graph = createGraph(MAX_SIZE);

    addEdge(graph, 0, 1, 3);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 4);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 2, 4, 8);
    addEdge(graph, 3, 4, 5);
    addEdge(graph, 3, 5, 7);
    addEdge(graph, 4, 5, 9);

  int startVertex = 0;  // 'a'

    for (int endVertex = 0; endVertex < graph->vertices; endVertex++) {
        if (endVertex != startVertex) {
            dijkstra(graph, startVertex, endVertex);
            printf("-----------------\n");
        }
    }

    return 0;
}