#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

/**
 * @author cristian.chilipirea
 * Run: mpirun -np 12 ./a.out
 */

int graph[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, 
                  { 3, 4 }, { 4, 11 }, { 11, 5 }, 
                  { 5, 6 }, { 6, 7 }, { 7, 8 },
                  { 8, 9 }, { 9, 10 }, { 10, 9 },
                  { 9, 8 }, { 8, 7 }, { 7, 6 },
                  { 6, 5 }, { 5, 11 }, { 11, 4 },
                  { 4, 3 }, { 3, 2 }, { 2, 1 },
                  { 1, 0 }, { 9, 5 }, { 5, 9 },
                  { 5, 3 }, { 3, 5 }, { 0, 2 },
                  { 2, 0 }, { 9, 7 }, { 7, 9 } };

void bfs(int **v, int *d, int *nexthop, int root) {
	
	int *queue = (int *) malloc( 12 * 12 * sizeof(int));
	int *queueDist = (int *) calloc( 12 * 12, sizeof(int));
	int *visited = (int *) calloc( 12, sizeof(int));
	
	int count = 0;
	int nr = 0;

	queue[0] = root;
	queueDist[0] = 0;
	visited[root] = 1;
	nr++;

	while (count < nr) {
		int el = queue[count];
		int depth = queueDist[count];
		count++;
		for (int i = 1; i <= v[el][0]; i++) {
			if (visited[v[el][i]] == 0) {
				visited[v[el][i]] = 1;
				queue[nr] = v[el][i];
				queueDist[nr] = depth + 1;
				d[v[el][i]] = queueDist[nr];
				nexthop[v[el][i]] = el;
				nr++;
			}
		}
	}

	for(int i = 0; i < 12; i++) {

		if(d[i] == 1) {

			nexthop[i] = i;
		}
			
		while(d[nexthop[i]] > 1 && nexthop[nexthop[i]] != i) {
			nexthop[i] = nexthop[nexthop[i]];
		}
	}
}





void getVecini(int* vecini, int topologie[][12], int rank) {

	for(int i = 0; i < 30; i++) {

		if(graph[i][0] == rank) {

			topologie[graph[i][0]][graph[i][1]] = 1;
			vecini[graph[i][1]] = 1;
		}
	}
}

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	int i, j;
	int iter;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	int topologie[12][12];
	int recv_topologie[12][12];
	
	for (i = 0; i < 12; i++){
		for (j = 0; j < 12; j++) {
			topologie[i][j] = 0;
			recv_topologie[i][j] = 0;
		}
	}


	printf("Hello from %i/%i\n", rank, nProcesses);

	int vecini[12] = {0};

// TOPOLOGIE
	getVecini(vecini, topologie, rank);

	// for (iter = 0; iter < 12; ++iter) {
	// 	for (int i = 0; i < 12; i++) {
	// 		if (vecini[i] == 1) {
	// 			MPI_Isend(topologie, 12 * 12, MPI_INT, i, 2, MPI_COMM_WORLD, &request);
	// 			MPI_Wait(&request, &status);
	// 		}
	// 	}

	// 	for (int i = 0; i < 12; i++)
	// 	{
	// 		if (vecini[i] == 1)
	// 		{
	// 			MPI_Irecv(recv_topologie, 12 * 12, MPI_INT, i, 2, MPI_COMM_WORLD, &request);
	// 			MPI_Wait(&request, &status);

	// 			// Update
	// 			for (int k = 0; k < 12; k++)
	// 			{
	// 				for (int j = 0; j < 12; j++)
	// 				{
	// 					if (recv_topologie[k][j] == 1)
	// 					{
	// 						topologie[k][j] = 1;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}

	// }

	// // GET BFS DATA.

	// int **v = calloc(12, sizeof(int*)); // VECTOR DE VECINI
	// int *d = calloc(12, sizeof(int)); // DISTANTA DE LA RANK LA NODUL i
	// int *nexthop = calloc(12, sizeof(int)); // NEXTHOP DE LA RANK LA NODUL i

	// for(int j = 0; j < 12; j++) {

	// 	v[j] = calloc(12, sizeof(int));
	// 	nexthop[j] = rank;
	// }

	// for (int i = 0; i < 12; i++)
	// {

	// 	int current = 0;

	// 	for (int j = 0; j < 12; j++)
	// 	{
	// 		if (topologie[i][j] == 1)
	// 		{

	// 			current = current + 1;
	// 			v[i][current] = j;
	// 		}
	// 	}

	// 	v[i][0] = current;
	// }

	// bfs(v,d,nexthop, rank);


	// int source = 0;
	// int dest = 10;
	// int hot_potato;


	// if(rank == source) {

	// 	hot_potato = 1;

	// 	MPI_Isend(&hot_potato, 1, MPI_INT, nexthop[dest], 5, MPI_COMM_WORLD, &request);
	// 	MPI_Wait(&request, &status);
	// 	printf("I am %d, I sent potato:%d to %d\n", rank, hot_potato, nexthop[dest]);
	// } else if (rank == dest) {
	// 	MPI_Irecv(&hot_potato, 1, MPI_INT, nexthop[source], 5, MPI_COMM_WORLD, &request);
	// 	MPI_Wait(&request, &status);
	// 	printf("I am %d, I received potato:%d from %d\n", rank, hot_potato, nexthop[source]);

	// } else {
	// 	MPI_Irecv(&hot_potato, 1, MPI_INT, nexthop[source], 5, MPI_COMM_WORLD, &request);
	// 	MPI_Wait(&request, &status);
	// 	MPI_Isend(&hot_potato, 1, MPI_INT, nexthop[dest], 5, MPI_COMM_WORLD, &request);
	// 	printf("I am %d, I received potato:%d from %d and i sent it to %d\n", rank, hot_potato, nexthop[source], nexthop[dest]);
	// }


	// if (rank == 0)
	// {
	// 	for (i = 0; i < 12; i++)
	// 	{
	// 		for (j = 0; j < 12; j++)
	// 		{
	// 			printf("%d ", topologie[i][j]);
	// 		}
	// 		printf("\n");
	// 	}

	// 	// for (int i = 0; i < 12; i++)
	// 	// {

	// 	// 	printf("Distata de %d la %d este %d.  Nexthop este %d\n", rank, i, d[i], nexthop[i]);
	// 	// }
	// }


	// CHOOSE THE LEADER
	int leader = rank;
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; j++) {
			if (vecini[j] == 1)
			{
				MPI_Isend(&leader, 1, MPI_INT, j, 15, MPI_COMM_WORLD, &request);
				MPI_Wait(&request, &status);
			}
		}

		for (int k = 0; k < 12; k++) {
			if (vecini[k] == 1) {
				int possible_leader;
				MPI_Irecv(&possible_leader, 1, MPI_INT, k, 15, MPI_COMM_WORLD, &request);
				MPI_Wait(&request, &status);
				if (leader < possible_leader) {
					leader = possible_leader;
				}
			}
		}
	}

	printf("I am %d and leader is %d \n", rank, leader);
	
	// NUMBER OF PROCESSES
	float value;

	if (rank == leader) {

		value = 1;
	} else {
		
		value = 0;
	}


	for(int i = 0; i < 1000; i++) {
		
		for(int j = 0; j < 12; j++) {
			
			if(vecini[j] == 1) {

				float recv_value;

				MPI_Sendrecv(&value, 1, MPI_FLOAT, j, 0, &recv_value, 1, MPI_FLOAT, j, 0, MPI_COMM_WORLD, &status);

				value = (value + recv_value) / 2.0f;
			}
		}
	}


	printf("Bye from %i/%i\n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}