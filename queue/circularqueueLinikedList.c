#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* front = NULL;
struct node* rear = NULL;

void enqueue(int x) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->next = NULL;

    if (rear == NULL) {
        front = rear = newnode;
        rear->next = front;
    }
    else {
        rear->next = newnode;
        rear = newnode;
        rear->next = front;
    }
}

void dequeue() {
    if (front == NULL && rear == NULL) {
        printf("Queue is empty\n");
        return;
    }
    struct node* temp = front;
    if (front == rear) {
        front = rear = NULL;
        free(temp);
    }
    else {
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

int peek() {
    if (front == NULL && rear == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    return front->data;
}

void display() {
    struct node* temp = front;
    printf("Elements in the queue: ");
    if (front == NULL && rear == NULL) {
        printf("Queue is empty\n");
        return;
    }
    while (temp->next != front) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

int main() {
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
                enqueue(element);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                printf("Front element: %d\n", peek());
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
