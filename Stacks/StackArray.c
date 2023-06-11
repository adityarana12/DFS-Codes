#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Stack {
    int* items;
    int top;
    int maxSize;
};

void initialize(struct Stack *stack, int maxSize) {
    stack->items = (int*)malloc(maxSize * sizeof(int));
    stack->top = -1;
    stack->maxSize = maxSize;
}

bool isFull(struct Stack *stack) {
    return stack->top == stack->maxSize - 1;
}

bool isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, int item) {
    if (isFull(stack)) {
        printf("Stack Overflow: Cannot push element, stack is full.\n");
        return;
    }
    stack->items[++stack->top] = item;
    printf("Element %d pushed to stack.\n", item);
}

void pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow: Cannot pop element, stack is empty.\n");
        return;
    }
    int item = stack->items[stack->top--];
    printf("Element %d popped from stack.\n", item);
}

void display(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Elements in stack: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}
void peek(struct Stack  *stack){
    printf("the element at the top is:%d",stack->items[stack->top]);
}

int main() {
    int maxSize;
    printf("Enter the size of the stack: ");
    scanf("%d", &maxSize);

    struct Stack stack;
    initialize(&stack, maxSize);

    int choice, element;
    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push (Insert an element)\n");
        printf("2. Pop (Delete an element)\n");
        printf("3. Peek(Print the top element)\n");
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
                free(stack.items);
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}
