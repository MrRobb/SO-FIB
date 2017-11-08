#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
	if(argc < 2)
		exit(0);

	int f = open(argv[1], O_RDWR | O_APPEND);
	int size = lseek(f, 0, SEEK_END);
	lseek(f, 0, SEEK_SET);

	char c;
	int i;
	for(i = 0; i * sizeof(char) < size; ++i)
	{
		lseek(f, i * sizeof(char), SEEK_SET);
		read(f, &c, sizeof(char));
		write(f, &c, sizeof(char));
	}
}