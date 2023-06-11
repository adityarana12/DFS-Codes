#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct HashTable {
    int size;
    struct Node** table;
};

int hash(int key, int size) {
    return key % size;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->size = size;
    ht->table = (struct Node**)malloc(size * sizeof(struct Node*));
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(struct HashTable* ht, int key) {
    int index = hash(key, ht->size);

    // Create a new node
    struct Node* newNode = createNode(key);

    // Insert the node at the beginning of the linked list
    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        struct Node* curr = ht->table[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

void display(struct HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Index %d: ", i);
        struct Node* curr = ht->table[i];
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    int size;
    printf("Enter the size of the hash table: ");
    scanf("%d", &size);

    struct HashTable* ht = createHashTable(size);

    int count;
    printf("Enter the number of integers to insert: ");
    scanf("%d", &count);

    printf("Enter %d integers:\n", count);
    for (int i = 0; i < count; i++) {
        int num;
        scanf("%d", &num);
        insert(ht, num);
    }

    // Display the hash table
    display(ht);

    return 0;
}
