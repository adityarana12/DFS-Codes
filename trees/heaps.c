#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int* array;
    int size;
};

typedef struct Heap Heap;

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapify(int array[], int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && array[l] > array[largest])
        largest = l;

    if (r < size && array[r] > array[largest])
        largest = r;

    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, size, largest);
    }
}

Heap* createHeap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->array = NULL;
    return heap;
}

void insert(Heap* heap, int newNum) {
    int size = heap->size;

    if (size == 0) {
        heap->array = (int*)malloc(sizeof(int));
    } else {
        heap->array = (int*)realloc(heap->array, (size + 1) * sizeof(int));
    }

    heap->array[size] = newNum;
    heap->size += 1;

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(heap->array, heap->size, i);
    }
}

void deleteRoot(Heap* heap, int num) {
    int size = heap->size;

    if (size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    int i;

    for (i = 0; i < size; i++) {
        if (num == heap->array[i])
            break;
    }

    if (i == size) {
        printf("Node not found in the heap.\n");
        return;
    }

    swap(&heap->array[i], &heap->array[size - 1]);
    heap->size -= 1;

    heap->array = (int*)realloc(heap->array, heap->size * sizeof(int));

    for (i = heap->size / 2 - 1; i >= 0; i--) {
        heapify(heap->array, heap->size, i);
    }
}

void printArray(Heap* heap) {
    int size = heap->size;

    if (size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Heap elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

void freeHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    int i, d, ch;
    Heap* heap = createHeap();

    do {
        printf("\nMENU\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Display heap\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter the node to be inserted: ");
                scanf("%d", &i);
                insert(heap, i);
                printf("Node %d inserted into the heap.\n", i);
                break;
            case 2:
                printf("Enter the node to be deleted: ");
                scanf("%d", &d);
                deleteRoot(heap, d);
                break;
            case 3:
                printArray(heap);
                break;
            case 4:
                freeHeap(heap);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (ch != 4);

    return 0;
}
