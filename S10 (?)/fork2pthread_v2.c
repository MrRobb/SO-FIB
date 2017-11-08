#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void * print_hijo(void *arg)
{
	char buffer[80];

	sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
	char buffer[80];
	pthread_t thread;

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write (1, buffer, strlen(buffer));

	if(pthread_create(&thread, NULL, &print_hijo, NULL) != 0)
	{
		sprintf(buffer,"Se ha prodcido un error\n");
		write(1, buffer, strlen(buffer));
	}
	else
	{
		sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
		write(1, buffer, strlen(buffer));
	}
	
	sprintf(buffer,"Solo lo ejecuta el padre: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	pthread_join(thread, NULL);

	return 0;
}
