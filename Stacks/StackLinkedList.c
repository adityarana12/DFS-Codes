#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

void initialize(struct Stack* stack) {
    stack->top = NULL;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

void push(struct Stack* stack, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
    printf("Element %d pushed to stack.\n", item);
}

void pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow: Cannot pop element, stack is empty.\n");
        return;
    }
    struct Node* temp = stack->top;
    int item = temp->data;
    stack->top = stack->top->next;
    free(temp);
    printf("Element %d popped from stack.\n", item);
}

void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Elements in stack: ");
    struct Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void peek(struct Stack *stack){
    printf("element at top is:%d",stack->top->data);
}

int main() {
    struct Stack stack;
    initialize(&stack);

    int choice, element;
    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push (Insert an element)\n");
        printf("2. Pop (Delete an element)\n");
        printf("3. Peek \n");
        printf("4. Display (Print all elements)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                push(&stack, element);
                break;
            case 2:
                pop(&stack);
                break;
            case 3:
                peek(&stack);
                break;
            case 4:
                display(&stack);
                break;
            case 5:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
