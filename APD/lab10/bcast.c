#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main()
{
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int buf[2] = {1, 0};
    int i;
    int received = 0;
    MPI_Status stat;
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);
    int p = numtasks / 2;
    if (rank != 0)
    {
        MPI_Recv(buf + 1, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
    }
    for (i = 1; i <= p; i*=2)
    {
        if (rank + i < numtasks)
            MPI_Send(buf, 1, MPI_INT, rank + i, 2, MPI_COMM_WORLD);
    }
    printf("Rank: %d: received %d\n", rank, buf[1]);
    MPI_Finalize();
    return 0;
}