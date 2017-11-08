#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
	int fifo = open("bridge", O_RDONLY);

	char c;
	while(read(fifo, &c, sizeof(char)) > 0)
		write(1, &c, sizeof(char));
}

