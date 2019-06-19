#include <stdio.h>
#include "mpi.h"

int main() {
        int numtasks, rank, len;
        char hostname[MPI_MAX_PROCESSOR_NAME];
        int buf[100];
        int i = 0;

        MPI_Init(NULL, NULL);

        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        MPI_Get_processor_name(hostname, &len);
        if (rank == 0) {
                for (i = 0; i < 100; i++)
                        buf[i] = i;
        }
        MPI_Bcast((void *)&buf, 100, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank != 0)
        {
                printf("Process %d: Received from rank %d: \n", rank, 0);
                for (i = 0; i < 100; i++) {
                        printf("%d ", buf[i]);
                }
                printf("\n\n");
        }

        MPI_Finalize();
}