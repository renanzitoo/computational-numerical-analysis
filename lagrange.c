#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double avalia_polinomio(int n, const double *coef, double x) {
    double resultado = 0.0;
    double potencia_x = 1.0;
    for (int i = 0; i < n; ++i) {
        resultado += coef[i] * potencia_x;
        potencia_x *= x;
    }
    return resultado;
}

int main(void) {
    int n;
    printf("Número de pontos (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Valor de n inválido\n");
        return 1;
    }

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));
    if (!x || !y) { 
        fprintf(stderr, "Erro de memória\n"); 
        return 1; 
    }

    printf("Digite %d pares x y (um por linha):\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%lf %lf", &x[i], &y[i]) != 2) {
            fprintf(stderr, "Entrada inválida para o ponto %d\n", i);
            free(x); free(y);
            return 1;
        }
    }

    double *coef = calloc(n, sizeof(double));
    if (!coef) { 
        fprintf(stderr, "Erro de memória\n"); 
        free(x); free(y); 
        return 1; 
    }

    double *base = malloc(n * sizeof(double));
    if (!base) { 
        fprintf(stderr, "Erro de memória\n"); 
        free(x); free(y); free(coef); 
        return 1; 
    }

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) base[k] = 0.0;
        base[0] = 1.0;
        double denominador = 1.0;

        for (int j = 0; j < n; ++j) if (j != i) {
            double xj = x[j];
            denominador *= (x[i] - xj);
            double *temp = calloc(n, sizeof(double));
            if (!temp) { 
                fprintf(stderr, "Erro de memória\n"); 
                free(x); free(y); free(coef); free(base); 
                return 1; 
            }
            for (int a = 0; a < n; ++a) {
                if (base[a] == 0.0) continue;
                temp[a] += base[a] * (-xj);
                if (a + 1 < n) temp[a + 1] += base[a];
            }
            for (int a = 0; a < n; ++a) base[a] = temp[a];
            free(temp);
        }

        if (fabs(denominador) < 1e-18) {
            fprintf(stderr, "Os pontos produzem denominador zero (x duplicado?).\n");
            free(x); free(y); free(coef); free(base);
            return 1;
        }

        double escala = y[i] / denominador;
        for (int k = 0; k < n; ++k) coef[k] += base[k] * escala;
    }

    printf("Coeficientes do polinômio (do grau 0 até %d):\n", n - 1);
    for (int i = 0; i < n; ++i) 
        printf("a[%d] = %.12g\n", i, coef[i]);

    int m;
    printf("Número de pontos para avaliação: ");
    if (scanf("%d", &m) != 1 || m < 0) m = 0;

    for (int i = 0; i < m; ++i) {
        double xv;
        printf("x = ");
        if (scanf("%lf", &xv) != 1) { 
            fprintf(stderr, "x inválido\n"); 
            break; 
        }
        double yv = avalia_polinomio(n, coef, xv);
        printf("P(%.12g) = %.12g\n", xv, yv);
    }

    free(x); 
    free(y); 
    free(coef); 
    free(base);
    return 0;
}
