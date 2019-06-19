/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define BLOCKSIZE 40


/*
 * Add your optimized implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	register int i = 0;
	register int j = 0;
	register int k = 0;
	register double sum = 0;
	register double aik = 0; 
	register double *p_reg1; // Used for fast access at collumns from the matrix
	register double *p_reg2; 

	double *A_trans = malloc(N * N * sizeof(double));
	double *B_trans = malloc(N * N * sizeof(double));
	double *RES = calloc(N * N , sizeof(double));
	double *RES1 = calloc(N * N , sizeof(double));
	double *final = calloc(N * N , sizeof(double));

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

	/* A' x B */
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


	/* Adunarea rezultatelor si zerotr */
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

	/* Înmulțire matrici triunghiulare */
	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			sum = 0;
			for (k = i; k <= j; ++k) {
				sum += RES[i * N + k] * RES[k * N + j];
			}
			final[i * N + j] = sum;
		}
	}
	free(RES);
	free(RES1);
	free(A_trans);
	free(B_trans);

	return final;
}
