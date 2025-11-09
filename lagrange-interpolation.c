#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double eval_poly(int n, const double *c, double x) {
    double res = 0.0;
    double xp = 1.0;
    for (int i = 0; i < n; ++i) {
        res += c[i] * xp;
        xp *= x;
    }
    return res;
}

int main(void) {
    int n;
    printf("Number of points (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid n\n");
        return 1;
    }

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));
    if (!x || !y) { fprintf(stderr, "Memory error\n"); return 1; }

    printf("Enter %d pairs x y (one per line):\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%lf %lf", &x[i], &y[i]) != 2) {
            fprintf(stderr, "Invalid input for point %d\n", i);
            free(x); free(y);
            return 1;
        }
    }

        double *coef = calloc(n, sizeof(double));
    if (!coef) { fprintf(stderr, "Memory error\n"); free(x); free(y); return 1; }

    double *basis = malloc(n * sizeof(double));
    if (!basis) { fprintf(stderr, "Memory error\n"); free(x); free(y); free(coef); return 1; }

    for (int i = 0; i < n; ++i) {
    for (int k = 0; k < n; ++k) basis[k] = 0.0;
    basis[0] = 1.0;
        double denom = 1.0;

        for (int j = 0; j < n; ++j) if (j != i) {
            double xj = x[j];
            denom *= (x[i] - xj);
            double *tmp = calloc(n, sizeof(double));
            if (!tmp) { fprintf(stderr, "Memory error\n"); free(x); free(y); free(coef); free(basis); return 1; }
            for (int a = 0; a < n; ++a) {
                if (basis[a] == 0.0) continue;
                tmp[a] += basis[a] * (-xj);
                if (a+1 < n) tmp[a+1] += basis[a];
            }
            for (int a = 0; a < n; ++a) basis[a] = tmp[a];
            free(tmp);
        }

        
        if (fabs(denom) < 1e-18) {
            fprintf(stderr, "Points produce zero denominator (duplicate x?).\n");
            free(x); free(y); free(coef); free(basis);
            return 1;
        }
        double scale = y[i] / denom;
        for (int k = 0; k < n; ++k) coef[k] += basis[k] * scale;
    }

    printf("Polynomial coefficients (from degree 0 to %d):\n", n-1);
    for (int i = 0; i < n; ++i) printf("a[%d] = %.12g\n", i, coef[i]);

    int m;
    printf("Number of evaluation points: ");
    if (scanf("%d", &m) != 1 || m < 0) m = 0;
    for (int i = 0; i < m; ++i) {
        double xv;
        printf("x = ");
        if (scanf("%lf", &xv) != 1) { fprintf(stderr, "Invalid x\n"); break; }
        double yv = eval_poly(n, coef, xv);
        printf("P(%.12g) = %.12g\n", xv, yv);
    }

    free(x); free(y); free(coef); free(basis);
    return 0;
}
