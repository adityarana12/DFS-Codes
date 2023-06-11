#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// Structure to represent a graph
struct Graph {
    int vertices;
    int adjMatrix[MAX_SIZE][MAX_SIZE];
};

// Function to create a graph
struct Graph *createGraph(int vertices) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    if (graph == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    graph->vertices = vertices;

    // Initialize adjacency matrix with 0 (no edges)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int source, int destination) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        graph->adjMatrix[source][destination] = 1;
        graph->adjMatrix[destination][source] = 1;
    } else {
        printf("Invalid vertex.\n");
    }
}

// Function to remove an edge from the graph
void removeEdge(struct Graph *graph, int source, int destination) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        graph->adjMatrix[source][destination] = 0;
        graph->adjMatrix[destination][source] = 0;
    } else {
        printf("Invalid vertex.\n");
    }
}

// Function to add a vertex to the graph
void addVertex(struct Graph *graph) {
    if (graph->vertices < MAX_SIZE) {
        graph->vertices++;
        // Initialize the new row and column with 0 (no edges)
        for (int i = 0; i < graph->vertices; i++) {
            graph->adjMatrix[i][graph->vertices - 1] = 0;
            graph->adjMatrix[graph->vertices - 1][i] = 0;
        }
    } else {
        printf("Maximum number of vertices reached.\n");
    }
}

// Function to remove a vertex from the graph
void removeVertex(struct Graph *graph, int vertex) {
    if (vertex >= 0 && vertex < graph->vertices) {
        for (int i = vertex; i < graph->vertices - 1; i++) {
            // Shift rows and columns to the left
            for (int j = 0; j < graph->vertices; j++) {
                graph->adjMatrix[j][i] = graph->adjMatrix[j][i + 1];
                graph->adjMatrix[i][j] = graph->adjMatrix[i + 1][j];
            }
        }
        graph->vertices--;
    } else {
        printf("Invalid vertex.\n");
    }
}

// Function to calculate the degree of each vertex in the graph
void calculateDegree(struct Graph *graph) {
    printf("Degree of each vertex:\n");
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                degree++;
            }
        }
        printf("Vertex %d: %d\n", i, degree);
    }
}

// Function to calculate the number of self-loops in the graph
void calculateSelfLoops(struct Graph *graph) {
    int count = 0;
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[i][i] == 1) {
            count++;
        }
    }
    printf("Number of self-loops in the graph: %d\n", count);
}

// Function to display the adjacency matrix of the graph
void displayGraph(struct Graph *graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int choice, source, destination;
    struct Graph *graph = NULL;

    while (1) {
        printf("\n----- Graph Operations -----\n");
        printf("1. Create a graph\n");
        printf("2. Insert an edge\n");
        printf("3. Delete an edge\n");
        printf("4. Insert a vertex\n");
        printf("5. Delete a vertex\n");
        printf("6. Calculate degree of each vertex\n");
        printf("7. Calculate number of self-loops\n");
        printf("8. Display graph\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (graph != NULL) {
                    printf("Graph already exists.\n");
                    break;
                }
                int vertices;
                printf("Enter the number of vertices in the graph: ");
                scanf("%d", &vertices);
                graph = createGraph(vertices);
                printf("Graph created successfully.\n");
                break;
            case 2:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                printf("Enter the source vertex: ");
                scanf("%d", &source);
                printf("Enter the destination vertex: ");
                scanf("%d", &destination);
                addEdge(graph, source, destination);
                printf("Edge inserted successfully.\n");
                break;
            case 3:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                printf("Enter the source vertex: ");
                scanf("%d", &source);
                printf("Enter the destination vertex: ");
                scanf("%d", &destination);
                removeEdge(graph, source, destination);
                printf("Edge deleted successfully.\n");
                break;
            case 4:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                addVertex(graph);
                printf("Vertex inserted successfully.\n");
                break;
            case 5:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                int vertex;
                printf("Enter the vertex to delete: ");
                scanf("%d", &vertex);
                removeVertex(graph, vertex);
                printf("Vertex deleted successfully.\n");
                break;
            case 6:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                calculateDegree(graph);
                break;
            case 7:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                calculateSelfLoops(graph);
                break;
            case 8:
                if (graph == NULL) {
                    printf("Graph does not exist. Create a graph first.\n");
                    break;
                }
                displayGraph(graph);
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}