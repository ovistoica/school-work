#include <stdio.h>
#include "mpi.h"

int main() {
        int numtasks, rank, len;
        char hostname[MPI_MAX_PROCESSOR_NAME];
        int buf[3];
        int buf2[3];
        int i = 0;
        MPI_Status stat;
        buf[0] = 0;
        buf[1] = 1;
        buf[2] = 2;

        MPI_Init(NULL, NULL);

        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        MPI_Get_processor_name(hostname, &len);
        if (rank == 0) {
            MPI_Recv(&buf2, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
            printf("Rank 0: Recived %d from rank %d \n", buf2[0], stat.MPI_SOURCE);
            MPI_Recv(&buf2 + 1, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
            printf("Rank 0: Recived %d from rank %d \n", buf2[1], stat.MPI_SOURCE);
            MPI_Recv(&buf2 + 2 , 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
            printf("Rank 0: Recived %d from rank %d \n", buf2[2], stat.MPI_SOURCE);
        }

        if (rank == 1){
            MPI_Send(buf, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }

        if (rank == 2){
            MPI_Send(buf + 1, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }

        if (rank == 3){
            MPI_Send(buf + 2, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }

        MPI_Finalize();
}