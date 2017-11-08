#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_STRING 256
#define LINEA ".............................................\n"
#define ID write(2,LINEA,strlen(LINEA));
#define FD write(2,LINEA,strlen(LINEA));
#define D(x) write(2,x,strlen(x))


main()
{
	char buffer[MAX_STRING];
	int value;
	char c;
	int i,ret;
	// Descripcion
	ID;
	D("Este programa asume que la entrada std son numeros en ascii (de longitud variable por lo tanto), seguidos de un caracter '\\n' \n");
	D("Despues de leer el numero los escribe tal cual por la salida std en ascii tambien \n");
	D("Puedes usar la salida del programa es2 con la opcion 0\n");
	FD;

	i=0;
	ret = read(0, &buffer[0], sizeof(char));
	while(ret >0){
		// Cuando leemos un numero en ascii , la longitud es variable
		// este es un ejemplo de como leerlo. En este caso la
		// marca separadora es el caracter \n
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
