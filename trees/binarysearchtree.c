#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node Node;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val > root->data) {
        root->right = insertNode(root->right, val);
    } else if (val < root->data) {
        root->left = insertNode(root->left, val);
    }
    return root;
}

Node* findMin(Node* root) {
    Node* temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (val > root->data) {
        root->right = deleteNode(root->right, val);
    } else if (val < root->data) {
        root->left = deleteNode(root->left, val);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* minNode = findMin(root->right);
            root->data = minNode->data;
            root->right = deleteNode(root->right, minNode->data);
        }
    }
    return root;
}

void inorderTraversal(Node* node) {
    if (node == NULL) {
        return;
    }

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int countLeafNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main() {
    Node* root = NULL;
    int choice, data;
    while (1) {
        printf("\nBinary Tree Operations:\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Inorder Traversal\n");
        printf("4. Count Leaf Nodes\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Total number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
