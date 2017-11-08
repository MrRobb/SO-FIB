#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define REGION_SIZE 256*1024*1024

/*
 * rdtsc is an assembler instruction that get the cycles executed by the processor since boot time.
 */
#define getCycles(low,high) __asm__ __volatile__("rdtsc": "=a"(low), "=d"(high))

static inline unsigned long long getTime(void)
{
	unsigned long low, high;
	getCycles(low, high);
	return ((unsigned long long)high << 32) + low;

}

int main(int argc, char **argv)
{
	int i, j;
	int *p;
	unsigned long long initTime;
	unsigned long long endTime;
	long long region_size;
	int nelts;
	int nits;
	int nprocs;
	int ret;
	char buff[256];					

	if (argc != 4) {
		sprintf( buff, "usage: mem2_4 region_size processes iterations \n");
		write(1, buff, strlen(buff));	
		exit(1);
	}

	region_size = atoll(argv[1]);
	nprocs = atoi(argv[2]);
	nits = atoi(argv[3]);

	// compute the number of integers that fits in the region
	nelts = region_size / sizeof(int);

	//loop to create the number of processes required
	i = 1;
	ret = 1;
	while ((i < nprocs) && (ret > 0)) {
		ret = fork();
		i++;
	}

	//code that executes each process
	p = malloc(region_size);
	if (p == NULL) {
		sprintf( buff, "Unable to allocate the memory region\n");
		write(1, buff, strlen(buff));	
		exit(1);
	}
	//loop to control how many times each process accesses all the elements of the vector
	i = 0;
	while (i < nits) {
		initTime = getTime();
		//loop to access all the elements in the vector
		for (j = 0; j < nelts; j++)
			p[j] = j;
		endTime = getTime();
		sprintf( buff, "process: %d, iteration %d, access loop time: %llu\n",
		      getpid(), i, (endTime - initTime));
		write(1, buff, strlen(buff));	
		i++;

	}
	sprintf( buff, "Entering endless loop\n");
	write(1, buff, strlen(buff));	
	while (1) ;
}
