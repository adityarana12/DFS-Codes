#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

int getHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int getSize(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + getSize(root->left) + getSize(root->right);
}

struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

struct Node* findInorderSuccessor(struct Node* root, struct Node* temp) {
    struct Node *target=search(root,temp->data);
    if (target->right != NULL) {
        return findMin(target->right);
    }
    struct Node* successor = NULL;
    while (root != NULL) {
        if (target->data < root->data) {
            successor = root;
            root = root->left;
        } else if (target->data > root->data) {
            root = root->right;
        } else {
            break;
        }
    }
    return successor;
}

int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

void printMenu() {
    printf("\n----- Binary Tree Operations -----\n");
    printf("1. Insert a node\n");
    printf("2. Calculate the height of the tree\n");
    printf("3. Count the number of nodes\n");
    printf("4. Find the inorder successor of a node\n");
    printf("5. Count the number of leaf nodes\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Node inserted successfully.\n");
                break;
            case 2:
                printf("Height of the tree: %d\n", getHeight(root));
                break;
            case 3:
                printf("Number of nodes in the tree: %d\n", getSize(root));
                break;
            case 4:
                printf("Enter the data of the node to find the inorder successor: ");
                scanf("%d", &data);
                struct Node* target = createNode(data);
                struct Node* successor = findInorderSuccessor(root, target);
                if (successor != NULL) {
                    printf("Inorder successor of %d is %d\n", data, successor->data);
                } else {
                    printf("No inorder successor found.\n");
                }
                break;
            case 5:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
