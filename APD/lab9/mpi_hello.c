#include <stdio.h>
#include "mpi.h"

int main() {
    int numtasks = 4, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);
    printf("Hello world from rank: %d running on processor: %s\n", rank, hostname);



    MPI_Finalize();
}