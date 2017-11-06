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
		sprintf(buffer, " 0--> escribe los numeros en ascii\n");
		write(2, buffer, strlen(buffer));
		sprintf(buffer, " 1--> escribe los numeros en formato int\n");
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
	sprintf(buffer,"............................\n");
	write(2,buffer,strlen(buffer));
	sprintf(buffer,"Si argv[1]==0 escribiremos los numero en ascii, sino en formato interno (int)\n");
	write(2,buffer,strlen(buffer));
	sprintf(buffer,"............................\n");
	write(2,buffer,strlen(buffer));

	srand(time(NULL));
	c='\n';
	for(i=0;i<number;i++){
		// Generamos numeros aleatorios
		value=rand();
		if (format == 1){
			// Escribimos el numero=4 bytes, y un '\n'
			write(1,&value,sizeof(value));
			write(1,&c,sizeof(c));
		} else{
			// En este caso escribimos el numero en ascii 
			// con un \n al final tambien
			sprintf(buffer,"%d\n",value);
			write(1,buffer, strlen(buffer));
		}
	}
}
