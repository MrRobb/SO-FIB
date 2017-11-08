#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_STRING 256

main(int argc, char *argv[])
{
	char buffer[MAX_STRING];
	int format;
	int number;
	int i,value;
	char c;

	if (argc != 3){
		sprintf(buffer, "usage: es1_2 {0|1]} number_of_integers\n");
		write(2, buffer, strlen(buffer));
		exit(1);
	}

	format=atoi(argv[1]);

	if ((format != 0) && (format != 1)){
		sprintf(buffer, "usage: es1_2 {0|1]}\n");
		write(2, buffer, strlen(buffer));
		exit(1);
	}

	number=atoi(argv[2]);

	srand(time(NULL));
	c='\n';
	for(i=0;i<number;i++){
		value=rand();
		if (format == 1){
			write(1,&value,sizeof(value));
			write(1,&c,sizeof(c));
		} else{
			sprintf(buffer,"%d\n",value);
			write(1,buffer, strlen(buffer));
		}
	}
}
