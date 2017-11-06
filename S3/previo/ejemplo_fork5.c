#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char variable_global='A';
int main(int argc,char *argv[])
{
	int pid;
	char variable_local='a';
	char buffer[80];

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pid=fork();
	switch (pid) {/* Esta linea la ejecutan tanto el padre como el hijo */

		case 0: /* Escribe aqui el codigo del proceso hijo */
			sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
			write(1,buffer,strlen(buffer));

			variable_local = 'b';
			variable_global = 'B';

			/* Comprobamos que tenemos acceso a las variables */
			sprintf(buffer,"HIJO:La variable_global vale %c y la local %c\n",
		variable_global,variable_local);
			write (1, buffer, strlen(buffer));

			/* Termina su ejecución */
			exit(0);

		case -1: /* Se ha producido un error */
			sprintf(buffer,"Se ha prodcido une error\n");
			write (1, buffer, strlen(buffer));
			break;

		default: /* Escribe aqui el codigo del padre */
			sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
			write (1, buffer, strlen(buffer));

			waitpid(-1, NULL, 0);
			/* Comprobamos que tenemos acceso a las variables */
			sprintf(buffer,"PADRE:La variable_global vale %c y la local %c\n",
		variable_global,variable_local);
			write (1, buffer, strlen(buffer));
	}
	sprintf(buffer,"Solo lo ejecuta el padre: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	return 0;
}
