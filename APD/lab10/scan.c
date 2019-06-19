#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main()
{
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int buf[2] = {1, 0};
    int i,j;
    int received = 0;
    MPI_Status stat;
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &len);
    float local_elem = rank;
    float recv_elem;
    int p = numtasks/2;
    float global_elem;
    
    for (i = 1; i <= p; i*=2)
    {
        if (rank >= i)
        {
            printf("Rank %d receives\n", rank);
            MPI_Recv(&recv_elem, 1, MPI_FLOAT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
            printf("Rank %d received from %d \n",rank, stat.MPI_SOURCE);
            local_elem += recv_elem;
        }
        if (rank + i < numtasks) {

            MPI_Send(&local_elem, 1, MPI_FLOAT, rank + i, 2, MPI_COMM_WORLD);
            printf("Rank %d sends to %d\n", rank, rank + i);
        }
    }
    printf("Rank %d Partial sum = %f\n", rank, local_elem);

    MPI_Finalize();

    return 0;
}