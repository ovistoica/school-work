#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

/**
 * @author cristian.chilipirea
 * Create files using
 * dd if=/dev/urandom of=1.txt bs=1024 count=102400
 * dd if=/dev/urandom of=2.txt bs=1024 count=102400
 */

int n = 1024 * 1024 * 1000;
char buf1[1048576000];
char buf2[1048576000];

int main(int argc, char *argv[])
{

	FILE *f;
#pragma omp parallel
	{
		if (omp_get_num_procs() == 1)
		{
			f = fopen("1.txt", "rb");
			FILE *g = fopen("2.txt", "rb");
			fread(buf1, sizeof(char), n, f);
			fread(buf2, sizeof(char), n, g);
			fclose(g);
			fclose(f);
		}
		else
		{

			if (omp_get_thread_num() == 0)
			{
				f = fopen("1.txt", "rb");
				fread(buf1, sizeof(char), n, f);
			}
			else
			{
				f = fopen("2.txt", "rb");
				fread(buf2, sizeof(char), n, f);
			}
			fclose(f);
		}
	}

	return 0;
}