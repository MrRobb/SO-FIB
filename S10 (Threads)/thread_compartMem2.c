#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int *p;

void *childfunction (void *dummy)
{
	char buf[100];
	sprintf(buf,"I am the child . Value of a=%d (BEFORE)\n",  *p);
	write (1, buf, strlen(buf));
	
	sleep (2); 

	a = 999;

	*p = 1111; /* PUNTO 1 */

	sprintf(buf,"I am the child . Value of a=%d (AFTER)\n",  *p);
	write (1, buf, strlen(buf));
	pthread_exit(0);
}

void usage(void)
{
	char buf[100];
	sprintf (buf,"Usage: thread_compartMem2 ESPERA\n");
	write (1, buf, strlen(buf));
	sprintf (buf," ESPERA: 0 - no espera al thread creado, 1 - espera\n");
	write (1, buf, strlen(buf));
	exit(1);
}


main(int argc, char **argv)
{

	int a;

	int res;
	pthread_t tid;
	char buf[100];
	int espera  = 0;

	if (argc > 2 || argc == 1) usage();

	espera = atoi(argv[1]);

	a = 666;
	p = &a;

	sprintf(buf,"Before pthread_create a=%d p=%p\n", a, p);
	write (1, buf, strlen(buf));

	if((res = pthread_create(&tid,NULL,childfunction,NULL))!=0){
		perror("pthread create");
		exit(1);
	}
	sprintf(buf,"I am the parent (pid=%d)\n", getpid());
	write (1, buf, strlen(buf));


	if ( espera ) {
		if ((res=pthread_join(tid, NULL))!=0) {
			perror("Error joining:");
			exit(1);
		}
	}
	sprintf(buf,"I am the parent and a=%d\n", a);
	write (1, buf, strlen(buf));
}
