#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void invert(int f, int start, int end)
{
	if(end < 0)
		return;

	char c;
	lseek(f, start, SEEK_SET);
	read(f, &c, sizeof(char));

	invert(f, start+sizeof(char), end-sizeof(char));

	lseek(f, end, SEEK_SET);
	write(f, &c, sizeof(char));
}

void main(int argc, char *argv[])
{
	if(argc < 2)
		exit(0);

	int f = open(argv[1], O_RDWR);
	int size = lseek(f, 0, SEEK_END);

	invert(f, 0, size);
}
