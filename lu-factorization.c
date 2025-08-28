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

void luDecomposition(int n, float* a, float* l, float* u) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            l[getOffset(i, j, n)] = 0.0;
            u[getOffset(i, j, n)] = 0.0;
        }
        l[getOffset(i, i, n)] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            float sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += l[getOffset(i, j, n)] * u[getOffset(j, k, n)];
            }
            u[getOffset(i, k, n)] = a[getOffset(i, k, n)] - sum;
        }

        for (int k = i + 1; k < n; k++) {
            float sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += l[getOffset(k, j, n)] * u[getOffset(j, i, n)];
            }
            l[getOffset(k, i, n)] = (a[getOffset(k, i, n)] - sum) / u[getOffset(i, i, n)];
        }
    }
}

void forwardSubstitution(int n, float* l, float* b, float* y) {
    for (int i = 0; i < n; i++) {
        float sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += l[getOffset(i, j, n)] * y[j];
        }
        y[i] = (b[i] - sum) / l[getOffset(i, i, n)];
    }
}

void backSubstitution(int n, float* u, float* y, float* x) {
    for (int i = n - 1; i >= 0; i--) {
        float sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += u[getOffset(i, j, n)] * x[j];
        }
        x[i] = (y[i] - sum) / u[getOffset(i, i, n)];
    }
}

void printMatrix(int n, float* matrix, const char* name) {
    printf("\nMatrix %s:\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.3f ", matrix[getOffset(i, j, n)]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    float *a, *b, *x, *l, *u, *y;

    readSystem(&n, &a, &b, &x);
    
    l = (float*) malloc(n * n * sizeof(float));
    u = (float*) malloc(n * n * sizeof(float));
    y = (float*) malloc(n * sizeof(float));
    
    if (!l || !u || !y) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    luDecomposition(n, a, l, u);
    
    printMatrix(n, l, "L");
    printMatrix(n, u, "U");
    
    forwardSubstitution(n, l, b, y);
    backSubstitution(n, u, y, x);

    printf("\nThe solution of the system is:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.3f\n", i + 1, x[i]);
    }
    
    free(a);
    free(b);
    free(x);
    free(l);
    free(u);
    free(y);

    return 0;
}
