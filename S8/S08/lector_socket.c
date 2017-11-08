#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
	int socketFD = createSocket("lector_server");
  	if (socketFD < 0)
	{
		perror ("Error creating socket\n");
		exit (1);
    	}

	int connectionFD = serverConnection (socketFD);
  	if (connectionFD < 0)
    	{
      		perror ("Error establishing connection \n");
      		exit (1);
    	}

	char c;
	while(read(connectionFD, &c, sizeof(char)) > 0)
		write(1, &c, sizeof(char));

	closeConnection (connectionFD);
	deleteSocket (socketFD, "lector_server");
}

