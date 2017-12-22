#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void Usage(char *name) {
char buf[80];
        sprintf(buf, "Usage %s: %s fichero\n", name, name);
        write(2, buf, strlen(buf));
        exit(1);
}

void error_y_exit(char *msg) {
        perror(msg);
        exit(1);
}


main(int argc, char *argv[]){
int ret, pos, contador, tam;
int fd;
char x='X';
char buf[80];

if (argc != 2) {
	Usage(argv[0]);
}

// solo necesitamos escribir, write only. Para controlar el tamaño del fichero hacemos un lseek al final (tamaño en bytes, si el fichero
// tuviera otro tipo de datos cuidado, dividid por sizeof(tipo))
// Como luego accederemos a posiciones directamente con lseek, no es necesario volver al principio
fd = open(argv[1], O_WRONLY);
if (fd < 0) {
	error_y_exit("Abriendo fichero");
}
tam=lseek(fd,0,SEEK_END);

contador = 0;

// Los datos que nos llegan estan en formato entero
ret = read (0, &pos, sizeof(pos));
while (ret > 0) {
	// Comprobamos que este ok la posicion, en linux las posiciones de un fichero van de 0 ..(size-1)
	if ((pos>=0) && (pos < tam)) {
		contador++;
		// En este caso son chars, no hace falta convertir de "posicion" a "byte"
		lseek(fd,pos,SEEK_SET);
		write(fd, &x, sizeof(x));
	} 
	ret = read(0, &pos,sizeof(pos));
}
// Las posiciones tachadas (la cantidad) la escribimos en texto por la salida std
sprintf(buf, "Letras tachadas: %d\n", contador);
write(1,buf,strlen(buf));


}
