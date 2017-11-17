#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Este codigo escribe todos los bytes que lee de la entrada std en la salida stda

main(){
char c[256];
char *buf="fin ejecución\n";
char buffer[1024];
int ret;
	// USO
	sprintf(buffer,"................................................\n");
	write(2,buffer,strlen(buffer));
	sprintf(buffer,"Este programa escribe por la salida std todo lo que lee de la entrada std. Si no has redirigido la salida, lo que escribas en el teclado saldra por la pantalla\n");
	write(2,buffer,strlen(buffer));
	sprintf(buffer,"Para acabar CtrlD\n");
	write(2,buffer,strlen(buffer));
	sprintf(buffer,"................................................\n");
	write(2,buffer,strlen(buffer));
	

	// Leemos del canal 0 (entrada std), 1 bye
	ret=read(0,&c,sizeof(c));
	// Cuando el read devuelve 0 significa que se ha acabado la 
	// entrada de datos --> acabamos el bucle de lectura
	while(ret>0){
		// Escribimos en el canal 1 (salida std) 1 byte
		write(1,&c,ret);
		ret=read(0,&c,sizeof(c));
	}
	write(1,buf,strlen(buf));
}
