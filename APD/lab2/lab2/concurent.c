#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int NReps;
int P;
int a = 0;
pthread_mutex_t mutex;

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N NReps printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void* threadFunction(void *var)
{
	int i;
	int thread_id = *(int*)var;
	for (i = 0; i < N; i++)
	{
		pthread_mutex_lock(&mutex);
		a = a + 2;
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv)
{
	int i;
	getArgs(argc, argv);

	pthread_t tid[P];
	pthread_mutex_init(&mutex, NULL);
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	pthread_mutex_destroy(&mutex);

	printf("a: %d", a);

	return 0;
}
