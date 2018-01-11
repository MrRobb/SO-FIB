#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void Usage() {
	char buff[128];
	sprintf(buff, "./set_holes ./file1 ./file2 \nEl file1 contiene números enteros de posiciones.\nEl file2 se llena con '0' en las posiciones marcadas\n");
	write(1, buff, strlen(buff));
	exit (1);
}

void error_y_exit(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		Usage();
	}
	
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_WRONLY);

	if (fd == -1 || fd2 == -1) error_y_exit("Error --> open");

	int i;
	while (read(fd, (void*) &i, sizeof(int)) > 0) {
		lseek(fd2, i, SEEK_SET);
		write(fd2, "0", sizeof(char));
	}

	return 0;
}
