#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define MAX 10000
#define NTHREADS 10

int globalvector[MAX];

struct infojob {
	int ini;	/* posición inicial */
	int fin;	/* posición final */
	int res;	/* resultado parcial */
} ;

struct infojob info[NTHREADS];

void *partial_sum(void *args)
{
	struct infojob *info = (struct infojob*)args;
	int i;
	int fin = info->fin;
	int res = 0;

	for(i = info->ini; i < fin; ++i)
		res += globalvector[i];

	info->res = res;
}

void main()
{
	int i;
	int suma = 0;
	char buf[100];
	pthread_t thread[NTHREADS];
	int num_elems = MAX / NTHREADS;

	/* init global vector */
	for (i=0; i < MAX; i++) {
		globalvector[i] = i;
	}

	for (i=0; i < NTHREADS; i++)
	{
		info[i].ini = i * num_elems;
		info[i].fin = (i+1) * num_elems;

   		if(pthread_create(&thread[i],NULL, partial_sum, (void*)&info[i]) != 0)
		{
      			perror("pthread create");
      			exit(1);
   		}
  	}
	
	int res;
	for (i=0; i < NTHREADS; i++)
	{
  		if(pthread_join(thread[i], NULL) !=0)
		{ 
			perror("Error joining:");
			exit(1);
  		}

		suma += info[i].res;
  	}
	

	sprintf (buf, "El resultado de la suma es %d\n", suma);
	write (1, buf, strlen(buf));
}
