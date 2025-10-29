#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double evaluate_function(const char* func, double x) {
  if (strcmp(func, "x*x - 4") == 0) {
    return x * x - 4;
  }
  if (strcmp(func, "exp(x) - sin(x) - 2") == 0) {
    return exp(x) - sin(x) - 2;
  }
  fprintf(stderr, "Function not recognized.\n");
  exit(1);
}

void secant_method(const char* func, double x0, double x1, double tol, int max_iter) {
  double f0 = evaluate_function(func, x0);
  double f1 = evaluate_function(func, x1);

  printf("Initial points: x0 = %.6f, f(x0) = %.6f\n", x0, f0);
  printf("Initial points: x1 = %.6f, f(x1) = %.6f\n", x1, f1);

  for (int i = 0; i < max_iter; i++) {
    if (fabs(f1 - f0) < 1e-12) {
      printf("Division by zero detected. f(x1) - f(x0) is too small.\n");
      return;
    }

    double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
    double f2 = evaluate_function(func, x2);

    printf("Iteration %d: x2 = %.6f, f(x2) = %.6f\n", i + 1, x2, f2);

    if (fabs(f2) < tol || fabs(x2 - x1) < tol) {
      printf("The approximate root is: %.6f\n", x2);
      return;
    }

    x0 = x1;
    f0 = f1;
    x1 = x2;
    f1 = f2;
  }

  printf("The method did not converge after %d iterations.\n", max_iter);
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    printf("Usage: %s <function> <x0> <x1> <tolerance> <max_iter>\n", argv[0]);
    printf("Where x0 and x1 are initial approximations near the root.\n");
    return 1;
  }

  const char* func = argv[1];
  double x0 = atof(argv[2]);
  double x1 = atof(argv[3]);
  double tol = atof(argv[4]);
  int max_iter = atoi(argv[5]);

  secant_method(func, x0, x1, tol, max_iter);

  return 0;
}
