#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main() 
{
	void *i = sbrk(0);
	//sbrk(4);
	malloc(4);
	void *j = sbrk(0);
	
	char buffer[20];
	sprintf(buffer,"%p %p\n", i, j);
	write(1, buffer, strlen(buffer));
	
}
