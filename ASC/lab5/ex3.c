
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// double *Multiply(int N, double *A, double *B)
// {
//         int bi = 0;
//         int bj = 0;
//         int bk = 0;
//         int i = 0;
//         int j = 0;
//         int k = 0;
//         int blockSize = 2;
//         int sum;

//         double *C = calloc(N * N , sizeof(double));

//         for (bi = 0; bi < N; bi += blockSize)
//                 for (bj = 0; bj < N; bj += blockSize)
//                         for (bk = 0; bk < N; bk += blockSize)
//                                 for (i = 0; i < blockSize; i++)
//                                         for (j = 0; j < blockSize; j++)
//                                                 for (k = 0; k < blockSize; k++)
//                                                         C[(bi + i) * N + (bj + j)] += A[(bi + i) * N + (bk + k)] * B[(bk + k) * N + (bj + j)];
//         return C;
// }

// double *mult(int N, double *A, double *B)
// {
//         double *C = calloc(N * N , sizeof(double));
//         int sum = 0;
//         for (int i = 0; i < N; ++i)
//         {
//                 for (int j = 0; j < N; ++j)
//                 {
//                         for (int k = 0; k < N; ++k)
//                         {
//                                 C[i * N + j] += A[i * N + k] * B[k * N + j];
//                         }
//                 }
//         }

//         return C;
// }

// double* transpose(int N, double *A) {
// 	double *A_copy = malloc(N * N * sizeof(double));
// 	for (int i = 0; i < N; ++i) {
// 		for(int j = 0; j < N; ++j) {
// 			A_copy[j * N + i] = A[i * N + j];
// 		}
// 	}

// 	return A_copy;
// }

// double *Transpose(int N, double *A)
// {
// 	int bi = 0;
// 	int bj = 0;
// 	int bk = 0;
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;
// 	int blockSize = 4;

// 	double *B = malloc(N * N * sizeof(double));

// 	for (bi = 0; bi < N; bi += blockSize)
// 		for (bj = 0; bj < N; bj += blockSize)
// 			for (i = 0; i < blockSize; i++)
// 				for (j = 0; j < blockSize; j++)
// 					B[(bj + j) * N + (bi + i)] += A[(bi + i) * N + (bj + j)];

// 	return B;
// }
        // printf("A: \n");
        // for (i = 0; i < N; ++i)
        // {
        //         for (j = 0; j < N; ++j)
        //         {
        //                 printf("%f ", *(&A[0] + i * N + j));
        //         }
        //         printf("\n");
        // }

        // printf("B: \n");
        // for (i = 0; i < N; ++i)
        // {
        //         for (j = 0; j < N; ++j)
        //         {
        //                 printf("%f ", *(&B[0] + i * N + j));
        //         }
        //         printf("\n");
        // }





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

        // scanf("%d", &N);

        A = (double *)calloc(N * N, sizeof(double));
        B = (double *)calloc(N * N, sizeof(double));
	double *A_trans = malloc(N * N * sizeof(double));
	double *B_trans = malloc(N * N * sizeof(double));
	double *RES = malloc(N * N * sizeof(double));
	double *RES1 = malloc(N * N * sizeof(double));
	double *final = calloc(N * N , sizeof(double));
        // memset(a, 1, N * N * sizeof(double));
        // memset(b, 2, N * N * sizeof(double));

        for (i = 0; i < N; ++i)
        {
                for (j = 0; j < N; ++j)
                {
                        if (i % 2 == 0) {
                                *(&A[0] + i * N + j) = 5;
                                *(&B[0] + i * N + j) = 2;
                        } else {
                                *(&A[0] + i * N + j) = 1;
                                *(&B[0] + i * N + j) = 1;
                        }
                }
        }


//	k = i <= j

	p_reg1 = A_trans;
	p_reg2 = B_trans;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
            *(p_reg1 + j) = A[j * N + i];
			*(p_reg2 + j) = B[j * N + i];

		}
		p_reg1 += N;
		p_reg2 += N;
	}

        printf("A\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", A[i * N + j]);
                }
                printf("\n");
        }

        printf("A_trans\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", A_trans[i * N + j]);
                }
                printf("\n");
        }

        printf("B\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", B[i * N + j]);
                }
                printf("\n");
        }

        printf("B_trans\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", B_trans[i * N + j]);
                }
                printf("\n");
        }


	/* A' x B */
	p_reg1 = RES;
	for (i = 0; i < N; ++i)
	{
		for (k = 0; k < N; ++k)
		{
			aik = A_trans[i * N + k]; // The value of A[i][k] is constant in the j_for
			p_reg2 = B + k * N;
			for (j = 0; j < N; ++j)
			{
				*(p_reg1 + j) += aik * *(p_reg2 + j);
			}
		}
		p_reg1 += N;
	}
        printf("A_Trans * B\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", RES[i * N + j]);
                }
                printf("\n");
        }

	/* B' x A */
	p_reg1 = RES1;
	for (i = 0; i < N; ++i)
	{
		for (k = 0; k < N; ++k)
		{
			aik = B_trans[i * N + k];
			p_reg2 = A + k * N;
			for (j = 0; j < N; ++j)
			{
				*(p_reg1 + j) += aik * *(p_reg2 + j);
			}
		}
		p_reg1 += N;
	}

        printf("B_Trans * A\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", RES1[i * N + j]);
                }
                printf("\n");
        }

	/* Adunarea rezultatelor si zerotr */
	p_reg1 = RES;
	p_reg2 = RES1;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (i > j) {
				*(p_reg1 + j) = 0;
			} else {
				*(p_reg1 + j) += *(p_reg2 + j);
			}
		}
		p_reg1 += N;
		p_reg2 += N;
	}

        printf("ZeroTR\n");
        for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                        printf("%f ", RES[i * N + j]);
                }
                printf("\n");
        }


	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			sum = 0;
			for (k = i; k <= j; ++k) {
				sum += RES[i * N + k] * RES[k * N + j];
			}
			final[i * N + j] = sum;
		}
	}


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

        return 0;
}
