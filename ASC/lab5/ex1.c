#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i, j, N, k; 
    double *a;
    double *b;
    double *c;

    // scanf("%d", &N);
    N = 4;

    a = (double *)calloc(N * N, sizeof(double));
    b = (double *)calloc(N * N, sizeof(double));
    c = (double *)malloc(sizeof(double) * N * N);
    // memset(a, 1, N * N * sizeof(double));
    // memset(b, 2, N * N * sizeof(double));

    for(i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            *(&a[0] + i * N + j) = 1;
            *(&b[0] + i * N + j) = 2;
        }
    }
    

    for (i = 0; i < N; i++)
    {
        double *orig_pa = &a[0] + i * N;
        for (j = 0; j < N; j++)
        {
            double *pa = orig_pa;
            double *pb = &b[0] + j;
            register double suma = 0;
            for (k = 0; k < N; k++)
            {
                suma += *pa * *pb;
                pa++;
                pb += N;
            }
            *(&c[0] + i * N + j) = suma;
        }
    }

    for(i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%f ", *(&c[0] + i * N + j));
        }
        printf("\n");
    }

    free(a);
    free(b);
    free(c);
    return 0;
}