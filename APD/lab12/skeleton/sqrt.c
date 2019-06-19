#include<string.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include <pthread.h>
#include<stdlib.h>


int start;
int end;
int n = 1024*1024*100;
int P;
int a;

int min(int a, int b) {
	return (a < b)? a : b;
}


void* threadFunction(void* var)
{
	int i, j;
	int thread_id = *(int*)var;

	start = (int)ceil(n / P * thread_id);
	end = min((int)ceil(n / P * (thread_id + 1)), n);

	printf("thread %i, start: %d, end: %d\n", thread_id, start, end);
	{
		int c;
		for (i = start; i < end; i++)
			c = sqrt(a);
	}
}

void getArgs(int argc, char **argv)
{
	if(argc < 2) {
		printf("Not enough paramters.\n");
		exit(1);
	}
	P = atoi(argv[1]);
}

/**
 * @author cristian.chilipirea
 * 
 */


int main(int argc, char * argv[]) {
	int i, j;
	getArgs(argc, argv);

	pthread_t tid[P];
	int thread_id[P];

	// {
	// 	int c;
	// 	for(i=0;i<n;i++)
	// 		c = sqrt(a);
	// }
	for(i = 0;i < P; i++)
		thread_id[i] = i;


	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}


	return 0;
}