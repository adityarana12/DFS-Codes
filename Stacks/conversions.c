#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for stack
struct Stack {
    int top;
    int capacity;
    char* array;
};

// Function to create a stack
struct Stack* createStack(int capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to push an element to the stack
void push(struct Stack* stack, char item)
{
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack)
{
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->array[stack->top--];
}

// Function to get the top element of the stack
char peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top];
}

// Function to check if a character is an operand
int isOperand(char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

// Function to get the precedence of an operator
int getPrecedence(char ch)
{
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix, char* postfix)
{
    struct Stack* stack = createStack(strlen(infix));
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i]))
            postfix[j++] = infix[i];
        else if (infix[i] == '(')
            push(stack, infix[i]);
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[j++] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                printf("Invalid Expression\n");
            pop(stack);
        }
        else {
            while (!isEmpty(stack) && getPrecedence(infix[i]) <= getPrecedence(peek(stack)))
                postfix[j++] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (!isEmpty(stack))
        postfix[j++] = pop(stack);
    postfix[j] = '\0';
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char* infix, char* prefix)
{
    int i, j = 0;
    // Reverse the infix expression
    strrev(infix);
    // Replace opening parentheses with closing parentheses and vice versa
    for (i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }
    // Convert the reversed infix expression to postfix expression
    infixToPostfix(infix, prefix);
    // Reverse the postfix expression to get the prefix expression
    strrev(prefix);
}

int main()
{
    char infix[100], postfix[100], prefix[100];

    printf("Enter an infix expression: ");
    scanf("%s",&infix);
    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("Postfix expression: %s\n", postfix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}
