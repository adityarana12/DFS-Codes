#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

void initialize(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

bool isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void enqueue(struct Queue* queue, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Element %d enqueued to the queue.\n", item);
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow: Cannot dequeue element, queue is empty.\n");
        return -1;
    }
    struct Node* temp = queue->front;
    int item = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    printf("Element %d dequeued from the queue.\n", item);
    return item;
}

void peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("The element at the front is: %d\n", queue->front->data);
}

void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Elements in queue: ");
    struct Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initialize(&queue);

    int choice, element;
    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue (Insert an element)\n");
        printf("2. Dequeue (Delete an element)\n");
        printf("3. Peek (Get the element at the front)\n");
        printf("4. Display (Print all elements)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &element);
                enqueue(&queue, element);
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                peek(&queue);
                break;
            case 4:
                display(&queue);
                break;
            case 5:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
