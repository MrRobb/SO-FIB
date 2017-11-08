#include <unistd.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[])
{
	int num;
	char buff[80];

	while(read(0, &num, sizeof(int)) > 0)
	{
		sprintf(buff, "%d\n", num);
		write(1, buff, strlen(buff));
	}
}
