/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	double *C = malloc(N * N * sizeof(double));
	double *D = malloc(N * N * sizeof(double));

	cblas_dsyr2k(CblasRowMajor,CblasUpper, CblasTrans, N, N,
                  1, A,  N, B, N, 1, C, N);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, C, N, C, N, 1, D, N);
	return D;
}