#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char variable_global='A';

void Escribe_variable_global(char * quiensoy)
{
char buffer[80];
	sprintf(buffer,"%s:La variable_global vale %c\n",quiensoy,variable_global);
	write(1, buffer, strlen(buffer));
}

int main(int argc,char *argv[])
{
	int pid;
	int i;
	char buffer[80];

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pid=fork();
	switch (pid) { /* Esta linea la ejecutan tanto el padre como el hijo */
		case 0:	/* Escribe aqui el codigo del proceso hijo */
			sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
			write(1, buffer, strlen(buffer));

			/* Probamos si tenemos acceso desde una función */	
			for (i=0;i<100000;i++) {
				/* Cada 10000 iteraciones cambiamos el valor de la variable */
				if ((i%10000)==0) variable_global++;
				Escribe_variable_global("HIJO");
			}

			/* Termina su ejecución */
			exit(0);
		case -1: /* Se ha producido un error */
			strcpy(buffer,"Se ha producido une error\n");
			write(1, buffer, strlen(buffer));
			break;

		default: /* (pid != 0) && (pid != -1) */
			/* Escribe aqui el codigo del padre */

			sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
			write(1, buffer, strlen(buffer));

			/* Probamos si tenemos acceso desde una función */	
			/* Cambiamos el valor de la variable */
			variable_global='a';
			for (i=0;i<100000;i++) {
				/* Cada 10000 iteraciones cambiamos el valor de la variable */
				if ((i%10000)==0) variable_global++;
				Escribe_variable_global("PADRE");
			}
		}
	sprintf(buffer,"Solo lo ejecuta el padre: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	return 0;
}
