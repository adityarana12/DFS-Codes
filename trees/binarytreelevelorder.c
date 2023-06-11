#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct QueueNode {
    struct TreeNode* node;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct QueueNode* createQueueNode(struct TreeNode* node) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue() {
    struct Queue* newQueue = (struct Queue*)malloc(sizeof(struct Queue));
    newQueue->front = NULL;
    newQueue->rear = NULL;
    return newQueue;
}

void enqueue(struct Queue* queue, struct TreeNode* node) {
    struct QueueNode* newNode = createQueueNode(node);

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

struct TreeNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    struct QueueNode* temp = queue->front;
    struct TreeNode* node = temp->node;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return node;
}

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertLevelOrder(int arr[], int size) {
    struct TreeNode* root = createNode(arr[0]);
    struct Queue* queue = createQueue();
    enqueue(queue, root);

    int i = 1;
    while (i < size) {
        struct TreeNode* parentNode = dequeue(queue);

        int leftChildData = arr[i++];
        if (leftChildData != -1) {
            parentNode->left = createNode(leftChildData);
            enqueue(queue, parentNode->left);
        }

        if (i < size) {
            int rightChildData = arr[i++];
            if (rightChildData != -1) {
                parentNode->right = createNode(rightChildData);
                enqueue(queue, parentNode->right);
            }
        }
    }

    return root;
}

void inorderTraversal(struct TreeNode* node) {
    if (node == NULL) {
        return;
    }

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int main() {
    int size;
    printf("Enter the number of elements in the binary tree: ");
    scanf("%d", &size);

    int* arr = (int*)malloc(size * sizeof(int));
    printf("Enter the elements of the binary tree (-1 for empty node):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    struct TreeNode* root = insertLevelOrder(arr, size);

    printf("Inorder traversal of the created tree: ");
    inorderTraversal(root);
    printf("\n");

    free(arr);

    return 0;
}
