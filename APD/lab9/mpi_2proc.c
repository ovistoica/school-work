#include <stdio.h>
#include "mpi.h"

int main() {
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    char buf[10] = "salut";
    char buf2[12] = {'0'};
    int i = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);
    MPI_Send((void *)&buf, 5, MPI_CHAR, 1, 2, MPI_COMM_WORLD);
    if (rank != 0)
    {
        MPI_Recv((void *)&buf2, 5, MPI_CHAR, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d: Received from rank %d: \n", rank, 0);
        for (i = 0; i < 5; i++) {
            printf("%c", buf2[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
}