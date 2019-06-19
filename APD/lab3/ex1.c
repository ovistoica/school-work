
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a = 0;

void* threadFunction(void *var)
{
	int i;
	int thread_id = *(int*)var;
	for (i = 0; i < 100; i++)
	{
		a = a + 2;
	}
}

int main(int argc, char **argv)
{
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < 2; i++)
		thread_id[i] = i;

	for(i = 0; i < 2; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < 2; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("a: %d", a);

	return 0;
}
