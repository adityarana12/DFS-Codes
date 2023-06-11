#include <stdio.h>
#include <stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the linked list
void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
    printf("Node with value %d inserted at the beginning\n", value);
}

// Function to insert a node at the end of the linked list
void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Node with value %d inserted at the end\n", value);
}

// Function to insert a node at a specific position in the linked list
void insertAtPosition(struct Node** head, int value, int position) {
    if (position < 0) {
        printf("Invalid position. Please try again.\n");
        return;
    }
    if (position == 0) {
        insertAtBeginning(head, value);
        return;
    }
    struct Node* newNode = createNode(value);
    struct Node* current = *head;
    int count = 0;
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("Invalid position. Please try again.\n");
        return;
    }
    newNode->next = current->next;
    current->next = newNode;
    printf("Node with value %d inserted at position %d\n", value, position);
}

// Function to delete a node at the beginning of the linked list
void deleteAtBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty. Nothing to delete.\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Node at the beginning deleted\n");
}

// Function to delete a node at the end of the linked list
void deleteAtEnd(struct Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty. Nothing to delete.\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Node at the end deleted\n");
        return;
    }
    struct Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    printf("Node at the end deleted\n");
}

// Function to delete a node at a specific position in the linked list
void deleteAtPosition(struct Node** head, int position) {
    if (position < 0) {
        printf("Invalid position. Please try again.\n");
        return;
    }
    if (position == 0) {
        deleteAtBeginning(head);
        return;
    }
    struct Node* current = *head;
    struct Node* previous = NULL;
    int count = 0;
    while (current != NULL && count < position) {
        previous = current;
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("Invalid position. Please try again.\n");
        return;
    }
    previous->next = current->next;
    free(current);
    printf("Node at position %d deleted\n", position);
}

// Function to display the linked list
void display(struct Node* head) {
    if (head == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    struct Node* current = head;
    printf("Linked list: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, value, position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert at a position\n");
        printf("4. Delete at the beginning\n");
        printf("5. Delete at the end\n");
        printf("6. Delete at a position\n");
        printf("7. Display the linked list\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert at the beginning: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;

            case 2:
                printf("Enter the value to insert at the end: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;

            case 3:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the position to insert at: ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;

            case 4:
                deleteAtBeginning(&head);
                break;

            case 5:
                deleteAtEnd(&head);
                break;

            case 6:
                printf("Enter the position to delete at: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;

            case 7:
                display(head);
                break;

            case 8:
                printf("Exiting the program\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
