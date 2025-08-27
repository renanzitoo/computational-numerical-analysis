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
}

void swapRows(int n, float* a, float* b, int row1, int row2) {
    if (row1 == row2) return;
    
    for (int j = 0; j < n; j++) {
        float temp = a[getOffset(row1, j, n)];
        a[getOffset(row1, j, n)] = a[getOffset(row2, j, n)];
        a[getOffset(row2, j, n)] = temp;
    }
    
    float temp = b[row1];
    b[row1] = b[row2];
    b[row2] = temp;
}

int findPivot(int n, float* a, int col, int startRow) {
    int maxRow = startRow;
    float maxVal = fabs(a[getOffset(startRow, col, n)]);
    
    for (int i = startRow + 1; i < n; i++) {
        float val = fabs(a[getOffset(i, col, n)]);
        if (val > maxVal) {
            maxVal = val;
            maxRow = i;
        }
    }
    
    return maxRow;
}

void gaussianElimination(int n, float* a, float* b) {
    for (int r = 0; r < n - 1; r++) {
        int pivotRow = findPivot(n, a, r, r);
        
        if (pivotRow != r) {
            swapRows(n, a, b, r, pivotRow);
            printf("Swapped rows %d and %d\n", r + 1, pivotRow + 1);
        }
        
        if (fabs(a[getOffset(r, r, n)]) < 1e-10) {
            printf("Warning: Near-zero pivot detected at position (%d, %d)\n", r + 1, r + 1);
        }
        
        for (int i = r + 1; i < n; i++) {
            float m = -a[getOffset(i, r, n)] / a[getOffset(r, r, n)];
            a[getOffset(i, r, n)] = 0;
            for (int j = r + 1; j < n; j++) {
                a[getOffset(i, j, n)] += m * a[getOffset(r, j, n)];
            }
            b[i] += m * b[r];
        }
    }
}

void backSubstitution(int n, float* a, float* b, float* x) {
    for (int i = n - 1; i >= 0; i--) {
        float sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += a[getOffset(i, j, n)] * x[j];
        }
        x[i] = (b[i] - sum) / a[getOffset(i, i, n)];
    }
}

int main() {
    int n;
    float *a, *b, *x;

    readSystem(&n, &a, &b, &x);
    gaussianElimination(n, a, b);
    backSubstitution(n, a, b, x);

    printf("The solution of the system is:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.3f\n", i + 1, x[i]);
    }
    
    free(a);
    free(b);
    free(x);

    return 0;
}
