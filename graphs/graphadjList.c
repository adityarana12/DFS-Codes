#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjacencyList;
};

struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjacencyList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int source, int destination) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        struct Node* newNode = createNode(destination);
        newNode->next = graph->adjacencyList[source];
        graph->adjacencyList[source] = newNode;

        newNode = createNode(source);
        newNode->next = graph->adjacencyList[destination];
        graph->adjacencyList[destination] = newNode;
    } else {
        printf("Invalid vertex.\n");
    }
}

void removeEdge(struct Graph* graph, int source, int destination) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        struct Node* curr = graph->adjacencyList[source];
        struct Node* prev = NULL;
        while (curr != NULL && curr->vertex != destination) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) {
            printf("Edge does not exist.\n");
            return;
        }
        if (prev == NULL) {
            graph->adjacencyList[source] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);

        curr = graph->adjacencyList[destination];
        prev = NULL;
        while (curr != NULL && curr->vertex != source) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == NULL) {
            graph->adjacencyList[destination] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    } else {
        printf("Invalid vertex.\n");
    }
}

void addVertex(struct Graph* graph) {
    int newVertices = graph->vertices + 1;
    struct Node** newAdjList = (struct Node**)malloc(newVertices * sizeof(struct Node*));
    for (int i = 0; i < newVertices; i++) {
        newAdjList[i] = NULL;
    }
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* curr = graph->adjacencyList[i];
        while (curr != NULL) {
            struct Node* newNode = createNode(curr->vertex);
            newNode->next = newAdjList[i];
            newAdjList[i] = newNode;
            curr = curr->next;
        }
    }
    free(graph->adjacencyList);
    graph->adjacencyList = newAdjList;
    graph->vertices = newVertices;
}

void removeVertex(struct Graph* graph, int vertex) {
    if (vertex >= 0 && vertex < graph->vertices) {
        struct Node* curr = graph->adjacencyList[vertex];
        while (curr != NULL) {
            int adjVertex = curr->vertex;
            struct Node* temp = graph->adjacencyList[adjVertex];
            struct Node* prev = NULL;
            while (temp != NULL && temp->vertex != vertex) {
                prev = temp;
                temp = temp->next;
            }
            if (prev == NULL) {
                graph->adjacencyList[adjVertex] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            curr = curr->next;
        }
        free(graph->adjacencyList[vertex]);
        graph->adjacencyList[vertex] = NULL;

        for (int i = vertex; i < graph->vertices - 1; i++) {
            graph->adjacencyList[i] = graph->adjacencyList[i + 1];
        }
        graph->adjacencyList[graph->vertices - 1] = NULL;

        struct Node** newAdjList = (struct Node**)malloc((graph->vertices - 1) * sizeof(struct Node*));
        for (int i = 0; i < graph->vertices - 1; i++) {
            newAdjList[i] = NULL;
        }
        for (int i = 0; i < graph->vertices - 1; i++) {
            struct Node* curr = graph->adjacencyList[i];
            while (curr != NULL) {
                struct Node* newNode = createNode(curr->vertex);
                newNode->next = newAdjList[i];
                newAdjList[i] = newNode;
                curr = curr->next;
            }
        }
        free(graph->adjacencyList);
        graph->adjacencyList = newAdjList;
        graph->vertices--;
    } else {
        printf("Invalid vertex.\n");
    }
}

void calculateDegree(struct Graph* graph) {
    printf("Degree of each vertex:\n");
    for (int i = 0; i < graph->vertices; i++) {
        int degree = 0;
        struct Node* curr = graph->adjacencyList[i];
        while (curr != NULL) {
            degree++;
            curr = curr->next;
        }
        printf("Vertex %d: %d\n", i, degree);
    }
}

void calculateSelfLoops(struct Graph* graph) {
    int count = 0;
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* curr = graph->adjacencyList[i];
        while (curr != NULL) {
            if (curr->vertex == i) {
                count++;
                break;
            }
            curr = curr->next;
        }
    }
    printf("Number of self-loops in the graph: %d\n", count);
}

void displayGraph(struct Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->vertices; i++) {
        printf("Vertex %d: ", i);
        struct Node* curr = graph->adjacencyList[i];
        while (curr != NULL) {
            printf("%d ", curr->vertex);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    int choice, source, destination;
    struct Graph* graph = NULL;

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
