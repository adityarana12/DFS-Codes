#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapify(int array[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest])
        largest = left;

    if (right < size && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int array[], int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    for (i = size - 1; i >= 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

int main() {
    int n, i;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int* array = (int*)malloc(n * sizeof(int));
    
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &array[i]);

    heapSort(array, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    free(array);

    return 0;
}
