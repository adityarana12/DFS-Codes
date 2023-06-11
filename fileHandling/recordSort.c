#include <stdio.h>

#define MAX_LENGTH 100

struct Student {
    float grade;
    char name[MAX_LENGTH];
};

void storeSampleData(const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "8.3 Gautam\n");
    fprintf(file, "9.4 Jasleen\n");
    fprintf(file, "6.7 Gaurav\n");
    fprintf(file, "9.4 Naman\n");
    fprintf(file, "5.7 Ishika\n");
    fprintf(file, "7.5 Rakesh\n");

    fclose(file);
}

void findHighestGrade(struct Student students[], int numStudents) {
    float highestGrade = students[0].grade;
    for (int i = 1; i < numStudents; i++) {
        if (students[i].grade > highestGrade) {
            highestGrade = students[i].grade;
        }
    }

    printf("Highest Grade: %.2f\n", highestGrade);

    printf("Students with the highest grade:\n");
    for (int i = 0; i < numStudents; i++) {
        if (students[i].grade == highestGrade) {
            printf("%s\n", students[i].name);
        }
    }
}

void findThirdHighestGrade(struct Student students[], int numStudents) {

    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].grade < students[j + 1].grade) {
         
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nDetails of the student with the 3rd highest grade:\n");
    if (numStudents >= 3) {
        printf("Grade: %.2f\n", students[2].grade);
        printf("Name: %s\n", students[2].name);
    } else {
        printf("There are less than 3 students\n");
    }
}

int main() {
    const char* fileName = "grades.txt";


    storeSampleData(fileName);


    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 0;
    }

    struct Student students[MAX_LENGTH];
    int numStudents = 0;

    while (fscanf(file, "%f %s", &students[numStudents].grade, students[numStudents].name) != EOF) {
        numStudents++;
    }

    fclose(file);

    findHighestGrade(students, numStudents);
    findThirdHighestGrade(students, numStudents);

    return 0;
}
