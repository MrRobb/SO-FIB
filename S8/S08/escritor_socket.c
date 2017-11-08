#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
	int connectionFD = clientConnection("lector_server");
  	if (connectionFD < 0)
	{
      		perror ("Error establishing connection\n");
      		exit (1);
    	}

	char c;
	while(read(0, &c, sizeof(char)) > 0)
	{
		write(connectionFD, &c, sizeof(char));
	}

	closeConnection (connectionFD);
}

