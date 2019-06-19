#include<string.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>


int start;
int end;
int n = 1024*1024*100;
int P;

/**
 * @author cristian.chilipirea
 * 
 */


int main(int argc, char * argv[]) {
	int i, j;
	int a;
#pragma omp parallel
	{
		int c;
#pragma omp for
		for (i = 0; i < n; i++)
			c = sqrt(a);
	}
	return 0;
}