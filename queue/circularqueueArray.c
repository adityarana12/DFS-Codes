#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int* items;
    int front;
    int rear;
    int size;
};

void initialize(struct Queue* q, int size) {
    q->items = (int*)malloc(size * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->size = size;
}

void enqueue(struct Queue* q, int element) {
    if ((q->rear + 1) % q->size == q->front) {
        printf("Queue is overflow\n");
    }
    else if (q->front == -1 && q->rear == -1) {
        q->front = 0;
        q->rear = 0;
        q->items[q->rear] = element;
    }
    else {
        q->rear = (q->rear + 1) % q->size;
        q->items[q->rear] = element;
    }
}

int dequeue(struct Queue* q) {
    if (q->front == -1 && q->rear == -1) {
        printf("Queue is underflow\n");
        return -1;
    }
    else if (q->front == q->rear) {
        int item = q->items[q->front];
        q->front = -1;
        q->rear = -1;
        return item;
    }
    else {
        int item = q->items[q->front];
        q->front = (q->front + 1) % q->size;
        return item;
    }
}

void display(struct Queue* q) {
    if (q->front == -1 && q->rear == -1) {
        printf("Queue is empty\n");
        return;
    }

    printf("Elements in the queue: ");
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->items[i]);
        i = (i + 1) % q->size;
    }
    printf("%d\n", q->items[q->rear]);
}

int main() {
    struct Queue q;
    q.front = -1;
    q.rear = -1;

    int size;
    printf("Enter the size of the queue: ");
    scanf("%d", &size);

    initialize(&q, size);

    int choice = 1, x;

    while (choice < 4 && choice != 0) {
        printf("\nPress 1: Insert an element");
        printf("\nPress 2: Delete an element");
        printf("\nPress 3: Display the elements");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to be inserted: ");
                scanf("%d", &x);
                enqueue(&q, x);
                break;
            case 2:
                printf("Deleted element: %d\n", dequeue(&q));
                break;
            case 3:
                display(&q);
                break;
        }
    }
    return 0;
}
