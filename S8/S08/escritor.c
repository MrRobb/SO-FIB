#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
	int fifo = open("bridge", O_WRONLY);

	char c;
	while(read(0, &c, sizeof(char)) > 0)
	{
		write(fifo, &c, sizeof(char));
	}
}

