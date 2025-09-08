//Made by Renan Costa
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getOffset(int i, int j, int n) {
    return i * n + j;
}

void readSystem(int* n, float** a, float** b, float** x) {
    printf("System order: ");
    scanf("%d", n);

    *a = (float*) malloc((*n) * (*n) * sizeof(float));
    *b = (float*) malloc((*n) * sizeof(float));
    *x = (float*) malloc((*n) * sizeof(float));

    if (!(*a) || !(*b) || !(*x)) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    printf("Coefficient matrix:\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            scanf("%f", &(*a)[getOffset(i, j, *n)]);
        }
    }

    printf("Independent terms:\n");
    for (int i = 0; i < *n; i++) {
        scanf("%f", &(*b)[i]);
    }
    
    // Initialize x with zeros
    for (int i = 0; i < *n; i++) {
        (*x)[i] = 0.0;
    }
}

int checkDiagonalDominance(int n, float* a) {
    for (int i = 0; i < n; i++) {
        float diag = fabs(a[getOffset(i, i, n)]);
        float sum = 0.0;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += fabs(a[getOffset(i, j, n)]);
            }
        }
        
        if (diag <= sum) {
            return 0; // Not diagonally dominant
        }
    }
    return 1; // Diagonally dominant
}

void jacobiIteration(int n, float* a, float* b, float* x, float* newX) {
    for (int i = 0; i < n; i++) {
        float sum = 0.0;
        
        // Sum all terms except diagonal
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += a[getOffset(i, j, n)] * x[j];
            }
        }
        
        // Calculate new value for x[i]
        newX[i] = (b[i] - sum) / a[getOffset(i, i, n)];
    }
}

float calculateError(int n, float* x, float* newX) {
    float maxError = 0.0;
    
    for (int i = 0; i < n; i++) {
        float error = fabs(newX[i] - x[i]);
        if (error > maxError) {
            maxError = error;
        }
    }
    
    return maxError;
}

void copyArray(int n, float* source, float* dest) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void jacobiMethod(int n, float* a, float* b, float* x, float tolerance, int maxIterations) {
    float* newX = (float*) malloc(n * sizeof(float));
    
    if (!newX) {
        printf("Memory allocation error.\n");
        exit(1);
    }
    
    // Check diagonal dominance
    if (!checkDiagonalDominance(n, a)) {
        printf("Warning: Matrix is not diagonally dominant. Convergence is not guaranteed.\n");
    }
    
    printf("\nJacobi Method Iterations:\n");
    printf("Iteration\t");
    for (int i = 0; i < n; i++) {
        printf("x%d\t\t", i + 1);
    }
    printf("Error\n");
    
    for (int iter = 0; iter < maxIterations; iter++) {
        jacobiIteration(n, a, b, x, newX);
        float error = calculateError(n, x, newX);
        
        printf("%d\t\t", iter + 1);
        for (int i = 0; i < n; i++) {
            printf("%.6f\t", newX[i]);
        }
        printf("%.6f\n", error);
        
        if (error < tolerance) {
            printf("\nConverged after %d iterations with tolerance %.6f\n", iter + 1, tolerance);
            copyArray(n, newX, x);
            free(newX);
            return;
        }
        
        copyArray(n, newX, x);
    }
    
    printf("\nMaximum iterations (%d) reached without convergence.\n", maxIterations);
    free(newX);
}

int main() {
    int n;
    float *a, *b, *x;
    float tolerance;
    int maxIterations;

    readSystem(&n, &a, &b, &x);
    
    printf("Enter tolerance (e.g., 0.001): ");
    scanf("%f", &tolerance);
    
    printf("Enter maximum iterations (e.g., 100): ");
    scanf("%d", &maxIterations);
    
    jacobiMethod(n, a, b, x, tolerance, maxIterations);

    printf("\nFinal solution:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }
    
    free(a);
    free(b);
    free(x);

    return 0;
}
