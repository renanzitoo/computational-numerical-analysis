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

double evaluate_derivative(const char* func, double x) {
  if (strcmp(func, "x*x - 4") == 0) {
    return 2 * x;
  }
  if (strcmp(func, "exp(x) - sin(x) - 2") == 0) {
    return exp(x) - cos(x);
  }
  fprintf(stderr, "Derivative not recognized.\n");
  exit(1);
}

void newton_method(const char* func, double x0, double tol, int max_iter) {
  double x = x0;
  
  printf("Initial point: x0 = %.6f\n", x0);
  
  for (int i = 0; i < max_iter; i++) {
    double fx = evaluate_function(func, x);
    double fpx = evaluate_derivative(func, x);
    
    printf("Iteration %d: x = %.6f, f(x) = %.6f, f'(x) = %.6f\n", i + 1, x, fx, fpx);
    
    if (fabs(fpx) < 1e-12) {
      printf("Derivative is too small. Method may not converge.\n");
      return;
    }
    
    double x_new = x - fx / fpx;
    
    if (fabs(x_new - x) < tol || fabs(fx) < tol) {
      printf("The approximate root is: %.6f\n", x_new);
      return;
    }
    
    x = x_new;
  }
  
  printf("The method did not converge after %d iterations.\n", max_iter);
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    printf("Usage: %s <function> <x0> <tolerance> <max_iter>\n", argv[0]);
    printf("Where x0 is the initial approximation near the root.\n");
    printf("Available functions:\n");
    printf("  \"x*x - 4\"               : f(x) = x² - 4, f'(x) = 2x\n");
    printf("  \"exp(x) - sin(x) - 2\"   : f(x) = e^x - sin(x) - 2, f'(x) = e^x - cos(x)\n");
    return 1;
  }

  const char* func = argv[1];
  double x0 = atof(argv[2]);
  double tol = atof(argv[3]);
  int max_iter = atoi(argv[4]);

  newton_method(func, x0, tol, max_iter);

  return 0;
}
