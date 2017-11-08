#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_STRING 256

main()
{
	char buffer[MAX_STRING];
	int value;
	char c;
	int i,ret;

	i=0;
	ret = read(0, &buffer[0], sizeof(char));
	while(ret >0){
		i++;
		while ((i<MAX_STRING) && (buffer[i-1] != '\n') && (ret > 0)){
			ret=read(0,&buffer[i],sizeof(char));
			i++;
		}
		write(1,buffer,i*sizeof(char));
		i=0;
		ret = read(0, &buffer[0], sizeof(char));
	}
}
