#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the doubly linked list
void insertAtBeginning(Node** head, int value) {
    Node* newNode = createNode(value);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
    printf("Node inserted at the beginning\n");
}

// Function to insert a node at the end of the doubly linked list
void insertAtEnd(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        printf("Node inserted at the end\n");
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    printf("Node inserted at the end\n");
}

// Function to insert a node at a specific position in the doubly linked list
void insertAtPosition(Node** head, int value, int position) {
    if (position <= 0) {
        printf("Invalid position. Position should be a positive integer.\n");
        return;
    }
    if (position == 1) {
        insertAtBeginning(head, value);
        return;
    }
    Node* newNode = createNode(value);
    Node* current = *head;
    int count = 1;
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("Position exceeds the length of the linked list. Insertion not possible.\n");
        return;
    }
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
    printf("Node inserted at position %d\n", position);
}

// Function to insert a node after a specific node in the doubly linked list
void insertAfterNode(Node** head, int value, int afterValue) {
    if (*head == NULL) {
        printf("Linked list is empty. Insertion not possible.\n");
        return;
    }
    Node* current = *head;
    while (current != NULL && current->data != afterValue) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with value %d not found. Insertion not possible.\n", afterValue);
        return;
    }
    Node* newNode = createNode(value);
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
    printf("Node inserted after node with value %d\n", afterValue);
}

// Function to insert a node before a specific node in the doubly linked list
void insertBeforeNode(Node** head, int value, int beforeValue) {
    if (*head == NULL) {
        printf("Linked list is empty. Insertion not possible.\n");
        return;
    }
    if ((*head)->data == beforeValue) {
        insertAtBeginning(head, value);
        return;
    }
    Node* current = *head;
    while (current != NULL && current->data != beforeValue) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with value %d not found. Insertion not possible.\n", beforeValue);
        return;
    }
    Node* newNode = createNode(value);
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    printf("Node inserted before node with value %d\n", beforeValue);
}

// Function to delete the first node of the doubly linked list
void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
    printf("Node deleted from the beginning\n");
}

// Function to delete the last node of the doubly linked list
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }
    if ((*head)->next == NULL) {
        deleteAtBeginning(head);
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->prev->next = NULL;
    free(current);
    printf("Node deleted from the end\n");
}

// Function to delete a node at a specific position in the doubly linked list
void deleteAtPosition(Node** head, int position) {
    if (position <= 0) {
        printf("Invalid position. Position should be a positive integer.\n");
        return;
    }
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }
    Node* current = *head;
    int count = 1;
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        printf("Position exceeds the length of the linked list. Deletion not possible.\n");
        return;
    }
    current->prev->next = current->next;
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
    printf("Node deleted from position %d\n", position);
}

// Function to delete the node after a specific node in the doubly linked list
void deleteAfterNode(Node** head, int afterValue) {
    if (*head == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }
    Node* current = *head;
    while (current != NULL && current->data != afterValue) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with value %d not found. Deletion not possible.\n", afterValue);
        return;
    }
    if (current->next == NULL) {
        printf("No node present after the node with value %d. Deletion not possible.\n", afterValue);
        return;
    }
    Node* temp = current->next;
    current->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = current;
    }
    free(temp);
    printf("Node deleted after node with value %d\n", afterValue);
}

// Function to delete the node before a specific node in the doubly linked list
void deleteBeforeNode(Node** head, int beforeValue) {
    if (*head == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }
    if ((*head)->data == beforeValue) {
        printf("No node present before the first node. Deletion not possible.\n");
        return;
    }
    Node* current = *head;
    while (current != NULL && current->data != beforeValue) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with value %d not found. Deletion not possible.\n", beforeValue);
        return;
    }
    if (current->prev == NULL) {
        deleteAtBeginning(head);
        return;
    }
    Node* temp = current->prev;
    temp->prev->next = current;
    current->prev = temp->prev;
    free(temp);
    printf("Node deleted before node with value %d\n", beforeValue);
}

// Function to display the doubly linked list
void display(Node* head) {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    printf("Doubly Linked List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int choice, value, position, afterValue, beforeValue;

    while (1) {
        printf("\n---- Doubly Linked List Menu ----\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert at a specific position\n");
        printf("4. Insert after a specific node\n");
        printf("5. Insert before a specific node\n");
        printf("6. Delete at the beginning\n");
        printf("7. Delete at the end\n");
        printf("8. Delete at a specific position\n");
        printf("9. Delete after a specific node\n");
        printf("10. Delete before a specific node\n");
        printf("11. Display the linked list\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertAtBeginning(&head, value);
                break;
            case 2:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;
            case 3:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the position: ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;
            case 4:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the value of the node after which to insert: ");
                scanf("%d", &afterValue);
                insertAfterNode(&head, value, afterValue);
                break;
            case 5:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                printf("Enter the value of the node before which to insert: ");
                scanf("%d", &beforeValue);
                insertBeforeNode(&head, value, beforeValue);
                break;
            case 6:
                deleteAtBeginning(&head);
                break;
            case 7:
                deleteAtEnd(&head);
                break;
            case 8:
                printf("Enter the position: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;
            case 9:
                printf("Enter the value of the node after which to delete: ");
                scanf("%d", &afterValue);
                deleteAfterNode(&head, afterValue);
                break;
            case 10:
                printf("Enter the value of the node before which to delete: ");
                scanf("%d", &beforeValue);
                deleteBeforeNode(&head, beforeValue);
                break;
            case 11:
                display(head);
                break;
            case 12:
                printf("Exiting the program\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
