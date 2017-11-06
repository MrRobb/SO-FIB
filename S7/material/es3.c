#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define LINEA ".............................................\n"
#define ID write(2,LINEA,strlen(LINEA));
#define FD write(2,LINEA,strlen(LINEA));
#define D(x) write(2,x,strlen(x))

#define MAX_STRING 256

main(){
	char buffer[MAX_STRING];
	int value;
	char c;
	int ret;
	// DESCRIPCION
	ID;
	D("Este programa asume que los datos de entrada son: entero(en formato int=4bytes)+'\\n'. Total 5 bytes por numero\n");
	D("Una vez leido el numero lo convierte a ascii y lo saca por la salida std\n");
	D("Para poder usarlo debes generar un fichero con el programa es2 , opcion 1, y redireccionar la entrada con ese fichero");
	FD;


	ret = read(0, &value, sizeof(value));
	while(ret >0){
		sprintf(buffer,"%d\n",value);
		write(1,buffer,strlen(buffer));
		ret = read(0,&c,sizeof(c));
		ret = read(0,&value, sizeof(value));
	}
}
