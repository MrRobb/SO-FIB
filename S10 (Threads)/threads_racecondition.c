#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 10
#define ITERS 10000

int data=0;


void *add_one(void *iters) 
{
	int max = (int)iters;
	int i;

	for (i=0; i<max; i++) {
		data++;
	}
	pthread_exit(NULL);  
}


int main() 
{
  int pid, j, status;
  pthread_t thread[NTHREADS];
  int res;

  srand(getpid());

  for (j=0; j<NTHREADS ; j++) {
   	if((res = pthread_create(&thread[j],NULL,add_one,(void*)ITERS))!=0){
      		perror("pthread create");
      		exit(1);
   	}
  }

  for (j=0; j<NTHREADS ; j++) {
  	if((res=pthread_join(thread[j],NULL))!=0){ 
		perror("Error joining:");
		exit(1);
  	}
  }
  printf("threads is %d, executing %d iterations and data is %d \n",NTHREADS, ITERS, data);

  return 0;
}  

