
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/sysinfo.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	int i, j, k;
	double m,n,p;
	m = 1215125.12325125;
	n = 12312.56444;
	p = 555555555;

	for(i = 1; i <= 1000; i++) {
		for (j = 1; j < 1000; j++){
			m = sqrt(n + p);
			p = sqrt(m + p);
			n = sqrt(n * p);
			p = sqrt(m + p);
			for (k = 1; k < 1000; k++)
			{
				m = sqrt(n + p);
				p = sqrt(m + p);
				n = sqrt(n * p);
				p = sqrt(m + p);
			}
		}
	}

	// printf("Hello world from thread %i\n", thread_id);
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
