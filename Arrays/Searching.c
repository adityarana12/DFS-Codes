#include <stdio.h>

// Linear Search
int linearSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i; // Return the index if key is found
        }
    }
    return -1; // Return -1 if key is not found
}

// Binary Search
int binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid; // Return the index if key is found
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Return -1 if key is not found
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    
    int arr[size];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int choice, key, result;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                result = linearSearch(arr, size, key);
                if (result == -1) {
                    printf("Key not found\n");
                } else {
                    printf("Key found at index %d\n", result);
                }
                break;
                
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                result = binarySearch(arr, 0, size - 1, key);
                if (result == -1) {
                    printf("Key not found\n");
                } else {
                    printf("Key found at index %d\n", result);
                }
                break;

            case 3:
                printf("Exiting the program\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
