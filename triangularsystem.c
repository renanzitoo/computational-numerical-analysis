//Made by Renan Costa
#include <stdio.h>
#include <stdlib.h>

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
