#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(int argc,char *argv[])
{
	int pid;
	char buffer[80];

	pid=fork();

	/* A partir de esta línea de código tenemos 2 procesos */

	sprintf(buffer,"Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	return 0;
}
