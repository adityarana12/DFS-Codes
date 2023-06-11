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
            if (i == j) {
                graph->adjacencyMatrix[i][j] = 0;
            } else {
                graph->adjacencyMatrix[i][j] = INT_MAX;
            }
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->adjacencyMatrix[src][dest] = weight;
}

void printSolution(int distance[][MAX_SIZE], int vertices) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (distance[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", distance[i][j]);
            }
        }
        printf("\n");
    }
}

void floydWarshall(struct Graph* graph) {
    int distance[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            distance[i][j] = graph->adjacencyMatrix[i][j];
        }
    }

    for (int k = 0; k < graph->vertices; k++) {
        for (int i = 0; i < graph->vertices; i++) {
            for (int j = 0; j < graph->vertices; j++) {
                if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX &&
                    distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    printSolution(distance, graph->vertices);
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

    floydWarshall(graph);

    return 0;
}