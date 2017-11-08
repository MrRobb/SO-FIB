#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void shift_right(int f, int start, int end)
{
	if(start > end)
		return;

	char buff[end-start];
	lseek(f, start, SEEK_SET);
	read(f, &buff, end-start);

	lseek(f, start+1, SEEK_SET);
	write(f, &buff, strlen(buff));
}

void insert(int f, char c, int pos, int size)
{
	shift_right(f, pos, size);

	lseek(f, pos, SEEK_SET);
	write(f, &c, sizeof(char));
}

void main(int argc, char *argv[])
{
	if(argc < 4)
		exit(0);

	int f = open(argv[1], O_RDWR);
	int size = lseek(f, 0, SEEK_END);

	insert(f, argv[2][0], atoi(argv[3])*sizeof(char), size);
}
