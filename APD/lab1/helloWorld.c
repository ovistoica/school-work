#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/sysinfo.h>


void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	for (int i = 0; i < 100; i++) {
		printf("Hello world: %d from thread %i\n", i, thread_id);
	}
}

int main(int argc, char **argv)
{
	int P = get_nprocs();
	int i;

	pthread_t tid[P];
	int thread_id[P];
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
