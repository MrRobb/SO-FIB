#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


int pidPadre ;
int a ;

void *childfunction (void* dummy)
{
	char buf[100];
	sprintf(buf,"I am the child and my father is %d. Value of a=%d (BEFORE)\n", pidPadre, a);
	write (1, buf, strlen(buf));
	a = 1;
	sprintf(buf,"I am the child and my father is %d. Value of a=%d (AFTER)\n", pidPadre, a);
	write (1, buf, strlen(buf));
	pthread_exit(0);
}

main()
{
	int res;
	pthread_t tid;
	char buf[100];

	pidPadre = getpid();
	sprintf(buf,"Before fork (pid=%d)\n", pidPadre);
	write (1, buf, strlen(buf));

	a = 666;

	if((res = pthread_create(&tid,NULL,childfunction,NULL))!=0){
		perror("pthread create");
		exit(1);
	}
	sprintf(buf,"I am the parent (pid=%d)\n", getpid());
	write (1, buf, strlen(buf));
	if((res=pthread_join(tid,NULL))!=0){ 
		perror("Error joining:");
		exit(1);
	}
	sprintf(buf,"I am the parent and a=%d\n", a);
	write (1, buf, strlen(buf));
}
