#include <stdio.h>
#include <stdlib.h>

void generateRandomIntegers(int n) {
    FILE *file = fopen("All.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int num = rand();
        fprintf(file, "%d\n", num);
    }

    fclose(file);
}

void separateNumbers() {
    FILE *allFile = fopen("All.txt", "r");
    if (allFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *oddFile = fopen("Odd.txt", "w");
    if (oddFile == NULL) {
        printf("Error opening file!\n");
        fclose(allFile);
        return;
    }

    FILE *evenFile = fopen("Even.txt", "w");
    if (evenFile == NULL) {
        printf("Error opening file!\n");
        fclose(allFile);
        fclose(oddFile);
        return;
    }

    int num;
    while (fscanf(allFile, "%d", &num) == 1) {
        if (num % 2 == 0) {
            fprintf(evenFile, "%d\n", num);
        } else {
            fprintf(oddFile, "%d\n", num);
        }
    }

    fclose(allFile);
    fclose(oddFile);
    fclose(evenFile);
}

void displayFileContents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int num;
    printf("Contents of %s:\n", filename);
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d\t", num);
    }

    fclose(file);
}

int main() {
    int n;
    printf("Enter the number of random integers to generate: ");
    scanf("%d", &n);

    generateRandomIntegers(n);
    separateNumbers();

    displayFileContents("All.txt");
    printf("\n");
    displayFileContents("Odd.txt");
    printf("\n");
    displayFileContents("Even.txt");

    return 0;
}
