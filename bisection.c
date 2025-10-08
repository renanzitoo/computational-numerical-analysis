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

void bisection_method(const char* func, double a, double b, double tol, int max_iter) {
  double fa = evaluate_function(func, a);
  double fb = evaluate_function(func, b);

  if (fa * fb >= 0) {
    printf("The provided interval does not contain a root.\n");
    return;
  }

  double c, fc;
  for (int i = 0; i < max_iter; i++) {
    c = (a + b) / 2.0;
    fc = evaluate_function(func, c);

    printf("Iteration %d: c = %.6f, f(c) = %.6f\n", i + 1, c, fc);

    if (fabs(fc) < tol || fabs(b - a) < tol) {
      printf("The approximate root is: %.6f\n", c);
      return;
    }

    if (fa * fc < 0) {
      b = c;
      fb = fc;
    } else {
      a = c;
      fa = fc;
    }
  }

  printf("The method did not converge after %d iterations.\n", max_iter);
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    printf("Usage: %s <function> <a> <b> <tolerance> <max_iter>\n", argv[0]);
    return 1;
  }

  const char* func = argv[1];
  double a = atof(argv[2]);
  double b = atof(argv[3]);
  double tol = atof(argv[4]);
  int max_iter = atoi(argv[5]);

  bisection_method(func, a, b, tol, max_iter);

  return 0;
}