#include<string.h>
#include<stdio.h>
#include<time.h>
#include <pthread.h>
#include <stdlib.h>

int n1GB = 1024*1024*1024;
char v[1024*1024*1024];

/**
 * @author cristian.chilipirea
 * 
 */


int main(int argc, char * argv[]) {
	int c;
	int i;
	memset(v, '1', n1GB);

#pragma omp parallel
{
	#pragma omp for
	for(i=0;i<32;i++)
		memset(v+(i*32*1024*1024), '1', 32*1024*1024);
}
	return 0;
}