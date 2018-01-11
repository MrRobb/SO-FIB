#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

main (int argc, char *argv[]) {
int fd;
int fd_pipe[2];
int i;
char *vocales[5]={"a","e","i","o","u"};

int pid_h;

if (argc != 2) {
	Usage(argv[0]);
}
// Con una unica pipe es suficiente, todos los buscaLestras escribiran en la pipe y crearemos un unico tachaCaracteres. 
// El orden en el que llegan las posiciones no es importante asi que no importa que no lleguen en orden
// Los procesos buscaLetra pueden ser concurrentes ya que las escrituras de 1  byte, al ser meno que los buffers del kernel,
// no se mezclan
// Creamos la pipe en el padre para que todos la hereden
pipe(fd_pipe);
for (i=0;i<5;i++) {
	pid_h=fork(); 
	if (pid_h == 0) {
		// el dup2 redireccina la salida std. Hace que el canal 1 este vinculado con la pipe, dup2(canal_a_duplicar,donde_duplicarlo)
		dup2(fd_pipe[1],1);
		// Cerramos los canales para evitar bloqueos
		close(fd_pipe[1]); close(fd_pipe[0]);
		execlp("./buscaLetra", "buscaLetra", vocales[i], argv[1],(char *) 0);
		error_y_exit("Mutando a buscaLetra");
	}
}
// El canal de escritura ya no lo necesitamos, podemos cerrarlo antes de crear el proceso que mutara a tachaCaracteres
close(fd_pipe[1]);
pid_h=fork();
if (pid_h == 0) {
	// este proceso ha de leer de la pipe, redireccionamos la entrada std
	dup2(fd_pipe[0],0);
	//Cerramos los canales para evitar posibles bloqueos
	close(fd_pipe[1]); close(fd_pipe[0]);
	execlp("./tachaCaracteres", "tachaCaracteres", argv[1],(char *) 0);
	error_y_exit("Mutando a tachaCaracteres");
}
//cerramos el canal que faltaba
close(fd_pipe[0]);
// Esperamos a los hijos
while (waitpid(-1,NULL,NULL) > 0); 
}
