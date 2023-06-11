#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct Queue {
    int *items;
    int front;
    int rear;
    int size;
};

void initialize(struct Queue* queue,int size) {
    queue->items = (int*)malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size=size;
}

bool isFull(struct Queue* queue) {
    return (queue->rear == queue->size);
}

bool isEmpty(struct Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue Overflow: Cannot enqueue element, queue is full.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = item;
    printf("Element %d enqueued to the queue.\n", item);
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue Underflow: Cannot dequeue element, queue is empty.\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    printf("Element %d dequeued from the queue.\n", item);
    return item;
}
void peek(struct Queue *queue){
    printf("the element at the front is:",queue->items[queue->front]);

}

void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Elements in queue: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    int size;
    printf("enter the size of queue");
    scanf("%d",size);
    initialize(&queue,size);

    int choice, element;
    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue (Insert an element)\n");
        printf("2. Dequeue (Delete an element)\n");
        printf("3. peek\n");
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
