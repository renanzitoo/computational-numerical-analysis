#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int idx(int i, int j, int n) { return i * n + j; }

void build_vandermonde(int n, double *A, double *x) {
	for (int i = 0; i < n; ++i) {
		double xi = 1.0;
		for (int j = 0; j < n; ++j) {
			A[idx(i,j,n)] = xi;
			xi *= x[i];
		}
	}
}

int gaussian_elim(int n, double *A, double *b, double *x) {
	for (int k = 0; k < n; ++k) {
		/* partial pivot */
		int piv = k;
		double max = fabs(A[idx(k,k,n)]);
		for (int i = k+1; i < n; ++i) {
			double v = fabs(A[idx(i,k,n)]);
			if (v > max) { max = v; piv = i; }
		}
		if (max < 1e-15) return -1; /* singular or nearly singular */
		if (piv != k) {
			for (int j = k; j < n; ++j) {
				double tmp = A[idx(k,j,n)]; A[idx(k,j,n)] = A[idx(piv,j,n)]; A[idx(piv,j,n)] = tmp;
			}
			double tmpb = b[k]; b[k] = b[piv]; b[piv] = tmpb;
		}

		for (int i = k+1; i < n; ++i) {
			double factor = A[idx(i,k,n)] / A[idx(k,k,n)];
			A[idx(i,k,n)] = 0.0;
			for (int j = k+1; j < n; ++j) {
				A[idx(i,j,n)] -= factor * A[idx(k,j,n)];
			}
			b[i] -= factor * b[k];
		}
	}

	/* back substitution */
	for (int i = n-1; i >= 0; --i) {
		double s = b[i];
		for (int j = i+1; j < n; ++j) s -= A[idx(i,j,n)] * x[j];
		x[i] = s / A[idx(i,i,n)];
	}
	return 0;
}

double eval_poly(int n, double *c, double x) {
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

	double *xs = malloc(n * sizeof(double));
	double *ys = malloc(n * sizeof(double));
	if (!xs || !ys) { fprintf(stderr, "Memory error\n"); return 1; }

	printf("Enter %d pairs x y (one per line):\n", n);
	for (int i = 0; i < n; ++i) {
		if (scanf("%lf %lf", &xs[i], &ys[i]) != 2) {
			fprintf(stderr, "Invalid input for point %d\n", i);
			free(xs); free(ys);
			return 1;
		}
	}

	double *A = malloc(n * n * sizeof(double));
	double *b = malloc(n * sizeof(double));
	double *coef = malloc(n * sizeof(double));
	if (!A || !b || !coef) { fprintf(stderr, "Memory error\n"); return 1; }

	build_vandermonde(n, A, xs);
	for (int i = 0; i < n; ++i) b[i] = ys[i];

	int status = gaussian_elim(n, A, b, coef);
	if (status != 0) {
		fprintf(stderr, "Failed to solve system (singular matrix)\n");
		free(xs); free(ys); free(A); free(b); free(coef);
		return 1;
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

	free(xs); free(ys); free(A); free(b); free(coef);
	return 0;
}

