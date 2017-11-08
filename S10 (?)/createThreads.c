#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "utils.h"

#define NTHREADS 50000

void *do_nothing(void *nothing) 
{
   int i;
   i= 0;
   pthread_exit(NULL);  
}

int main() 
{
	int pid, j, status;
	pthread_t thread[NTHREADS];
	int res;
	double start, stop;
	char buff[100];

	start=timersec();
	for (j=0; j<NTHREADS ; j++) {
		if((res = pthread_create(&thread[j],NULL,do_nothing,NULL))!=0){
			perror("pthread create");
			exit(1);
		}
		if((res=pthread_join(thread[j],NULL))!=0){ 
			perror("Error joining:");
			exit(1);
		}
	}
	stop=timersec();
	sprintf(buff, "%d threads created in %g sec.\n",NTHREADS,stop-start);
	write (1, buff, strlen(buff));

	return 0;
}  

