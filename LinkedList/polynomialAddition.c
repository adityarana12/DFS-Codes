#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
};

// Function to create a new term
struct Term* createTerm(int coefficient, int exponent) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;
    return newTerm;
}

// Function to insert a term at the end of the polynomial
void insertTerm(struct Term** poly, int coefficient, int exponent) {
    struct Term* newTerm = createTerm(coefficient, exponent);
    
    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* current = *poly;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTerm;
    }
}

// Function to display a polynomial
void displayPolynomial(struct Term* poly) {
    struct Term* current = poly;
    while (current != NULL) {
        printf("%dx^%d ", current->coefficient, current->exponent);
        current = current->next;
        if (current != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term* current1 = poly1;
    struct Term* current2 = poly2;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            insertTerm(&result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            insertTerm(&result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        } else {
            int sum = current1->coefficient + current2->coefficient;
            insertTerm(&result, sum, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    
    // Append remaining terms of polynomial 1, if any
    while (current1 != NULL) {
        insertTerm(&result, current1->coefficient, current1->exponent);
        current1 = current1->next;
    }
    
    // Append remaining terms of polynomial 2, if any
    while (current2 != NULL) {
        insertTerm(&result, current2->coefficient, current2->exponent);
        current2 = current2->next;
    }
    
    return result;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    
    // Read the first polynomial from the user
    int numTerms1;
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &numTerms1);
    
    for (int i = 0; i < numTerms1; i++) {
        int coefficient, exponent;
        printf("Enter the coefficient and exponent of term %d: ", i + 1);
        scanf("%d%d", &coefficient, &exponent);
        insertTerm(&poly1, coefficient, exponent);
    }
    
    // Read the second polynomial from the user
    int numTerms2;
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &numTerms2);
    
    for (int i = 0; i < numTerms2; i++) {
        int coefficient, exponent;
        printf("Enter the coefficient and exponent of term %d: ", i + 1);
        scanf("%d%d", &coefficient, &exponent);
        insertTerm(&poly2, coefficient, exponent);
    }
    
    // Display the input polynomials
    printf("First polynomial: ");
    displayPolynomial(poly1);
    
    printf("Second polynomial: ");
    displayPolynomial(poly2);
    
    // Add the two polynomials
    struct Term* sum = addPolynomials(poly1, poly2);
    
    // Display the sum of the polynomials
    printf("Sum of the polynomials: ");
    displayPolynomial(sum);
    
    return 0;
}
