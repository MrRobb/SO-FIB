#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void Usage(char *name) {
char buf[80];
	sprintf(buf, "Usage %s: %s letra fichero\n", name, name);
	write(2, buf, strlen(buf));
	exit(1);
}

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

main(int argc, char *argv[]) {

int fd;
int ret,i;
char c;
char letra;

if (argc != 3) {
	Usage(argv[0]);
}

// Abrimos el fichero solo para lectura. El control de errores siempre despues
// llamada a sistema. 
// si lo haceis en una linea recordad: if ((fd=open(...))<0){
fd = open (argv[2], O_RDONLY);
if (fd < 0) {
	error_y_exit("Abriendo fichero");	
}

// argv[1] es un string, si queremos una letra concreta argv[1][posicion]

letra = argv[1][0];

// Es un acceso secuencial a un fichero, posicion a posicion, no es necesario ningun lseek
ret = read(fd, &c, sizeof(c));
i=0;
while (ret >0) {
	if (c==letra){
		// Con la variable i controlamos en que posicion del fichero estamos
		// Para escribir un int simplemente pasamos la direccion (&) y el tamaño (sizeof)
		write(1, &i, sizeof(i));
	}
	i++;
	ret = read(fd,&c, sizeof(c));
}

}
