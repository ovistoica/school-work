#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

/**
 * @author cristian.chilipirea
 *
 */

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if(rank==0) { // This code is run by a single process
		int polynomialSize;
		int n;
		int i;
		int j;
		float x;

		FILE * polFunctionFile = fopen("a1.txt","rt");
		fscanf(polFunctionFile, "%i", &polynomialSize);
		float * a = malloc(sizeof(float)*polynomialSize);
		for(i=0;i<polynomialSize;i++) {
			fscanf(polFunctionFile, "%f", a+i);
		}
		fclose(polFunctionFile);

		MPI_Send(&local_elem, 1, MPI_FLOAT, rank + i, 2, MPI_COMM_WORLD);

		float sum0 = 0;
		float xPowI0 = 1;
		int x0 = 0
		float sum1 = 0;
		float xPowI1 = 1;
		int x1 = 1
		float sum2 = 0;
		float xPowI2 = 1;
		int x2 = 2
		float sum3 = 0;
		float xPowI3 = 1;
		int x3 = 3

		for (i = 0; i < polynomialSize; i++)
		{
			if (rank == 0) {
				sum0 += xPowI0 * a[rank];
				sum1 += xPowI1 * a[rank];
				sum2 += xPowI2 * a[rank];
				sum3 += xPowI3 * a[rank];
				xPowI0 *= x0; // more efficient than pow(x,i);
				xPowI1 *= x1; // more efficient than pow(x,i);
				xPowI2 *= x2; // more efficient than pow(x,i);
				xPowI3 *= x3; // more efficient than pow(x,i);
				MPI_Send(&sum0, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum1, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum2, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum3, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI0, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI1, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI2, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI3, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
			}
			if (rank != 0)
			{
				MPI_Recv(&sum0, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&sum1, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&sum2, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&sum3, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&xPowI0, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&xPowI1, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&xPowI2, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				MPI_Recv(&xPowI3, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
				sum0 += xPowI0 * a[rank];
				sum1 += xPowI1 * a[rank];
				sum2 += xPowI2 * a[rank];
				sum3 += xPowI3 * a[rank];
				xPowI0 *= x0; // more efficient than pow(x,i);
				xPowI1 *= x1; // more efficient than pow(x,i);
				xPowI2 *= x2; // more efficient than pow(x,i);
				xPowI3 *= x3; // more efficient than pow(x,i);
				MPI_Send(&sum0, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum1, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum2, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&sum3, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI0, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI1, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI2, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
				MPI_Send(&xPowI3, 1, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD);
			}
		}
	}

	MPI_Finalize();
	return 0;
}