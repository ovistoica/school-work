#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a = 0;
pthread_barrier_t barrier;

void* threadFunction2(void *var)
{
	int thread_id = *(int*)var;
	a = 3;
	pthread_barrier_wait(&barrier);
	pthread_barrier_wait(&barrier);
	a += 2;

}

void* threadFunction1(void *var)
{
	int thread_id = *(int*)var;
	pthread_barrier_wait(&barrier);
	a = 5;
	a += 7;
	pthread_barrier_wait(&barrier);
}



int main(int argc, char **argv)
{
	int i;

	pthread_t tid[2];
	int thread_id[2];
	for(i = 0;i < 2; i++)
		thread_id[i] = i;

	pthread_barrier_init(&barrier, NULL, 2);
	pthread_create(&(tid[0]), NULL, threadFunction1, &(thread_id[i]));
	pthread_create(&(tid[1]), NULL, threadFunction2, &(thread_id[i]));

	for(i = 0; i < 2; i++) {
		pthread_join(tid[i], NULL);
	}
	pthread_barrier_destroy(&barrier);

	printf("%d", a);

	return 0;
}
