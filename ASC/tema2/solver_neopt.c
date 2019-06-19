/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <string.h>

double* transpose(int N, double *A) {
	double *A_copy = malloc(N * N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			A_copy[j * N + i] = A[i * N + j];
		}
	}

	return A_copy;
}

double* mult(int N, double *A, double *B) {
	double *C = calloc(N * N , sizeof(double));
	for (int i = 0 ; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}

	return C;
}

double* zerotr(int N, double *MAT) {
	double *C_MAT = malloc(N * N * sizeof(double));
	memcpy(C_MAT, MAT, N * N);

	for (int i = 1; i < N; ++i) { // SKIP FIRST LINE
		for (int j = 0; j < N; ++j) {
			if ( i > j )
				C_MAT[i * N + j] = 0;
		}
	}

	return C_MAT;
}

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	double* A_trans = transpose(N, A);
	double* B_trans = transpose(N, B);

	double* first = mult(N, A_trans, B);
	double* second = mult(N, B_trans, A);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) 
			if (i > j)
				first[i * N + j] = 0;
			else 
				first[i * N + j] += second[i * N + j];
	}

	double *res =  mult(N, first, first);

	free(A_trans);
	free(B_trans);
	free(first);
	free(second);

	return res;
}
