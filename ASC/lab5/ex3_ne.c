
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *transpose(int N, double *A)
{
        double *A_copy = malloc(N * N * sizeof(double));
        for (int i = 0; i < N; ++i)
        {
                for (int j = 0; j < N; ++j)
                {
                        A_copy[j * N + i] = A[i * N + j];
                }
        }

        return A_copy;
}

double *mult(int N, double *A, double *B)
{
        double *C = calloc(N * N, sizeof(double));
        for (int i = 0; i < N; ++i)
        {
                for (int j = 0; j < N; ++j)
                {
                        for (int k = 0; k < N; ++k)
                        {
                                C[i * N + j] += A[i * N + k] * B[k * N + j];
                        }
                }
        }

        return C;
}

double *zerotr(int N, double *MAT)
{
        double *C_MAT = malloc(N * N * sizeof(double));
        memcpy(C_MAT, MAT, N * N * sizeof(double));

        for (int i = 1; i < N; ++i)
        { // SKIP FIRST LINE
                for (int j = 0; j < N; ++j)
                {
                        if (i > j)
                                C_MAT[i * N + j] = 0;
                }
        }

        return C_MAT;
}

int main()
{
        register int i = 0;
        register int j = 0;
        register int k = 0;
        register double sum = 0;
        register double aik = 0;
        register double *p_reg1; // Used for fast access at collumns from the matrix
        register double *p_reg2;
        int N;

        double *A;
        double *B;

        N = 8;

        A = (double *)calloc(N * N, sizeof(double));
        B = (double *)calloc(N * N, sizeof(double));


        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        if (i % 2 == 0)
                        {
                                *(&A[0] + i * N + j) = 5;
                                *(&B[0] + i * N + j) = 2;
                        }
                        else
                        {
                                *(&A[0] + i * N + j) = 1;
                                *(&B[0] + i * N + j) = 1;
                        }
                }
        }

	double* A_trans = transpose(N, A);
	double* B_trans = transpose(N, B);

        printf("A\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", A[i * N + j]);
                }
                printf("\n");
        }

        printf("A_trans\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", A_trans[i * N + j]);
                }
                printf("\n");
        }

        printf("B\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", B[i * N + j]);
                }
                printf("\n");
        }

        printf("B_trans\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", B_trans[i * N + j]);
                }
                printf("\n");
        }

	double* RES = mult(N, A_trans, B);
        printf("A_Trans * B\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", RES[i * N + j]);
                }
                printf("\n");
        }

        double *RES1 = mult(N, B_trans, A);
        printf("B_Trans * A\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", RES1[i * N + j]);
                }
                printf("\n");
        }

        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        RES[i * N + j] += RES1[i * N + j];
                }
        }

        double *zeroTR = zerotr(N, RES);
        printf("B_Trans * A\n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", zeroTR[i * N + j]);
                }
                printf("\n");
        }

        double *final = mult(N, zeroTR, zeroTR);


        printf("final: \n");
        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        printf("%f ", *(&final[0] + i * N + j));
                }
                printf("\n");
        }

        free(RES);
        free(RES1);
        free(A_trans);
        free(B_trans);
        free(A);
        free(B);
        free(final);
        free(zeroTR);

        return 0;
}
