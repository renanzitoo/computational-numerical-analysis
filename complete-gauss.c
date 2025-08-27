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

void swapCols(int n, float* a, int col1, int col2) {
    if (col1 == col2) return;
    
    for (int i = 0; i < n; i++) {
        float temp = a[getOffset(i, col1, n)];
        a[getOffset(i, col1, n)] = a[getOffset(i, col2, n)];
        a[getOffset(i, col2, n)] = temp;
    }
}

void findCompletePivot(int n, float* a, int startRow, int startCol, int* pivotRow, int* pivotCol) {
    *pivotRow = startRow;
    *pivotCol = startCol;
    float maxVal = fabs(a[getOffset(startRow, startCol, n)]);
    
    for (int i = startRow; i < n; i++) {
        for (int j = startCol; j < n; j++) {
            float val = fabs(a[getOffset(i, j, n)]);
            if (val > maxVal) {
                maxVal = val;
                *pivotRow = i;
                *pivotCol = j;
            }
        }
    }
}

void gaussianElimination(int n, float* a, float* b, int* colOrder) {
    for (int r = 0; r < n - 1; r++) {
        int pivotRow, pivotCol;
        findCompletePivot(n, a, r, r, &pivotRow, &pivotCol);
        
        if (pivotRow != r) {
            swapRows(n, a, b, r, pivotRow);
            printf("Swapped rows %d and %d\n", r + 1, pivotRow + 1);
        }
        
        if (pivotCol != r) {
            swapCols(n, a, r, pivotCol);
            int temp = colOrder[r];
            colOrder[r] = colOrder[pivotCol];
            colOrder[pivotCol] = temp;
            printf("Swapped columns %d and %d\n", r + 1, pivotCol + 1);
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

void reorderSolution(int n, float* x, int* colOrder, float* finalX) {
    for (int i = 0; i < n; i++) {
        finalX[colOrder[i]] = x[i];
    }
}

int main() {
    int n;
    float *a, *b, *x, *finalX;
    int *colOrder;

    readSystem(&n, &a, &b, &x);
    
    colOrder = (int*) malloc(n * sizeof(int));
    finalX = (float*) malloc(n * sizeof(float));
    
    for (int i = 0; i < n; i++) {
        colOrder[i] = i;
    }
    
    gaussianElimination(n, a, b, colOrder);
    backSubstitution(n, a, b, x);
    reorderSolution(n, x, colOrder, finalX);

    printf("The solution of the system is:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.3f\n", i + 1, finalX[i]);
    }
    
    free(a);
    free(b);
    free(x);
    free(finalX);
    free(colOrder);

    return 0;
}
