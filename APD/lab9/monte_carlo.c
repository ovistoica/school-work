#define INTERVAL 10000 
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  
int main() 
{ 
    int interval, i, rank, numtasks, len;
    double rand_x, rand_y, origin_dist, pi; 
    int circle_points = 0, square_points = 0;
    double pis[4];
    MPI_Status stat;
    time_t t;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initializing rand() 
    srand((unsigned)time(&t) + rank); 
  
    // Total Random numbers generated = possible x 
    // values * possible y values 
    for (i = 0; i < (INTERVAL * INTERVAL); i++) { 
  
        // Randomly generated x and y values 
        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
  
        // Distance between (x, y) from the origin 
        origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
        // Checking if (x, y) lies inside the define 
        // circle with R=1 
        if (origin_dist <= 1) 
            circle_points++; 
  
        // Total number of points generated 
        square_points++; 
  
        // estimated pi after this iteration 
        pi = (double)(4 * circle_points) / square_points; 
  
        // For visual understanding (Optional) 
        /*
        cout << rand_x << " " << rand_y << " " << circle_points 
             << " " << square_points << " - " << pi << endl << endl; 
             */
        //printf("X: %lf Y: %lf circl_points: %d, square_points: %d.    Pi: %lf  \n", rand);
  
        // Pausing estimation for first 10 values (Optional) 
        // if (rank == 0 ) {
        //     printf("Aici. pi=%lf\n", pi);
        // }
    } 
  
    // Final Estimated Value 
    printf(" Rank %d: Final Estimation of Pi = %lf \n",rank,pi);


    if (rank == 1)
    {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    if (rank == 2)
    {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    if (rank == 3)
    {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {

        pis[3] = pi;
        MPI_Recv(pis, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
        MPI_Recv(pis + 1, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
        MPI_Recv(pis + 2, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &stat);
        pi = pis[0] + pis[1] + pis[2] + pis[3];
        pi /= 4;

        printf("Final Estimation of Pi per all processes = %lf \n",pi);
    }

    MPI_Finalize();

    return 0; 
} 