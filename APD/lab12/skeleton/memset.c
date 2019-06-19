#include<string.h>
#include<stdio.h>
#include<time.h>
#include <pthread.h>
#include <stdlib.h>

int start;
int end;
int P;

int n1GB = 1024*1024*1024;
char v[1024*1024*1024];

int min(int a, int b) {
	return (a < b)? a : b;
}

void* threadFunction(void* var)
{
	int i, j;
	int thread_id = *(int*)var;

	start = (int)ceil(32 / P * thread_id);
	end = min((int)ceil(32 / P * (thread_id + 1)), 32);

	for(i=start;i<end;i++)
		memset(v+(i*32*1024*1024), '1', 32*1024*1024);

	printf("thread %i, start: %d, end: %d\n", thread_id, start, end);
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
	int c;
	int i;
	memset(v, '1', n1GB);

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